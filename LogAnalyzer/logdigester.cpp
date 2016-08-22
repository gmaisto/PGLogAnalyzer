//
//  logdigester.cpp
//  LogAnalyzer
//
//  Created by Luigi Maisto on 05/08/2016.
//  Copyright © 2016 Luigi Maisto. All rights reserved.
//

#include "logdigester.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>
//#include <boost/iostreams/filtering_stream.hpp>
//#include <boost/iostreams/filter/gzip.hpp>
#include <regex>
#include <vector>
#include "statement.hpp"
#include "prettyprint.hpp"





void digester::digest()
{


	bool newline = true;


	std::string linebuffer;
	std::string fulline;
	std::regex expr("\\s+");
	std::string fmt{" "};
	std::cmatch res;
	std::regex rx("duration: (\\d+\\.\\d+) ms.+statement: (.+)");

	for ( auto filename : logs )
	{
		std::ifstream file(filename);

		while (file && getline(file, linebuffer))
		{
			if (linebuffer.length() == 0)continue;
			if (boost::algorithm::starts_with(linebuffer, "LOG"))
			{
				if (newline == false)
				{

					std::string str = std::regex_replace(fulline, expr, fmt);


					if (std::regex_search(str.c_str(), res, rx))
					{

						float rt = std::stof(res[1]);
						Statement st(res[2], rt);
						// std::size_t _chash = st.getHash();

						if (!digestMap.count(res[2]))
						{
							Tuple::Tuple _tuple(st);
							_tuple.addOneToCount();
							_tuple.addTiming(rt);
							digestMap[res[2]] = _tuple;
						}
						else
						{
							digestMap[res[2]].addOneToCount();
							digestMap[res[2]].addTiming(rt);
						}
					}
				}
				newline = true;
				fulline = linebuffer;
				lines++;
			}
			else
			{
				fulline += linebuffer;
				newline = false;
			}
		}

	}
	/*

	  for ( auto filename : zlogs ) {
	  std::ifstream file(filename,std::ios_base::in | std::ios_base::binary);

	  try {
	  boost::iostreams::filtering_istream in;
	  in.push(boost::iostreams::gzip_decompressor());
	  in.push(file);

	  for(std::string istr; std::getline(in, istr); )
	  {
	  if (istr.length() == 0)continue;

	  if (boost::algorithm::starts_with(istr, "LOG")) {
	  if(newline == false) {

	  std::string nstr = std::regex_replace(fulline, expr, fmt);


	  if(std::regex_search(nstr.c_str(), res, rx)) {
	  //std::cout << res[1] << " " << res[2] << "\n";

	  // if(str.find("statement: ") != std::string::npos) {
	  //     std::string realstatement = str.substr(str.find("statement: ") + 11);


	  float rt = std::stof(res[1]);
	  Statement st(res[2], rt);

	  if(!digestMap.count(st.getHash())) {
	  Tuple _tuple(st);
	  _tuple.addOneToCount();
	  _tuple.addTiming(rt);
	  digestMap[st.getHash()] = _tuple;
	  } else {
	  digestMap[st.getHash()].addOneToCount();
	  digestMap[st.getHash()].addTiming(rt);
	  }
	  }
	  }
	  newline = true;
	  fulline = istr;
	  lines++;
	  } else {
	  fulline += istr;
	  newline = false;
	  }

	  }
	  }
	  catch(const boost::iostreams::gzip_error& e) {
	  std::cout << e.what() << '\n';
	  }


	  }
	*/


	worked = true; // set the flag to true.
    queries = digestMap.size();

	//  std::cout << "Lines found: " << lines << std::endl;
	//  std::cout << "Map Elements: " << digestMap.size() << std::endl;
	//
	//  for(auto i : digestMap) {
	//      //<< i.first
	//    std::cout << "\nRun: " << i.second.getCount() <<  "\nTimings: " << i.second.getTimings() << '\n';
	//      /* auto stats = i.second.getStats();
	//      std::cout << "Count: " << std::get<0>(stats) << " Min: " << std::get<1>(stats) << " Max: " << std::get<2>(stats) << " Mean: " << std::get<3>(stats) << " Var: " << std::get<4>(stats) << " Median " << std::get<5>(stats) << '\n';
	//      std::cout << i.second.getStatement().statement() << std::endl; */
	//
	//      /* Tuple::Stats stats = i.second.getStatistics();
	//      std::cout << "Count: " << stats.samples << " Min: " << stats.min << " Max: " << stats.max << " Mean: " << stats.mean << " Var: " << stats.variance << " Median " << stats.median << '\n'; */
	//      std::cout << i.second << std::endl;
	//
	//  }

}
