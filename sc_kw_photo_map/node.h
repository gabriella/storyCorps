//
//  node.h
//  scFont
//
//  Created by Nick Yulman on 3/13/13.
//
//

#ifndef __scFont__node__
#define __scFont__node__

#include <iostream>
#include "ofMain.h"
#include "scPhoto.h"

class node{

public:
    
    //vars
    
    
    scPhoto photo;
    
    ofColor c;
    ofVec2f pos;
    ofVec2f tPos;  //targed position
    string shape;  //rect or ellpise
    ofVec2f dims;
    
    //we'll have and image too later
    //constructor
   // node();
    
    void init(ofVec2f _pos);
    void display();
    void update();
    void resize(ofVec2f _dims);
    void repos(ofVec2f _pos);

};

#endif /* defined(__scFont__node__) */
