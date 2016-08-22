//
//  main.cpp
//  LogAnalyzer
//
//  Created by Luigi Maisto on 01/04/16.
//  Copyright © 2016 Luigi Maisto. All rights reserved.

#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include "logdigester.hpp"
#include "prettyprint.hpp"
#include "outputter.hpp"
#include "crow_all.h"
#include "Mustache.hpp"
#include "template.h"

extern const char* VERSION;
static const int OUTPUT_LINES = 10;




namespace
{
const size_t SUCCESS = 0;
const size_t ERROR_IN_COMMAND_LINE = 1;
const size_t ERROR_UNHANDLED_EXCEPTION = 2;
} // namespace



namespace po = boost::program_options;



int main(int argc, const char * argv[])
{

	std::vector<std::string> svect;
	int output_lines;

	// Declare the supported options.
	po::options_description general("Options");
	po::options_description report("Options for report output (apply only to STDOUT and HTTP");

	try
	{


		general.add_options()
		("help", "produce help message")
		("version,v", "show program version")
		("log,f", po::value< std::vector<std::string> >()->multitoken(), "log files")
		("server,S", po::value<std::string>(), "start http server on 127.0.0.1:8088")
		("output,o", po::value<std::string>(), "output file")
		("csv", po::value<std::string>(), "csv format output file")
		("html", po::value<std::string>(), "html output file")
		("zlog,Z", po::value< std::vector<std::string> >()->multitoken(), "gzipped log files")
		;

		report.add_options()
		("num,n", po::value<int>(&output_lines)->default_value(OUTPUT_LINES), "Number of SQL queries shown on report")
		("mean", "Sort by mean query execution time")
		("count", "Sort by number of executions")
		("max", "Sort by Max execution time")
		("min", "Sort by Min execution time")
		(",R", "Reverse the order of timings (fast -> slow)")
		;

		general.add(report);


		po::variables_map vm;

		try
		{
			po::store(po::parse_command_line(argc, argv, general), vm);
			po::notify(vm);

			if (vm.count("help"))
			{
				std::cout << general << "\n";
				return SUCCESS;
			}

			if (vm.count("version"))
			{
				std::cout << VERSION << " (" << __TIMESTAMP__ << ')' << "\n";
				return SUCCESS;
			}


			if (vm.count("zlog"))
			{
				svect = vm["zlog"].as< std::vector<std::string> >();
				for (auto s : svect)
				{
					std::cout << s << std::endl;
				}
			}

			digester myDigester;
			Output::Sortpar osp = Output::Sortpar::mean;

			int optsemaphore = 0;
			if (vm.count("count"))
			{
				osp = Output::Sortpar::num;
				optsemaphore++;

			}
			if (vm.count("mean"))
			{
				osp = Output::Sortpar::mean;
				optsemaphore++;
			}
			if (vm.count("max"))
			{
				osp = Output::Sortpar::max;
				optsemaphore++;

			}
			if (vm.count("min"))
			{
				osp = Output::Sortpar::min;
				optsemaphore++;
			}

			if (optsemaphore > 1)
			{
				std::cout << "Error: multiple sort parameter specified!" << std::endl;
				std::cout << general << std::endl;
				return ERROR_IN_COMMAND_LINE;
			}

			Output::Filter filter = {osp, Output::Target::stdout, output_lines};

			if (vm.count("log"))
			{
				//digester myDigester(vm["log"].as< std::vector<std::string> >());
				myDigester.setLogs(vm["log"].as< std::vector<std::string> >());
				myDigester.digest();
				Output::Target ot = Output::Target::stdout;
				std::string fileout = "pgloganalizer_output.txt";

				if (vm.count("output"))
				{
					ot = Output::Target::txt;
					fileout = vm["output"].as<std::string>();
				}
				else if (vm.count("html"))
				{
					ot = Output::Target::html;
					fileout = vm["html"].as<std::string>();
				}
				else if (vm.count("csv"))
				{
					ot = Output::Target::csv;
					fileout = vm["csv"].as<std::string>();
				}

				if (!vm.count("server"))
				{
					Outputter pgout(myDigester, ot, fileout);
					pgout.Produce(filter);
				}

			}

			if (vm.count("server") && !vm.count("log"))
			{
				std::cerr << "Error: missing -log parameter" << std::endl;
				return ERROR_IN_COMMAND_LINE;
			}

			if (vm.count("server"))
			{
				std::cout << "Http server start on: " << vm["server"].as<std::string>() << ".\n";
				crow::SimpleApp app;

				Kainjow::Mustache::Data data;
				data.set("analysistime", myDigester.getRundate());
				data.set("loglines", std::to_string(myDigester.getLines()));
				data.set("queriesfound", std::to_string(myDigester.getQueries()));

				std::string response(std::begin(htmltemplate_html), std::end(htmltemplate_html));
				CROW_ROUTE(app, "/")([&]()
				{
					Kainjow::Mustache tmpl(response);


					return tmpl.render(data);
					//  return response;
				});
				app.port(18080).run();
			}

			if (!vm.count("log") || vm.empty())
			{
				std::cout << general << std::endl;
			}
		}
		catch (po::error &e)
		{
			std::cout << "Command line parse error: " << e.what() << std::endl;
			return ERROR_IN_COMMAND_LINE;
		}

	}
	catch (std::exception& e)
	{
		std::cout << "Unknown error: " << e.what() << std::endl;
		return ERROR_UNHANDLED_EXCEPTION;
	}



	return SUCCESS;
}
