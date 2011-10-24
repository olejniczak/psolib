/**
 * @mainpage
 * @par O PSOlib:
 * Biblioteka programistyczna do optymalizacji za pomoc&#261; algorytmów PSO.
 * @par Praca dyplomowa magisterska
 * @par POLITECHNIKA WARSZAWSKA
 * @par Wydzia&#322; Elektroniki i Technik Informacyjnych
 * @par Instytut Automatyki
 * @par Temat: Œrodowisko programistyczne do optymalizacji przy wykorzystaniu algorytmów inteligencji masowej.
 * Praca wykonana pod kierunkiem
 * Dr in?. Paw&#322;a Wnuka
 * @author Przemys&#322;aw Olejniczak
 * @date 2011.06.24
 * @version 0.1.0
*/

/**
 * The following code declares class Algorithm,
 * base class for every variant of Particle Swarm Optimization
 *
 * See <WEBSITE> for documentation.
 *
 * @author Copyright &copy 2011 Przemys&#322;aw Olejniczak.
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
      static bool TerminateUponConvergence(Algorithm&);
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
      double ConvergenceDiff() const { return conv_diff; }
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
      double       conv_diff;
      double       convergence;
      bests_buf    bests;
      MinMax       minimaxi;
      Swarm        swarm;
      Particle*    gbest;
      Parameters   params;

      friend std::ostream& operator<<(std::ostream&, const Algorithm&);
  };

} /* namespace psolib */

#endif /*PSO_PSOBASE_HPP */
