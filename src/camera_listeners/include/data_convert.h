#ifndef _IMAGE_CONVERT_H_
#define _IMAGE_CONVERT_H_

#include "my_include.h"

namespace enc = sensor_msgs::image_encodings;


class DataConvert
{
private:

    const bool SHOW_IMAGE = false;
    uint64_t timeBegin = 0, timeEnd = 0;
    
    ros::NodeHandle n;
    
    message_filters::Subscriber<sensor_msgs::Image> leftSub;
    message_filters::Subscriber<sensor_msgs::Image> rightSub;
    message_filters::Subscriber<sensor_msgs::Image> depthSub;
    message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image, sensor_msgs::Image> stereoSub;

public:

    Mat leftImage, rightImage, depthImage;
    bool imageUpdate = false;

    DataConvert(void);
    
    ~DataConvert(void);

    void Stereo_Callback(
        const sensor_msgs::ImageConstPtr& leftImg, 
        const sensor_msgs::ImageConstPtr& rightImg, 
        const sensor_msgs::ImageConstPtr& depthImg);
};

#endif