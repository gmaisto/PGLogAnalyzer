//
//  outputter.hpp
//  LogAnalyzer
//
//  Created by Luigi Maisto on 12/08/2016.
//  Copyright © 2016 Luigi Maisto. All rights reserved.
//

#ifndef outputter_hpp
#define outputter_hpp

#include "logdigester.hpp"
#include <string>


namespace Output {

    enum Target {
        stdout,
        txt,
        csv,
        html
    };

}

class Outputter {
private:
    Output::Target type;
    digester idg;
    std::string dst;

public:
    Outputter(digester const &dg, Output::Target otype, std::string const &ofile): type(otype), dst(ofile),idg(dg) {};

    void Produce();

};




#endif /* outputter_hpp */
