//----------------------------------------------------------------------
/**
   @file cell_test.cc
   @brief Cell Unit Test Program
   
   @author Shibata
   @date 2014-12-20(土) 14:31:49
   
***********************************************************************/

#include "cell.hpp"
#include "gtest/gtest.h"

// Default Constructor is prohibited

// TEST(Cell, DefaultConstructor){
//   Cell cell;
//   EXPECT_EQ((size_t)20, cell.nodes().size());
//   EXPECT_EQ((size_t)6, cell.faces().size());
//   EXPECT_EQ(0, cell.index());
// }

TEST(Cell, Constructors){
  
  // constructor
  Cell cell2(4,3,1);
  EXPECT_EQ((size_t)4, cell2.node_ptrs().size());
  EXPECT_EQ((size_t)3, cell2.face_ptrs().size());
  EXPECT_EQ(1, cell2.index());

  // copy constructor
  Cell cell3 = cell2;
  EXPECT_EQ((size_t)4, cell3.node_ptrs().size());
  EXPECT_EQ((size_t)3, cell3.face_ptrs().size());
  EXPECT_EQ(1, cell3.index());
  Cell cell4(cell2);
  EXPECT_EQ((size_t)4, cell4.node_ptrs().size());
  EXPECT_EQ((size_t)3, cell3.face_ptrs().size());
  EXPECT_EQ(1, cell4.index());

  // copy (prohibited)
  // Cell cell5;
  // cell5 = cell2;
  // EXPECT_EQ((size_t)4, cell5.nodes().size());
  // EXPECT_EQ(1, cell5.index());

}




