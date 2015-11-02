//----------------------------------------------------------------------
/**
   @file mesh.cpp
   @brief メッシュクラス
   
   @author Shibata
   @date 2014-12-20(土) 11:05:02
   
***********************************************************************/

#include "mesh.hpp"

#include <assert.h>
#include <iostream>


// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
void Mesh::Init()
{
  for(size_t i=0; i<nodes_.size(); i++){
    nodes(i).SetIndex(i);
  }
  for(size_t i=0; i<faces_.size(); i++){
    faces(i).SetIndex(i);
  }
  for(size_t i=0; i<cells_.size(); i++){
    cells(i).SetIndex(i);
  }
}

// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Function
// ---- Copy Constructor
// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
Mesh::Mesh
(const int num_nodes,
 const int num_faces,
 const int num_cells,
 const MeshInfo::CellType max_celltype)
  :nodes_(num_nodes),
   faces_(num_faces,Face::GetFaceOf(max_celltype)),
   cells_(num_cells,Cell::GetCellOf(max_celltype)),
   max_celltype_(max_celltype)
{
  Init();
}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
Mesh::~Mesh()
{}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
void Mesh::Check() const
{
  for(size_t i=0; i<faces_.size(); i++){
    const Face& face = faces(i);
    // facenodes
    for(size_t jnode=0; jnode<face.node_ptrs().size(); jnode++){
      assert( face.node_ptrs().at(jnode) != NULL );
    }
  }
  for(size_t i=0; i<cells_.size(); i++){
    const Cell& cell = cells(i);
    // cellnodes
    for(size_t jnode=0; jnode<cell.node_ptrs().size(); jnode++){
      assert( cell.node_ptrs().at(jnode) != NULL );
    }
    // cellfaces
    for(size_t jface=0; jface<cell.face_ptrs().size(); jface++){
      assert( cell.face_ptrs().at(jface) != NULL );
    }
  }
}

void Mesh::Link()
{
  int iface=0;
  for(int icell=0; icell<(int)cells_.size(); icell++){

    MeshInfo::CellType celltype = cells(icell).celltype();
    int num_cellfaces = MeshInfo::GetNumOf(celltype,MeshInfo::CELLFACES);

    // fitting cellfaces
    cells(icell).SetSizeOfFaces(num_cellfaces);

    for(int jface=0; jface<num_cellfaces; jface++){
      // linking cell to face
      cells(icell).SetFacePtr(jface, &(faces(iface)) );
      // set celltype
      faces(iface).SetCelltype(celltype);
      // incriment index
      iface++;
    }

    // linking face to node
    int jface;
    switch(celltype){
    case MeshInfo::TRIA3:
      jface=0;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[0]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[1]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[2]);
      break;
    case MeshInfo::QUAD4:
      jface=0;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[0]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[1]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[2]);
      cells(icell).SetFaceNodePtr(jface,3,cells(icell).node_ptrs()[3]);
      break;
    case MeshInfo::TETRA4:
      // face1
      jface=0;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[2]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[1]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[0]);
      // face2
      jface=1;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[0]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[1]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[3]);
      // face3
      jface=2;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[1]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[2]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[3]);
      // face4
      jface=3;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[3]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[2]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[0]);
      break;
    case MeshInfo::HEXA8:
      // face1
      jface=0;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[3]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[2]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[1]);
      cells(icell).SetFaceNodePtr(jface,3,cells(icell).node_ptrs()[0]);
      // face2
      jface=1;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[4]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[5]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[6]);
      cells(icell).SetFaceNodePtr(jface,3,cells(icell).node_ptrs()[7]);
      // face3
      jface=2;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[0]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[4]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[7]);
      cells(icell).SetFaceNodePtr(jface,3,cells(icell).node_ptrs()[3]);
      // face4
      jface=3;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[1]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[2]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[6]);
      cells(icell).SetFaceNodePtr(jface,3,cells(icell).node_ptrs()[5]);
      // face5
      jface=4;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[0]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[1]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[5]);
      cells(icell).SetFaceNodePtr(jface,3,cells(icell).node_ptrs()[4]);
      // face6
      jface=5;
      cells(icell).SetFaceNodePtr(jface,0,cells(icell).node_ptrs()[7]);
      cells(icell).SetFaceNodePtr(jface,1,cells(icell).node_ptrs()[6]);
      cells(icell).SetFaceNodePtr(jface,2,cells(icell).node_ptrs()[2]);
      cells(icell).SetFaceNodePtr(jface,3,cells(icell).node_ptrs()[3]);
      break;
    }
  }
}
// ---- Getter
const MeshInfo::CellType Mesh::max_celltype() const{
  return max_celltype_;
}
// access nodes
NodeArray& Mesh::nodes(){
  return nodes_;
}
const NodeArray& Mesh::nodes()const{
  return nodes_;
}
Node& Mesh::nodes(const int index){
  return nodes_.at(index);
}
const Node&  Mesh::nodes(const int index)const{
  return nodes_.at(index);
}

// access faces
FaceArray& Mesh::faces(){
  return faces_;
}
const FaceArray& Mesh::faces()const{
  return faces_;
}
Face& Mesh::faces(const int index){
  return faces_.at(index);
}
const Face&  Mesh::faces(const int index)const{
  return faces_.at(index);
}

// access cells
CellArray& Mesh::cells(){
  return cells_;
}
const CellArray& Mesh::cells()const{
  return cells_;
}
Cell& Mesh::cells(const int index){
  return cells_.at(index);
}
const Cell&  Mesh::cells(const int index)const{
  return cells_.at(index);
}

// ---- Setter
// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //

