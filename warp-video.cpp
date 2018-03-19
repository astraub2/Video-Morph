   #include <chrono>

#include <iostream> // for standard I/O
#include <string>   // for strings

#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

using namespace std;
using namespace cv;
//WITH_FFMPEG=ON
typedef std::chrono::high_resolution_clock Clock;
static void help()
{
    cout
        << "------------------------------------------------------------------------------" << endl
        << "This program distortes and writes video files utilizing parallel processing."                                   << endl
        << "You can extract multiple distortions from the input video."              << endl
        << "Usage:"                                                                         << endl
        << "./video-write inputvideoName <command> <-serial OR -parallel>"                              << endl
        << "------------------------------------------------------------------------------" << endl
        << "Available commands: invert, bw, sepia, watermark, darken, self_overlay" << endl
        << "./video-write inputvideoName <command> <-serial OR -parallel> watermarkimage"                              << endl

        << endl;
}

void invert_p(VideoCapture inputVideo, VideoWriter outputVideo){

        cout<<"Inverting...."<<endl;
        #pragma omp parallel for
        for(;;) 
            {
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            Mat cframe=frame.clone();
            
            if (frame.empty()) break; 

            uchar pixValue;
            #pragma omp parallel for
            for (int i = 0; i < cframe.cols; i++) {
                for (int j = 0; j < cframe.rows; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(j, i);
                    Vec3b &inverse = cframe.at<Vec3b>(cframe.rows-j, cframe.cols-i);
                    intensity.val[0] = inverse.val[0];
                    intensity.val[1] = inverse.val[1];
                    intensity.val[2] = inverse.val[2];
    
               }
            }
           outputVideo.write(frame);
        }
}
void invert_s(VideoCapture inputVideo, VideoWriter outputVideo){

        cout<<"Inverting...."<<endl;
        for(;;) 
            {
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            Mat cframe=frame.clone();
            
            if (frame.empty()) break; 

            uchar pixValue;
            for (int i = 0; i < cframe.cols; i++) {
                for (int j = 0; j < cframe.rows; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(j, i);
                    Vec3b &inverse = cframe.at<Vec3b>(cframe.rows-j, cframe.cols-i);
                    intensity.val[0] = inverse.val[0];
                    intensity.val[1] = inverse.val[1];
                    intensity.val[2] = inverse.val[2];
    
               }
            }
           outputVideo.write(frame);
        }
}
void self_overlay_s(VideoCapture inputVideo, VideoWriter outputVideo){
	 cout<<"Overlaying...."<<endl;
        for(;;) 
            {
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            Mat cframe=frame.clone();
            double opacity = .5;
            if (frame.empty()) break; 
            for (int i = 0; i < cframe.cols; i++) {
                for (int j = 0; j < cframe.rows; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(j, i);
                    Vec3b &inverse = cframe.at<Vec3b>(cframe.rows-j, cframe.cols-i);
              
                    intensity.val[0] = inverse.val[0]*opacity + intensity.val[0]*(1-opacity);
                    intensity.val[1] = inverse.val[1]*opacity + intensity.val[1]*(1-opacity);
                    intensity.val[2] = inverse.val[2]*opacity + intensity.val[2]*(1-opacity);
    
                }
            }
            
           outputVideo.write(frame);
        }

}
void self_overlay_p(VideoCapture inputVideo, VideoWriter outputVideo){
	 cout<<"Overlaying...."<<endl;
        #pragma omp parallel for
        for(;;) 
            {
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            Mat cframe=frame.clone();
            double opacity = .5;
            if (frame.empty()) break; 
            #pragma omp parallel for
            for (int i = 0; i < cframe.cols; i++) {
                for (int j = 0; j < cframe.rows; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(j, i);
                    Vec3b &inverse = cframe.at<Vec3b>(cframe.rows-j, cframe.cols-i);
              
                    intensity.val[0] = inverse.val[0]*opacity + intensity.val[0]*(1-opacity);
                    intensity.val[1] = inverse.val[1]*opacity + intensity.val[1]*(1-opacity);
                    intensity.val[2] = inverse.val[2]*opacity + intensity.val[2]*(1-opacity);
    
                }
            }
            
           outputVideo.write(frame);
        }

}
void darken_s(VideoCapture inputVideo, VideoWriter outputVideo){
	cout<<"Darkening...."<<endl;
        for(;;) 
            {
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            Mat cframe=frame.clone();
            if (frame.empty()) break; 

            for (int i = 0; i < cframe.cols; i++) {
                for (int j = 0; j < cframe.rows; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(j, i);
                    Vec3b &inverse = cframe.at<Vec3b>(j, i);
                    intensity.val[0] = inverse.val[0]>>1;
                    intensity.val[1] = inverse.val[1]>>1;
                    intensity.val[2] = inverse.val[2]>>1;
    
                }
            }
           outputVideo.write(frame);
        }

}
void darken_p(VideoCapture inputVideo, VideoWriter outputVideo){
	cout<<"Darkening...."<<endl;
		#pragma omp parallel for
        for(;;) 
            {
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            Mat cframe=frame.clone();
            if (frame.empty()) break; 
            #pragma omp parallel for
            for (int i = 0; i < cframe.cols; i++) {
                for (int j = 0; j < cframe.rows; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(j, i);
                    Vec3b &inverse = cframe.at<Vec3b>(j, i);
                    intensity.val[0] = inverse.val[0]>>1;
                    intensity.val[1] = inverse.val[1]>>1;
                    intensity.val[2] = inverse.val[2]>>1;
    
                }
            }
           outputVideo.write(frame);
        }

}

