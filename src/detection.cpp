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

    if(!this->consitency())
        std::cout << "Unconsistent at frame : " << _frame_counter << std::endl;

    this->computeOpticalFlow();
}

bool Detection::consitency()
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

void Detection::computeOpticalFlow()
{
    const int MAX_COUNT = 50;

    std::vector<cv::Point2f> prev_points;
    std::vector<cv::Point2f> next_points;
    std::vector<uchar> status;
    std::vector<float> err;

    cv::goodFeaturesToTrack(*_next_frame, prev_points, MAX_COUNT, 0.01, 10);
    cv::calcOpticalFlowPyrLK(*_prev_frame, *_next_frame, prev_points, next_points, status, err);

    for(int  i = 0; i < next_points.size(); i++)
        if(status[i])
            line(*_next_frame, prev_points[i], next_points[i], cv::Scalar(0,0,255), 2);
}


