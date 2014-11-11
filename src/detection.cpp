#include "Security_Camera/detection.h"

Detection::Detection(cv::Mat *prev_frame, cv::Mat *next_frame, int frame_count)
{
    _prev_frame = prev_frame;
    _next_frame = next_frame;

    if(_prev_frame->size != _next_frame->size)
    {
        std::cerr << "Frames are not the same size !" << std::endl;
        EXIT_FAILURE;
    }
    else
    {
        _rows = _prev_frame->rows;
        _cols = _prev_frame->cols;
        _frame_counter = frame_count;
    }

    if(!this->Consitency())
        std::cout << "Unconsistent at frame : " << _frame_counter << std::endl;
}

bool Detection::Consitency()
{
    bool consitency = false;

    int prev_sum = 0;
    int next_sum = 0;

    for (int i = 0; i < _cols; i++)
    {
        for(int j = 0; j < _rows; j++)
        {
            prev_sum += _prev_frame->at<uchar>(j, i);
            next_sum += _next_frame->at<uchar>(j, i);
        }
    }

    double tolerence = 1; /* In percent */

    double ratio = (double)prev_sum / (double)next_sum;

    if((ratio < 1 + tolerence / 100) && (ratio > 1 - tolerence / 100))
        consitency = true;

    return consitency;
}

void Detection::Optical_Flow()
{
    cv::Point2f *prev_points = new cv::Point2f[_cols * _rows];
    cv::Point2f *next_points = new cv::Point2f[_cols * _rows];
    uchar *status = new uchar[_cols * _rows];
    float *err = new float[_cols * _rows];

    //const int MAX_COUNT = 500;

    //cv::goodFeaturesToTrack(*_next_frame, points[1], MAX_COUNT, 0.01, 10);
    //cv::calcOpticalFlowPyrLK(*_prev_frame, *_next_frame, prev_points, next_points, status, err);

    delete prev_points, next_points, status, err;
}


