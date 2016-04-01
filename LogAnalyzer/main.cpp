//
//  main.cpp
//  LogAnalyzer
//
//  Created by Luigi Maisto on 01/04/16.
//  Copyright © 2016 Luigi Maisto. All rights reserved.
//

#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
int opt;

int main(int argc, const char * argv[]) {
    
    // Declare the supported options.
    po::options_description desc("Allowed options");
    
    desc.add_options()
    ("help", "produce help message")
    ("compression", po::value<int>(), "set compression level")
    ("optimization,O", po::value<int>(&opt)->default_value(10),"optimization level")
    ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }
    
    if (vm.count("compression")) {
        std::cout << "Compression level was set to "
        << vm["compression"].as<int>() << ".\n";
    } else {
        std::cout << "Compression level was not set.\n";
    }
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
