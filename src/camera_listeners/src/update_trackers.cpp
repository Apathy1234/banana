#include "update_trackers.h"

UpdateTrackers::UpdateTrackers(void):n_id(0)
{
    BORDERSIZE = Config::get<int>("BorderSize");
    MIN_DIS = Config::get<int>("FeatureMinDis");
    MAX_CNT = Config::get<int>("MaxFeatureCnt");
    F_THRESHOLD = Config::get<double>("F_THRESHOLD");
}

UpdateTrackers::~UpdateTrackers(void)
{

}

bool UpdateTrackers::Point_In_Border(const Point2f& pt)
{
    int x = cvRound(pt.x);
    int y = cvRound(pt.y);
    return (BORDERSIZE <= x && x <= (WIDTH - BORDERSIZE) && BORDERSIZE <= y && y <= (HEIGHT - BORDERSIZE) );
}

void UpdateTrackers::Reduce_Vector(vector<Point2f>& v, vector<uchar> status)
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

void UpdateTrackers::Reduce_Vector(vector<int>& v, vector<uchar> status)
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
    if ( keyPointsRef.empty() )
        return;
    vector<uchar> status;
    findFundamentalMat(keyPointsRef, keyPointsCurr, FM_RANSAC, F_THRESHOLD, 0.99, status);

    Reduce_Vector(keyPointsRef, status);
    Reduce_Vector(keyPointsCurr, status);
    Reduce_Vector(trackerId, status);
    Reduce_Vector(trackerCnt, status);

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
        if ( mask.at<uchar>(it.second.first) == 255 )
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
            trackerId[i] = n_id++;
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

void UpdateTrackers::Find_Feature( const Mat& _img, double _currTime, const bool pubThisFrame)
{
    Mat img;

    img = _img;

    imgCurr = img.clone();
    keyPointsCurr.clear();


    if ( keyPointsRef.size() > 0 )
    {
        vector<uchar> status;
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
        // imshow("mask", mask);
        // waitKey(1);
        int featureMaxCnt = MAX_CNT - static_cast<int>(keyPointsCurr.size());
        if ( featureMaxCnt > 0 )            // 特征点数量不足
        {
            goodFeaturesToTrack(imgCurr, keyPointsAdd, featureMaxCnt, 0.1, MIN_DIS, mask);
        }
        else
        {
            keyPointsAdd.clear();
        }

        Add_Points();
    }

    imgRef = imgCurr.clone();
    keyPointsRef = keyPointsCurr;
}