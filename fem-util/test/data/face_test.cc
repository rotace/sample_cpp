//----------------------------------------------------------------------
/**
   @file face_test.cc
   @brief Face Unit Test Program
   
   @author Shibata
   @date 2014-12-20(土) 14:10:43
   
***********************************************************************/

#include "face.hpp"
#include "gtest/gtest.h"

// default constructor is prohibited

// TEST(Face, DefaultConstructor){
//   Face face;
//   EXPECT_EQ((size_t)9, face.nodes().size());
//   EXPECT_EQ(0, face.index());
// }


TEST(Face, Constructors){
  
  // constructor
  Face face2(4,1);
  EXPECT_EQ((size_t)4, face2.node_ptrs().size());
  EXPECT_EQ(1, face2.index());

  // copy constructor
  Face face3 = face2;
  EXPECT_EQ((size_t)4, face3.node_ptrs().size());
  EXPECT_EQ(1, face3.index());
  Face face4(face2);
  EXPECT_EQ((size_t)4, face4.node_ptrs().size());
  EXPECT_EQ(1, face4.index());

  // copy (prohibited)
  // Face face5;
  // face5 = face2;
  // EXPECT_EQ((size_t)4, face5.nodes().size());
  // EXPECT_EQ(1, face5.index());

}



