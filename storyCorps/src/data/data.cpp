//
//  data.cpp
//  StoryCorps
//
//  Created by Jack Kalish on 4/7/13.
//
//

#include "data.h"

void data::loadCSV(string path){
    // Load a CSV File into the data class
	csv.loadFile(path);
}

void data::loadXML(string path){
    // Load a CSV File into the data class
	//csv.loadFile(path);
    //load and parse XML data file
    cout << "Load XML file" << endl;
    string message;
    if( XML.loadFile(path) ){
        message = "data loaded!";
    }else{
        message = "unable to load mySettings.xml check data/ folder";
    }
    cout << message << endl;
}

//parse
void data::parse(){
    cout << "parse" << endl;

    //iterate through all keywords in the CSV file and generate a list of all the keywords used and their frequencies
    //add keyword to keyword list if it is not already in the list
    //go to first row with data in it
    XML.pushTag("Workbook");
    XML.pushTag("Worksheet");
    XML.pushTag("Table");
    int numRows = XML.getNumTags("Row");
    for (int rCnt = 1;rCnt < numRows ;rCnt++){

        XML.pushTag("Row",rCnt);
    //now i need to iterate through all the cells of the row and look for the one with the correct index of 86
        int numCells = XML.getNumTags("Cell");
        bool collectKeywords = false;

    for (int cCnt = 0;cCnt< numCells;cCnt++){
      //  cout << "cell:";
      //  cout << i << endl;
        if(XML.getAttribute("Cell", "ss:Index", 0, cCnt) == 86){
            collectKeywords = true;
        }
        
        //get all keywords in cells starting at cell 86
        if(collectKeywords){
            
            XML.pushTag("Cell",cCnt);//col with keywords
            string kws = XML.getValue("Data","");//this should return the keywords that need to be split at the return
            
         
           /* vector<string> skws = ofSplitString(kws, "|");
           
            for (int i = 0; i < skws.size(); i++){
                //add keyword to list of keywords...
                addKeyword(skws[i]);
            }*/
            addKeywords(kws);
            
            XML.popTag();
            
           /* if(numCells<cCnt+1){
                //get tags from the next row also?
                XML.pushTag("Cell",cCnt+1);//col with keywords
                kws = XML.getValue("Data","");//this should return the keywords that need to be split
                skws = ofSplitString(kws, "|");
                for (int i = 0; i < skws.size(); i++){
                    //add keyword to list of keywords...
                    addKeyword(skws[i]);
                }
                XML.popTag();
            }
            else{
                break;
            }*/

         
        }
        
    }
        XML.popTag();

    }
    
    //kwyword list has been generated, let's see it!
    cout << endl << endl << "KEYWORD LIST: " << endl;
    for (int kCnt = 0; kCnt<keywords.size(); kCnt++){
        //cout << keywords[kCnt].first << ", "<< keywords[kCnt].second << endl;
    }
    //sort the list
    struct sort_pred {
        bool operator()(const std::pair<string,int> &left, const std::pair<string,int> &right) {
            return left.second > right.second;
        }
    };
    
    std::sort(keywords.begin(), keywords.end(), sort_pred());
    //std::sort(keywords.begin(), keywords.end(), boost::bind(&std::pair<string, int>::second, _1) < boost::bind(&std::pair<string, int>::second, _2));
    
    //now return the sorted list...
    cout << endl << endl << "KEYWORD LIST: " << endl;
    for (int kCnt = 0; kCnt<keywords.size(); kCnt++){
        cout << keywords[kCnt].first << ", "<< keywords[kCnt].second << endl;
    }
}

void data::addKeywords(string k){
    
    vector<string> skws = ofSplitString(k, "|");
    
    for (int i = 0; i < skws.size(); i++){
        //add keyword to list of keywords...
        addKeyword(skws[i]);
    }
    
}

void data::addKeyword(string k){
    //check to see if the keyword is already in the kwyword list
    for (int i = 0; i< keywords.size(); i++){
        if(keywords[i].first == k){
            //keyword already in list, add to counter!
            keywords[i].second++;
            //end method
            return;
        }
    }
    //keyword was not found in the keyword list, so add it to the keyword list... with a count of 1... duh!
    keywords.push_back(std::make_pair (k,1));
}


//return a list of interview data objects that match the requested keyword
std::vector<InterviewData> data::getInterviewsWithKeyword(string k){
    std::vector<InterviewData> interviews;
    
    //iterate through all keywords in the CSV file and generate a list of all the keywords used and their frequencies
    //add keyword to keyword list if it is not already in the list
    //go to first row with data in it
   // XML.pushTag("Workbook");
   // XML.pushTag("Worksheet");
   // XML.pushTag("Table");
    int numRows = XML.getNumTags("Row");
    for (int rCnt = 1;rCnt < numRows ;rCnt++){
       // cout << "row:";
       // cout << rCnt << endl;
        
        XML.pushTag("Row",rCnt);
        //now i need to iterate through all the cells of the row and look for the one with the correct index of 86
        for (int i = 0;i< XML.getNumTags("Cell");i++){
            //  cout << "cell:";
            //  cout << i << endl;
            if(XML.getAttribute("Cell", "ss:Index", 0, i) == 86){
                XML.pushTag("Cell",i);//col with keywords
                string kws = XML.getValue("Data","");//this should return the keywords that need to be split at the return
                
              //  cout << "all strings: "+kws << endl;
                //split the keywords on the returns
                // vector<string> skws = ofSplitString(kws, " ");
                vector<string> skws = ofSplitString(kws, "|");
                //std::vector<int> first;
                //  std::vector<string> skws;
                //split(kws, "&#13;&#13;", skws);
               // cout << "split strings: " << endl;
                //cout << skws << endl;
                for (int i = 0; i < skws.size(); i++){
                   // cout << "keyword ";
                   // cout << i;
                   // cout << ": ";
                  //  cout << skws[i] << endl;
                    //if keyword matches, add to list
                    if(skws[i] == k){
                        //create new interview object
                        InterviewData id;
                        XML.popTag();
                        XML.pushTag("Cell",0);
                        string interviewID = XML.getValue("Data","");
                       // cout << "interviewID: ";
                       // cout << interviewID << endl;
                        
                        id.interviewID = interviewID;
                        //***here is where we need to add the location information
                        
                        //
                        string location="60002";//sample string to input into the zip code data function
                        zipcodes.getIncomingZip(location);
                        
                        //***
                        interviews.push_back(id);
                    }
                    
                }
                XML.popTag();
                break;
            }
        }
        XML.popTag();
        
    }
    
    return interviews;

}

//return the list of keywords from the CSV item
std::vector<string> data::getKeywordsForItem(int i){
    //keyword column is...94?
    cout << csv.data[2][94] << endl;

   // string keywords = csv.data[i][94];
   // cout << keywords;
    //split string at newline
    //return ofSplitString(keywords, "\n");
    
}

void split(string str, string delimiters , vector<string> tokens)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    
    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}