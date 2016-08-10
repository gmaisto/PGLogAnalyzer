//
//  main.cpp
//  LogAnalyzer
//
//  Created by Luigi Maisto on 01/04/16.
//  Copyright © 2016 Luigi Maisto. All rights reserved.
//

#include <iostream>
#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include "logdigester.hpp"




namespace
{
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;
    const char* VERSION = "0.9 beta";

} // namespace



namespace po = boost::program_options;



int main(int argc, const char * argv[]) {
    
    std::vector<std::string> svect;

    
    // Declare the supported options.
    po::options_description desc("Options");

    try {


    desc.add_options()
    ("help", "produce help message")
    ("version,v", "show program version")
    ("log,f", po::value< std::vector<std::string> >()->multitoken(), "log files")
    ("server,S", po::value<std::string>(),"start http server on 127.0.0.1:8088")
    ("zlog,Z", po::value< std::vector<std::string> >()->multitoken(), "gzipped log files")
    ;

    
    po::variables_map vm;

        try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return SUCCESS;
    }

    if (vm.count("version")) {
        std::cout << VERSION << " (" << __TIMESTAMP__ << ')' << "\n";
        return SUCCESS;
    }


    if(vm.count("zlog")) {
        svect = vm["zlog"].as< std::vector<std::string> >();
        for(auto s : svect) {
            std::cout << s << std::endl;
        }
    }
    
    if(vm.count("log")) {
        digester myDigester(vm["log"].as< std::vector<std::string> >());
        myDigester.digest();
    }



    if (vm.count("server")) {
        std::cout << "Http server start on: " << vm["server"].as<std::string>() << ".\n";
    }

    
    if(vm.empty()) {
        std::cout << desc << std::endl;
    }
        } catch (po::error &e) {
            std::cout << "Command line parse error: " << e.what() << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }

    } catch(std::exception& e) {
        std::cout << "Unknown error: " << e.what() << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }
    return SUCCESS;
}
