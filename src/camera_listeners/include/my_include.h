#ifndef _MY_INCLUDE_H_
#define _MY_INCLUDE_H_

#include "ros/ros.h"
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/calib3d/calib3d.hpp>

#include <algorithm>
#include <vector>
// #include <list>
#include <memory>
#include <string>
#include <iostream>
// #include <set>
// #include <unordered_map>
// #include <map>

using namespace std;

using namespace cv;

const string FILE_DIR = "/home/tg/my_slam/src/camera_listeners/config/parameter.yaml";

#endif 