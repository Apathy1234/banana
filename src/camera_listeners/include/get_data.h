#ifndef _GET_DATA_H_
#define _GET_DATA_H_


#include "ros/ros.h"
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;



const bool SHOW_IMAGE = true;

namespace enc = sensor_msgs::image_encodings;

class imageConvert
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
  

public:
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
    
    imageConvert(void):it(n)
    {
        leftGreySub = it.subscribe("/mynteye/left/image_mono", 1, &imageConvert::LeftImageCallBack, this);
        rightGreySub = it.subscribe("/mynteye/right/image_mono", 1, &imageConvert::RightImageCallBack, this);
        depthGreySub = it.subscribe("/mynteye/depth/image_raw", 1, &imageConvert::DepthGreyCallBack, this);
    }

    void LeftImageCallBack(const sensor_msgs::ImageConstPtr& img)
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

        leftImageReady = true;

        if ( SHOW_IMAGE )
        {
            imshow("left", cvPtr->image);
            waitKey(1);
        }

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

        if ( SHOW_IMAGE )
        {
            imshow("depth", cvPtr->image);
            waitKey(1);
        }
    }

};



#endif 