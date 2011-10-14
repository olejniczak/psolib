#ifndef __gnuplot_h__
#define __gnuplot_h__

#include <cstdio>
#include <string>

class gnuplot
{
public:
  gnuplot(const std::string&);
  ~gnuplot();
  bool valid() const { return pipe; }
  void flush() { std::fflush(pipe); }
  gnuplot& operator << (const std::string&);
private:
  void command(const std::string&);
private:
  FILE* pipe;
};

#endif