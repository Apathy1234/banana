#include "feature_tracker.h"


VisualOdometry::VisualOdometry():state(INITIALIZING), ref(nullptr), curr(nullptr), lostNum(0)
{
    featureNum = Config::get<int>("numberOfFeature");
    scaleFactor = Config::get<double>("scaleFactor");
    pyramidLevel = Config::get<int>("levelOfPyramid");
    matchRatio = Config::get<float>("matchRatio");
    maxLostNum = Config::get<int>("maxNumLost");
    keyframeMiniRot = Config::get<double>("keyFrameRotation");
    keyframeMiniTrans = Config::get<double>("keyFrameTranslation");

    orb = ORB::create(featureNum, scaleFactor, pyramidLevel);
}

VisualOdometry::~VisualOdometry()
{

}

void VisualOdometry::Extract_Keypoints(void)
{
    orb->detect(curr->leftImage, keyPointsCurr);
}

void VisualOdometry::Compute_Descriptors(void)
{
    orb->compute(curr->leftImage, keyPointsCurr, descriptorsCurr);
}

void VisualOdometry::Feature_Match(void)
{
    vector<DMatch> matches;
    BFMatcher matcher(NORM_HAMMING);
    matcher.match(descriptorsRef, descriptorsCurr, matches);

    // select the best matches
    float minDist =min_element(matches.begin(), matches.end(),
                               [] ( const cv::DMatch& m1, const cv::DMatch& m2 )
    {
        return m1.distance < m2.distance;
    } )->distance;
    featureMatches.clear();
    for ( cv::DMatch& m : matches )
    {
        if ( m.distance < max<float> ( minDist*matchRatio, 30.0 ) )
        {
            featureMatches.push_back(m);
        }
    }
    cout<<"good matches: "<<featureMatches.size()<<endl;
}

bool VisualOdometry::Add_Frame(Frame::ptr frame)
{
    switch(state)
    {
        case INITIALIZING:
        {
            state = OK;
            curr = ref = frame;
            Extract_Keypoints();
            Compute_Descriptors();
            break;
        }
        case OK:
        {
            curr = frame;
            Extract_Keypoints();
            Compute_Descriptors();
            // Feature_Match();
            ref = curr;
            break;
        }
        case LOST:
        {
            cout << "vo has lost! Please check it!";
            break;
        }
        default:
            break;
    }
    return true;
}