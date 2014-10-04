#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <fstream>
#include "string.h"

using namespace cv;
using namespace std;

string testername;
bool brecordable;
string showface="showface";
CascadeClassifier face_casecade;
int numbersofimg;

//display the scene
void detectanddisplay(Mat frame);
//save the images
void savefaceimgs(char * SaveFileName, int SecondInterval );


//the main function
int main(int argc, char ** argv){
	


	//1. load face detection
	String face_casecade_name="haarcascade_frontalface_alt2.xml";
	if(!face_casecade.load(face_casecade_name)){
		cerr<<"error loading the face detector!";
		return -1;
	}

    //initialize the recording parameter
    cout<<"type name of the person: ";
    cin>>testername;
    cout<<"Do you want record "<<testername<<" \'s face ?  N/y"<<endl;
    brecordable=false;
    char keyin;
    cin>>keyin;
    if (keyin=='y') brecordable=true;
	//2. capture the video stream
    //VideoCapture  capture(-1);
	Mat frame;
    //if (!capture.isOpened()){
    //	return -1;
    //	cerr<<"cam is not open..."<<endl;
    //}
    CvCapture * capture;
    capture=cvCaptureFromCAM(-1);
    int img_counter=0;
    while(true){
    	//capture>>frame;
    	Mat frameroi;
    	frame=cvQueryFrame(capture);
    	if(!frame.empty()){
    		//detectanddisplay(frame);
    		vector<Rect> faces;
	        Mat frame_gray;
	        cvtColor(frame,frame_gray, CV_BGR2GRAY);
	        equalizeHist(frame_gray, frame_gray);
    
            //detect
            face_casecade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30,30));
            for(int i=0;i< faces.size();i++){
    	        rectangle(frame, faces[i], Scalar(255,0,255));        
                //imwrite(testername,frame(Range(faces[i].x,faces[i].x+faces[i].width),Range(faces[i].y,faces[i].y+faces[i].height)));
                string imgname="DATA/"+testername+to_string(++img_counter)+".jpg";
                frameroi=frame(faces[i]);
                
                if(brecordable)imwrite(imgname,frameroi);
                imshow("roiimage",frameroi);
            }

            //define how many images you wanna take
            if(img_counter==100)return 1;

            // show the instant scene
            imshow(showface,frame);
    	    
    	}
    	else{
    		cout<<"no frame captured...";
    		//capture.release();
    		break;
    	}
    	int c = waitKey(100);
        if( (char)c == 'c' ) { break; }

    }	

    return 1;
}


