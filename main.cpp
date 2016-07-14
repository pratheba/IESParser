//
//  main.cpp
//  IESParser
//
//  Created by Pratheba Selvaraju on 6/9/16.
//  Copyright © 2016 Pratheba Selvaraju. All rights reserved.
//

#include <iostream>
#include<fstream>
#include "IESParser.hpp"
#include "IESParserToCSV.hpp"
#include <dirent.h>
#include <unordered_set>
#include <sstream>
#include <sys/types.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

using namespace boost::filesystem;

unordered_set<string> lightdistribution{"Direct", "Indirect", "Semi-Direct", "Semi-Indirect", "General diffuse"};

struct recursive_directory_range
{
    typedef recursive_directory_iterator iterator;
    recursive_directory_range(path p) : p_(p) {}
    
    iterator begin() { return recursive_directory_iterator(p_); }
    iterator end() { return recursive_directory_iterator(); }
    
    path p_;
};

int main(int argc, const char * argv[]) {
    
    IESParserToCSV* iesParserToCSV = new IESParserToCSV();
    
    string inputfolder = "Input/" ;
    string finalpath =  inputfolder;
    string key, value;
    for (auto it : recursive_directory_range(finalpath))
    {
        if(is_regular_file(it)) {
            string p =  it.path().string();
            //cout << p << endl;
            std::istringstream token(p);
        
            while(std::getline(token, key, '/')) {
                boost::algorithm::trim(key);
            
                if(key == ".DS_Store")
                    break;
                if(key ==  "Circular") {
                    getline(token, key, '/');
                    if(key == ".DS_Store")
                        break;
                    string outputfilename =   "Output/Circular_" +  key +"_";
                    
                    getline(token, key, '/');
                    boost::algorithm::trim(key);
                    if(key == ".DS_Store")
                        break;
                    cout << key << endl;
                    
                    std::istringstream keytoken(key);
                    std::getline(keytoken, value, '.');
                    
                    //iesParser->Parse(p, path, value);
                    iesParserToCSV->Parse(p, outputfilename, value);
                    break;
                }
            }
        }
    }
    //iesParserToCSV->outputFile.close();
    
//    if((pDIR=opendir(finalpath.c_str()))) {
//        while((entry = readdir(pDIR))){
//            if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ) {
//                string filename = finalpath + entry->d_name;
//                iesParser->Parse(path, filename);
//            }
//        }
//        closedir(pDIR);
//    }
    cout << "done " << endl;
}


