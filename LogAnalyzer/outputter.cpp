//
//  outputter.cpp
//  LogAnalyzer
//
//  Created by Luigi Maisto on 12/08/2016.
//  Copyright © 2016 Luigi Maisto. All rights reserved.
//

#include "outputter.hpp"
#include <iostream>
#include <fstream>
#include "version.h"
#include "tuple.hpp"
#include "prettyprint.hpp"


std::ostream& operator<<(std::ostream& os,  Tuple::Tuple& obj)
{
    Tuple::Stats stats = obj.getStatistics();
    os << "Count: " << stats.samples << " Min: " << stats.min << " Max: " << stats.max << " Mean: " << stats.mean << " Var: " << stats.variance << " Median " << stats.median << '\n';

    return os;
}



void Outputter::Produce() {

    std::ofstream fout;

    if(type == Output::Target::stdout) {
        if(idg.getWorked() == true) {
            std::cout << "PGLogAnalyzer (" << VERSION << ")\n";
            std::cout << "Date: " << __TIMESTAMP__ << '\n';
            std::cout << "\nNumber of executed queries: "  << idg.getLines() << '\n';
            auto dm = idg.getDigestMap();


            std::cout << "Number of different SQL Queries found: " << dm.size() << '\n' << std::endl;

            for(auto i : dm) {
                long eq = i.second.getCount();
                std::cout << "Query Executed " << eq << ((eq > 1) ? " times." : " time.") << "\nTimings: " << i.second.getTimings() << '\n';
                std::cout << i.second << std::endl;
            }
        }
    } else if(type == Output::Target::txt) {
        if(idg.getWorked() == true) {
            try {
                fout.open( dst );
                if(!fout.is_open()) {
                    throw std::runtime_error("Unable to open output file");
                }

                fout << "PGLogAnalyzer (" << VERSION << ")\n";
                fout << "Date: " << __TIMESTAMP__ << '\n';
                fout << "\nNumber of executed queries: "  << idg.getLines() << '\n';
                auto dm = idg.getDigestMap();


                fout << "Number of different SQL Queries found: " << dm.size() << '\n' << std::endl;

                for(auto i : dm) {
                    long eq = i.second.getCount();
                    fout << "Query Executed " << eq << ((eq > 1) ? " times." : " time.") << "\nTimings: " << i.second.getTimings() << '\n';
                    fout << i.second << std::endl;

                }

                fout.close();

            } catch(std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                throw;
            }

        }
    } else if(type == Output::Target::csv) {
        if(idg.getWorked() == true) {
            try {
                fout.open( dst );
                if(!fout.is_open()) {
                    throw std::runtime_error("Unable to open output file");
                }

                fout << "PGLogAnalyzer (" << VERSION << ")\n";
                fout << "Date: " << __TIMESTAMP__ << '\n';
                fout << "\nNumber of executed queries: "  << idg.getLines() << '\n';
                auto dm = idg.getDigestMap();


                fout << "Number of different SQL Queries found: " << dm.size() << '\n' << std::endl;

                for(auto i : dm) {
                    long eq = i.second.getCount();
                    fout << "Query Executed " << eq << ((eq > 1) ? " times." : " time.") << "\nTimings: " << i.second.getTimings() << '\n';
                    fout << i.second << std::endl;

                }

                fout.close();

            } catch(std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                throw;
            }
            
        }
    } else if(type == Output::Target::html) {
        if(idg.getWorked() == true) {
            try {
                fout.open( dst );
                if(!fout.is_open()) {
                    throw std::runtime_error("Unable to open output file");
                }

                fout << "PGLogAnalyzer (" << VERSION << ")\n";
                fout << "Date: " << __TIMESTAMP__ << '\n';
                fout << "\nNumber of executed queries: "  << idg.getLines() << '\n';
                auto dm = idg.getDigestMap();


                fout << "Number of different SQL Queries found: " << dm.size() << '\n' << std::endl;

                for(auto i : dm) {
                    long eq = i.second.getCount();
                    fout << "Query Executed " << eq << ((eq > 1) ? " times." : " time.") << "\nTimings: " << i.second.getTimings() << '\n';
                    fout << i.second << std::endl;

                }

                fout.close();

            } catch(std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                throw;
            }
            
        }
    }
}
