#ifndef OPTSUITE_H
#define OPTSUITE_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <RealParticle.hpp>
#include <Algorithm.hpp>
#include <muParser/muParser.h>
#include "gnuplot.h"

class optimization_suite
{
private:
  // singleton
  optimization_suite();
  optimization_suite(const optimization_suite&);
  optimization_suite& operator=(const optimization_suite&);
  ~optimization_suite();
private:
  static void Initializer(psolib::Particle& particle_);                                                                                
  static double Evaluator(psolib::Position& position_);
public:
  static optimization_suite& getInstance();
  template <class A>
  void create_algorithm(size_t swarm_size_ = 20)
  {
    if (algorithm) delete algorithm;
    algorithm = new A(particle, swarm_size_);
  }
  void load_from_file(const std::string& filename_);
  void optimize();
  void step(int count_ = 1);
  bool done() { return algorithm->Done(); }
  bool ready();
private:
  void replace_tokens(std::string& cmd_, const std::string& token_, const std::string& value_);
private:
  double               minx, maxx, miny, maxy;
  std::string          objective_function;
  int                  swarm_size;
  int                  iterations;
  psolib::RealParticle particle;
  psolib::Algorithm*   algorithm;
  mu::Parser           parser;
  double               x, y;
  typedef boost::shared_ptr<gnuplot> pplot;
  std::vector<pplot>   plots;
};

#endif
