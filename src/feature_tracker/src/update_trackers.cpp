#include "feature_tracker/update_trackers.h"

UpdateTrackers::UpdateTrackers(void):n_id(0), camera(new Camera)
{
    BORDERSIZE = Config::get<int>("BorderSize");
    MIN_DIS = Config::get<int>("FeatureMinDis");
    MAX_CNT = Config::get<int>("MaxFeatureCnt");
    F_THRESHOLD = Config::get<double>("F_THRESHOLD");
    EQUALIZE = Config::get<int>("EQUALIZE");
}

UpdateTrackers::~UpdateTrackers(void)
{

}

bool UpdateTrackers::Point_In_Border(const Point2f& pt)
{
    int x = cvRound(pt.x);
    int y = cvRound(pt.y);
    return (BORDERSIZE < x && x <= (WIDTH - BORDERSIZE) && BORDERSIZE < y && y <= (HEIGHT - BORDERSIZE) );
}

void UpdateTrackers::Reduce_Vector(vector<Point2f>& v, vector<unsigned char> status)
{
    int num = 0;
    for ( int i =  0; i <  int(v.size()); i++)
    {
        if ( status[i] )
        {
            v[num++] = v[i];
        }
    }
    v.resize(num);
}

void UpdateTrackers::Reduce_Vector(vector<int>& v, vector<unsigned char> status)
{
    int num = 0;
    for ( int i =  0; i <  int(v.size()); i++)
    {
        if ( status[i] )
        {
            v[num++] = v[i];
        }
    }
    v.resize(num);
}

void UpdateTrackers::Delete_Point_With_F(void)
{
    if ( keyPointsCurr.size() >= 8 )
    {
        vector<unsigned char> status;
        findFundamentalMat(keyPointsRef, keyPointsCurr, FM_RANSAC, F_THRESHOLD, 0.99, status);

        Reduce_Vector(keyPointsRef, status);
        Reduce_Vector(keyPointsCurr, status);
        Reduce_Vector(trackerId, status);
        Reduce_Vector(trackerCnt, status);
    }
}

void UpdateTrackers::Set_Mask(void)
{
    mask = Mat(HEIGHT, WIDTH, CV_8UC1, Scalar(255));

    vector<pair<int, pair<Point2f, int>>> cnt_pts_id;

    for (unsigned int i = 0; i < keyPointsCurr.size(); i++)
    {
        cnt_pts_id.push_back(make_pair(trackerCnt[i], make_pair(keyPointsCurr[i], trackerId[i])));
    }
    sort(cnt_pts_id.begin(), cnt_pts_id.end(), [] (const pair<int, pair<Point2f, int>>& a, const pair<int, pair<Point2f, int>>& b)
    {
        return a.first > b.first;
    });

    keyPointsCurr.clear();
    trackerCnt.clear();
    trackerId.clear();

    for ( auto& it : cnt_pts_id)
    {
        if ( mask.at<unsigned char>(it.second.first) == 255 )
        {
            trackerCnt.push_back(it.first);                         //重新放入特征点
            trackerId.push_back(it.second.second);
            keyPointsCurr.push_back(it.second.first);
            circle(mask, it.second.first, MIN_DIS, 0, -1);
        }
    }
}

bool UpdateTrackers::Update_Tracker_ID(int i)
{
    if ( i < trackerId.size() )
    {
        if ( trackerId[i] == -1 )
        {
             trackerId[i] = n_id++;
            //  ROS_INFO_STREAM("the id: " << n_id);
        }
        return true;
    }
    else
        return false;
}

void UpdateTrackers::Add_Points(void)
{
    for ( auto kps : keyPointsAdd )
    {
        keyPointsCurr.push_back(kps);
        trackerId.push_back(-1);
        trackerCnt.push_back(1);
    }
}

void UpdateTrackers::Calculation_Points_From_Depth(void)
{
    kpsCameraCurr.clear();
    kpsCameraId.clear();
    kpsCameraCnt.clear();
    kpsCamera_uv.clear();
    for ( ushort i = 0; i < keyPointsCurr.size(); i++ )
    {
        Eigen::Vector3f a(keyPointsCurr[i].x, keyPointsCurr[i].y, 1);
        Eigen::Vector3f b;
        if ( !camera->Pixel_2_Camera(a, b) )
        {
            continue;
        }
        kpsCameraCurr.push_back(Point3f(b.x(), b.y(), b.z()));
        kpsCameraId.push_back(trackerId[i]);
        kpsCameraCnt.push_back(trackerCnt[i]);
        kpsCamera_uv.push_back(Point2f(a.x(), a.y()));
    }
    // ROS_INFO_STREAM("the size of publish point: " << kpsCameraCurr.size());
    // ROS_INFO_STREAM("1: " << kpsCameraId.size());
    // ROS_INFO_STREAM("2: " << kpsCameraCnt.size());
    // ROS_INFO_STREAM("3: " << kpsCamera_uv.size());
}

void UpdateTrackers::Find_Feature( const Mat& _img, const Mat& depth_img, double _currTime, const bool pubThisFrame)
{
    Mat img;
    timeCurr = _currTime;
    if( EQUALIZE )
    {
        Ptr<CLAHE> clahe = createCLAHE(3.0, Size(8, 8));
        clahe->apply(_img, img);
    }
    else
    {
        img = _img;
    }


    // imgCurr = img.clone();

    imgCurr = img;
    keyPointsCurr.clear();


    if ( keyPointsRef.size() > 0 )
    {
        vector<unsigned char> status;
        vector<float> err;
        
        calcOpticalFlowPyrLK(imgRef, imgCurr, keyPointsRef, keyPointsCurr, status, err);
        for( int i = 0; i < int(keyPointsCurr.size()); i++)
        {
            if ( status[i] && !Point_In_Border(keyPointsCurr[i]) )
            {
                status[i] = 0;
            }
        }
        Reduce_Vector(keyPointsRef, status);
        Reduce_Vector(keyPointsCurr, status);
        Reduce_Vector(trackerId, status);
        Reduce_Vector(trackerCnt, status);
    }

    for ( auto& num : trackerCnt)           // trackerCnt计数加1
        num++;

    if ( pubThisFrame )
    {
        Delete_Point_With_F();
        Set_Mask();
        int featureMaxCnt = MAX_CNT - static_cast<int>(keyPointsCurr.size());
        if ( featureMaxCnt > 0 )            // 特征点数量不足
        {
            goodFeaturesToTrack(imgCurr, keyPointsAdd, featureMaxCnt, 0.01, MIN_DIS, mask);
        }
        else
        {
            keyPointsAdd.clear();
        }

        Add_Points();
    }

    camera->depthImage = depth_img.clone();
    imgRef = imgCurr;
    for( unsigned int i = 0;; i++ )
    {
        bool completed = false;
        completed |= Update_Tracker_ID(i);
        if (!completed)
            break;
    }
    keyPointsRef = keyPointsCurr;
    timeRef = timeCurr;
    // for(int i = 0; i< trackerId.size(); i++)
    // {
    //     ROS_INFO_STREAM(trackerId[i] << ": " << keyPointsCurr[i].x);
    // }
    // ROS_INFO_STREAM("====================END===============");
    Calculation_Points_From_Depth();
}