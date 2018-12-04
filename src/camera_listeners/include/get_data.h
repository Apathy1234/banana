#ifndef _GET_DATA_H_
#define _GET_DATA_H_


#include "my_include.h"

const bool SHOW_IMAGE = false;

namespace enc = sensor_msgs::image_encodings;

class ImageConvert
{
private:
    ros::NodeHandle n;
    image_transport::ImageTransport it;
    image_transport::Subscriber leftGreySub;
    image_transport::Subscriber rightGreySub;
    image_transport::Subscriber depthGreySub;

    bool leftImageReady = false;
    bool rightImageReady = false;
    bool depthImageReady = false;
    // uint64_t timeBegin, timeEnd;

public:
    Mat leftImage;
    Mat rightImage;
    Mat depthImage;
    bool Image_Fresh( void )
    {
        if ( leftImageReady == true && rightImageReady == true && depthImageReady == true)
        {
            leftImageReady = false;
            rightImageReady = false;
            depthImageReady = false;
            return true;
        }
        return false;
    }
    
    ImageConvert(void):it(n)
    {
        leftGreySub = it.subscribe("/mynteye/left/image_mono", 1, &ImageConvert::LeftImageCallBack, this);
        rightGreySub = it.subscribe("/mynteye/right/image_mono", 1, &ImageConvert::RightImageCallBack, this);
        depthGreySub = it.subscribe("/mynteye/depth/image_raw", 1, &ImageConvert::DepthGreyCallBack, this);
    }

    void LeftImageCallBack(const sensor_msgs::ImageConstPtr& img)
    {
        // timeBegin = ros::Time::now().toNSec();
        cv_bridge::CvImageConstPtr cvPtr;
        try 
        {
            cvPtr = cv_bridge::toCvShare(img, enc::MONO8);
        }
        catch ( cv_bridge::Exception& e )
        {
            ROS_ERROR_STREAM("cv_bridge exception: " << e.what());
            return;
        }

        leftImageReady = true;
        leftImage = cvPtr->image.clone();

        if ( SHOW_IMAGE )
        {
            imshow("left", cvPtr->image);
            waitKey(1);
        }
        // timeEnd = ros::Time::now().toNSec();
        // ROS_INFO_STREAM("code cost time: "<<(timeEnd-timeBegin)<<" ns");
    }

    void RightImageCallBack(const sensor_msgs::ImageConstPtr& img)
    {
        cv_bridge::CvImageConstPtr cvPtr;
        try 
        {
            cvPtr = cv_bridge::toCvShare(img, enc::MONO8);
        }
        catch ( cv_bridge::Exception& e )
        {
            ROS_ERROR_STREAM("cv_bridge exception: " << e.what());
            return;
        }

        rightImageReady = true;
        rightImage = cvPtr->image.clone();

        if ( SHOW_IMAGE )
        {
            imshow("right", cvPtr->image);
            waitKey(1);
        }
    }
    
    void DepthGreyCallBack(const sensor_msgs::ImageConstPtr& img)
    {
        cv_bridge::CvImageConstPtr cvPtr;
        try 
        {
            if (enc::isColor(img->encoding)) 
            {
                cvPtr = cv_bridge::toCvShare(img, enc::RGB8);
            } 
            else if (img->encoding == enc::MONO16) 
            {
                cvPtr = cv_bridge::toCvShare(img, enc::MONO16);
            } 
            else 
            {
                cvPtr = cv_bridge::toCvShare(img, enc::MONO8);
            }
        } 
        catch (cv_bridge::Exception& e) 
        {
            ROS_ERROR_STREAM("cv_bridge exception: " << e.what());
            return;
        }

        depthImageReady = true;
        depthImage = cvPtr->image.clone();
        if ( SHOW_IMAGE )
        {
            imshow("depth", cvPtr->image);
            waitKey(1);
        }
    }

};



#endif 