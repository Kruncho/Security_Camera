#ifndef DETECTION_H
#define DETECTION_H

#include <cv.h>

class Detection
{
    public:
        Detection(cv::Mat *prev_frame, cv::Mat *next_frame, int frame_count);
        bool Consitency(); /* Check the ratio between the two frames */
        void Optical_Flow();
    private :
        cv::Mat *_prev_frame;
        cv::Mat *_next_frame;
        int _rows, _cols, _frame_counter;
};

#endif // DETECTION_H
