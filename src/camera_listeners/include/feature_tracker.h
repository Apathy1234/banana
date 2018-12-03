#ifndef _FEATURE_TRACKER_H_
#define _FEATURE_TRACKER_H_

#include "my_include.h"
#include "frame.h"
#include "config.h"
class VisualOdometry
{
public:
    typedef shared_ptr<VisualOdometry> ptr;
    enum VOState
    {
        INITIALIZING = -1,
        OK = 0,
        LOST = 1
    };
        
    VOState state;                      // current VO state
    Frame::ptr ref;                     // the reference frame
    Frame::ptr curr;                    // the current frame
    cv::Ptr<ORB>        orb;            // orb detector and computer
    vector<Point3f>     pos3dRef;       // 3d points in reference frame 
    vector<KeyPoint>    keyPointsCurr;  // keypoints in current frame
    Mat                 descriptorsCurr;// descriptors in current frame
    Mat                 descriptorsRef; // descriptors in reference frame

    vector<DMatch>      featureMatches;

    int     lostNum;
    int     featureNum;
    double  scaleFactor;
    int     pyramidLevel;
    float   matchRatio;
    int     maxLostNum;
    
    double keyframeMiniRot;
    double keyframeMiniTrans;
public:
    VisualOdometry();
    ~VisualOdometry();
        
    bool Add_Frame(Frame::ptr frame);   // add a new frame
       
private:

    //inner operation
    void Extract_Keypoints(void);   // get the keypoints
    void Compute_Descriptors(void); // compute the descriptors of keypoints
    void Feature_Match(void);       // match the feature of two image

};




#endif