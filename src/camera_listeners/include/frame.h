#ifndef _FRAME_H_
#define _FRAME_H_

#include "my_include.h"


class Frame
{
public:
    typedef shared_ptr<Frame> ptr;
    Frame();
    ~Frame();
    Mat leftImage, rightImage, depthImage;
    
    static Frame::ptr Create_Frame(void);
private:

};





#endif 