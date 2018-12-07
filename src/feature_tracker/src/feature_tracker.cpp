#include "feature_tracker.h"

FeatureTracker::FeatureTracker(void):stereoSub(1), state(FIRST_IMAGE), firstImageTime(0), currImageTime(0), pubCnt(1), pubThisFrame(false), tracker(new UpdateTrackers)
{
    leftSub.subscribe(n, "/mynteye/left/image_mono", 1);
    rightSub.subscribe(n, "/mynteye/right/image_mono", 1);
    depthSub.subscribe(n, "mynteye/depth/image_raw", 1);
    stereoSub.connectInput(leftSub, rightSub, depthSub);
    stereoSub.registerCallback(&FeatureTracker::Stereo_Callback, this); 

    FREQ = Config::get<int>("Frequence");
    SHOW_TRACKER = Config::get<int>("SHOW_TRACKER");
}

FeatureTracker::~FeatureTracker(void)
{

}

void FeatureTracker::Stereo_Callback(const sensor_msgs::ImageConstPtr& leftImg, const sensor_msgs::ImageConstPtr& rightImg, const sensor_msgs::ImageConstPtr& depthImg)
{
    timeBegin = ros::Time::now().toNSec();
    ROS_INFO_STREAM("code cost time: " << (timeBegin - timeEnd) << " ns");
    timeEnd = timeBegin;
    
    if ( state == FIRST_IMAGE )
    {
        state = NOT_FIRST_IMAGE;        // 状态转换
        currImageTime = firstImageTime = leftImg->header.stamp.toSec();
        return;
    }
    if ( (leftImg->header.stamp.toSec()-currImageTime) > 1.0 )
    {
        ROS_WARN("image fault! reset the feature tracker");
        state = FIRST_IMAGE;
        pubCnt = 1;
        return;
    }

    currImageTime = leftImg->header.stamp.toSec();  //获取当前帧时间戳

    // 控制频率
    if ( round(1.0*pubCnt / (currImageTime - firstImageTime)) <= FREQ )
    {   
        pubThisFrame = true;                        //发布标志位置位

        if ( abs(1.0*pubCnt/(currImageTime - firstImageTime) - FREQ) < 0.02 * FREQ)   // 频率控制误差
        {
            firstImageTime = currImageTime;         // 重置图像帧数时间戳
            pubCnt = 0;                             // 重置发布计数器
        }
    }
    else
    {
        pubThisFrame = false;
    }

    cv_bridge::CvImageConstPtr leftImagePtr, rightImagePtr, depthImagePtr;

    leftImagePtr = cv_bridge::toCvCopy(leftImg, enc::MONO8);
    rightImagePtr = cv_bridge::toCvCopy(rightImg, enc::MONO8);
    depthImagePtr = cv_bridge::toCvCopy(depthImg, enc::MONO16);
    

    tracker->Find_Feature(leftImagePtr->image, leftImagePtr->header.stamp.toSec(), pubThisFrame);

    for( unsigned int i = 0;; i++ )
    {
        bool completed = false;
        completed |= tracker->Update_Tracker_ID(i);
        if (!completed)
            break;
    }

    if( pubThisFrame )
    {
        if( SHOW_TRACKER )
        {
            Mat imgShow = leftImagePtr->image.clone();
            for( auto kps: tracker->keyPointsCurr )
            {
                circle(imgShow, kps, 2, Scalar(255), -1);
            }
            imshow("Tracker", imgShow);
            waitKey(1);
        }
    }
}
