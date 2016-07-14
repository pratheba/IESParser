//
//  IESParser.cpp
//  IESParser
//
//  Created by Pratheba Selvaraju on 6/9/16.
//  Copyright © 2016 Pratheba Selvaraju. All rights reserved.
//

#include "IESParserToCSV.hpp"
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

void IESParserToCSV::Parse(const string& inputfile, string& outputfilename, const string& fileName) {
    
    //string outputfilename =  path + "output/" ;
    
    std::string line;
    std::string key, value;
    std::vector<double> vectorValues;
    std::ifstream iesFileName(inputfile);
    
    while (std::getline(iesFileName,line)) {
        boost::algorithm::trim(line);
        if (line.empty()) {
            continue;
        }
        std::istringstream token(line);
        std::string tokenString = token.str();
        if (!isdigit(tokenString[0]))
            continue;
        else {
            
            double tmp;
            while (token >> tmp) {
                vectorValues.push_back(tmp);
            }
            
            if ((vectorValues.size() == 10)||(vectorValues.size() == 13)) {
                int numVerticalDegree = vectorValues[3];
                outputfilename += to_string(numVerticalDegree) + "_";
                int numHorizDegree    = vectorValues[4];
                outputfilename += to_string(numHorizDegree) ;
                
//                if(!boost::filesystem::is_directory(outputfilename)) {
//                    boost::filesystem::path dir(outputfilename);
//                    if(!(boost::filesystem::create_directory(dir)))
//                        return;
//                }
                
                outputfilename += ".csv";
                outputFile.open(outputfilename,ios::out | ios::app );
                
//                for(int i=1; i < numVerticalDegree; ++i) {
//                    outputFile << "V" << i << ",";
//                }
//                outputFile << "V" << numVerticalDegree << "\n";
                //outputFile << numHorizDegree << "\n";
                
                if(vectorValues.size() == 10)
                    ParseIESIntensity(iesFileName, numVerticalDegree, numHorizDegree, true);
                else
                    ParseIESIntensity(iesFileName, numVerticalDegree, numHorizDegree, false);
            }
        }
    }
}

void IESParserToCSV::ParseIESIntensity(ifstream& iesFileName, int numVerticalDegree,int numHorizDegree, bool ignoreFirstLine) {
    
    std::string line;
    std::string value;
    std::vector<double> vectorValues;
    
    int currHorizDegreecount = 1;
    int currVertDegreecount = 1;
    int countV = 1, countH = 1;
    
    bool isVerticalAnglesRetrieved = false;
    bool isHorizontalAnglesRetrieved = false;
    vectorValues.clear();
    
    while (std::getline(iesFileName,line)) {
        boost::algorithm::trim(line);
        if (line.empty()) {
            continue;
        }
        
        if(ignoreFirstLine) {
            ignoreFirstLine = false;
            continue;
        }
        
        //cout << line << endl;
        std::stringstream token(line);
        
        double value;
        while (token >> value) {
            //outputFile << value << ",";
            //vectorValues.push_back(atof(value.c_str()));
            
            if(isVerticalAnglesRetrieved && isHorizontalAnglesRetrieved ) {
                if(countV < numVerticalDegree){
                    outputFile << value << ",";
                    countV++;
                }
                else if(countV == numVerticalDegree) {
                    if(countH == numHorizDegree)
                        outputFile << value << "\n";
                    else {
                        outputFile << value << ",";
                        countV = 1;
                        countH++;
                    }
                }
            }
            else if(!isVerticalAnglesRetrieved && (currVertDegreecount < numVerticalDegree)) {
                //outputFile << value << ",";
                ++currVertDegreecount;
            }
            else if(!isVerticalAnglesRetrieved &&(currVertDegreecount == numVerticalDegree)) {
                //outputFile << value <<"\n";
                isVerticalAnglesRetrieved = true;
                //vectorValues.clear();
            }
            else if(isVerticalAnglesRetrieved && !isHorizontalAnglesRetrieved && (currHorizDegreecount < numHorizDegree)) {
                //outputFile << value <<",";
                ++currHorizDegreecount;
            }
            else if(isVerticalAnglesRetrieved && !isHorizontalAnglesRetrieved && (currHorizDegreecount == numHorizDegree)) {
                //outputFile << value <<"\n";
                isHorizontalAnglesRetrieved = true;
            }
        }
    }
    
    //if(countH == numHorizDegree)
    outputFile.close();
}



