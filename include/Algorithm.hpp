/**
 * The following code declares class Algorithm,
 * base class for every variant of Particle Swarm Optimization
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
#ifndef PSOLIB_ALGORITHM_HPP
#define PSOLIB_ALGORITHM_HPP

#include "Swarm.hpp"
#include "Parameters.hpp"
#include "Statistics.hpp"
#include "Constants.hpp"

#include <iostream>
#include <boost/circular_buffer.hpp>

namespace psolib {

  class Algorithm
  {
    public:
      typedef bool (*Terminator_t)(Algorithm&);
      static bool TerminateUponGeneration(Algorithm&);
    public:
      Algorithm(const Particle& particle_, size_t size_, MinMax mm_ = Minimize);
      virtual ~Algorithm() = 0;

      virtual void Initialize();
      virtual void Optimize();
      virtual void Move(Particle&) = 0;
      virtual void Step();
      virtual void UpdateParameters();
      virtual bool Done();

      MinMax MiniMaxi() const { return minimaxi; } 
      double Convergence() const { return convergence; }
      double ConvergencePerc() const { return conv_perc; }
    protected:
      virtual void RegisterParameters();
      size_t Iteration() const { return curr_iter; }
      size_t IterationsCount() const { return iter_count; }
    protected:
      typedef boost::circular_buffer<double> bests_buf;
      Terminator_t terminator;
      size_t       swarm_size;
      size_t       iter_count; 
      size_t       curr_iter;
      int          conv_count;
      double       conv_perc;
      double       convergence;
      bests_buf    bests;
      MinMax       minimaxi;
      Swarm        swarm;
      Particle*    gbest;
      Parameters   params;
      Statistics   stats;

      friend std::ostream& operator<<(std::ostream&, const Algorithm&);
  };

} /* namespace psolib */

#endif /*PSO_PSOBASE_HPP */
