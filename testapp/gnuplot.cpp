#include "gnuplot.h"

#if defined(_WIN32) || defined(_WIN64)
  #define popen _popen
  #define pclose _pclose
#endif

gnuplot::gnuplot(const std::string& path_)
{
    pipe = popen((path_ + "gnuplot -p").c_str(), "w");
}

gnuplot::~gnuplot()
{
    command("exit");
    pclose(pipe);
}

void gnuplot::command(const std::string& cmd_)
{
    fprintf(pipe, (cmd_ + "\n").c_str());
}

gnuplot& gnuplot::operator << (const std::string& cmd_)
{
    command(cmd_);
    return *this;
}
