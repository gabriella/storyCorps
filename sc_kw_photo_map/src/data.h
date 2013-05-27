//
//  data.h
//  StoryCorps
//
//  Created by Jack Kalish on 4/7/13.
//
//

#ifndef __scPhotoFont__data__
#define __scPhotoFont__data__

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofxXmlSettings.h"
#include "InterviewData.h"
#include "zipcodes.h"


using namespace wng;

class data
{
    
    public:
    //methods
        void loadCSV(string path);
        void loadInterviewXML(string path);
        void loadParticipantXML(string path);
        void loadParticipantCSV(string path);
        void parse();
        std::vector<InterviewData> getInterviewsWithKeyword(string k);
        std::vector<string> getKeywordsForItem(int i);
        void split(string str, string delimiters , vector<string> tokens);
        void addKeyword(string k);
        void addKeywords(string k);
        string getZipForId(string id);

    //vars
        ofxCsv participantCSV;
        ofxXmlSettings XML;
        ofxXmlSettings participantXML;
        std::vector<std::pair<string, int> > keywords;
        zipcodes zipcodes;
};

#endif /* defined(__scPhotoFont__data__) */
