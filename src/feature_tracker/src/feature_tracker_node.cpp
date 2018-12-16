#include "my_include.h"
#include "config.h"
#include "feature_tracker.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "feature_tracker");

    Config::Open_ParameterFile( FILE_DIR );

    FeatureTracker featureTracker;


    ros::spin();

    return 0;
}
