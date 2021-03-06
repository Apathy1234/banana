#ifndef _FEATURE_TRACKER_H_
#define _FEATURE_TRACKER_H_

#include "feature_tracker/my_include.h"
#include "feature_tracker/update_trackers.h"
#include "feature_tracker/config.h"

namespace enc = sensor_msgs::image_encodings;


class FeatureTracker
{
private:
    int SHOW_TRACKER;
    int TRACKERSIZE;
    uint64_t timeBegin;
    uint64_t timeEnd;

    bool initPub = true;
    enum FeatureState
    {
        FIRST_IMAGE = -1,
        NOT_FIRST_IMAGE = 0
    };
    
    FeatureState state;

    UpdateTrackers::ptr tracker;

    double firstImageTime, currImageTime;
    int pubCnt;
    int FREQ;
    bool pubThisFrame;
    
    ros::NodeHandle n;
    
    ros::Publisher pubMatchImage;
    ros::Publisher pubPoints;
    message_filters::Subscriber<sensor_msgs::Image> leftSub;
    message_filters::Subscriber<sensor_msgs::Image> rightSub;
    message_filters::Subscriber<sensor_msgs::Image> depthSub;
    message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image, sensor_msgs::Image> stereoSub;

public:
    typedef shared_ptr<FeatureTracker> ptr;
    
    FeatureTracker(ros::NodeHandle& nh);
    ~FeatureTracker(void);

    void Stereo_Callback(
        const sensor_msgs::ImageConstPtr& leftImg, 
        const sensor_msgs::ImageConstPtr& rightImg, 
        const sensor_msgs::ImageConstPtr& depthImg);
};

#endif