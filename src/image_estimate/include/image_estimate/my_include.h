#ifndef _MY_INCLUDE_H_
#define _MY_INCLUDE_H_

#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>


class NodeletTest : public nodelet::Nodelet
{
    public:
        virtual void onInit();
};


#endif