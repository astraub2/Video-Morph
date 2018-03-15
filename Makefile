LIB=-L/usr/local/lib
INC=-I/usr/local/include/opencv -I/usr/local/include/opencv2

all:
	g++ -o video-write -std=c++11 $(LIB) $(INC) warp_serial.cpp -lopencv_dnn -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_viz -lopencv_core

clean:
	rm -rf *.o
	rm -rf *_out.avi
	rm -rf video-write