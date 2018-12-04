#include "my_include.h"
#include "feature_tracker.h"
#include "frame.h"
#include "config.h"
#include "camera.h"

const bool SHOW_IMAGE = false;
bool Image_Update = false;

Mat leftImage, rightImage, depthImage;

uint64_t timeBegin = 0, timeEnd = 0;

void Stereo_Callback(const sensor_msgs::ImageConstPtr& leftImg, const sensor_msgs::ImageConstPtr& rightImg, const sensor_msgs::ImageConstPtr& depthImg)
{
    // timeBegin = ros::Time::now().toNSec();
    // ROS_INFO_STREAM("code cost time: " << (timeBegin - timeEnd) << " ns");
    // timeEnd = timeBegin;
    cv_bridge::CvImageConstPtr cvLeftPtr, cvRightPtr, cvDepthPtr;

    cvLeftPtr = cv_bridge::toCvShare(leftImg, enc::MONO8);
    cvRightPtr = cv_bridge::toCvShare(rightImg, enc::MONO8);
    cvDepthPtr = cv_bridge::toCvShare(depthImg, enc::MONO16);
    
    leftImage = cvLeftPtr->image.clone();
    rightImage = cvRightPtr->image.clone();
    depthImage = cvDepthPtr->image.clone();

    Image_Update = true;

    if ( SHOW_IMAGE )
    {
        imshow("left", cvLeftPtr->image);
        imshow("right", cvRightPtr->image);
        imshow("depth", cvDepthPtr->image);
        waitKey(1);
    }

}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "get_image");

    ros::NodeHandle n;
    message_filters::Subscriber<sensor_msgs::Image> leftSub;
    message_filters::Subscriber<sensor_msgs::Image> rightSub;
    message_filters::Subscriber<sensor_msgs::Image> depthSub;
    message_filters::TimeSynchronizer<sensor_msgs::Image, sensor_msgs::Image, sensor_msgs::Image> stereoSub(3);

    leftSub.subscribe(n, "/mynteye/left/image_mono", 1);
    rightSub.subscribe(n, "/mynteye/right/image_mono", 1);
    depthSub.subscribe(n, "mynteye/depth/image_raw", 1);
    stereoSub.connectInput(leftSub, rightSub, depthSub);
    stereoSub.registerCallback(Stereo_Callback);

    Config::Open_ParameterFile( FILE_DIR );
    VisualOdometry::ptr vo(new VisualOdometry);
    Camera::ptr camera(new Camera);



    while(ros::ok())
    {
        ros::spinOnce();
        if ( Image_Update )
        {
            timeBegin = ros::Time::now().toNSec();
            Frame::ptr newFrame = Frame::Create_Frame();
            newFrame->leftImage = leftImage;
            newFrame->depthImage = depthImage;

            vo->Add_Frame( newFrame );

            // Mat outimg;
            // drawKeypoints(newFrame->leftImage, vo->keyPointsCurr, outimg);
            // imshow("left", outimg);
            // imshow("depth", newFrame->depthImage);
            // waitKey(1);

            Image_Update = false;

            timeEnd = ros::Time::now().toNSec();
            ROS_INFO_STREAM("code time cost: " << (timeEnd-timeBegin) << " ns");
        }
    }

    return 0;
}
