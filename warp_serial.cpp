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
        << "./video-write inputvideoName <command> <watermark image file name>"                              << endl

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

   } else if (Command == "bw"){
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

   } else if (Command == "negative"){
	cout << "Negative..." << endl;
	Mat frame;
	Mat copyFrame;
	uchar pixValue;

	for(;;){
		inputVideo >> frame;
		copyFrame = frame;
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

	} else if (Command == "sepia"){
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
		for (int i = 0; i < frame.rows; i++) {
	        	for (int j = 0; j < frame.cols; j++) {
        	    		Vec3b &in = frame.at<Vec3b>(i, j);
	        	        Vec3b &out = copyFrame.at<Vec3b>(i, j);
	                
    				//Create sepia values
				tr = (int) (0.393 * in.val[0]) +
				     	   (0.769 * in.val[1]) +
				     	   (0.189 * in.val[2]);
				tg = (int) (0.349 * in.val[0]) +
				       	   (0.686 * in.val[1]) +
				     	   (0.168 * in.val[2]);
				tb = (int) (0.272 * in.val[0]) +
				           (0.534 * in.val[1]) +
				    	   (0.131 * in.val[2]);

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


        Mat cframe(frame.rows, frame.cols, frame.type());
        
	Mat newframe(frame.rows, frame.cols, frame.type()); //new frame same size as original
        int halfrow = frame.rows/2;
	int halfcol = frame.cols/2; 
        Mat q1(halfrow, halfcol, frame.type());
        Mat q2(halfrow, halfcol, frame.type());
        Mat q3(halfrow, halfcol, frame.type());
        Mat q4(halfrow, halfcol, frame.type());

	resize(frame, q1, q1.size(), 0, 0, INTER_AREA);
	resize(frame, q2, q2.size(), 0, 0, INTER_AREA);
	resize(frame, q3, q3.size(), 0, 0, INTER_AREA);
	resize(frame, q4, q4.size(), 0, 0, INTER_AREA);
 	
	int offset = 32;	

        for(int i = 0; i < halfrow; i++){
	    for(int j = 0; j < halfcol; j++){	
		Vec3b &q1color = q1.at<Vec3b>(j,i);
		Vec3b &q2color = q2.at<Vec3b>(j,i);
		Vec3b &q3color = q3.at<Vec3b>(j,i);
		Vec3b &q4color = q4.at<Vec3b>(j,i);

		q1color.val[0] += offset;
		q1color.val[1] += offset;
		q1color.val[2] += offset;
		q2color.val[0] += (offset*2);
		q2color.val[1] += (offset*2);
		q2color.val[2] += (offset*2);
		q3color.val[0] += (offset*3);
		q3color.val[1] += (offset*3);
		q3color.val[2] += (offset*3);
		q4color.val[0] += (offset*4);
		q4color.val[1] += (offset*4);
		q4color.val[2] += (offset*4);
	    }
	}
	for(int i = 0; i < halfrow; i++){
	    for(int j = 0; j < halfcol; j++){
		Vec3b &newframecolor = newframe.at<Vec3b>(j,i);
		Vec3b &q1color = q1.at<Vec3b>(j, i);
		newframecolor.val[0] = q1color.val[0];
		newframecolor.val[1] = q1color.val[1];
		newframecolor.val[2] = q1color.val[2];
	    }
	}
	for(int i = halfrow; i < (halfrow*2); i++){
	    for(int j = 0; j < halfcol; j++){
		Vec3b &newframecolor = newframe.at<Vec3b>(j,i);
		Vec3b &q2color = q2.at<Vec3b>(j, i);
		newframecolor.val[0] = q2color.val[0];
		newframecolor.val[1] = q2color.val[1];
		newframecolor.val[2] = q2color.val[2];
	    }
	}
	for(int i = 0; i < halfrow; i++){
	    for(int j = halfcol; j < (halfcol*2); j++){
		Vec3b &newframecolor = newframe.at<Vec3b>(j,i);
		Vec3b &q3color = q3.at<Vec3b>(j, i);
		newframecolor.val[0] = q3color.val[0];
		newframecolor.val[1] = q3color.val[1];
		newframecolor.val[2] = q3color.val[2];
	    }
	}
	for(int i = halfrow; i < (halfrow*2); i++){
	    for(int j = halfcol; j < (halfcol*2); j++){
		Vec3b &newframecolor = newframe.at<Vec3b>(j,i);
		Vec3b &q4color = q4.at<Vec3b>(j, i);
		newframecolor.val[0] = q4color.val[0];
		newframecolor.val[1] = q4color.val[1];
		newframecolor.val[2] = q4color.val[2];
	    }
	}
	outputVideo.write(frame);
    }
    }	

    inputVideo.release();
    outputVideo.release();
    cout << "Finished writing" << endl;
    return 0;
}
