#include "camera.h"

Camera::Camera()
{
    fx = Config::get<float>("camera.fx");
    fy = Config::get<float>("camera.fy");
    cx = Config::get<float>("camera.cx");
    cy = Config::get<float>("camera.cy");
    factorScale = Config::get<int>("camera.factorScale");
    kMatrix << fx,  0, cx, 
                0, fy, cy, 
                0,  0,  1;
    kMatrixInv = kMatrix.inverse();
}
Camera::~Camera()
{


}

void Camera::Find_Depth(const vector<Point2f>& kps, vector<unsigned char>& status)
{
    for( unsigned int i = 0; i < kps.size(); i++ )
    {
        int x = cvRound(kps[i].x);
        int y = cvRound(kps[i].y);
        unsigned short d = depthImage.at<unsigned short>(y, x);
        if ( d != 0)
        {
            depth = d;
            status[i] = 1;
        }
        else
        {   
            // check the nearby points
            int dx[8] = { 0, 1,  0, -1, -1, 1,  1, -1};
            int dy[8] = { 1, 0, -1,  0,  1, 1, -1, -1};
            for (int num = 0; num < 8; num++)
            {
                d = depthImage.at<unsigned short>(y+dy[num], x+dx[num]);
                if ( d != 0)
                {
                    depth = d;
                    status[i] = 1;
                    break;
                }
                else
                {
                    depth = 0;
                    status[i] = 0;
                }
            }
        }
    }
}

bool Camera::Pixel_2_Camera(const Eigen::Vector3f& p_src, Eigen::Vector3f& p_dis)
{
    int x = cvRound(p_src.x());
    int y = cvRound(p_src.y());
    ushort d = depthImage.at<ushort>(y, x);
    if( d != 0)
    {
        depth = d / factorScale;
    }
    else
    {
        // check the nearby points
        int dx[8] = { 0, 1,  0, -1, -1, 1,  1, -1};
        int dy[8] = { 1, 0, -1,  0,  1, 1, -1, -1};
        for (int num = 0; num < 8; num++)
        {
            d = depthImage.at<unsigned short>(y+dy[num], x+dx[num]);
            if ( d != 0 )
            {
                depth = d / factorScale;
                break;
            }
        }
    }
    if ( depth == 0 )
    {
        return false;
    }
    else
    {
        p_dis = kMatrixInv * p_src;
        p_dis = depth * p_dis;     
        return true;
    }
}