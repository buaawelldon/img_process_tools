#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "dirent.h"

using namespace std;
using namespace cv;

int main(int argc, char ** argv){
	if((argc<3)||argc>4){
		cout<<"please follow format of input: 0 imgpath| 1 imgfolderpath.";
		return -1;
	}
	cout<<" please input the size you want: width and height"<<endl;
    
    int h,w;
	cin>>w>>h;
	cout<<"the size you want is "<<w<<"x "<<h<<endl;
    Size sz(w,h);
    //parsing the input

    //single img process
    string todo(argv[1]);
    if (todo==string("0")){
    	Mat img=imread(argv[2]);
    	//imshow("show img",img);
        Mat dst;
        resize(img,dst,sz);
        imwrite("resized.jpg",dst);
    }

    //now we deal with the folder
    if(todo==string("1")){
    	//oprater pointer
    	DIR * dir;
        //filename pointer
        dirent *pdir;

        dir =opendir(argv[2]);
        //return NULL when file end
        while(pdir=readdir(dir)){
        	//cout<<pdir->d_name<<endl;
        	string filename(pdir->d_name);
        	if(filename.find(".jpg")>0){
        		//cout<<filename<<endl;
        		if( (filename[0]=='a')||(filename[0]=='n')||(filename[0]=='h') ){
                    string pathprefix(argv[2]);
                    Mat img=imread(pathprefix+ filename);
    	            //imshow("show img",img);
                    cout<<filename<<endl;
                    Mat dst;
                    resize(img,dst,sz);
                    imwrite(string(argv[3])+filename,dst);

        		}
        	}
  
        }
    }


	return 0;
}