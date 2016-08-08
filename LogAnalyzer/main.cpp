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


namespace po = boost::program_options;
int opt;



//using namespace Net;

//class HelloHandler : public Http::Handler {
//private:
//    std::string hello = "Hello World";
//public:
    
//    HTTP_PROTOTYPE(HelloHandler)
    
//    void onRequest(const Http::Request& request, Net::Http::ResponseWriter response) {
        //response.send(Http::Code::Ok, "Hello, World");
//        response.send(Net::Http::Code::Ok, "Test");
        
//    }
//};


int main(int argc, const char * argv[]) {
    
    std::vector<std::string> svect;
    
    // Declare the supported options.
    po::options_description desc("Allowed options");
    
    desc.add_options()
    ("help", "produce help message")
    ("compression,C", po::value<int>(), "set compression level")
    //("log,f", po::value<std::string>(), "log filename")
    ("log,f", po::value< std::vector<std::string> >()->multitoken(), "log files")
    ("optimization,O", po::value<int>(&opt),"optimization level")
    ("zlog,Z", po::value< std::vector<std::string> >()->multitoken(), "gzipped log files")
    ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }
    /*
    if (vm.count("compression")) {
        std::cout << "Compression level was set to "
        << vm["compression"].as<int>() << ".\n";
    }
    
    if (vm.count("optimization")) {
        std::cout << "Optimization level was set to "
        << opt << ".\n";
    }
    */
    
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
    
    if(vm.empty()) {
        std::cout << desc << std::endl;
    }

   // Http::listenAndServe<HelloHandler>("*:9080");
    
    // insert code here...
    //std::cout << "Hello, World!\n";
    
    
    
    return 0;
}
