#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <cstdio>
#include <string>

class gnuplot
{
public:
  gnuplot(const std::string& plot_cmd_);
  ~gnuplot();
  bool valid() const { return pipe != 0; }
  void flush() { std::fflush(pipe); }
  gnuplot& operator << (const std::string&);
  void plot();
private:
  void command(const std::string&);
private:
  FILE*       pipe;
  std::string data_file;
  std::string plot_command;
};

#endif