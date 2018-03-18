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
        << "Available commands: invert, bw, sepia, watermark, darken, self_overlay" << endl
        << "./video-write inputvideoName <command> watermarkimage"                              << endl

        << endl;
}

int main(int argc, char *argv[])
{
    help();

    if (argc < 3)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    const string source  = argv[1];           // the source file name
    const string Command = argv[2];

    string watermark_img_file;
    if (argc == 4) 
    {
        watermark_img_file = argv[3];          //watermark image file name
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
	        Mat frame;
	        inputVideo >> frame; // get a new frame from camera
	        Mat cframe;
	        inputVideo >> cframe;
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
    
    else if(Command=="blur"){

    	cout<<"Blurry...."<<endl;
    	for(;;) 
        	{
	        Mat frame;
	        inputVideo >> frame; // get a new frame from camera
	        Mat cframe;
	        inputVideo >> cframe;
	        if (frame.empty()) break; 

	        uchar pixValue;
	        for (int i = 0; i < cframe.cols; i=i+2) {
            		for (int j = 0; j < cframe.rows; j=j+2) {
				GaussianBlur(cframe, frame, Size(i,j), 0, 0);	
	             }
	        }
	       outputVideo.write(frame);
	    }

   } else if (Command == "bw"){
	cout << "Black and Whiting..." << endl;

	Mat frame;
	Mat cframe;

	uchar pixValue;
	float rconst = 0.2125;
	float gconst = 0.7154;
	float bconst = 0.0721;

	for(;;){
		inputVideo >> frame;
		inputVideo >> cframe;
		if(frame.empty()) break;

		for (int i = 0; i < cframe.cols; i++) {
  	        	for (int j = 0; j < cframe.rows; j++) {

				Vec3b &outframe = frame.at<Vec3b>(i, j);
                		Vec3b &inframe = cframe.at<Vec3b>(i, j);

				// Change each color value to black and white	
				outframe.val[0] = (int)(rconst * inframe.val[0]);
				outframe.val[1] = (int)(rconst * inframe.val[1]);
				outframe.val[2] = (int)(rconst * inframe.val[2]);
			}
		}	
	       outputVideo.write(frame);
	}

    } else if (Command == "watermark") {

        cout<<"Adding watermark..."<<endl;
        Mat wframe = imread(watermark_img_file);
        double opacity = .25;
        int offset = 100;
        for(;;){
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            
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
    else if(Command=="darken"){

        cout<<"Darkening...."<<endl;
        for(;;) 
            {
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            Mat cframe;
            inputVideo >> cframe;
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
    else if(Command=="self_overlay"){

        cout<<"Overlaying...."<<endl;
        for(;;) 
            {
            Mat frame;
            inputVideo >> frame; // get a new frame from camera
            Mat cframe;
            inputVideo >> cframe;
            if (frame.empty()) break; 

            for (int i = 0; i < cframe.cols; i+=2) {
            for (int j = 0; j < cframe.rows; j+=2) {
                  Vec3b &intensity = frame.at<Vec3b>(j, i);
                    Vec3b &inverse = cframe.at<Vec3b>(cframe.rows-j, cframe.cols-i);
                    intensity.val[0] = inverse.val[0];
                    intensity.val[1] = inverse.val[1];
                    intensity.val[2] = inverse.val[2];
    
                 }
            }
            for (int i = 1; i < cframe.cols; i+=2) {
            for (int j = 1; j < cframe.rows; j+=2) {
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
    else if(Command == "andy"){
    
        cout << "Making art...." << endl;
	for(;;){
        Mat frame;
	inputVideo >> frame;
	if (frame.empty()) break;

        Mat cframe(frame.rows, frame.cols);
        
	Mat newframe(frame.rows, frame.cols); //new frame same size as original
        int halfrow = frame.rows/2;
	int halfcol = frame.cols/2; 
        Mat q1(halfrow, halfcol);
        Mat q2(halfrow, halfcol);
        Mat q3(halfrow, halfcol);
        Mat q4(halfrow, halfcol);

	resize(frame, q1, q1.size(), 0, 0, interpolation);
	resize(frame, q2, q2.size(), 0, 0, interpolation);
	resize(frame, q3, q3.size(), 0, 0, interpolation);
	resize(frame, q4, dst.size(), 0, 0, interpolation);
	
        for(int i = 0; i < halfrow; i++){
	    for(int j = 0; j < halfcol; j++){	
		Vec3b &q1color = q1.at<Vec3b>(j,i);
		Vec3b &q2color = q2.at<Vec3b>(j,i);
		Vec3b &q3color = q3.at<Vec3b>(j,i);
		Vec3b &q4color = q4.at<Vec3b>(j,i);
    }	

    inputVideo.release();
    outputVideo.release();
    cout << "Finished writing" << endl;
    return 0;
}
