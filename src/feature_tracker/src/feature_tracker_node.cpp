#include "feature_tracker/my_include.h"
#include "feature_tracker/config.h"
#include "feature_tracker/feature_tracker.h"

int main(int argc, char **argv)
{
    string file_dir;
    ros::init(argc, argv, "feature_tracker");
    ros::param::get("file_dir", file_dir);
    Config::Open_ParameterFile( FILE_DIR );

    FeatureTracker featureTracker;


    ros::spin();

    return 0;
}
