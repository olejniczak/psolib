/**
 * The following code declares class Swarm,
 * which is a collection of particles
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
#ifndef PSOLIB_SWARM_HPP
#define PSOLIB_SWARM_HPP

#include "Constants.hpp"

#include <vector>
#include <boost/shared_ptr.hpp>

namespace psolib {

  class Algorithm;
  class Particle;
  typedef boost::shared_ptr<Particle> PParticle;
  
  class Swarm
  {      
    public:
      Swarm(const Particle&, size_t, const MinMax&);

      Swarm(const Swarm&);
      Swarm& operator=(const Swarm&);
      ~Swarm();
    public:
      size_t size() const;
      Particle& operator[](size_t);
      const Particle& operator[](size_t) const;
      const Particle& GetBest() const;
      const Particle& GetWorst() const;
      const Particle& Sort();
    public:
      void Initialize();
      void Evaluate(bool flag_ = false);
    protected:
    private:
      const Particle*        particle;
      std::vector<PParticle> particles;
      MinMax                 minmax;
  };

} /* namespace psolib */

#endif /*PSO_SWARM_HPP */
