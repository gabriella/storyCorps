//
//  photo.cpp
//  SC_image_keyword
//
//  Created by Nick Yulman on 1/22/13.
//
//

#include "scPhoto.h"

//constructor
//is it better to load directly here or pass in a preloaded ofImage?
//scPhoto::scPhoto(string _file, int _x, int _y, int _w, int _h)
//scPhoto::scPhoto(ofImage _image, float _x, float _y, int _w, int _h, float _easeVal)


//version of initializer that takes interview ID parameter for loading photo.
void scPhoto:: init(string _interviewID, ofVec2f _pos, ofVec2f _dims){
    //image = _image;
    
    interviewID=_interviewID;
    pos = _pos;
    tPos = _pos;
    dims = _dims;
    yOffSet = 10;
    //shape = "circ";
    shape = "rect";
    tShape = shape;
    
    textScale =1;
    tTextScale =textScale;
    
    if(shape == "rect"){
        maskAlpha = 255;
    }
    else
        maskAlpha =0;
    
    
    //get zipcode location
    ofVec2f zLoc=ofVec2f(ofRandom(ofGetWidth()/2,ofGetWidth()),ofRandom(ofGetHeight()/2,ofGetHeight()));
    
    zipLoc=zLoc;
    getLocation("60064");//just a test of the function to pass in zip and get x,y pair
    
    //initialize variables
  //  image.loadImage(interviewID);
    //image = _image;
    //image.resize(_w,_h);
    tPos = pos;
    tDims = dims;
    
    pointLoc.x= ofGetWidth()/2;
    pointLoc.y= ofGetHeight()/2;
    
    ease = ofVec2f(10,10);
    alphaVal = 255;
    fade = false;
    shade = false;
}



//version of initializer that takes a pre loaded image
void scPhoto:: init(ofImage _image, ofVec2f _pos, ofVec2f _dims){
    image = _image;
    pos = _pos;
    tPos = _pos;
    dims = _dims;
    yOffSet = 10;
    //shape = "circ";
    shape = "rect";
    tShape = shape;
    
    textScale =1;
    tTextScale =textScale;
    
    if(shape == "rect"){
        maskAlpha = 255;
    }
    else
        maskAlpha =0;
    
    
    //get zipcode location
    ofVec2f zLoc=ofVec2f(ofRandom(ofGetWidth()/2,ofGetWidth()),ofRandom(ofGetHeight()/2,ofGetHeight()));
    
    zipLoc=zLoc;
   // getLocation("60064");//just a test of the function to pass in zip and get x,y pair
    
    //initialize variables
    //image.loadImage(_file);
    image = _image;
    //image.resize(_w,_h);
    tPos = pos;
    tDims = dims;
    
    
    ease = ofVec2f(10,10);
    alphaVal = 255;
    fade = false;
    shade = false;
}


void scPhoto::draw(){
    
    ofEnableAlphaBlending();
    ofFill();
    
    ofSetCircleResolution(360);
    //    ofSetColor(ofRandom(150,255),ofRandom(70),ofRandom(40),alphaVal);
    //
    //    if(shape=="circ"){
    //    ofCircle(pos.x+dims.x/2,pos.y+dims.y/2-yOffSet,dims.x/2+10);
    //    }
    //
    
    
    ofSetColor(255,255,255,alphaVal);
    if(image.isAllocated()){
    
    image.draw(pos.x,pos.y,dims.x*textScale,dims.y*textScale);
    //ofNoFill();
    //ofSetLineWidth(5);
    
    // ofCircle(x+w/2,y+h/2-10, w/2);
    
    ofDisableAlphaBlending();
    ofEnableAlphaBlending();
    ofSetColor(255,255,255,255-alphaVal);
    ofFill();
    //ofRect(x,y,w,h);
    ofDisableAlphaBlending();
    }
    
    if(shade){
        ofEnableAlphaBlending();
        ofFill();
        ofSetColor(0,0,0,160);
        ofRect(pos.x,pos.y,dims.x,dims.y);
        ofDisableAlphaBlending();
    }
    
}

void scPhoto::rePos(float _x,  float _y){
    tPos.x=_x;
    tPos.y=_y;
}

void scPhoto::reSize(int _w,  int _h){
    tDims.x=_w;
    tDims.y=_h;
}

void scPhoto::checkMouse(int _x, int _y){
    if(_x>pos.x && _x<pos.x+dims.x && _y>pos.y && _y<pos.y+dims.y){
        fade= !fade;
        //shade = !shade;
        string str = "scPhoto " + ofToString(x)+", "+ofToString(y)+"= "+ ofToString(fade)+"\n";
        printf("%s",str.c_str());
        
    }
}

void scPhoto::process(){
    
    if(image.isAllocated()){
    image.setImageType(OF_IMAGE_COLOR_ALPHA);
    unsigned char * pixels = image.getPixels();
    
    
    for (int y=0; y<dims.y; y++){
        for(int x=0; x<dims.x; x++){
            
            // the index of the pixel:
            //int index = y*dims.x*3 + x*3;
            int index = y*dims.x*4 + x*4;
            //cout<<"pixel_index= "<<index<<"\n";
            int red = pixels[index];
            int green = pixels[index+1];
            int blue = pixels[index+2];
            
            if(ofDist(x,y,dims.x/2,dims.y/2-yOffSet)>dims.x/2){
                image.setColor(x,y,ofColor(red,green,blue,maskAlpha));
                //cout<<"red val ="<<red<< " ";
            }
        }
    }
    // delete [] pixels;
    image.update();
    }
}


