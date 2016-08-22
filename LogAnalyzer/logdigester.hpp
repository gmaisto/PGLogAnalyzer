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
    long queries;
    bool worked;
    char mbstr[100];

public:
    digester(const std::string& name): filename(name), lines(0L), queries(0L), worked(false) {
        std::time_t t = std::time(nullptr);
        std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t));
        rundate = mbstr;
    }
    digester(const std::vector<std::string>& lfiles): logs(lfiles), lines(0L), queries(0L), worked(false) {
        std::time_t t = std::time(nullptr);
        std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t));
        rundate = mbstr;
    }
    digester(): filename(""), lines(0L), worked(false) {
        std::time_t t = std::time(nullptr);
        std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t));
        rundate = mbstr;
    }


    void setLogfile(const std::string& name) { filename = name; }
    void setLogs(const std::vector<std::string> &vect) { logs = vect; }

    void digest();

    long getLines() const { return lines; }

    bool getWorked() const { return worked; }

    std::string getRundate() const { return rundate; }

    long getQueries() const { return queries; }

    std::map<std::string, Tuple::Tuple>  getDigestMap() const {
        return digestMap;
    }

};


#endif /* logdigester_hpp */
