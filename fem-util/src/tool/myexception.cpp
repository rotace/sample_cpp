//----------------------------------------------------------------------
/**
   @file myexception.cpp
   @brief 
   
   @author Shibata
   @date 2015-02-11(水) 01:34:44
   
***********************************************************************/

#include "myexception.hpp"

#include <iostream>

const char* tool::MyException::what() const throw()
{
  std::cerr << std::endl;
  std::cerr << "ERROR!" << std::endl;
  std::cerr << *boost::get_error_info<boost::throw_file>(*this)
	    << "(" << *boost::get_error_info<boost::throw_line>(*this) << ")"
	    << std::endl;
  std::cerr << "FUNCTION : "
	    << *boost::get_error_info<boost::throw_function>(*this) << std::endl;
  std::cerr << "WHAT     : ";
  return msg_.c_str();
}

