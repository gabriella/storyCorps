//
//  data.cpp
//  StoryCorps
//
//  Created by Jack Kalish on 4/7/13.
//
//

#include "data.h"

void data::loadParticipantCSV(string path){
    // Load a CSV File into the data class
	participantCSV.loadFile(path);
}

void data::loadInterviewXML(string path){
    //load and parse XML data file
    cout << "Load XML file" << endl;
    string message;
    if( XML.loadFile(path) ){
        message = "data loaded!";
    }else{
        message = "unable to load xml check data/ folder";
    }
    cout << message << endl;
}

void data::loadParticipantXML(string path){
    //load and parse XML data file
    cout << "Load participant XML file" << endl;
    string message;
    if( participantXML.loadFile(path) ){
        message = "data loaded!";
    }else{
        message = "unable to load mySettings.xml check data/ folder";
    }
    cout << message << endl;
}

//parse
void data::parse(){
    cout << "parse" << endl;
    //prep the particiapnt xml file
    participantXML.pushTag("Document");
    
    //iterate through all keywords in the XML file and generate a list of all the keywords used and their frequencies
    //add keyword to keyword list if it is not already in the list
    //go to first row with data in it
    XML.pushTag("Document");
    // XML.pushTag("Worksheet");
    // XML.pushTag("Table");
    int numRows = XML.getNumTags("Row");
    for (int rCnt = 1;rCnt < numRows ;rCnt++){
        XML.pushTag("Row",rCnt);
        //now i need to iterate through all the cells of the row and look for the one with the correct index of 86
        //    int numCells = XML.getNumTags("Cell");
        //    bool collectKeywords = false;
        
        // for (int cCnt = 0;cCnt< numCells;cCnt++){
        //   if(XML.getAttribute("Cell", "ss:Index", 0, cCnt) == 86){
        //     collectKeywords = true;
        //}
        
        
        
        //get all keywords in cells starting at cell 86
        //  if(collectKeywords){
        
        //  XML.pushTag("Cell",cCnt);//col with keywords
        // string kws = XML.getValue("Field_85","");//this should return the keywords that need to be split at the return
        addKeywords(XML.getValue("Field_85",""));
        addKeywords(XML.getValue("Field_86",""));
        addKeywords(XML.getValue("Field_87",""));
        addKeywords(XML.getValue("Field_88",""));
        
        XML.popTag();
        //  }
        
        //  }
        // XML.popTag();
        
    }
    
    //keyword list has been generated, let's see it!
    /*cout << endl << endl << "KEYWORD LIST: " << endl;
     for (int kCnt = 0; kCnt<keywords.size(); kCnt++){
     //cout << keywords[kCnt].first << ", "<< keywords[kCnt].second << endl;
     }*/
    //sort the list
    struct sort_pred {
        bool operator()(const std::pair<string,int> &left, const std::pair<string,int> &right) {
            return left.second > right.second;
        }
    };
    
    std::sort(keywords.begin(), keywords.end(), sort_pred());
    //std::sort(keywords.begin(), keywords.end(), boost::bind(&std::pair<string, int>::second, _1) < boost::bind(&std::pair<string, int>::second, _2));
    
    //now return the sorted list...
   /* cout << endl << endl << "KEYWORD LIST: " << endl;
    for (int kCnt = 0; kCnt<keywords.size(); kCnt++){
        cout << keywords[kCnt].first << ", "<< keywords[kCnt].second << endl;
    }*/
}

void data::addKeywords(string k){
    if(k != ""){
    
    vector<string> skws = ofSplitString(k, "|");
    
    for (int i = 0; i < skws.size(); i++){
        //add keyword to list of keywords...
       // if(skws[i] != ""){
            addKeyword(skws[i]);
       // }
    }
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
    
    //add keyword to keyword list if it is not already in the list
    //go to first row with data in it
    int numRows = XML.getNumTags("Row");
    for (int rCnt = 1;rCnt < numRows ;rCnt++){
        
        XML.pushTag("Row",rCnt);
        //now i need to iterate through all the cells of the row and look for the one with the correct index of 86
      //  for (int i = 0;i< XML.getNumTags("Cell");i++){
            //  cout << "cell:";
            //  cout << i << endl;
        //    if(XML.getAttribute("Cell", "ss:Index", 0, i) == 86){
          //      XML.pushTag("Cell",i);//col with keywords
                string kws = XML.getValue("Field_85","");//this should return the keywords that need to be split at the return
        
        kws += "|"+XML.getValue("Field_86","");
        kws += "|"+XML.getValue("Field_87","");
        kws += "|"+XML.getValue("Field_88","");


        
                vector<string> skws = ofSplitString(kws, "|");
                
        
                for (int i = 0; i < skws.size(); i++){
                    //if keyword is found...
                    if(skws[i] == k){
                        //create new interview object
                        InterviewData id;
                        string interviewID = XML.getValue("Field_0","");
                        
                        id.interviewID = interviewID;
                        id.zip = getZipForId(interviewID);
                 
                        interviews.push_back(id);

                        break;
                    }
                    
                }

        
           // }
       // }
        XML.popTag();
        
    }
    return interviews;
}

string data::getZipForId(string id){
    //parse the csv file...
    //cout << "getZipForId" << endl;
    for(int i=1; i< participantXML.getNumTags("Row"); i++){
        participantXML.pushTag("Row", i);
        string iid = participantXML.getValue("Field_0","");
       // cout << "iid: " << iid << endl;

        //find matching id
        if(iid == id){
            string role = participantXML.getValue("Field_25","");
            if(role == "Storyteller 1"){
                string zip = participantXML.getValue("Field_37","");
                participantXML.popTag();
                return zip;
            }
        }
        participantXML.popTag();
    }
    /*
    //CSV mode (not working :(
    for (int i=0 ;i < participantCSV.numRows ; i++){
        //match the ids
        cout << "id:" << participantCSV.data[i][0] << endl;
        if(participantCSV.data[i][0] == id){ //0 or 1??? NOT SURE...
            //look for the storyteller ROLE
            if(participantCSV.data[i][26-1] == "Storyteller 1"){
                //return the zip!
                return participantCSV.data[i][38-1];
            }
        }
    }
     */
}

/*
string data::getZipForId(string id){
    //find zipcode for the interviewer address based in the interview id
    participantXML.pushTag("Workbook");
    participantXML.pushTag("Worksheet");
    participantXML.pushTag("Table");
    int numRows = XML.getNumTags("Row");
    for (int rCnt = 1;rCnt < numRows ;rCnt++){
        XML.pushTag("Row",rCnt);
        //loop through rows
        int numCells = XML.getNumTags("Cell");
        bool collectKeywords = false;
        
        for (int cCnt = 0;cCnt< numCells;cCnt++){
            //loop through cells, compare ids
            XML.pushTag("Cell",0);//col with id
            string iid = XML.getValue("Data","");
            if(iid == id){
                //id match found
                //look for the interviewee
                
            }
            
            if(XML.getAttribute("Cell", "ss:Index", 0, cCnt) == 86){
                collectKeywords = true;
            }
            
            //get all keywords in cells starting at cell 86
          //  if(collectKeywords){
                
                XML.pushTag("Cell",cCnt);//col with keywords
                string kws = XML.getValue("Data","");//this should return the keywords that need to be split at the return
                
                addKeywords(kws);
                
                XML.popTag();
                
                
         //   }
            
        }
        XML.popTag();
        
        
}
}
*/

/*
//return the list of keywords from the CSV item
std::vector<string> data::getKeywordsForItem(int i){
    //keyword column is...94?
    cout << csv.data[2][94] << endl;
    
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
}*/