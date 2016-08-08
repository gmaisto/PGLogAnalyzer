//
//  statement.hpp
//  LogAnalyzer
//
//  Created by Luigi Maisto on 05/08/2016.
//  Copyright © 2016 Luigi Maisto. All rights reserved.
//

#ifndef statement_hpp
#define statement_hpp

#include <string>

class Statement {
    private:
    //std::string basestmt;
    std::string stmt;
    float duration;
    std::size_t hash;
    
    
    
public:
    
    Statement(std::string s = "", float const& runtime = 0.0): stmt(s) {
        hash = std::hash<std::string>{}(stmt);
        duration = runtime;
        count++;
    }
    
    std::size_t getHash() {
        return hash;
    }
    
    long getCount() {
        return count;
    }
    
    float getDuration() const {
        return duration;
    }
    
    std::string statement() {
        return stmt;
    }
    
    static long count;
    
};

#endif /* statement_hpp */
