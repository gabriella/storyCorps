//
//  zipcodes.h
//  scPhotoFont
//
//  Created by gabriella levine on 5/18/13.
//
//

#ifndef __scPhotoFont__zipcodes__
#define __scPhotoFont__zipcodes__

#include <iostream>
#include "ofMain.h"


class zipcodes
{
public:
    //methods
    void getIncomingZip(string Mlocation);
    ofVec2f loadData(string Minput);
    ofVec2f mapData(ofVec2f latlong,float mapSouthEdge, float mapNorthEdge, float mapWestEdge, float mapEastEdge );
    
    //vars
    string Minput;//this is the string , the zip code, that is the input
    vector<string> fileTxt ;//vector of words of each line of the input text from the CSV file with zip, lat, long
    ofVec2f latitudeLongitude;
    
    //edge of the image
    float mapSouthEdge;
    float mapNorthEdge ;
    float mapWestEdge ;
    float mapEastEdge;
    
    
};
#endif /* defined(__scPhotoFont__zipcodes__) */
