/**
 * gnuplot
 * Class for communication with gnuplot plotting tool
 * gnuplot have to be in the system path
 *
 * See <WEBSITE> for documentation.
 *
 * @author Copyright &copy 2011 Przemys³aw Olejniczak.
 * @version <VERSION>
 * @date <DATE>
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <cstdio>
#include <string>

class gnuplot
{
public:
  gnuplot();
  ~gnuplot();
  bool valid() const { return pipe != 0; }
  void flush() { std::fflush(pipe); }
  gnuplot& operator << (const std::string&);
private:
  void command(const std::string&);
private:
  FILE*       pipe;
};

#endif