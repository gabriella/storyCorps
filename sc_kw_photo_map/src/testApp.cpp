#include "testApp.h"
//--------------------------------------------------------------
void testApp::setup(){
    
    
    //mode=1;
    mode=0;
    
    ofSetDataPathRoot("../Resources/data/");
    displayMap = true;
    displayGrid = false;
    displayLg = true;
    modeSwitch = true;
    
  
    lgIndex = 0;
    lgIndex2 = 10;
    
  
    lgMark = 0;
    lgMark2 = 500;
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    
    
    headerFont.loadFont("DINPro-Regular.otf", 44);
     din.loadFont("DINPro-Regular.otf", 100);
    selectFont.loadFont("DINPro-Regular.otf", 100);
    //bg.loadFont("DINPro-Regular.otf", 24);
    
    headerHeight = headerFont.getSize()*2;

    
           
    cout<<"width: "<<w<<", height: "<<h<<endl;
    
    map.load("chicago_maps/US-IL-Chicago-orange_gr.svg");
    scLogo.loadImage("SC_orange_small.png");
    
    int lw = w/2-scLogo.width/4;
    //cout<<"width: "<<ofGetWidth()<<", logo width:"<<lw<<endl;
    
    logoPos = ofVec2f(w-lw, 50);
    
    fontSize = h/3;
    cout<<"fontsize = "<<fontSize<<"\n";
    
       
    ofSetFrameRate(100);
    int nodeTot = 0;
    int nFiles = dir.listDir("g2");
    numPhotos = dir.numFiles();
    
    cout<<"Num Photos: "<<numPhotos<<"\n";
    dims.x = 110;  //define standard size of image
    dims.y = dims.x*1.5;
    easeDef = 6;
    scale = 1;
    tScale =scale;
    
    textScale = 2;
    
    translate = ofVec2f(0,0);
    
    ofSetCircleResolution(100);
    //gridX = ofGetWidth()/dims.x;
    //gridY = ofGetHeight()/dims.y;
    
    gridX = 6;
    gridY = 5;
    
    
    mapBoxWidth=w-dims.x*gridX;
    footerHeight=h-gridY*dims.y-headerHeight;
    mapBoxheight = h-headerHeight-footerHeight;
    headerTextWidth = headerFont.getStringBoundingBox(headerText, 0, 0).width;
    
    headerTextX = w/2-headerTextWidth/2- ((w-mapBoxWidth)-headerTextWidth)/2;
    
    mapBoxX= w/2-mapBoxWidth/2;
    mapBoxY=h-footerHeight-mapBoxheight;
    
    if(mode==0 || modeSwitch == true){
    //load list of key words
        //run with 10 keywords
    dispKW.loadFile(ofToDataPath("kw10.csv"));
        
        //run with 70 keywords
        //dispKW.loadFile(ofToDataPath("kw70.csv"));
    cout << "load keywords, size:" << dispKW.numRows << endl;
    
    //setup data object
    scData.loadInterviewXML(ofToDataPath("search-export-interviews-Interview_City_Chicago.xml"));
    scData.loadParticipantXML(ofToDataPath("search-export-participants-Interview.xml"));
    scData.parse();
    
    //initialize kw objects
    
    for(int i = 0; i<dispKW.numRows; i++){
    
    string s = dispKW.data[i][0];
    ofVec2f tempPos = ofVec2f(ofRandom(mapBoxX,mapBoxX+mapBoxWidth),ofRandom(mapBoxY,mapBoxY+mapBoxheight));
        
        scKeyword kw;
        
        keywords.push_back(kw);
        
        
        ofVec2f lim1= ofVec2f(mapBoxX,mapBoxY);
        ofVec2f lim2= ofVec2f(mapBoxX+mapBoxWidth,mapBoxY+mapBoxheight);
        
        keywords[i].init(s, tempPos, lim1, lim2, din, scData);
        
    }
    
  
    //initialize cloud kewwords
    bgKW.loadFile(ofToDataPath("kwOrig.csv"));
        cout << "bg keywords, size:" << bgKW.numRows << endl;
    for(int i = 0; i<bgKW.numRows; i++){
        string s = bgKW.data[i][0];
        
        
        ofVec2f tempPos = ofVec2f(ofRandom(0,w),ofRandom(0,h));

        
        scKeyword kw;
        
        bgKeywords.push_back(kw);
        
        
        ofVec2f lim1= ofVec2f(0,0);
        ofVec2f lim2= ofVec2f(w,h);
        
        bgKeywords[i].initBG(s, tempPos, lim1, lim2, din);
    
    }

    }
    
    
    numDisplay = gridX * gridY;
   // cout<<"numDisplay: "<<numDisplay;
    //load photos from directory into photos vector
    if(nFiles) {
        for(int i=0; i<numPhotos; i++) {
            // add the image to the vector
            string filePath = dir.getPath(i);
            images.push_back(ofImage());
            images.back().loadImage(filePath);
            
        }
        
       // cout<<"images size"<<images.size()<<"\n";
        
        //load large images
//        
//        for(int i=0; i <numPhotos; i++){
//            
//            int m = 4;
//            //images[i].resize(dims.x*m,dims.y*m);
//             scPhoto p;
//            lgPhotos.push_back(p);
//            lgPhotos[i].init(images[i],ofVec2f(w/2-dims.x*m/2, headerHeight),ofVec2f(dims.x*m,dims.y*m));
//            lgPhotos[i].fade = true;
//            lgPhotos[i].alphaVal =0;
//        }

        
        
//        //resize photos
//        for(int i=0; i<numPhotos; i++) {
//            //images[i].resize(dims.x,dims.y);
//            
//        }
//        
        
        
//        //load images into scPhoto objects
//        for(int i=0; i <numDisplay; i++){
//            ofVec2f v =ofVec2f(0,headerHeight);
//            scPhoto p;
//           scPhotos.push_back(p);
//           // cout<<"scPhotos size "<<scPhotos.size()<<"\n";
//            
//           scPhotos[i].init(images[ofRandom(images.size())], v, dims);
//        }
        
//        for(int y = 0; y< gridY; y++){
//            for(int x = 0; x< gridX; x++){
//                int index = y*gridX+x;
//                scPhotos[index].process();
//                
//            }
//        }
    }
    
       
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    
    //updates for map mode
    if(mode==0){
   
    switchKW();
    for(int i=0; i<keywords.size();i++){
        keywords[i].move();
      
        //if(keywords[i].featured){
            keywords[i].update();
            //bgKeywords[i].update();
        //}
    
    }
    
        for(int i = 0; i<bgKeywords.size(); i++){
             bgKeywords[i].move();
        }
    
        //updates for displaying photos in map mode
//    for(int i = 0; i<numDisplay;i++){
//        scPhotos[i].update();
//                
//    }
    
    for(int i = 0; i<keywords[featured].interviews.size();i++){
        keywords[featured].interviews[i].update();
    }
    }
    
        
   // if(fmod(ofGetElapsedTimeMillis(),1000.0)==0){
    
    
    
    //updates for portrait mode
    if(mode ==1){
             
    //check to see if it's time to switch photos
    if(ofGetElapsedTimeMillis()-lgMark>lgDispTime){
        lgMark = ofGetElapsedTimeMillis();
        
        switchLargePhotos();
        
             }
        
        if(ofGetElapsedTimeMillis()-lgMark>lgDispTime-lgFadeTime){
        //lgPhotos[lgIndex].fade = true;
        }
        
        
    
//    if(ofGetElapsedTimeMillis()-lgMark2>lgDispTime){
//        lgMark2 = ofGetElapsedTimeMillis();
//            //lgIndex++;
//        pLgIndex2 = lgIndex2;
//        lgIndex2 = ofRandom(numPhotos);
//        
//       // lgPhotos[lgIndex2].alphaVal = 0;
//       // lgPhotos[lgIndex2].fade = false;
//        
//            if(lgIndex2==numPhotos){
//                lgIndex2=0;
//            }
//    }
    }
    
//    if(ofGetElapsedTimeMillis()-lgMark2>lgDispTime-lgFadeTime){
//        //lgPhotos[lgIndex2].fade = true;
//    }
    
        
    if(modeSwitch){
    //check to see if it's time to switch modes and do it
        switchModes();
    }
    
    }

