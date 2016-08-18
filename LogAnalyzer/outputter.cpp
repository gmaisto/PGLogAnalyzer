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

/* formatting float with comma separator insead of point. No cares of Locale */
template <typename T>
struct comma_separator : std::numpunct<T>
{
    typename std::numpunct<T>::char_type do_decimal_point() const
    {
        return ',';
    }
};

template <typename T>
std::basic_ostream<T>& comma_sep(std::basic_ostream<T>& os)
{
    os.imbue(std::locale(std::locale(""), new comma_separator<T>));
    return os;
}

// Sort Tuples by mean function
bool sortByMean(const Tuple::Tuple &lhs, const Tuple::Tuple &rhs) {
    auto first = const_cast<Tuple::Tuple&>(lhs).getStatistics();
    auto second = const_cast<Tuple::Tuple&>(rhs).getStatistics();
    return first.mean < second.mean;
}

// reverse Sort Tuples by mean function
bool sortByMeanR(const Tuple::Tuple &lhs, const Tuple::Tuple &rhs) {
    auto first = const_cast<Tuple::Tuple&>(lhs).getStatistics();
    auto second = const_cast<Tuple::Tuple&>(rhs).getStatistics();
    return first.mean > second.mean;
}

// Sort Tuples by max function
bool sortByMax(const Tuple::Tuple &lhs, const Tuple::Tuple &rhs) {
    auto first = const_cast<Tuple::Tuple&>(lhs).getStatistics();
    auto second = const_cast<Tuple::Tuple&>(rhs).getStatistics();
    return first.max < second.max;
}


// Sort Tuples by count function
bool sortByCount(const Tuple::Tuple &lhs, const Tuple::Tuple &rhs) {
    auto first = const_cast<Tuple::Tuple&>(lhs).getStatistics();
    auto second = const_cast<Tuple::Tuple&>(rhs).getStatistics();
    return first.samples < second.samples;
}

bool sortByCountR(const Tuple::Tuple &lhs, const Tuple::Tuple &rhs) {
    auto first = const_cast<Tuple::Tuple&>(lhs).getStatistics();
    auto second = const_cast<Tuple::Tuple&>(rhs).getStatistics();
    return first.samples > second.samples;
}



void Outputter::Produce(Output::Filter &ft) {

  std::ofstream fout;

  if(ft.tg == Output::Target::stdout) {
    if(idg.getWorked() == true) {
      std::cout << "PGLogAnalyzer (" << VERSION << ")\n";
      std::cout << "Date: " << __TIMESTAMP__ << '\n';
      std::cout << "\nNumber of executed queries: "  << idg.getLines() << '\n';
      auto dm = idg.getDigestMap();

      std::vector<Tuple::Tuple> values;
      for(auto i : dm) {
          values.push_back(i.second);
      }

      //sort vector of Tuples
      std::sort(values.begin(), values.end(), sortByCountR);

      std::cout << "Number of different SQL Queries found: " << dm.size() << '\n' << std::endl;

      for( int x = 0; x < ft.lines; x++) {
            if(x > values.size())
                break;
          std::cout << values[x].getStatement().statement() << '\n';
            std::cout << values[x] << std::endl;
      }

//      for(auto i : dm) {
//        long eq = i.second.getCount();
//        std::cout << "Query Executed " << eq << ((eq > 1) ? " times." : " time.") << "\nTimings: " << i.second.getTimings() << '\n';
//        std::cout << i.second << std::endl;
//      }
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

        std::cout << "PGLogAnalyzer (" << VERSION << ")\n";
        std::cout << "Date: " << __TIMESTAMP__ << '\n';
        std::cout << "\nNumber of executed queries: "  << idg.getLines() << '\n';
        auto dm = idg.getDigestMap();


          std::cout << "Number of different SQL Queries found: " << dm.size() << '\n' << std::endl;
        //  os << "Count: " << stats.samples << " Min: " << stats.min << " Max: " << stats.max << " Mean: " << stats.mean << " Var: " << stats.variance << " Median " << stats.median << '\n';

          fout << "SQL Query;Executions;Min (ms);Max (ms);Mean (ms);Variance (quadratic);Median (ms)\n";
        for(auto i : dm) {
          long eq = i.second.getCount();
          Tuple::Stats ts = i.second.getStatistics();
          fout << '"' << i.first <<  "\";" << eq << ';' << comma_sep << ts.min << ';' << comma_sep << ts.max << ';' << comma_sep << ts.mean << ';' << comma_sep << ts.variance << ';' << comma_sep << ts.median << '\n';
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
