#include "camera.h"

Camera::Camera()
{
    fx = Config::get<float>("camera.fx");
    fy = Config::get<float>("camera.fy");
    cx = Config::get<float>("camera.cx");
    cy = Config::get<float>("camera.cy");
}
Camera::~Camera()
{


}