//--------------------------------------------------------------
void testApp::draw(){
    
    if(mode==1){
         ofBackground(0);
        displayLargePhotos();
        
    }
   
    if(mode==0){
    
    ofFill();
        
   
    if(displayLogo){
        drawLogo();
    }
    
    ofSetColor(50);
    //ofRect(mapBoxX, headerHeight, mapBoxWidth, h-headerHeight-footerHeight);
    
    ofRect(0, headerHeight, ofGetWindowWidth(), ofGetWindowHeight()-headerHeight-footerHeight);
    //draw bg word texture
    
    
    for(int i = 0; i<keywords.size(); i++){
        if(!keywords[i].featured){
        keywords[i].draw(din);
               }
    }
        
        for(int i = 0; i<bgKeywords.size(); i++){
            bgKeywords[i].draw(din);
        }
    
    
   if(displayMap){
    ofPushMatrix();
    //ofScale(scale,scale);
    //ofTranslate(w-100, h-100);
       ofEnableAlphaBlending();

    ofTranslate(mapBoxX + (mapBoxWidth- map.getWidth())/2, h-mapBoxheight+(mapBoxheight-map.getHeight())/2-footerHeight);
       map.draw();
       ofDisableAlphaBlending();
    ofPopMatrix();
    }
    
     
    
       
    
    keywords[featured].drawPhotos(gridX, gridY, dims.x, dims.y, headerHeight);
    
      

    drawPoints();
    

       keywords[featured].draw(din);
        
        ofSetColor(160, 60, 0);
        ofRect(0, 0, w, headerHeight);
        
        ofSetColor(255);
        
        headerFont.drawString(headerText, headerTextX, headerHeight-(headerHeight/2-headerFont.getSize()/2));

      
    
    }
    
   }

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == 'a'){
        int rand = ofRandom(numDisplay);
        scPhotos[rand].fade = !scPhotos[rand].fade;
    }
    
    if(key == 'f'){
        
        int i = ofRandom(keywords.size());
      
        //keywords[i].setFeatured();
        //keywords[featured].featured=false;
        featured=i;
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
    
    //scale+= (y-pMousePos.y)/100;
    translate.x+=(x-pMousePos.x);
    translate.y+=(y-pMousePos.y);
    
    pMousePos= ofVec2f(x,y);
    
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    pMousePos = ofVec2f(x,y);
    
    cout<<"mouse pos= "<<x<<", "<<y<<endl;
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    for(int i = 0; i<numDisplay-1; i++){
        
    }
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


//void testApp::formGrid(){
//
//    for(int y = 0; y< gridY; y++){
//        for(int x = 0; x< gridX; x++){
//            int index = y*gridX+x;
//             scPhotos[index].fade = false;
//             scPhotos[index].tPos = ofVec2f(x* dims.x,y* dims.y+headerHeight);
//            scPhotos[index].shapeTrans("rect");
//            scPhotos[index].tTextScale = 1;
//
//
//         }
//    }
//}

void testApp::switchKW(){

    if(ofGetElapsedTimeMillis()-kwSwitchMark>kwSwitchTresh){
        kwSwitchMark=ofGetElapsedTimeMillis();
        switchCount++;
       
        int k = ofRandom(keywords.size());
        
        string kw = keywords[k].keyword;
        cout << "new chosen keyword is: " << kw << endl;
        
       
        
        //***get interview data array for chosen keyword
         //vector<InterviewData> interviewDataArray = scData.getInterviewsWithKeyword(kw);
        
        //vector<scPhoto> _interviews;
       
        /* for(int i=0; i<ofRandom(10,30); i++){
            
          _interviews.push_back(scPhotos[ofRandom(scPhotos.size())]);
            
        }*/
        
       
        //keywords[k].getInterviews(_interviews);
         keywords[featured].setBg();
        keywords[k].setFeatured();
       
        //keywords[featured].featured=false;
        featured=k;
        pointIndex=0;
        //kwSwitchTresh=pointDelay*keywords[featured].interviews.size();
        
        
    }
}


int testApp::randNeg(){
    int mult = ofRandom(-2,2);
    if(mult>0){
        return 1;
    }
    if(mult<=0)
    {        return -1;
    }
}


void testApp::drawLogo(){
    
    ofPushMatrix();
    //draw StoryCorps logo;
    ofEnableAlphaBlending();
    ofScale(.5,.5);
    ofSetColor(255,255,255,255);
    ofTranslate(ofGetWidth()-10, logoPos.y);
    scLogo.draw(0,0);
    
    //scLogo.draw(0,0);    
    ofDisableAlphaBlending();
    ofPopMatrix();

}


//draw the points for featured word interviews one by one
void testApp::drawPoints(){
    
    keywords[featured].drawPoints();
    keywords[featured].addPhoto(pointIndex);
    //pointIndex++;
    //pointMark=ofGetElapsedTimeMillis();
    
    
}



void testApp::switchLargePhotos(){
    switchCount++;
    int p1 = ofRandom(0,images.size()/2);
    int p2 = ofRandom(images.size()/2,images.size());
    
    lg1=images[p1];
    lg2=images[p2];
 
    
}


void testApp::displayLargePhotos(){
    //lgPhotos[0].draw();
    
    int rectW = 20;
    int lgPhotoX = ofGetWidth()/2-lg1.getWidth()-rectW/2;
    
    //ofSetColor(255);
    ofSetColor(160, 60, 0);

    ofRect(lgPhotoX+lg1.getWidth(), headerHeight, rectW, lg1.getHeight());
    
     ofSetColor(255);
    lg1.draw(lgPhotoX, headerHeight, lg1.width, lg1.height);
    lg2.draw(lg1.width+lgPhotoX+rectW, headerHeight, lg2.width, lg2.height);
    
    //headerTextWidth = headerFont.getStringBoundingBox(headerText, 0, 0).width;
    
    //headerTextX = w/2-headerTextWidth/2-rectW/2;
    displayHeader(lgPhotoX, lg1.getWidth()*2+rectW);
    
}

//draws the header
void testApp::displayHeader(int _x, int _w){
    
    ofSetColor(160, 60, 0);
    ofRect(_x, 0, _w, headerHeight);
    
    ofSetColor(255);
    
    
    headerFont.drawString(headerText, headerTextX, headerHeight-(headerHeight/2-headerFont.getSize()/2));
    
    
}

//function to check if it's time to switch modes
void testApp::switchModes(){
    if(switchCount>switchThresh){
        //switch form mode 1 to 0
        if(mode==1){
            mode=0;
            switchCount=0;
             headerText = "What Is Chicago Talking About?";
            
            headerTextWidth = headerFont.getStringBoundingBox(headerText, 0, 0).width;
            
            headerTextX = ofGetWindowWidth()/2-headerTextWidth/2;
            
            
        }
          //switch form mode 0 to 1
        else if(mode==0){
            headerText = "Who Is Telling Their Stories?";
            
            headerTextWidth = headerFont.getStringBoundingBox(headerText, 0, 0).width;
            
            headerTextX = ofGetWindowWidth()/2-headerTextWidth/2;
            


            mode=1;
             switchCount=0;
        }

        
    }



}
