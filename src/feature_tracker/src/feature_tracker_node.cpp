#include "my_include.h"
#include "frame.h"
#include "config.h"
#include "camera.h"
#include "feature_tracker.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "get_image");

    Config::Open_ParameterFile( FILE_DIR );

    FeatureTracker featureTracker;


    ros::spin();

    return 0;
}
