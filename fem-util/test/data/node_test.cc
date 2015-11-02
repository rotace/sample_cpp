//----------------------------------------------------------------------
/**
   @file node_test.cc
   @brief Node Unit Test Program
   
   @author Shibata
   @date 2014-12-20(土) 13:44:41
   
***********************************************************************/

#include "node.hpp"
#include "gtest/gtest.h"

TEST(Node, DefaultConstructor){
  const XYZ q(0,0,0);
  Node node;
  EXPECT_EQ(q, node.grid());
  EXPECT_EQ(0, node.index());
}

TEST(Node, Constructors){
  
  // constructor
  const XYZ u(1,2,3);
  Node node2(u,1);
  EXPECT_EQ(u, node2.grid());
  EXPECT_EQ(1, node2.index());

  // copy constructor
  Node node3 = node2;
  EXPECT_EQ(u, node3.grid());
  EXPECT_EQ(1, node3.index());
  Node node4(node2);
  EXPECT_EQ(u, node4.grid());
  EXPECT_EQ(1, node4.index());

  // copy (prohibited)
  // Node node5;
  // node5 = node2;
  // EXPECT_EQ(u, node4.grid());
  // EXPECT_EQ(1, node4.index());
}


