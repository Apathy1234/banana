#include "my_include.h"
#include "get_data.h"
#include "feature_tracker.h"
#include "frame.h"
#include "config.h"
#include "camera.h"

const string FILE_DIR = "/home/tg/my_slam/src/camera_listeners/config/parameter.yaml";

int main(int argc, char** argv)
{
    ros::init(argc, argv, "run_vo_node");
    ImageConvert img;
    Config::Open_ParameterFile( FILE_DIR );
    VisualOdometry::ptr vo(new VisualOdometry);
    Camera::ptr camera(new Camera);

    static uint64_t timeBegin = 0, timeEnd = 0; 
    while( ros::ok() )
    {
        ros::spinOnce();
        if ( img.Image_Fresh() )
        {
            timeBegin = ros::Time::now().toNSec();
            // ROS_INFO_STREAM("code time cost: " << (timeBegin-timeEnd));
            // timeEnd = timeBegin;
            Frame::ptr newFrame = Frame::Create_Frame();
            newFrame->leftImage = img.leftImage;
            newFrame->depthImage = img.depthImage;

            vo->Add_Frame( newFrame );
            // Mat outimg;
            // drawKeypoints(newFrame->leftImage, vo->keyPointsCurr, outimg);
            // imshow("left", outimg);
            // imshow("depth", newFrame->depthImage);
            // waitKey(1);

            timeEnd = ros::Time::now().toNSec();
            ROS_INFO_STREAM("code time cost: " << (timeEnd-timeBegin) << " ns");
        }
    }
    return 0;
}