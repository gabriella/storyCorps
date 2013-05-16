//
//  data.h
//  StoryCorps
//
//  Created by Jack Kalish on 4/7/13.
//
//


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
        void loadXML(string path);
        void parse();
        std::vector<InterviewData> getInterviewsWithKeyword(string k);
        std::vector<string> getKeywordsForItem(int i);
        void split(string str, string delimiters , vector<string> tokens);
        void addKeyword(string k);
        void addKeywords(string k);

    //vars
        ofxCsv csv;
        ofxXmlSettings XML;
        std::vector<std::pair<string, int> > keywords;
        zipcodes zipcodes;
};