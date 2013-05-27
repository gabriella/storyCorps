//
//  scChar.h
//  scFont
//
//  Created by Nick Yulman on 3/13/13.
//
//



#ifndef __scFont__scChar__
#define __scFont__scChar__



#include <iostream>
#include "node.h"
#include "ofMain.h"


class scChar{

    //scChar is a specific manifestation of the master characters defined in font made up of nodes.
    
public:
   
    ofVec2f cPos; //character master position.  basis for locating nodes
    ofVec2f dims; //how many nodes in x & y. inherit from Font
    ofVec2f nDims; //how big are the nodes. inherit from Font
    ofVec2f spacing; // how spaced out are the node. inherit from Font
    
    char name;  //what char is it?
    int numNodes;  //how many nodes in the char
    string nShape;
    
    
    vector<ofVec2f> positions; //initializer from font will feed this;
    vector<node> nodes;      //a place to store the nodes
    

    
    
    void init(char _name, ofVec2f _dims, ofVec2f nDims, ofVec2f _spacing, vector<ofVec2f> _positions, string _shape);
    void display();
    void update();
    
    

};



#endif /* defined(__scFont__scChar__) */
