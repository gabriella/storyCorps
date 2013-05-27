//
//  scKeyword.cpp
//  scPhotoFont
//
//  Created by Nick Yulman on 5/12/13.
//
//

#include "scKeyword.h"
#include "interviewData/InterviewData.h"

void scKeyword::initBG(string _keyword, ofVec2f _pos, ofVec2f _lim1, ofVec2f _lim2, ofTrueTypeFont _font){

    keyword = _keyword;
    pos = _pos;
    font = _font;
    
    limit1 = _lim1;
    limit2 = _lim2;
    
    int neg[2] = {-1,1};
    int neg1 = neg[ofToInt(ofToString(ofRandom(2)))];
    int neg2 = neg[ofToInt(ofToString(ofRandom(2)))];
    
    float speedMax=.2;
    float speedMin=.05;
    
    speed = ofVec2f(ofRandom(speedMin, speedMax)*neg1,ofRandom(speedMin, speedMax)*neg2);
    
    color= ofColor(ofRandom(55,110));

}


void scKeyword::init(string _keyword, ofVec2f _pos, ofVec2f _lim1, ofVec2f _lim2, ofTrueTypeFont _font,
                     data scData){
    
    //cout << "initialize keyword:" << _keyword << endl;


    keyword = _keyword;
    pos = _pos;
    font = _font;
    
    limit1 = _lim1;
    limit2 = _lim2;
    
    int neg[2] = {-1,1};
    int neg1 = neg[ofToInt(ofToString(ofRandom(2)))];
    int neg2 = neg[ofToInt(ofToString(ofRandom(2)))];

    float speedMax=.2;
    float speedMin=.05;
    
    speed = ofVec2f(ofRandom(speedMin, speedMax)*neg1,ofRandom(speedMin, speedMax)*neg2);

    color= ofColor(ofRandom(55,110));
    
    
    //generate vector of interview data objects for the keyword
    interviewDataObjects = scData.getInterviewsWithKeyword(_keyword);
    
    for(int i = 0; i<interviewDataObjects.size();i++){
        //init photo objects for interviewdata array
        string zip = interviewDataObjects[i].zip;
        if(zip != ""){
        
        scPhoto p;
        p.init(interviewDataObjects[i].interviewID, ofVec2f(0,0),ofVec2f(0,0));
        //set photo zip code
        p.zip = zip;
        //cout <<"zip: " << p.zip << endl;
        //set x and y target location on map
        p.zipLoc = p.getLocation(p.zip);
        
        //an array of photo objects
        interviews.push_back(p);
        }
    }
    
}

void scKeyword::draw(ofTrueTypeFont _font){
    ofPushMatrix();
    ofScale(scale,scale);
   
    
    //if(abs(tScale-scale)<.1){
    if(featured){
    int a= ofMap(abs(tScale-scale), 1, 0, 0, 255);
        ofSetColor(0, a);
        _font.drawString(keyword, pos.x/scale+3, pos.y/scale+3);
    //}
    }
     ofSetColor(color);
    _font.drawString(keyword, pos.x/scale, pos.y/scale);
    
    

    
    ofPopMatrix();

   }


void scKeyword::update(){
    
    
    if(tScale<scale){
        scale-=easeVal*abs(tScale-scale);
    }
    
    if(tScale>scale){
        scale+=easeVal*abs(tScale-scale);
    }
    
    if(abs(tScale-scale)<.001){
    
        scale=tScale;
        

    }
    
    
    if(tPos.x > pos.x){
        pos.x+=easeVal*abs(tPos.x-pos.x);
    
    }
    
    if(tPos.y > pos.y){
        pos.y+=easeVal*abs(tPos.y-pos.y);
        
    }
    
    
    if(tPos.x < pos.x){
        pos.x-=easeVal*abs(tPos.x-pos.x);
        
    }
    
    if(tPos.y < pos.y){
        pos.y-=easeVal*abs(tPos.y-pos.y);
        
    }

}

