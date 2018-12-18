#ifndef _FEATURE_TRACKER_NODELET_H_
#define _FEATURE_TRACKER_NODELET_H_

#include <feature_tracker/feature_tracker.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>

class FeatureTrackerNodelet : public nodelet::Nodelet
{
public:
  FeatureTrackerNodelet(void);
  ~FeatureTrackerNodelet(void);


private:
    virtual void onInit();
    FeatureTracker::ptr featureTracker;
};


#endif