#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "my_include.h"
#include "config.h"

typedef unsigned short ushort;


class Camera
{
private:
    float fx, fy, cx, cy;
    float factorScale;
    float depth;

public:
    typedef shared_ptr<Camera> ptr;
    Mat depthImage;
    Eigen::Matrix<float, 3, 3> kMatrix;
    Eigen::Matrix<float, 3, 3> kMatrixInv;
    bool Pixel_2_Camera(const Eigen::Vector3f& p_src, Eigen::Vector3f& p_dis);
    void Find_Depth(const vector<Point2f>& kps, vector<unsigned char>& status);
    Camera();
     ~Camera();

};



#endif 