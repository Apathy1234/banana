#include "data_convert.h"

DataConvert::DataConvert(void):stereoSub(1)
{
    leftSub.subscribe(n, "/mynteye/left/image_mono", 1);
    rightSub.subscribe(n, "/mynteye/right/image_mono", 1);
    depthSub.subscribe(n, "mynteye/depth/image_raw", 1);
    stereoSub.connectInput(leftSub, rightSub, depthSub);
    stereoSub.registerCallback(&DataConvert::Stereo_Callback, this); 

}

DataConvert::~DataConvert(void)
{

}

void DataConvert::Stereo_Callback(const sensor_msgs::ImageConstPtr& leftImg, const sensor_msgs::ImageConstPtr& rightImg, const sensor_msgs::ImageConstPtr& depthImg)
{
    timeBegin = ros::Time::now().toNSec();
    ROS_INFO_STREAM("code cost time: " << (timeBegin - timeEnd) << " ns");
    timeEnd = timeBegin;
    
    cv_bridge::CvImageConstPtr cvLeftPtr, cvRightPtr, cvDepthPtr;

    cvLeftPtr = cv_bridge::toCvShare(leftImg, enc::MONO8);
    cvRightPtr = cv_bridge::toCvShare(rightImg, enc::MONO8);
    cvDepthPtr = cv_bridge::toCvShare(depthImg, enc::MONO16);
    
    leftImage = cvLeftPtr->image.clone();
    rightImage = cvRightPtr->image.clone();
    depthImage = cvDepthPtr->image.clone();
    
    imageUpdate = true;
    
    if ( SHOW_IMAGE )
    {
        imshow("left", cvLeftPtr->image);
        imshow("right", cvRightPtr->image);
        imshow("depth", cvDepthPtr->image);
        waitKey(1);
    }
}
