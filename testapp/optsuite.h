#ifndef OPTSUITE_H
#define OPTSUITE_H

#include <Algorithm.hpp>
#include <RealParticle.hpp>                                                                                                             
#include <PSO.hpp>                                                                                                                      
#include <random.hpp>  
#include <muParser/muParser.h>

#include <iostream>

class optimization_suite
{
private:
  // singleton
  optimization_suite() 
   : real_particle(2, Evaluator), pso(0)
  {
    real_particle.Initializer(Initializer);
    parser.DefineVar("x", &x);
    parser.DefineVar("y", &y);
  }
  optimization_suite(const optimization_suite&);
  optimization_suite& operator=(const optimization_suite&);
  ~optimization_suite() { if (pso) delete pso; }
public:
  void init(double minx_, double maxx_, double miny_, double maxy_, const std::string obj_fun_, int count_)
  {
    minx = minx_;
    maxx = maxx_;
    miny = miny_;
    maxy = maxy_;
    if (pso) delete pso;
    pso = new psolib::PSO(real_particle, count_);
    parser.SetExpr(obj_fun_);
  }
  
  void optimize()
  {
    pso->Initialize();                                                                                                                   
    std::cout << "Initial swarm:" << std::endl << pso << std::endl;                                                                                    
    pso->Optimize();                                                                                                                     
    std::cout << "Optimized swarm:" << std::endl  << pso << std::endl;                          
  }  
  
  static void Initializer(psolib::Particle& particle_)                                                                                
  {                                                                                                                                   
    optimization_suite& opt = optimization_suite::getInstance();
    psolib::RealParticle& part = *dynamic_cast<psolib::RealParticle*>(&particle_);                                                    
    part.GetPos()[0] = psolib::RandomReal(opt.minx, opt.maxx);                                                                                
    part.GetPos()[1] = psolib::RandomReal(opt.miny, opt.maxy);                                                                                  
    part.GetVel()[0] = 0;                                                                                                             
    part.GetVel()[1] = 0;                                                                                                             
  };               

  static double Evaluator(psolib::Position& position_)
  {
    psolib::RealPosition& pos = *dynamic_cast<psolib::RealPosition*>(&position_);
    optimization_suite& opt = optimization_suite::getInstance();
    opt.x = pos[0];
    opt.y = pos[1];
    return opt.parser.Eval();
  }     
  
  bool ready() { return pso; }
  
  static optimization_suite& getInstance()
  {
    static optimization_suite instance;
    return instance;
  }
private:
  double               minx, maxx, miny, maxy;
  psolib::RealParticle real_particle;
  psolib::PSO*         pso;
  mu::Parser           parser;
  double               x, y;
};

#endif
