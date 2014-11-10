#ifndef DETECTION_H
#define DETECTION_H

#include <cv.h>

class Detection
{
    public:
        Detection(cv::Mat *prev_frame, cv::Mat *next_frame);
        bool Consitency(); /* Check the ratio between the two frames */
    private :
        cv::Mat *_prev_frame;
        cv::Mat *_next_frame;
};

#endif // DETECTION_H
