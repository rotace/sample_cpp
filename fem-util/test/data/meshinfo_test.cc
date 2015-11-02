//----------------------------------------------------------------------
/**
   @file meshinfo_test.cc
   @brief Meshinfo Unit Test Program
   
   @author Shibata
   @date 2014-12-20(土) 13:13:12
   
***********************************************************************/

#include "meshinfo.hpp"
#include "gtest/gtest.h"

TEST(MeshInfo, GetNumOf){
  int a,b,c,d;
  int num_cellnodes;
  int num_cellfaces;
  int num_facenodes;
  int num_cornernodes;

  // TRIA3
  num_cellnodes = 3;
  num_cellfaces = 1;
  num_facenodes = 3;
  num_cornernodes = 3;
  a = MeshInfo::GetNumOf(MeshInfo::TRIA3,MeshInfo::CELLNODES);
  b = MeshInfo::GetNumOf(MeshInfo::TRIA3,MeshInfo::CELLFACES);
  c = MeshInfo::GetNumOf(MeshInfo::TRIA3,MeshInfo::FACENODES);
  d = MeshInfo::GetNumOf(MeshInfo::TRIA3,MeshInfo::CORNERNODES);
  EXPECT_EQ(num_cellnodes, a);
  EXPECT_EQ(num_cellfaces, b);
  EXPECT_EQ(num_facenodes, c);
  EXPECT_EQ(num_cornernodes, d);

  // QUAD4
  num_cellnodes = 4;
  num_cellfaces = 1;
  num_facenodes = 4;
  num_cornernodes = 4;
  a = MeshInfo::GetNumOf(MeshInfo::QUAD4,MeshInfo::CELLNODES);
  b = MeshInfo::GetNumOf(MeshInfo::QUAD4,MeshInfo::CELLFACES);
  c = MeshInfo::GetNumOf(MeshInfo::QUAD4,MeshInfo::FACENODES);
  d = MeshInfo::GetNumOf(MeshInfo::QUAD4,MeshInfo::CORNERNODES);
  EXPECT_EQ(num_cellnodes, a);
  EXPECT_EQ(num_cellfaces, b);
  EXPECT_EQ(num_facenodes, c);
  EXPECT_EQ(num_cornernodes, d);  
}
