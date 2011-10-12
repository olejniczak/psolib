/**
 * The following code declares class PSO, which implements
 * original, classic PSO algorithm proposed
 * by Eberhart and Kennedy in "Particle Swarm Optimization" (1995)
 * Proceedings of IEEE International Conference 
 * on Neural Networks. IV. pp. 1942–1948.
 *
 * See <WEBSITE> for documentation.
 *
 * @author Copyright &copy 2011 Przemys³aw Olejniczak.
 * @version <VERSION>
 * @date <DATE>
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 */
#ifndef PSOLIB_PSO_HPP
#define PSOLIB_PSO_HPP

#include "Algorithm.hpp"

namespace psolib {

  class PSO : public Algorithm
  {
    public:
      explicit PSO(const Particle&, size_t, MinMax mm_ = Minimize);
      ~PSO();
    protected:
      void Move(Particle&);
      void RegisterParameters();
      void UpdateParameters();
   private:
      double inertia;
      double particle_learn;
      double swarm_learn;
  };

} /* namespace psolib */

#endif /* PSOLIB_PSO_HPP */