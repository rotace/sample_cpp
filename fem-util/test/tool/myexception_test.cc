//----------------------------------------------------------------------
/**
   @file myexception_test.cc
   @brief Myexception Unit Test Program
   
   @author Shibata
   @date 2015-01-03(土) 12:18:19
   
***********************************************************************/

#include "myexception.hpp"
#include "gtest/gtest.h"

TEST(MyException, MyExceptionTest){
  
  try{
    try{
    
      BOOST_THROW_EXCEPTION( tool::MyException("EXCEPTION_TEST") );
      EXPECT_TRUE(false);

    }catch( std::exception& e){
      std::cerr << std::endl;
      std::cerr << "####### what override test" <<  std::endl;
      std::cerr << e.what() << std::endl;
      std::cerr << std::endl;

      EXPECT_TRUE(true);
      throw;
    }

  }catch(const tool::MyException& e){
    // add information
    e << tool::errmsg_info("EXECUTED IN MYEXCEPTION_TEST.CC");
    
    // display
    std::cerr << "####### boost error_info test" <<  std::endl;
    std::cerr << std::endl;
    std::cerr << "ERROR!" << std::endl;
    std::cerr << *boost::get_error_info<boost::throw_file>(e)
	      << "(" << *boost::get_error_info<boost::throw_line>(e) << ")"
	      << std::endl;
    std::cerr << "FUNCTION : "
	      << *boost::get_error_info<boost::throw_function>(e) << std::endl;
    std::cerr << "ERR_INFO : "
	      << *boost::get_error_info<tool::errmsg_info>(e) << std::endl;
    
    std::cerr << std::endl;
    std::cerr << "####### diagnostic_information" <<  std::endl;
    std::cerr << diagnostic_information(e) << std::endl;
    std::cerr << std::endl;

    EXPECT_TRUE(true);
    
  }catch(...){
    EXPECT_TRUE(false);
  }
}

// runtimeerror
TEST(MyException, RuntimeErrorTest){
  try{
    BOOST_THROW_EXCEPTION( tool::RuntimeError() );
  }catch(const tool::RuntimeError& e){
    std::cerr << e.what() << std::endl;
    std::cerr << std::endl;
  }
  try{
    BOOST_THROW_EXCEPTION( tool::RuntimeError("Cannot Open File") );
  }catch(const tool::RuntimeError& e){
    std::cerr << e.what() << std::endl;
    std::cerr << std::endl;
  }
}

// ioerror
TEST(MyException, IOErrorTest){
  try{
    BOOST_THROW_EXCEPTION( tool::IOError() );
  }catch(const tool::IOError& e){
    std::cerr << e.what() << std::endl;
    std::cerr << std::endl;
  }
  try{
    BOOST_THROW_EXCEPTION( tool::IOError("Cannot Open File") );
  }catch(const tool::IOError& e){
    std::cerr << e.what() << std::endl;
    std::cerr << std::endl;
  }
}

// logic_error
TEST(MyException, LogicErrorTest){
  try{
    BOOST_THROW_EXCEPTION( tool::LogicError() );
  }catch(const tool::LogicError& e){
    std::cerr << e.what() << std::endl;
    std::cerr << std::endl;
  }
  try{
    BOOST_THROW_EXCEPTION( tool::LogicError("Out of range!") );
  }catch(const tool::LogicError& e){
    std::cerr << e.what() << std::endl;
    std::cerr << std::endl;
  }
}
