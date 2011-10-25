/**
 * @class Parameters
 * @brief Heterogeneous Container for parameters
 *  
 * This class can store parameters of types:
 * double, int, bool and string
 * You cann access this parameter by name
 * given as string key.
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
#ifndef PSOLIB_PARAMETERS_HPP
#define PSOLIB_PARAMETERS_HPP

#include <map>
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include "Exception.hpp"

namespace psolib {

  class Parameters
  {
    public:
      /**
       *
       */
      explicit Parameters();
      /**
       *
       */
      ~Parameters();
    public:
      /**
       *
       */
      void Load(const std::string filename_);
      /**
       *
       */
      void Save(const std::string filename_);
      /**
       *
       */
      template<class T>
      T Get(const std::string name_) const
      {
        Container::const_iterator iparam = params.find(name_);
        if (iparam == params.end()) throw unknown_parameter(name_);
        return boost::any_cast<T>(iparam->second);
      }
      /**
       *
       */
      template<class T>
      void Set(const std::string name_, T value_ = T())
      {
        if (params.find(name_) == params.end()) throw unknown_parameter(name_);
        dirty = true;
        boost::any_cast<T>(params[name_]);
      }
      /**
       *
       */
      template<class T>
      void Add(const std::string name_, T value_ = T())
      {
        dirty = true;
        params[name_] = value_;
      }
      /**
       *
       */
      void Del(const std::string name_)
      {
        if (params.find(name_) == params.end()) throw unknown_parameter(name_);
        dirty = true;
        params.erase(name_);
      }
      /**
       *
       */
      bool Dirty() const { return dirty; }
      /**
       *
       */
      bool Touch() 
      { 
        bool ret = dirty;
        dirty = false;
        return ret;
      }
      /**
       *
       */
      void Set(const std::string& name_, const std::string& value_) 
      {
        if (params.find(name_) == params.end()) throw unknown_parameter(name_);
        boost::any& param = params[name_];

        if (param.type() == typeid(double)) {
          param = boost::lexical_cast<double>(value_);
        } else if (param.type() == typeid(int)) {
          param = boost::lexical_cast<int>(value_);
        } else if (param.type() == typeid(bool)) {
          param = boost::lexical_cast<bool>(value_);
        } else if (param.type() == typeid(std::string)) {
          param = value_;
        } else throw parameter_type(name_, param.type().name());
        Touch();
      }
      /**
       *
       */
      const std::string Get(const std::string& name_)
      {
        if (params.find(name_) == params.end()) throw unknown_parameter(name_);
        std::string ret;
        boost::any& param = params[name_];
        
        if (double* p = boost::any_cast<double>(&param)) {
          return boost::lexical_cast<std::string>(*p);
        } else if (int* p = boost::any_cast<int>(&param)) {
          return boost::lexical_cast<std::string>(*p);
        } else if (bool* p = boost::any_cast<bool>(&param)) {
          return boost::lexical_cast<std::string>(*p);
        } else if (std::string* p = boost::any_cast<std::string>(&param)) {
          return *p;
        } else throw parameter_type(name_, param.type().name());
      }
    private:
      typedef std::map<std::string, boost::any> Container;
      Container params;
      bool dirty;
  };

} /* namespace psolib */

#endif /*PSO_PARAMETERS_HPP */
