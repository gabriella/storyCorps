#include "testApp.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>



using namespace std;

//--------------------------------------------------------------
void testApp::setup(){
    
   

	dir.listDir("images/of_logos/");
	dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    Minput = "60061";//sample string to input into the zip code data function

   ofVec2f zipcode = loadData( Minput); //function that takes a zip code as input, returns an x,y pair lat / longitude from a text file based on zip, lat, long and scales it to an image
    
    cout<<zipcode;//prints out the result
    
	//allocate the vector to have as many ofImages as files
	if( dir.size() ){
		images.assign(dir.size(), ofImage());
	}

	// you can now iterate through the files and load them into the ofImage vector
	for(int i = 0; i < (int)dir.size(); i++){
		images[i].loadImage(dir.getPath(i));
	}
	currentImage = 0;

	ofBackground(ofColor::white);
}
//--------------------------------------------------------------
ofVec2f testApp::loadData(string input){
    ifstream file;//initiates input data stream from a file 
    string line; //initiates string object called line to read each line  from the text 
    
    file.open(ofToDataPath("zips.csv").c_str());//open text file
    
   
    if(!file.is_open())
    {
        cout<<" can't open the file ";
        return;
    }
    
    while(!file.eof())//file!=NULL)
    {
        getline(file, line);//extract characters from the file and stores them into the string line 
        //cout<<line<<endl;//print out the data
        
        fileTxt = ofSplitString(line, "\"");//delete the ", get each line as a vector of words 
               
        for(int j=0;j<fileTxt.size();j++)//step through the words of each line

        {
             if(j>13)//if there are enough elements in each line that ensure there is a zip, lat, long..... 
             {
           // cout<<"j= "<<j<<"   "<<fileTxt[1]<<":zip " <<  fileTxt[7]<<":lat "<<fileTxt[9]<<":long"<<endl;
                 if(input ==fileTxt[1])//if the input string zip code is equal to one of the zips in the csv 
                 {
                     float latitude = ofToFloat(fileTxt[7]);//get the latitude which is the 7th element of the line
                     float longitude =ofToFloat(fileTxt[9]);//get the longitude which is the 9th element in the vector 
                    return ofVec2f(latitude, longitude);//return the lat and longitude
                 }
           }
        }
        }
    file.close();//close the file
    cout<<"file closed";  
    
    }


//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	if (dir.size() > 0){
		ofSetColor(ofColor::white);
		images[currentImage].draw(300,50);

		ofSetColor(ofColor::gray);
		string pathInfo = dir.getName(currentImage) + " " + dir.getPath(currentImage) + "\n\n" +
			"press any key to advance current image\n\n" +
			"many thanks to hikaru furuhashi for the OFs";
		ofDrawBitmapString(pathInfo, 300, images[currentImage].getHeight() + 80);
	}

	ofSetColor(ofColor::gray);
	for(int i = 0; i < (int)dir.size(); i++){
		if(i == currentImage) {
			ofSetColor(ofColor::red);
		}	else {
			ofSetColor(ofColor::black);
		}
		string fileInfo = "file " + ofToString(i + 1) + " = " + dir.getName(i);
		ofDrawBitmapString(fileInfo, 50,i * 20 + 50);
	}

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (dir.size() > 0){
		currentImage++;
		currentImage %= dir.size();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
