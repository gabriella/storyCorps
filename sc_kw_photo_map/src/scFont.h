//
//  scFont.h
//  scFont
//
//  Created by Nick Yulman on 3/13/13.
//
//

#ifndef __scFont__scFont__
#define __scFont__scFont__

#include <iostream>
#include "ofMain.h"
#include "scChar.h"



class scFont{
    
    public:

    ofVec2f dims;
    ofVec2f nSize;
    ofVec2f nSpace;
    string nShape;
    vector<scChar> chars;
    vector<vector<ofVec2f> > charPos;  //vector of position vectors
    
    
    scChar letters[26];
    scChar qMark;
    
    
    void init(int xDim, int yDim, int nDimX, int nDimY, float nSpaceX, float nSpaceY, string _shape);
    
    
    

};

#endif /* defined(__scFont__scFont__) */
