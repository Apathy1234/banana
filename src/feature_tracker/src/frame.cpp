#include "feature_tracker/frame.h"

Frame::Frame()
{

}

Frame::~Frame()
{

}

Frame::ptr Frame::Create_Frame(void)
{
    return Frame::ptr(new Frame);
}
