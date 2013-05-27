//
//  photo.h
//  SC_image_keyword
//
//  Created by Nick Yulman on 1/22/13.
//
//

#ifndef SC_image_keyword_scPhoto_h
#define SC_image_keyword_scPhoto_h
#include "ofMain.h"
#include <iostream>
#include <math.h>
#include "zipcodes.h"


class scPhoto {
public:
    
//variables
    
    string interviewID;
    string zip;// = "60002";
    ofImage image;
    ofImage pImage;
    
    
    ofVec2f pos; //original position of the dot
    ofVec2f tPos;  //targed position
    string shape;  //rect or ellpise
    string tShape;
    
    ofVec2f dims;
    ofVec2f tDims;
    
    zipcodes zipcodes;
    
    
    int yOffSet;
    float x,y; //position
    //ofVec2f cent;
    float xw, yh;
    float xT, yT; //position targets;
    float textScale;
    float tTextScale;
    
    
    //int w, h; //width & height
    //int wT, hT;// width & height Targets;
    
    float easeVal=.01;
    ofVec2f ease;
    float dimEase;
    
    //fade vars
    float alphaVal;
    float fadeVal=1;
    
    float maskAlpha;
    float tMaskAlpha;
    
    bool fade;
    bool shade;
    bool shadeOn;
    bool maskFade;

    
    
    
    ofVec2f zipLoc;//this is the zipcode that is now random , initial point location that then heads to the target point loc
    
    //to start centered in map
    //ofVec2f pointLoc=ofVec2f(ofGetWidth()*.75,ofGetHeight()*.75);
    //to start at photo
    ofVec2f pointLoc=pos;
    //pos is the position of the IMAGE; which is the initial position of the dot 
    
    
    ofVec2f tPointLoc=pointLoc;//use this for the target position for the x,y after receiving a zipcode; it is equal to pointLoc which needs to be = to the point on the map based on the scale
    float pointAlpha=0;
    float tPointAlpha=0;
    int pointSize=10;
    ofColor pointColor =255;
    //correspond to points mapped on the
   // getLocation accept zip and assign pointLocation based on that
    //interview ID corresponds to photo
    //interviewData class contains a phoot
    
   ofVec2f getLocation(string Mzipcode);//takes a string zipcode value from the data class interviewID object,  id.Zip = interviewZip;
    //returns an x,y position based on mapped image
    string Mzipcode = zip;//just for the sake of trying, I'm assigning zip up above to equal "60002" and see that the getLocation function returns a scaled x,y position
    
       
//constructor
   // scPhoto(string _file, int _x, int _y, int _w, int _h);
    //scPhoto(, float _x, float _y, int _w, int _h, float _easeVal);
//methods
    void init(ofImage _image, ofVec2f _pos, ofVec2f _dims);
    void init(string _interviewID, ofVec2f _pos, ofVec2f _dims);
    void display();
    void resize(ofVec2f _dims);
    void repos(ofVec2f _pos);
    void mask();
    void process();
    void update();
    void draw();
    void rePos(float _x, float _y);
    void reSize(int _w, int _h);
    void checkMouse(int _x,int _y);
    void shapeTrans(string _shape);
    void drawPoint();
    
    
    
};

#endif
