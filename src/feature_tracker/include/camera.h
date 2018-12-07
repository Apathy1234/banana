#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "my_include.h"
#include "config.h"

class Camera
{
public:
    typedef shared_ptr<Camera> ptr;
    float fx, fy, cx, cy;

public:
    Camera();
     ~Camera();

private:

};



#endif 