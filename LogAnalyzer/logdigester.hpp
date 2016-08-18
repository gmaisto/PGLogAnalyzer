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
#include <map>
#include "statement.hpp"
#include "tuple.hpp"
#include <ctime>




class digester {
    std::string filename;
    std::string rundate;
    std::vector<std::string> logs;
    std::vector<std::string> zlogs;
    std::map<std::string, Tuple::Tuple> digestMap;
    long lines;
    bool worked;

public:
    digester(const std::string& name): filename(name), lines(0L), worked(false) {
        std::time_t t = std::time(nullptr);
        rundate = std::asctime(std::localtime(&t));
    }
    digester(const std::vector<std::string>& lfiles): logs(lfiles), lines(0L), worked(false) {
        std::time_t t = std::time(nullptr);
        rundate = std::asctime(std::localtime(&t));
    }
    digester(): filename(""), lines(0L), worked(false) {
        std::time_t t = std::time(nullptr);
        rundate = std::asctime(std::localtime(&t));
    }


    void setLogfile(const std::string& name) { filename = name; }
    void setLogs(const std::vector<std::string> vect) { logs = vect; }

    void digest();

    long getLines() const { return lines; }

    bool getWorked() const { return worked; }

    std::string getRundate() const { return rundate; }

    std::map<std::string, Tuple::Tuple>  getDigestMap() const {
        return digestMap;
    }

};


#endif /* logdigester_hpp */
