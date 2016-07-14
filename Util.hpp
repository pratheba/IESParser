//
//  Util.hpp
//  IESParser
//
//  Created by Pratheba Selvaraju on 6/14/16.
//  Copyright © 2016 Pratheba Selvaraju. All rights reserved.
//

#ifndef Util_hpp
#define Util_hpp

#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

unordered_set<string> lightdistribution{"Direct", "Indirect", "Semi-Direct", "Semi-Indirect", "General diffuse"};

class Util {
public:
    Util();
private:
    
};

#endif /* Util_hpp */
