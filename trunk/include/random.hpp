/**
 * The following code declares random generators
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
#ifndef PSOLIB_RANDOM_HPP
#define PSOLIB_RANDOM_HPP

namespace psolib {

  void Seed(int);
  int RandomInt(int, int);
  double RandomReal(double min_ = 0, double max_ = 1);

} /* namespace psolib */

#endif /* PSOLIB_REALPARTICLE_HPP */
