#include <cv.h>
#include <highgui.h>
#include <iostream>

int main(int argc, char** argv)
{
    std::string capture = "";

    if (argc != 2)
        capture = 0; // open the video camera no. 0
    else
        capture = argv[2];

    cv::VideoCapture cap(capture);

    if (!cap.isOpened())  // if not success, exit program
    {
        std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;

    cv::namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    while (1)
    {
        cv::Mat color_frame;
        cv::Mat gray_frame;

        bool bSuccess = cap.read(color_frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }

        cvtColor(color_frame, gray_frame, CV_BGR2GRAY);

        cv::imshow("MyVideo", gray_frame); //show the frame in "MyVideo" window

        if (cv::waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            std::cout << "esc key is pressed by user" << std::endl;
            break;
        }
    }
    return 0;

}
