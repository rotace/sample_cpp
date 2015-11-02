//----------------------------------------------------------------------
/**
   @file face.cpp
   @brief フェイスクラス
   
   @author Shibata
   @date 2014-12-20(土) 14:06:10
   
***********************************************************************/

#include "face.hpp"

#include <assert.h>
#include <iostream>


// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
const Face Face::GetFaceOf
(const MeshInfo::CellType celltype)
{
  Face face(MeshInfo::GetNumOf(celltype, MeshInfo::FACENODES));
  return face;
}

// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Function
// ---- Copy Constructor
Face::Face(const Face& face)
  :node_ptrs_(face.node_ptrs()),
   index_(face.index())
{}

// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
Face::Face
(const int facenodes,
 const int index)
  :node_ptrs_(facenodes,NULL),
   index_(index)
{}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
Face::~Face()
{}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
const int Face::index() const{return index_;}
const MeshInfo::CellType Face::celltype() const{return celltype_;}

// access nodes
NodePtrArray& Face::node_ptrs(){
  return node_ptrs_;
}
const NodePtrArray& Face::node_ptrs()const{
  return node_ptrs_;
}
Node& Face::nodes(const int index){
  return *(node_ptrs_.at(index));
}
const Node&  Face::nodes(const int index)const{
  return *(node_ptrs_.at(index));
}

// ---- Setter
void Face::SetNodePtr(const int index, Node* node)
{
  node_ptrs_.at(index) = node;
}

void Face::SetSizeOfNodes(const int num_facenodes)
{
  node_ptrs_.resize(num_facenodes);
}

void Face::SetIndex(const int index)
{
  index_ = index;
}

void Face::SetCelltype(const MeshInfo::CellType celltype)
{
  celltype_ = celltype;
}

// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //

