#include <cv.h>
#include <highgui.h>
#include <iostream>

#include"Security_Camera/detection.h"

int main(int argc, char** argv)
{
    cv::VideoCapture cap(0);

    if (!cap.isOpened())  // if not success, exit program
    {
        std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

    std::string title = "I'm Watching You";

    cv::namedWindow(title,CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    cv::Mat prev_frame;

    bool first_frame = true; /* To do just in the first loop */

    int count = 0; /* Frame counter */

    while (1)
    {
        cv::Mat color_frame, gray_frame;

        bool bSuccess = cap.read(color_frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        cvtColor(color_frame, gray_frame, CV_BGR2GRAY);

        if (first_frame)
        {
            first_frame = false;
            prev_frame = gray_frame;
        }

        /* Begin process*/

        Detection *detection = new Detection(&prev_frame, &gray_frame);

        if(!detection->Consitency())
            std::cout << "Unconsistent at frame : " << count << std::endl;

        /* End process */

        cv::imshow(title, gray_frame); //show the frame

        if (cv::waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            std::cout << "esc key is pressed by user" << std::endl;
            break;
        }

        prev_frame = gray_frame;
        count++;
    }
    return 0;

}
