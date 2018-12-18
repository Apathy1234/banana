#ifndef _UPDATE_TRACKERS_H_
#define _UPDATE_TRACKERS_H_

#include "feature_tracker/my_include.h"
#include "feature_tracker/config.h"
#include "feature_tracker/camera.h"

class UpdateTrackers
{
private:
    Mat imgRef;
    Mat imgCurr;
    int BORDERSIZE;
    int EQUALIZE;
    int MIN_DIS;
    int MAX_CNT;
    double F_THRESHOLD;
    double timeRef;
    double timeCurr;
    int n_id;
    Mat mask;
    vector<Point2f> keyPointsAdd;
    Camera::ptr camera;

    bool Point_In_Border(const Point2f& pt);
    void Reduce_Vector(vector<Point2f>& v, vector<unsigned char> status);
    void Reduce_Vector(vector<int>& v, vector<unsigned char> status);
    void Add_Points(void);
    void Set_Mask(void);
    void Delete_Point_With_F(void);
    void Calculation_Points_From_Depth(void);
    
public:
    typedef shared_ptr<UpdateTrackers> ptr;
    vector<Point2f> keyPointsRef;
    vector<Point2f> keyPointsCurr;
    vector<int> trackerId;
    vector<int> trackerCnt;

    vector<Point3f> kpsCameraCurr;
    vector<Point2d> kpsCamera_uv;
    vector<int> kpsCameraId;
    vector<int> kpsCameraCnt;

    UpdateTrackers(void);
    ~UpdateTrackers(void);

    bool Update_Tracker_ID(int i);

    void Find_Feature( const Mat& _img, const Mat& depth_img, double _currTime, const bool pubThisFrame);
};




#endif