void scPhoto::update(){
    
    
    if(tPointAlpha>pointAlpha){
        pointAlpha+=fadeVal;
        
    }
    if(tPointAlpha<pointAlpha){
        pointAlpha-=fadeVal;
        
    }
    
    if(tPointLoc.x>pointLoc.x){
        pointLoc.x+=easeVal*abs(tPointLoc.x-pointLoc.x);
        
    }
    if(tPointLoc.y>pointLoc.y){
        pointLoc.y+=easeVal*abs(tPointLoc.y-pointLoc.y);
        
    }
    
    if(tPointLoc.x<pointLoc.x){
        pointLoc.x-=easeVal*abs(tPointLoc.x-pointLoc.x);
        
    }
    if(tPointLoc.y<pointLoc.y){
        pointLoc.y-=easeVal*abs(tPointLoc.y-pointLoc.y);
        
    }
    
    
    if(abs(tPointLoc.y-pointLoc.y)<1){
        pointLoc.y= tPointLoc.y;
    }
    if(abs(tPointLoc.x-pointLoc.x)<1){
        pointLoc.x= tPointLoc.x;
    }
    
    
    //check if vals = targets and update if not
    //easeVal = abs()
    ease = ofVec2f(fabs(tPos.x-pos.x)*.05,fabs(tPos.y-pos.y)*.05);
    
    if (tShape == shape){
        if(tPos.x > pos.x){
            pos.x+=ease.x;
        }
        
        if(tPos.x< pos.x){
            pos.x-=ease.x;
        }
        
        if(tPos.y > pos.y){
            pos.y+=ease.y;
        }
        if(tPos.y< pos.y){
            pos.y-=ease.y;
        }
        
        if(tDims.x > dims.x){
            dims.x+=ease.x;
        }
        if(tDims.x < dims.x){
            dims.x-=ease.x;
        }
        
        if(tDims.y > dims.y){
            dims.y+=ease.y;
        }
        if(tDims.y< dims.y){
            dims.y-=ease.y;
        }
        
        
        if(fade && alphaVal>0){
            // alphaVal-=alphaVal*fadeVal;
            alphaVal-=fadeVal;
        }
        if(!fade && alphaVal<255){
            
            //alphaVal+=(alphaVal+1)*fadeVal;
            alphaVal+=fadeVal;
        }
        
        
        //scale
        
        if(tTextScale > textScale){
            textScale+=.05;
        }
        if(tTextScale < textScale){
            textScale-=.05;
        }
        if(fabs(tTextScale - textScale) <.01 ){
            textScale=tTextScale;
            
        }
        
    }
    
    //shape transistions
    if(tShape != shape){
        if(tShape == "circ" && maskAlpha>0){
            //maskAlpha-=maskAlpha*.1;
            maskAlpha-=10;
            if(maskAlpha<=1){
                shape = "circ";
                maskAlpha = 0;
            }
            
        }
        
        if(tShape == "rect" && maskAlpha<255){
            // maskAlpha+=(maskAlpha+1)*.1;
            maskAlpha+=10;
            if(maskAlpha>=254){
                shape = "rect";
                maskAlpha = 255;
            }
            
        }
        process();
        
    }
}

void scPhoto::shapeTrans(string _shape){
    
    if(_shape == "rect"){
        tMaskAlpha = 255;
        tShape = "rect";
    }
    
    if(_shape == "circ"){
        tMaskAlpha = 0;
        tShape = "circ";
        
    }
    
    //cout<<"t shape = "<<tShape<<", shape = "<<shape<<"\n";
    
}

void scPhoto::drawPoint(){
    //    if(abs(tPointLoc.y-pointLoc.y)<5 && abs(tPointLoc.x-pointLoc.x)<5){
    //        ofSetColor(255, 50, 0, pointAlpha);
    //        pointSize=10;
    //
    //    }
    
    //    else {
    
    pointSize=10;
    
    //}
    
    
    ofEnableAlphaBlending();
    
    ofSetColor(255, 40,0, pointAlpha);
    ofCircle(pointLoc.x,pointLoc.y,pointSize);
    ofSetColor(255, pointAlpha);
   
    ofCircle(pointLoc.x,pointLoc.y,pointSize-3);
  
    
   //ofSetColor(255);
    
    //ofDrawBitmapString(zip,pointLoc.x,pointLoc.y);
    
    //cout<<"got here"<<endl;
    ofDisableAlphaBlending();
    
    
}
ofVec2f scPhoto::getLocation(string Mzipcode){
    
    //this accepts a string zipcode and assigns pointLocation , returns ofVec2f x,y that is then equal to pointLoc (ofVec2f tPointLoc)
    string location = Mzipcode;
    
    zipcodes.getIncomingZip( location);
    // cout<<zipcodes.latitudeLongitude<<endl;
    ofVec2f pointLocCoords=zipcodes.latitudeLongitude;//based on a map of chicago , scale the points -
    return pointLocCoords;
    
    //I believe that we need to set this, based on zLoc "setFeatured() in scKeyword.cpp... but I'm not 100% sure of this so we'll figure it out tomorrow 
}
