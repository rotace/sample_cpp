//----------------------------------------------------------------------
/**
   @file cell.hpp
   @brief セルクラス
   
   @author Shibata
   @date 2014-12-20(土) 14:24:41
   
***********************************************************************/

#ifndef _CELL_H_
#define _CELL_H_

#include <vector>

#include "node.hpp"
#include "face.hpp"

/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class Cell
{
public:
  // ##### enum
  // ##### Static Data Members
  // ##### Static Member Functions

  /// Get Cell of a celltype
  static const Cell GetCellOf
  (const MeshInfo::CellType celltype);

  
private:
  // ##### Private Data Members
  NodePtrArray node_ptrs_;	// Array of Pointer to Node
  FacePtrArray face_ptrs_;	// Array of Pointer to Face
  int index_;			// Index Number
  MeshInfo::CellType celltype_;
  int id_;
  
  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy (prohibited)
  // ---- Copy Function
  bool Copy(const Cell& cell);	// prohibited
  
  // ---- Copy Operator
  Cell& operator=(const Cell& cell); // prohibited

public:
  // ---- Copy Constructor
  Cell(const Cell& cell);

  // ##### Constructors
private:
  Cell();			// prohibited

public:
  Cell(const int cellnodes,
       const int cellfaces,
       const int index=0,
       const int id=0);
  
  // ##### Destructor
  virtual ~Cell();
  
  // ##### Member Functions
  // ---- Getter
  const int index() const;
  const MeshInfo::CellType celltype() const;
  const int id() const;
  // access nodes
  NodePtrArray& node_ptrs();
  const NodePtrArray& node_ptrs()const;
  Node& nodes(const int index);
  const Node&  nodes(const int index)const;
  // access faces
  FacePtrArray& face_ptrs();
  const FacePtrArray& face_ptrs()const;
  Face& faces(const int index);
  const Face&  faces(const int index)const;
  
  // ---- Setter
  void SetNodePtr(const int index, Node *const node);
  void SetFacePtr(const int index, Face *const face);
  void SetFaceNodePtr(const int jface, const int knode, Node *const node);
  void SetSizeOfNodes(const int num_cellnodes);
  void SetSizeOfFaces(const int num_cellfaces);
  void SetIndex(const int index);
  void SetCellType(const MeshInfo::CellType celltype);
  void SetID(const int id);
  
  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef
typedef std::vector<Cell*> CellPtrSet;
typedef std::vector<Cell>  CellArray;

// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _CELL_H_ */
