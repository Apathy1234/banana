#ifndef _MY_INCLUDE_H_
#define _MY_INCLUDE_H_

#include "ros/ros.h"
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/PointCloud.h>
#include <image_transport/image_transport.h>
#include <geometry_msgs/Point32.h>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <algorithm>
#include <vector>
#include <utility>
// #include <list>
#include <memory>
#include <string>
#include <iostream>
#include <cmath>
// #include <set>
// #include <unordered_map>
#include <map>


#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;

using namespace cv;

const string FILE_DIR = "/home/tg/my_slam/src/feature_tracker/config/parameter.yaml";

const int WIDTH = 640;
const int HEIGHT = 480;


#endif 