//----------------------------------------------------------------------
/**
   @file node.cpp
   @brief ノードクラス
   
   @author Shibata
   @date 2014-12-20(土) 13:34:25
   
***********************************************************************/

#include "node.hpp"

#include <assert.h>
#include <iostream>

// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Function
// ---- Copy Constructor
Node::Node(const Node& node)
  :grid_(node.grid()),
   index_(node.index())
{}

// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
Node::Node()
  :grid_(0,0,0),
   index_(0)
{}

Node::Node(const XYZ grid, const int index, const int id)
  :grid_(grid),
   index_(index),
   id_(id)
{}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
Node::~Node()
{}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
const XYZ Node::grid() const{return grid_;}
const int Node::index() const{return index_;}
const int Node::id() const{return id_;}

// ---- Setter
void Node::SetGrid(const XYZ grid)
{
  grid_ = grid;
}
void Node::SetIndex(const int index)
{
  index_ = index;
}
void Node::SetID(const int id)
{
  id_ = id;
}

// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //

