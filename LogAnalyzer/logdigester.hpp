//
//  logdigester.hpp
//  LogAnalyzer
//
//  Created by Luigi Maisto on 05/08/2016.
//  Copyright © 2016 Luigi Maisto. All rights reserved.
//

#ifndef logdigester_hpp
#define logdigester_hpp
#include <string>
#include <vector>
#include <unordered_map>
#include "statement.hpp"
#include "tuple.hpp"

class digester {
    std::string filename;
    std::vector<std::string> logs;
    std::vector<std::string> zlogs;
    std::unordered_map<std::size_t, Tuple> digestMap;
    
public:
    digester(const std::string& name): filename(name) {}
    digester(const std::vector<std::string>& lfiles): logs(lfiles){}
    
    void digest();
    
};

#endif /* logdigester_hpp */