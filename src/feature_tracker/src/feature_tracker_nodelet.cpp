// #include "feature_tracker/my_include.h"
// #include "feature_tracker/config.h"
// #include "feature_tracker/feature_tracker.h"

// int main(int argc, char **argv)
// {
//     string file_dir;
//     ros::init(argc, argv, "feature_tracker");
//     ros::param::get("file_dir", file_dir);
//     Config::Open_ParameterFile( FILE_DIR );

//     FeatureTracker featureTracker;


//     ros::spin();

//     return 0;
// }

#include "feature_tracker/my_include.h"
#include "feature_tracker/config.h"
#include "feature_tracker/feature_tracker_nodelet.h"

PLUGINLIB_EXPORT_CLASS(FeatureTrackerNodelet, nodelet::Nodelet);

FeatureTrackerNodelet::FeatureTrackerNodelet(void)
{

}

FeatureTrackerNodelet::~FeatureTrackerNodelet(void)
{

}

void FeatureTrackerNodelet::onInit()
{
    ROS_INFO("Start feature tracker...");
    Config::Open_ParameterFile( FILE_DIR );
    featureTracker.reset(new FeatureTracker(getNodeHandle()));
}


