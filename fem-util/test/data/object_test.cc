//----------------------------------------------------------------------
/**
   @file object_test.cc
   @brief Object Unit Test Program
   
   @author Shibata
   @date 2014-12-21(日) 21:17:44
   
***********************************************************************/

#include "object.hpp"
#include "gtest/gtest.h"

TEST(Object, DefaultDestructor){
  Object object;

  EXPECT_EQ(0,0);
}
