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
        << "Available commands: invert, self_overlay, darken, watermark, bw, negative, blur
" << endl
        << "./video-write inputvideoName <command> <-serial OR -parallel> watermarkimage"                              << endl

        << endl;
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
void invert_p(Mat* frames_temp, Mat* newframes_temp, int NUMFRAMES){

        cout<<"Inverting...."<<endl;
        #pragma omp parallel for
        for(int i=0;i<NUMFRAMES; i++) 
            {
            Mat frame=frames_temp[i];
            
            Mat cframe=frame.clone();
            
            if (frame.empty()) break; 
            int chunk_size = frame.cols/4;
            uchar pixValue;
            #pragma omp parallel for
            for (int i = 0; i < cframe.cols; i++) {
                #pragma omp for nowait, schedule(dynamic, chunk_size)
                for (int j = 0; j < cframe.rows; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(j, i);
                    Vec3b &inverse = cframe.at<Vec3b>(cframe.rows-j, cframe.cols-i);
                    intensity.val[0] = inverse.val[0];
                    intensity.val[1] = inverse.val[1];
                    intensity.val[2] = inverse.val[2];
    
               }
            }
           newframes_temp[i]=frame;
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
void self_overlay_p(Mat* frames_temp, Mat* newframes_temp, int NUMFRAMES){
     cout<<"Overlaying...."<<endl;
     	#pragma omp parallel for
        for(int i=0;i<NUMFRAMES; i++) 
            {
            Mat frame=frames_temp[i];
            Mat cframe=frame.clone();
            double opacity = .5;
            int chunk_size = cframe.rows/4;
            if (frame.empty()) break; 
            #pragma omp parallel for
            for (int i = 0; i < cframe.cols; i++) {
                #pragma omp for nowait, schedule(dynamic, chunk_size)
                for (int j = 0; j < cframe.rows; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(j, i);
                    Vec3b &inverse = cframe.at<Vec3b>(cframe.rows-j, cframe.cols-i);
              
                    intensity.val[0] = inverse.val[0]*opacity + intensity.val[0]*(1-opacity);
                    intensity.val[1] = inverse.val[1]*opacity + intensity.val[1]*(1-opacity);
                    intensity.val[2] = inverse.val[2]*opacity + intensity.val[2]*(1-opacity);
    
                }
            }
            newframes_temp[i]=frame;
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
void darken_p(Mat* frames_temp, Mat* newframes_temp, int NUMFRAMES){
    
    cout<<"Darkening...."<<endl;
    #pragma omp parallel for
        for(int i=0;i<NUMFRAMES; i++) 
      
            {
            Mat frame=frames_temp[i];
            Mat cframe=frame.clone();
            if (frame.empty()) break; 
            int chunk_size = cframe.rows/4;
            #pragma omp parallel for
            for (int i = 0; i < cframe.cols; i++) {
                #pragma omp for nowait, schedule(dynamic, chunk_size)
                for (int j = 0; j < cframe.rows; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(j, i);
                    Vec3b &inverse = cframe.at<Vec3b>(j, i);
                    intensity.val[0] = inverse.val[0]>>1;
                    intensity.val[1] = inverse.val[1]>>1;
                    intensity.val[2] = inverse.val[2]>>1;
    
                }
            }
          newframes_temp[i]=frame;
        }

}

void watermark_s(VideoCapture inputVideo, VideoWriter outputVideo, string& watermark_img_file) {
    cout<<"Adding watermark..."<<endl;
        Mat wframe = imread(watermark_img_file);
        double opacity = .25;
        int offset = 100;
        for(;;){
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            Mat copyframe=frame.clone();
            
            if (frame.empty()) break; 

            for (int i = 0; i < wframe.rows; i++) {
                for (int j = 0; j < wframe.cols; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(i+offset, j+offset);
                    Vec3b &watermark = wframe.at<Vec3b>(i, j);
                    intensity.val[0] = watermark.val[0]*opacity + intensity.val[0]*(1-opacity);
                    intensity.val[1] = watermark.val[1]*opacity + intensity.val[1]*(1-opacity);
                    intensity.val[2] = watermark.val[2]*opacity + intensity.val[2]*(1-opacity);
        
                }
            }
           outputVideo.write(frame);
        }
}

void watermark_p(Mat* frames_temp, Mat* newframes_temp, int NUMFRAMES, string& watermark_img_file) {
    cout<<"Adding watermark..."<<endl;
        Mat wframe = imread(watermark_img_file);
        double opacity = .25;
        int offset = 100;
        
        for(int i=0;i<NUMFRAMES; i++) 
            #pragma omp parallel for
            {
            Mat frame=frames_temp[i];
            int chunk_size = frame.cols/4;
            if (frame.empty()) break; 
            #pragma omp parallel for
            for (int i = 0; i < wframe.rows; i++) {
                #pragma omp for nowait, schedule(dynamic, chunk_size)
                for (int j = 0; j < wframe.cols; j++) {
                    Vec3b &intensity = frame.at<Vec3b>(i+offset, j+offset);
                    Vec3b &watermark = wframe.at<Vec3b>(i, j);
                    intensity.val[0] = watermark.val[0]*opacity + intensity.val[0]*(1-opacity);
                    intensity.val[1] = watermark.val[1]*opacity + intensity.val[1]*(1-opacity);
                    intensity.val[2] = watermark.val[2]*opacity + intensity.val[2]*(1-opacity);
        
                }
            }
           newframes_temp[i]=frame;
        }
}

void bw_s(VideoCapture inputVideo, VideoWriter outputVideo) {
    cout << "Black and Whiting..." << endl;
    Mat frame;
    Mat copyFrame;
    uchar pixValue;
    float rconst = 0.2125;
    float gconst = 0.7154;
    float bconst = 0.0721;
    char luminosity;

    for(;;){
        inputVideo >> frame;
        copyFrame = frame;
        if(frame.empty()) break;
        for (int i = 0; i < frame.rows; i++) {
                for (int j = 0; j < frame.cols; j++) {
                        Vec3b &inputPixel = frame.at<Vec3b>(i, j);
                        Vec3b &outputPixel = copyFrame.at<Vec3b>(i, j);
                    
                    //Create luminosity value
                luminosity = (rconst * inputPixel.val[0] + gconst * inputPixel.val[1] + bconst * inputPixel.val[2]);
                outputPixel.val[0] = luminosity;
                outputPixel.val[1] = luminosity;
                outputPixel.val[2] = luminosity;
                    }
        }   
            outputVideo.write(copyFrame);
    }
}

void bw_p(Mat* frames_temp, Mat* newframes_temp, int NUMFRAMES) {
    
    cout << "Black and Whiting..." << endl;
    
    uchar pixValue;
    float rconst = 0.2125;
    float gconst = 0.7154;
    float bconst = 0.0721;
    char luminosity;

    for(int i=0;i<NUMFRAMES; i++) 
        #pragma omp parallel for
        {
        Mat frame=frames_temp[i];
        Mat copyFrame=frame.clone();

            
        if(frame.empty()) break;
        int chunk_size = frame.cols/4;
        #pragma omp parallel for
        for (int i = 0; i < frame.rows; i++) {
                #pragma omp for nowait, schedule(dynamic, chunk_size)
                for (int j = 0; j < frame.cols; j++) {
                        Vec3b &inputPixel = frame.at<Vec3b>(i, j);
                        Vec3b &outputPixel = copyFrame.at<Vec3b>(i, j);
                    
                    //Create luminosity value
                    luminosity = (rconst * inputPixel.val[0] + gconst * inputPixel.val[1] + bconst * inputPixel.val[2]);
                outputPixel.val[0] = luminosity;
                outputPixel.val[1] = luminosity;
                outputPixel.val[2] = luminosity;
                    }
        }   
            newframes_temp[i]=copyFrame;
    }
}

void negative_s(VideoCapture inputVideo, VideoWriter outputVideo) {
    cout << "Negative..." << endl;
    
    uchar pixValue;
    Mat frame;
    Mat copyFrame;

    for(;;){
        inputVideo >> frame;
        Mat copyFrame=frame.clone();
        if(frame.empty()) break;
        for (int i = 0; i < frame.rows; i++) {
                for (int j = 0; j < frame.cols; j++) {
                    Vec3b &inputPixel = frame.at<Vec3b>(i, j);
                    Vec3b &outputPixel = copyFrame.at<Vec3b>(i, j);
                
                    outputPixel.val[0] = 255 - inputPixel.val[0];
                    outputPixel.val[1] = 255 - inputPixel.val[1];
                    outputPixel.val[2] = 255 - inputPixel.val[2];
                }
        }   
            outputVideo.write(copyFrame);
    }
}

void negative_p(Mat* frames_temp, Mat* newframes_temp, int NUMFRAMES) {

    for(int i=0;i<NUMFRAMES; i++) 
        #pragma omp parallel for
        {
        Mat frame=frames_temp[i];
        Mat copyFrame=frame.clone();
           
        if(frame.empty()) break;
        int chunk_size = frame.cols/4;
        #pragma omp parallel for
        for (int i = 0; i < frame.rows; i++) {
                #pragma omp for nowait, schedule(dynamic, chunk_size)
                for (int j = 0; j < frame.cols; j++) {
                    Vec3b &inputPixel = frame.at<Vec3b>(i, j);
                    Vec3b &outputPixel = copyFrame.at<Vec3b>(i, j);
                
                    outputPixel.val[0] = 255 - inputPixel.val[0];
                    outputPixel.val[1] = 255 - inputPixel.val[1];
                    outputPixel.val[2] = 255 - inputPixel.val[2];
                }
        }   
            newframes_temp[i]=frame;
    }
}

/* The sepia filter is a work in progress.
void sepia_s(VideoCapture inputVideo, VideoWriter outputVideo) {
    cout << "Sepia..." << endl;
    Mat frame;
    Mat copyFrame;
    uchar pixValue;

    int tr;
    int tg;
    int tb;
    int r;
    int g;
    int b;

    for(;;){
        inputVideo >> frame;
        copyFrame = frame;
        if(frame.empty()) break;
        #pragma omp parallel for
        for (int i = 0; i < frame.rows; i++) {
                for (int j = 0; j < frame.cols; j++) {
                        Vec3b &in = frame.at<Vec3b>(i, j);
                        Vec3b &out = copyFrame.at<Vec3b>(i, j);
                    
                    //Create sepia values
                tr = (int) (0.299 * in.val[0]) +
                           (0.587 * in.val[1]) +
                           (0.114 * in.val[2]);
                tg = (int) (0.299 * in.val[0]) +
                           (0.587 * in.val[1]) +
                           (0.114 * in.val[2]);
                tb = (int) (0.299 * in.val[0]) +
                           (0.587 * in.val[1]) +
                           (0.114 * in.val[2]);

                // If they are over max value, set to max
                if(tr > 255){ r = 255; } else { r = tr; }   
                if(tg > 255){ g = 255; } else { g = tg; }   
                if(tb > 255){ b = 255; } else { b = tb; }   

                out.val[0] = r;
                out.val[1] = g;
                out.val[2] = b;
                    }
        }   
            outputVideo.write(copyFrame);
    }
}

void sepia_p(Mat* frames_temp, Mat* newframes_temp, int NUMFRAMES) {

    cout << "Sepia..." << endl;
    
    uchar pixValue;

    int tr;
    int tg;
    int tb;
    int r;
    int g;
    int b;

    for(int i=0;i<NUMFRAMES; i++) 
        #pragma omp parallel for
        {
        Mat frame=frames_temp[i];
        Mat copyFrame=frame.clone();
        if(frame.empty()) break;
        int chunk_size = frame.cols/4;
        #pragma omp parallel for
        for (int i = 0; i < frame.rows; i++) {
                #pragma omp for nowait, schedule(dynamic, chunk_size)
                for (int j = 0; j < frame.cols; j++) {
                        Vec3b &in = frame.at<Vec3b>(i, j);
                        Vec3b &out = copyFrame.at<Vec3b>(i, j);
                    
                    //Create sepia values
                tr = (int) (0.299 * in.val[0]) +
                           (0.587 * in.val[1]) +
                           (0.114 * in.val[2]);
                tg = (int) (0.299 * in.val[0]) +
                           (0.587 * in.val[1]) +
                           (0.114 * in.val[2]);
                tb = (int) (0.299 * in.val[0]) +
                           (0.587 * in.val[1]) +
                           (0.114 * in.val[2]);

                // If they are over max value, set to max
                if(tr > 255){ r = 255; } else { r = tr; }   
                if(tg > 255){ g = 255; } else { g = tg; }   
                if(tb > 255){ b = 255; } else { b = tb; }   

                out.val[0] = r;
                out.val[1] = g;
                out.val[2] = b;
                    }
        }   
            newframes_temp[i]=copyFrame;
    }
}
*/
void blur_s(VideoCapture inputVideo, VideoWriter outputVideo) {
    cout<<"Blurry...."<<endl;

        auto start = Clock::now();
        Mat frame;
        Mat copyFrame;
        for(;;) 
            {
            inputVideo >> frame;
            copyFrame = frame;
            if (frame.empty()) break; 

            uchar pixValue;

            for ( int i = 1; i < 31; i = i + 2 ) {
                GaussianBlur( copyFrame, frame, Size( i, i ), 0, 0 );
            }

            outputVideo.write(frame);
        }
        auto stop = Clock::now();
        std::cout << "Timer: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
                  << " milliseconds\n";
}

void blur_p(Mat* frames_temp, Mat* newframes_temp, int NUMFRAMES) {

    cout<<"Blurry...."<<endl;

        auto start = Clock::now();
        
        int kernel = 31;
        int chunk_size = kernel/4;
        for(int i=0;i<NUMFRAMES; i++) 
            #pragma omp parallel for
            {
            Mat frame=frames_temp[i];
            Mat copyFrame=frame.clone();
            if (frame.empty()) break; 

            uchar pixValue;
            #pragma omp for nowait, schedule(dynamic, chunk_size)
            for ( int i = 1; i < kernel; i = i + 2 ) {
                GaussianBlur( copyFrame, frame, Size( i, i ), 0, 0 );
            }

            newframes_temp[i]=frame;
        }
        auto stop = Clock::now();
        std::cout << "Timer: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
                  << " milliseconds\n";
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
    
    int NUMFRAMES=inputVideo.get(CV_CAP_PROP_FRAME_COUNT);
    VideoWriter outputVideo;                                        // Open the output
    outputVideo.open(NAME, ex=0, inputVideo.get(CV_CAP_PROP_FPS), S, true);
    
    if (!outputVideo.isOpened())
    {
        cout  << "Could not open the output video for write: " << source << endl;
        return -1;
    }

    cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
         << " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT) << endl;
    
    //watermark error message
    if(Command=="watermark"){
        if(argc < 5) {
            cout  << "Not enough parameters. Don't forget image file name!" << endl;
            return -1;
        }
    }

    if(processing=="-serial"){
        auto t1 = Clock::now();
        if(Command=="invert")
            invert_s(inputVideo, outputVideo);
        else if(Command=="self_overlay")
            self_overlay_s(inputVideo, outputVideo);
        else if(Command=="darken")
            darken_s(inputVideo, outputVideo);
        else if(Command=="watermark")
            watermark_s(inputVideo, outputVideo, watermark_img_file);
        else if(Command=="bw")
            bw_s(inputVideo, outputVideo);
        else if(Command=="negative")
            negative_s(inputVideo, outputVideo);
        else if(Command=="blur")
            blur_s(inputVideo, outputVideo);
        else{
            inputVideo.release();
            outputVideo.release();
            cout << "Bad input, see usage" << endl;
            return 0;
        }
        auto t2 = Clock::now();
    std::cout << "Serial Runtime: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
    << " milliseconds" << std::endl;
    }
    if(processing=="-parallel"){
        // Mat frames_temp[NUMFRAMES];
        // Mat newframes_temp[NUMFRAMES];  
        Mat* frames_temp;
        frames_temp= new Mat[NUMFRAMES];
        Mat* newframes_temp;
        newframes_temp= new Mat[NUMFRAMES];
        for(int i=0;i<NUMFRAMES; i++) 
            {
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            if (frame.empty()) break; 
            frames_temp[i]=frame;
        }
        auto t1 = Clock::now();
        if(Command=="invert"){
            invert_p(frames_temp, newframes_temp, NUMFRAMES);
            
        }
        else if(Command=="self_overlay"){
            self_overlay_p(frames_temp, newframes_temp, NUMFRAMES); 
        }
        else if(Command=="darken"){
            darken_p(frames_temp, newframes_temp, NUMFRAMES);   
        }
        else if(Command=="watermark"){
            watermark_p(frames_temp, newframes_temp, NUMFRAMES, watermark_img_file);    
        }
        else if(Command=="bw"){
            bw_p(frames_temp, newframes_temp, NUMFRAMES);   
        }
        else if(Command=="negative"){
            negative_p(frames_temp, newframes_temp, NUMFRAMES); 
        }
        else if(Command=="blur"){
            blur_p(frames_temp, newframes_temp, NUMFRAMES);    
        }
        else{
            inputVideo.release();
            outputVideo.release();
            cout << "Bad input, see usage" << endl;
            return 0;
        }
        for(int i=0;i<NUMFRAMES; i++) 
            {
            Mat frame=newframes_temp[i];
            if (frame.empty()) break; 

            outputVideo.write(frame);
        }
        auto t2 = Clock::now();
    std::cout << "Parallel Runtime: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
    << " milliseconds" << std::endl;
        

    }
    

    inputVideo.release();
    outputVideo.release();
    cout << "Finished writing" << endl;
    return 0;
}
