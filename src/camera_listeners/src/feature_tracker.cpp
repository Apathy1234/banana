#include "get_data.h"


int main(int argc, char** argv)
{
    ros::init(argc, argv, "get_image");
    imageConvert img;
    static uint64_t timeBegin = 0, timeEnd = 0; 


    while( ros::ok() )
    {
        ros::spinOnce();
        if ( img.Image_Fresh() )
        {
            timeBegin = ros::Time::now().toNSec();
            ROS_INFO_STREAM("fresh time cost: " << (timeBegin-timeEnd));
            timeEnd = timeBegin;
        }
    }
    return 0;
}