//----------------------------------------------------------------------
/**
   @file mesh_test.cc
   @brief Mesh Unit Test Program
   
   @author Shibata
   @date 2014-12-20(土) 14:45:17
   
***********************************************************************/

#include "mesh.hpp"
#include "gtest/gtest.h"

// Default Constructor is prohibited

// TEST(Mesh, DefaultConstructor){
  
//   const Mesh mesh;

//   // call by reference test
//   const NodeArray& nodes = mesh.nodes();
//   const FaceArray& faces = mesh.faces();
//   const CellArray& cells = mesh.cells();

//   // size check
//   EXPECT_EQ((size_t)0, nodes.size());
//   EXPECT_EQ((size_t)0, faces.size());
//   EXPECT_EQ((size_t)0, cells.size());
// }


TEST(Mesh, Constructors){

  // mesh(int        num_nodes,
  //      int        num_faces,
  //      int        num_cells,
  //      CellType   celltype)
  size_t num=10;
  MeshInfo::CellType celltype=MeshInfo::HEXA8;
  size_t facenodes=4;
  size_t cellnodes=8;
  size_t cellfaces=6;
  
  // definition
  Mesh mesh(num,num,num,celltype);

  // call by reference test
  NodeArray& nodes = mesh.nodes();
  FaceArray& faces = mesh.faces();
  CellArray& cells = mesh.cells();

  // size check
  EXPECT_EQ(num, nodes.size());
  EXPECT_EQ(num, faces.size());
  EXPECT_EQ(num, cells.size());

  // call by reference test
  const NodePtrArray& facenodes_ptr = faces[0].node_ptrs();
  const NodePtrArray& cellnodes_ptr = cells[0].node_ptrs();
  const FacePtrArray& cellfaces_ptr = cells[0].face_ptrs();
  EXPECT_EQ(facenodes, facenodes_ptr.size());
  EXPECT_EQ(cellnodes, cellnodes_ptr.size());
  EXPECT_EQ(cellfaces, cellfaces_ptr.size());

  for(size_t i=0; i<num; i++){
    // EachCell and EachFace check
    EXPECT_EQ(facenodes, faces[i].node_ptrs().size());
    EXPECT_EQ(cellnodes, cells[i].node_ptrs().size());
    EXPECT_EQ(cellfaces, cells[i].face_ptrs().size());
  }
}

