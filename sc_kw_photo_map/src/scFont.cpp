//
//  scFont.cpp
//  scFont
//
//  Created by Nick Yulman on 3/13/13.
//
//

#include "scFont.h"

void scFont::init(int xDim, int yDim, int nDimX, int nDimY, float nSpaceX, float nSpaceY, string _shape){
    
    
    //define charcter positions here later store this in a text file maybe
   
    //5 x 7 grid
    
    vector<ofVec2f> a;
    a.push_back(ofVec2f(2,0));
    //a.push_back(ofVec2f(.75,.75));
    //a.push_back(ofVec2f(3.25,.75));
    a.push_back(ofVec2f(.75,1));
    a.push_back(ofVec2f(3.25,1));
    a.push_back(ofVec2f(0,2));
    a.push_back(ofVec2f(4,2));
    for(int i = 0; i<5; i++){
    a.push_back(ofVec2f(i,3));
    }
    a.push_back(ofVec2f(0,4));
    a.push_back(ofVec2f(4,4));
    a.push_back(ofVec2f(0,5));
    a.push_back(ofVec2f(4,5));
    a.push_back(ofVec2f(0,6));
    a.push_back(ofVec2f(4,6));
    
    charPos.push_back(a);
    charPos.push_back(a);
      charPos.push_back(a);
    

    
    //define the characters
    
    
    for(int i=0; i<3; i++){
    scChar let;
    
    letters[i] = let;
        letters[i].init(i, ofVec2f(xDim,yDim), ofVec2f(nDimX,nDimY), ofVec2f(nSpaceX,nSpaceY), charPos[i], _shape);

        }

}