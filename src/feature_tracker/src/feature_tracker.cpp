#include "feature_tracker.h"

FeatureTracker::FeatureTracker(void):stereoSub(1), state(FIRST_IMAGE), firstImageTime(0), currImageTime(0), pubCnt(1), pubThisFrame(false), tracker(new UpdateTrackers)
{
    pubMatchImage = n.advertise<sensor_msgs::Image>("/featur_tracker/left/image", 1);
    leftSub.subscribe(n, "/mynteye/left/image_mono", 1);
    rightSub.subscribe(n, "/mynteye/right/image_mono", 1);
    depthSub.subscribe(n, "mynteye/depth/image_raw", 1);
    stereoSub.connectInput(leftSub, rightSub, depthSub);
    stereoSub.registerCallback(&FeatureTracker::Stereo_Callback, this); 

    FREQ = Config::get<int>("Frequence");
    SHOW_TRACKER = Config::get<int>("SHOW_TRACKER");
    TRACKERSIZE = Config::get<int>("TrackerSize");
}

FeatureTracker::~FeatureTracker(void)
{

}

void FeatureTracker::Stereo_Callback(const sensor_msgs::ImageConstPtr& leftImg, const sensor_msgs::ImageConstPtr& rightImg, const sensor_msgs::ImageConstPtr& depthImg)
{
    timeBegin = ros::Time::now().toNSec();
    
    if ( state == FIRST_IMAGE )
    {
        state = NOT_FIRST_IMAGE;        // 状态转换
        currImageTime = firstImageTime = leftImg->header.stamp.toSec();
        return;
    }
    if ( (leftImg->header.stamp.toSec()-currImageTime) > 1.0 )
    {
        ROS_WARN("image fault! reset the feature tracker!");
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
        pubCnt++;
        ROS_INFO_STREAM("the number of trackers: " << tracker->keyPointsCurr.size());
        if( SHOW_TRACKER )
        {
            leftImagePtr = cv_bridge::cvtColor(leftImagePtr, enc::BGR8);
            Mat imgShow = leftImagePtr->image;
            for( unsigned int i = 0; i < tracker->keyPointsCurr.size(); i++)
            {
                double cnt = min(1.0, 1.0*tracker->trackerCnt[i]/TRACKERSIZE);
                circle(imgShow, tracker->keyPointsCurr[i], 3, Scalar(255*(1-cnt), 0, 255*cnt), -1);
            }
            // imshow("Tracker", imgShow);
            // waitKey(1);
            pubMatchImage.publish(leftImagePtr->toImageMsg());
        }
    }
    timeEnd = ros::Time::now().toNSec();
    ROS_INFO_STREAM("code cost time: " << (timeEnd - timeBegin) << " ns");
}
