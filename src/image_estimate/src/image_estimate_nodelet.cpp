#include <image_estimate/my_include.h>

PLUGINLIB_EXPORT_CLASS(NodeletTest, nodelet::Nodelet);


void NodeletTest::onInit()
{
    NODELET_DEBUG("Hello, nodelet!");
    ROS_INFO_STREAM("Nodelet test is ok!");
}