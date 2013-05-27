//
//  node.cpp
//  scFont
//
//  Created by Nick Yulman on 3/13/13.
//
//

#include "node.h"

void node::init(ofVec2f _pos){
   
    scPhoto photo;
    //photo = _photo;
  // c = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
pos = _pos;
   tPos = _pos;
  // shape = _shape;
   //dims = _dims;
}


void node::display(){
    ofSetColor(c);
    if(shape == "square"){
        ofRect(pos.x,pos.y,dims.x,dims.y);
    }
    
    if(shape == "ellipse"){
          ofSetColor(c);
        ofEllipse(pos.x,pos.y,dims.x,dims.y);
    }

}


void node::repos(ofVec2f _pos){

    pos = _pos;
    
    
}

void node::update(){
    
    //pos = _pos;
    
    
}