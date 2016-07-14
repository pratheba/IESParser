//
//  IESParserToCSV.hpp
//  IESParser
//
//  Created by Pratheba Selvaraju on 6/9/16.
//  Copyright © 2016 Pratheba Selvaraju. All rights reserved.
//

#ifndef IESParserToCSV_hpp
#define IESParserToCSV_hpp


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class IESParserToCSV
{
public:
    IESParserToCSV(){}
    void Parse(const string& inputfile, string& outputfilename, const string& fileName);
    
    
private:
    
    
    void ParseIESIntensity(ifstream& fileName);
    void ParseIESIntensity(ifstream& iesFileName, int numVerticalDegree,int numHorizDegree, bool ignoreFirstLine);
    
    void WriteDataToCSVFile();
    ofstream outputFile;
};


#endif /* IESParserToCSV_hpp */
