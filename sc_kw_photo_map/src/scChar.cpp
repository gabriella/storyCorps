//
//  scChar.cpp
//  scFont
//
//  Created by Nick Yulman on 3/13/13.
//
//

#include "scChar.h"

//scChar::scChar(int _xDim,int _yDim){
//}


void scChar::init(char _name, ofVec2f _dims, ofVec2f _nDims, ofVec2f _spacing, vector<ofVec2f> _positions, string _shape){
    numNodes = _positions.size();
    name = _name;
    cPos = ofVec2f(100,100);
    dims = _dims;
    nDims = _nDims;
    spacing = _spacing;
    nShape = _shape; //does the char need to know this?
 
    
    
    for(int i = 0; i<numNodes; i++){
        positions.push_back(_positions[i]);
        node n;
        n.init(cPos+positions[i]*nDims*spacing);
        nodes.push_back(n);
    }
}

void scChar::display(){
    for(int i = 0; i<numNodes; i++){
        nodes[i].display();
    }
}

void scChar::update(){
    
    for(int i = 0; i<numNodes; i++){
        nodes[i].pos = cPos+positions[i]*nDims*spacing;
    }
    
    
    for(int i = 0; i<numNodes; i++){
        nodes[i].update();
    }
}