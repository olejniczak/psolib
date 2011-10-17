#ifndef OPTSUITE_H
#define OPTSUITE_H

#include <RealParticle.hpp>
#include <PSO.hpp>
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
public:
  void init(double minx_, double maxx_, double miny_, double maxy_, const std::string obj_fun_, int count_);
  void optimize();
  void step(int count_ = 1);
  bool done() { return pso->Done(); }
  static void Initializer(psolib::Particle& particle_);                                                                                
  static double Evaluator(psolib::Position& position_);
  bool ready();
  static optimization_suite& getInstance();
private:
  double               minx, maxx, miny, maxy;
  psolib::RealParticle real_particle;
  psolib::PSO*         pso;
  mu::Parser           parser;
  double               x, y;
  gnuplot              plot;
};

#endif
