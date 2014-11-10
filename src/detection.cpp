#include "Security_Camera/detection.h"

Detection::Detection(cv::Mat *prev_frame, cv::Mat *next_frame)
{
    _prev_frame = prev_frame;
    _next_frame = next_frame;

    if(_prev_frame->size != _next_frame->size)
    {
        std::cerr << "Frame sizes are not the same !" << std::endl;
        EXIT_FAILURE;
    }

}

bool Detection::Consitency()
{
    bool consitency = false;

    int prev_sum = 0;
    int next_sum = 0;

    for (int i = 0; i < _prev_frame->cols; i++)
        for(int j = 0; j < _prev_frame->rows; j++)
        {
            prev_sum += _prev_frame->at<uchar>(j, i);
            next_sum += _next_frame->at<uchar>(j, i);

        }


    double tolerence = 1; /* In percent */

    double ratio = (double)prev_sum / (double)next_sum;

    if((ratio < 1 + tolerence / 100) && (ratio > 1 - tolerence / 100))
        consitency = true;

    return consitency;
}


