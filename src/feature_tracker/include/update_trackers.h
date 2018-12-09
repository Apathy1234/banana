#ifndef _UPDATE_TRACKERS_H_
#define _UPDATE_TRACKERS_H_

#include "my_include.h"
#include "config.h"

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
    int n_id;
    vector<Point2f> keyPointsAdd;
    Mat mask;


    bool Point_In_Border(const Point2f& pt);
    void Reduce_Vector(vector<Point2f>& v, vector<uchar> status);
    void Reduce_Vector(vector<int>& v, vector<uchar> status);
    void Add_Points(void);
    void Set_Mask(void);
    void Delete_Point_With_F(void);
public:
    typedef shared_ptr<UpdateTrackers> ptr;
    vector<Point2f> keyPointsRef;
    vector<Point2f> keyPointsCurr;
    vector<int> trackerId;
    vector<int> trackerCnt;


    UpdateTrackers(void);
    ~UpdateTrackers(void);

    bool Update_Tracker_ID(int i);

    void Find_Feature( const Mat& _img, double _currTime, const bool pubThisFrame);
};




#endif