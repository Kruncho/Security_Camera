#include <cv.h>
#include <highgui.h>
#include <iostream>

#include"Security_Camera/detection.h"

int main(int argc, char** argv)
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "Cannot open the video cam" << std::endl;
        EXIT_FAILURE;
    }

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); /* get the width of frames of the video */
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); /* get the height of frames of the video */
    double fps = cap.get(CV_CAP_PROP_FPS); /* Not working for some unknown reasons*/

    std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;
    std::cout << "FPS : " << fps << std::endl;

    std::string title = "I'm Watching You";

    cv::namedWindow(title,CV_WINDOW_AUTOSIZE);

    cv::Mat prev_frame;

    bool first_frame = true; /* To do just in the first loop */

    int count = 0; /* Frame counter */

    while (1)
    {
        cv::Mat color_frame, gray_frame;

        cap >> color_frame;

        cvtColor(color_frame, gray_frame, CV_BGR2GRAY);

        if (first_frame)
        {
            first_frame = false;
            prev_frame = gray_frame;
        }

        /* Begin process */

        Detection detection =  Detection(&prev_frame, &gray_frame, count);

        /* End process */

        cv::imshow(title, gray_frame); //show the frame

        if (cv::waitKey(30) == 27) // 27 = 'esc' button
        {
            std::cout << "esc key is pressed by user" << std::endl;
            break;
        }

        prev_frame = gray_frame;
        count++;
    }

    EXIT_SUCCESS;
}
