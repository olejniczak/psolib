project(psolib)
SET(psolib_SOURCES 
  Algorithm.cpp
  Parameters.cpp
  Particle.cpp
  PSO.cpp
  random.cpp
  RealParticle.cpp
  Scaling.hpp
  Statistics.cpp
  Swarm.cpp
) 

ADD_LIBRARY(psolib ${psolib_SOURCES})