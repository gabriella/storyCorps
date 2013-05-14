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
    Minput = "60002";
    
   //ofVec2f zipcode = loadData( );
    string zipcode = loadData( Minput);
    cout<<zipcode;
    
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
string testApp::loadData(string input){
    ifstream file;
    string line;
   
    cout<<input<<endl;
    
    file.open(ofToDataPath("zips.csv").c_str());//open text file
   
    if(!file.is_open())
    {
        cout<<" can't open the file ";
    }
    
    while(!file.eof())//file!=NULL)
    {
        getline(file, line);
       // cout<<line<<endl;
        fileTxt = ofSplitString(line, "\"");
        
        for(int j=0;j<fileTxt.size();j++)

        {
             if(j>13){
           // cout<<fileTxt[1]<<":zip " <<  fileTxt[7]<<":lat "<<fileTxt[9]<<":long"<<endl;
                 if(input ==fileTxt[1]){
                     
                     cout<<"got it"<<fileTxt[7]<<endl;
                     return fileTxt[7];
                 }
           }
        }
        }
    file.close();
    cout<<"file closed";
   
    
    //int d1;
   // stringstream(fileTxt[7])<<d1;
    //cout<<fileTxt[7]<<" is the string"<<d1<<"  : is the double"<<endl; 
   // float f = std::atof(*fileTxt[7]);    
   // return ofVec2f((float)fileTxt[7], (float)fileTxt[9]);
    
   
    
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