int main(int argc, char *argv[])
{
    help();

    if (argc < 4)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    const string source  = argv[1];           // the source file name
    const string Command = argv[2];
    const string processing=argv[3];

    string watermark_img_file;
    if (argc == 5) 
    {
        watermark_img_file = argv[4];          //watermark image file name
    }

    VideoCapture inputVideo(source);              // Open input
    if (!inputVideo.isOpened())
    {
        cout  << "Could not open the input video: " << source << endl;
        return -1;
    }

    string::size_type pAt = source.find_last_of('.');                  // Find extension point
    const string NAME = source.substr(0, pAt)+"_out.avi";   // Form the new name with container
    int ex;    // Get Codec Type- Int form

    Size S = Size((int) inputVideo.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT));

    VideoWriter outputVideo;                                        // Open the output
    outputVideo.open(NAME, ex=0, inputVideo.get(CV_CAP_PROP_FPS), S, true);
    
    if (!outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write: " << source << endl;
        return -1;
    }

    cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
         << " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
    
    auto t1 = Clock::now();
    if(Command=="invert"){
    	if(processing=="-serial")
        	invert_s(inputVideo, outputVideo);
        else if(processing=="-parallel")
        	invert_p(inputVideo, outputVideo);
        else{
        	inputVideo.release();
		    outputVideo.release();
		    cout << "Bad input, see usage" << endl;
		    return 0;
		}

    
    }
    else if(Command=="self_overlay"){
    	if(processing=="-serial")
        	self_overlay_s(inputVideo, outputVideo);
        else if(processing=="-parallel")
        	self_overlay_p(inputVideo, outputVideo);
        else{
        	inputVideo.release();
		    outputVideo.release();
		    cout << "Bad input, see usage" << endl;
		    return 0;
		}
    }
      else if(Command=="darken"){
      	if(processing=="-serial")
        	darken_s(inputVideo, outputVideo);
        else if(processing=="-parallel")
        	darken_p(inputVideo, outputVideo);
        else{
        	inputVideo.release();
		    outputVideo.release();
		    cout << "Bad input, see usage" << endl;
		    return 0;
		}


     
    }
    else{
        	inputVideo.release();
		    outputVideo.release();
		    cout << "Bad input, see usage" << endl;
		    return 0;
		}
    auto t2 = Clock::now();
    std::cout << "Runtime: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
    << " milliseconds" << std::endl;

    inputVideo.release();
    outputVideo.release();
    cout << "Finished writing" << endl;
    return 0;
}