void scKeyword::move(){
    
    if(moving){
    pos+=speed;
    tPos=pos;
  

    if(pos.x>limit2.x){
        speed.x*=-1;
    
    }
    if(pos.y>limit2.y){
        speed.y*=-1;
        
    }
    if(pos.x<limit1.x){
        speed.x*=-1;
        
    }
    if(pos.y<limit1.y){
        speed.y*=-1;
        
    }
    }
    
}


void scKeyword::setFeatured(){
    color=255;
    featured = true;
    moving = false;
    
    /*
    for(int i = 0; i<_interviews.size();i++){
        //init photo objects for interviewdata array
        scPhoto p;
        p.init(_interviews[i].interviewID, ofVec2f(0,0),ofVec2f(0,0));
        //set photo zip code
        p.zip = _interviews[i].zip;
        //set x and y target location on map
        p.zipLoc = p.getLocation(p.zip);
        
        interviews.push_back(p);
    }*/
    
    int tWidth=limit2.x-limit1.x-200;
    
    tScale = ( tWidth/font.stringWidth(keyword));
    
    if(tScale>1.3){
        tScale=1.3;
    }
    
    tPos = ofVec2f(limit1.x+(limit2.x-limit1.x)/2-(font.stringWidth(keyword)*tScale/2), (limit1.y+(limit2.y-limit1.y)/2)+font.stringHeight(keyword)/2 );
   
   /* if(!intInit){
        for(int i=0; i<_interviews.size();i++){
            //instantiate photo objects
            
         //   interviews.push_back(_interviews[i]);
            
         //   interviews[i].alphaVal=0;
         //   interviews[i].fade=true;
            
            //get zipcode location
           // ofVec2f zLoc=zipcodes.latitudeLongitude;
             ofVec2f zLoc=ofVec2f(ofRandom(limit1.x,limit2.x),ofRandom(limit1.y,limit2.y));
            
            
          //  ofVec2f zLoc  = interviews.
            
            
            
          //  interviews[i].zipLoc=zLoc;
            //cout<<keyword<<" zloc= "<<interviews[i].zipLoc.x<<", "<<interviews[i].zipLoc.y<<endl;
            
        }
        intInit=true;

    }*/
    
}

void scKeyword::setBg(){
    
    featured = false;
    moving = true;
    color= ofColor(ofRandom(55,110));
    tScale = .2;
     for(int i=0; i< interviews.size(); i++){
         interviews[i].tPointLoc.x= ofGetWidth()/2;
         interviews[i].tPointLoc.y= ofGetHeight()/2;
    interviews[i].pointLoc.x= ofGetWidth()/2;
    interviews[i].pointLoc.y= ofGetHeight()/2;
         
         interviews[i].tPointAlpha=0;

     }
}


void scKeyword::drawPoints(){
    
   
    for(int i=0; i< interviews.size(); i++){
        addPoint(i);
        interviews[i].update();
        interviews[i].drawPoint();
               }
    
}

void scKeyword::addPhoto(int p){
  //interviews[p].fade=false;

}

//the dot on the map
void scKeyword::addPoint(int p){
    interviews[p].tPointAlpha=230;
    interviews[p].tPointLoc.x=interviews[p].zipLoc.x;
    interviews[p].tPointLoc.y=interviews[p].zipLoc.y;
    
}


void scKeyword::drawPhotos(int _gridX, int _gridY, int _dimX, int _dimY, int _offset){
    for (int y=0; y<_gridY; y++) {
       for (int x=0; x<_gridX; x++) {
        int index = y*_gridX+x;
           
           
           if(interviews.size()>index){
               if(!photoInit){
               interviews[index].tPos.x=x*_dimX;
                interviews[index].tPos.y=y*_dimY+_offset;
                //interviews[index].tPointLoc= interviews[index].tPos;
                //interviews[index].pointLoc= interviews[index].tPointLoc;
                  
               }
        interviews[index].draw();
               
           }
    }
         
    }

photoInit=true;

}
