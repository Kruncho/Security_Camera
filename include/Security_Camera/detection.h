/**
  * @file detection.h
  * @author Kruncho (Vincent Rose <vincent.rose95@gmail.com>)
  * @version 1.0
  * @date November 10, 2014
  */

#ifndef DETECTION_H
#define DETECTION_H

#include <cv.h>

/**
 * @class Detection
 * @brief Detect if something apears or moves between two frames
 */
class Detection
{
    public:
        /**
         * @brief   Detection constructor
         * @param   prev_frame  Adress of the first frame
         * @param   next_frame  Adress of the second frame
         */
        Detection(cv::Mat *prev_frame, cv::Mat *next_frame, int frame_count);

        /**
         * @brief   According to the simple optical flow equation, by frame,
         *          the sum of each pixels must be constent
         * @return bool true if the sum it's constent, false otherwise
         */
        bool consitency(); /* Check the ratio between the two frames */

        /**
         * @brief Compute the optical flow using the opencv goodFeaturesToTrack and calcOpticalFlowPyrLK
         */
        void computeOpticalFlow();

    protected :
        cv::Mat *_prev_frame; ///< Pointer to the first frame
        cv::Mat *_next_frame; ///< Pointer to the second frame

        int _rows, _cols; ///< The frame size (must be the same for all frames)
        int _frame_counter; ///< Debug

        std::vector<cv::Point2f> _prev_points;
        std::vector<cv::Point2f> _next_points;
        std::vector<uchar> _status;
        std::vector<float> _err; /// Used in the computeOpticalFlow method

};

#endif // DETECTION_H
