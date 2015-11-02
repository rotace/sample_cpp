//----------------------------------------------------------------------
/**
   @file cell.cpp
   @brief セルクラス
   
   @author Shibata
   @date 2014-12-20(土) 14:28:09
   
***********************************************************************/

#include "cell.hpp"

#include <assert.h>
#include <iostream>

// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
const Cell Cell::GetCellOf
(const MeshInfo::CellType celltype)
{
  Cell cell(MeshInfo::GetNumOf(celltype, MeshInfo::CELLNODES),
		 MeshInfo::GetNumOf(celltype, MeshInfo::CELLFACES));
  return cell;
}

// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Function
// ---- Copy Constructor
Cell::Cell(const Cell& cell)
  :node_ptrs_(cell.node_ptrs()),
   face_ptrs_(cell.face_ptrs()),
   index_(cell.index())
{}

// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
Cell::Cell
(const int cellnodes,
 const int cellfaces,
 const int index,
 const int id)
  :node_ptrs_(cellnodes,NULL),
   face_ptrs_(cellfaces,NULL),
   index_(index),
   id_(id)
{}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
Cell::~Cell(){}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
const int Cell::index() const{return index_;}
const MeshInfo::CellType Cell::celltype() const {return celltype_;}
const int Cell::id() const{return id_;}

// access nodes
NodePtrArray& Cell::node_ptrs(){
  return node_ptrs_;
}
const NodePtrArray& Cell::node_ptrs()const{
  return node_ptrs_;
}
Node& Cell::nodes(const int index){
  return *(node_ptrs_.at(index));
}
const Node&  Cell::nodes(const int index)const{
  return *(node_ptrs_.at(index));
}

// access faces
FacePtrArray& Cell::face_ptrs(){
  return face_ptrs_;
}
const FacePtrArray& Cell::face_ptrs()const{
  return face_ptrs_;
}
Face& Cell::faces(const int index){
  return *(face_ptrs_.at(index));
}
const Face&  Cell::faces(const int index)const{
  return *(face_ptrs_.at(index));
}

// ---- Setter
void Cell::SetNodePtr(const int index, Node *const node)
{
  node_ptrs_.at(index) = node;
}

void Cell::SetFacePtr(const int index,Face *const face)
{
  face_ptrs_.at(index) = face;
}

void Cell::SetFaceNodePtr(const int jface,const int knode, Node *const node)
{
  face_ptrs_.at(jface)->SetNodePtr(knode, node);
}

void Cell::SetSizeOfNodes(const int num_cellnodes)
{
  node_ptrs_.resize(num_cellnodes);
}

void Cell::SetSizeOfFaces(const int num_cellfaces)
{
  face_ptrs_.resize(num_cellfaces);
}

void Cell::SetIndex(const int index)
{
  index_ = index;
}

void Cell::SetCellType(const MeshInfo::CellType celltype)
{
  celltype_ = celltype;
}

void Cell::SetID(const int id)
{
  id_ = id;
}

// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //

