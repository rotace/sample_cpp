//----------------------------------------------------------------------
/**
   @file xyz_test.cc
   @brief XYZ Unit Test Program
   
   @author Shibata
   @date 2014-12-20(土) 11:57:54
   
***********************************************************************/

#include "xyz.hpp"
#include "gtest/gtest.h"


TEST(XYZ, DefaultConstructor){
  const XYZ u;
  EXPECT_EQ(0, u.x);
  EXPECT_EQ(0, u.y);
  EXPECT_EQ(0, u.z);
}

TEST(XYZ, CopyConstructor){
  const XYZ u(1,2,3);
  const XYZ v = u;
  XYZ w;
  w = u;
  EXPECT_EQ(1, v.x);
  EXPECT_EQ(2, v.y);
  EXPECT_EQ(3, v.z);
  EXPECT_EQ(1, w.x);
  EXPECT_EQ(2, w.y);
  EXPECT_EQ(3, w.z);
}

TEST(XYZ, Calclation){
  const XYZ u(4,5,6);
  const XYZ v(1,2,3);
  XYZ w;
  w.Set(5,7,9);
  EXPECT_EQ(w, u+v);			// addition
  w.Set(3,3,3);
  EXPECT_EQ(w, u-v);			// subtraction

  EXPECT_EQ(32, u*v);			// inner product
  w.Set(3,-6,3);
  EXPECT_EQ(w, u%v);			// outer product
  w.Set(2,4,6);
  EXPECT_EQ(w, 2*v);			// scalar product
  EXPECT_EQ(w, v*2);			// scalar product
  w.Set(0.5,1,1.5);
  EXPECT_EQ(w, v/2);			// scalar division
}

