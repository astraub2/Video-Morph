#include <iostream> // for standard I/O
#include <string>   // for strings

#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

using namespace std;
using namespace cv;
//WITH_FFMPEG=ON
static void help()
{
    cout
        << "------------------------------------------------------------------------------" << endl
        << "This program distortes and writes video files utilizing parallel processing."                                   << endl
        << "You can extract multiple distortions from the input video."              << endl
        << "Usage:"                                                                         << endl
        << "./video-write inputvideoName <command>"                              << endl
        << "------------------------------------------------------------------------------" << endl
         << "Available commands: invert" << endl
        << endl;
}

int main(int argc, char *argv[])
{
    help();

    if (argc != 3)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    const string source      = argv[1];           // the source file name
    const string Command=argv[2];

    VideoCapture inputVideo(source);              // Open input
    if (!inputVideo.isOpened())
    {
        cout  << "Could not open the input video: " << source << endl;
        return -1;
    }

    string::size_type pAt = source.find_last_of('.');                  // Find extension point
    const string NAME = source.substr(0, pAt)+"_out.avi";   // Form the new name with container
    int ex;    // Get Codec Type- Int form

    // Transform from int to char via Bitwise operators
    // char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};

    Size S = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));

    VideoWriter outputVideo;                                        // Open the output
    
    outputVideo.open(NAME, ex=0, inputVideo.get(CV_CAP_PROP_FPS)*.5, S, true);
    
    if (!outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write: " << source << endl;
        return -1;
    }

    cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
         << " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
    

    if(Command=="invert"){
        cout<<"Inverting...."<<endl;
    for(;;) 
        {
        //cout<<"1st"<<endl;
        Mat frame;
        inputVideo >> frame; // get a new frame from camera
        Mat cframe;
        inputVideo >> cframe;
        if (frame.empty()) break; 
        //cout<<"2nd"<<endl;


        uchar pixValue;
        for (int i = 0; i < cframe.cols; i++) {
            for (int j = 0; j < cframe.rows; j++) {

                Vec3b &intensity = frame.at<Vec3b>(j, i);
                //if(intensity.val[0]=0) break;
                Vec3b &inverse = cframe.at<Vec3b>(cframe.rows-j, cframe.cols-i);
                intensity.val[0] = inverse.val[0];
                intensity.val[1] = inverse.val[1];
                intensity.val[2] = inverse.val[2];

             }
        }
       outputVideo.write(frame);
       //cout<<"4"<<endl;
    }
}

    cout << "Finished writing" << endl;
    return 0;
}