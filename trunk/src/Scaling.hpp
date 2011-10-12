/**
 * The following code declares class Scaling,
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
#ifndef PSOLIB_SCALING_HPP
#define PSOLIB_SCALING_HPP

namespace psolib {

  class Scaling
  {
    public:
      Scaling();
      ~Scaling();
    protected:
      virtual void initialize();
      virtual void optimize();
      virtual void step();
    private:
      class Swarm* swarm;
      class Particle* gbest;
  };

} /* namespace psolib */

#endif /*PSO_SCALING_HPP */
