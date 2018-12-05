#include "my_include.h"
#include "feature_tracker.h"
#include "frame.h"
#include "config.h"
#include "camera.h"
#include "data_convert.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "get_image");

    uint64_t timeBegin, timeEnd;
    DataConvert camData;

    Config::Open_ParameterFile( FILE_DIR );
    VisualOdometry::ptr vo(new VisualOdometry);
    Camera::ptr camera(new Camera);



    while(ros::ok())
    {
        ros::spinOnce();
        if ( camData.imageUpdate )
        {
            timeBegin = ros::Time::now().toNSec();
            Frame::ptr newFrame = Frame::Create_Frame();
            newFrame->leftImage = camData.leftImage;
            newFrame->depthImage = camData.depthImage;

            vo->Add_Frame( newFrame );

            // Mat outimg;
            // drawKeypoints(newFrame->leftImage, vo->keyPointsCurr, outimg);
            // imshow("left", outimg);
            // imshow("depth", newFrame->depthImage);
            // waitKey(1);

            camData.imageUpdate = false;

            timeEnd = ros::Time::now().toNSec();
            ROS_INFO_STREAM("code time cost: " << (timeEnd-timeBegin) << " ns");
        }
    }

    return 0;
}
