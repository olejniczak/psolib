/**
 * Exception classes for pso-library
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
#ifndef PSOLIB_EXCEPTION_HPP
#define PSOLIB_EXCEPTION_HPP

#include <exception>
#include <string>

namespace psolib {

  class unknown_parameter : public std::exception
  {
    public:
      unknown_parameter(const std::string& param_) throw()
      {
        msg = "Unknown parameter: <" + param_ + ">.";
      }
      ~unknown_parameter() throw();
      const char* what() const throw() { return msg.c_str(); }
    private:
      std::string msg;
  };

  class parameter_type : public std::exception
  {
    public:
      parameter_type(const std::string& param_, const std::string& type_) throw()
      {
        msg = "Type of parameter: <" + param_ + "> is " + type_;
      }
      ~parameter_type() throw();
      const char* what() const throw() { return msg.c_str(); }
    private:
      std::string msg;
  };

} /* namespace psolib */

#endif