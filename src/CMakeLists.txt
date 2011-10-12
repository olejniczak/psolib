SET ( psolib_SOURCES 
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

# Optionally you can use file glob (uncomment the next line)
# file( GLOB psolib_SOURCES *.cpp )below

add_library( psolib ${psolib_SOURCES} )