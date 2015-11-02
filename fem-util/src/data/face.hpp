//----------------------------------------------------------------------
/**
   @file face.hpp
   @brief フェイスクラス
   
   @author Shibata
   @date 2014-12-20(土) 13:59:06
   
***********************************************************************/

#ifndef _FACE_H_
#define _FACE_H_

#include <vector>

#include "meshinfo.hpp"
#include "node.hpp"

/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class Face
{
public:
  // ##### enum
  // ##### Static Data Members
  // ##### Static Member Functions
  
  /// Get Face of a celltype
  static const Face GetFaceOf
  (const MeshInfo::CellType celltype);

  
private:
  // ##### Private Data Members
  NodePtrArray node_ptrs_;	///< Array of Pointer to Node
  int index_;			///< Index Number
  MeshInfo::CellType celltype_;
  
  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy
  // ---- Copy Function
  bool Copy(const Face& face);	// prohibited
  
  // ---- Copy Operator
  Face& operator=(const Face& face); // prohibited
  
public:
  // ---- Copy Constructor
  Face(const Face& face);
  
  // ##### Constructors
private:
  Face();			// prohibited

public:
  Face(const int facenodes,const int index=0);
  
  // ##### Destructor
  virtual ~Face();
  
  // ##### Member Functions
  // ---- Getter
  const int index() const;
  const MeshInfo::CellType celltype() const;
  // access nodes
  NodePtrArray& node_ptrs();
  const NodePtrArray& node_ptrs()const;
  Node& nodes(const int index);
  const Node&  nodes(const int index)const;
  
  // ---- Setter
  void SetNodePtr(const int index, Node* node);
  void SetSizeOfNodes(const int num_facenodes);
  void SetIndex(const int index);
  void SetCelltype(const MeshInfo::CellType celltype);
  
  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef
typedef std::vector<Face*> FacePtrArray;
typedef std::vector<Face>  FaceArray;

// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _FACE_H_ */
