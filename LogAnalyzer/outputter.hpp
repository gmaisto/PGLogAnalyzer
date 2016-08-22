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


namespace Output
{

enum Target
{
  stdout,
  txt,
  csv,
  html
};

enum Sortpar
{
  mean,
  max,
  min,
  median,
  num
};

struct Filter
{
  Sortpar sp;
  Target  tg;
  int     lines;
};

}

class Outputter
{
private:
  Output::Target type;
  digester idg;
  std::string dst;

public:
  Outputter(digester const &dg, Output::Target otype, std::string const &ofile): type(otype), dst(ofile), idg(dg) {};

  void Produce(Output::Filter &ft);

};




#endif /* outputter_hpp */
