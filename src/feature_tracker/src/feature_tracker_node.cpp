#include "my_include.h"
#include "frame.h"
#include "config.h"
#include "camera.h"
#include "feature_tracker.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "get_image");

    Config::Open_ParameterFile( FILE_DIR );

    Camera::ptr camera(new Camera);

    FeatureTracker featureTracker;


    while(ros::ok())
    {
        ros::spinOnce();
    }

    return 0;
}
