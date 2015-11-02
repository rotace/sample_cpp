//----------------------------------------------------------------------
/**
   @file mesh.hpp
   @brief メッシュクラス
   
   @author Shibata
   @date 2014-12-20(土) 11:04:19
   
***********************************************************************/

#ifndef _MESH_H_
#define _MESH_H_

#include <vector>

#include "xyz.hpp"
#include "meshinfo.hpp"
#include "node.hpp"
#include "face.hpp"
#include "cell.hpp"


/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class Mesh
{
public:
  // ##### enum
  // ##### Static Data Members
  // ##### Static Member Functions
private:
  // ##### Private Data Members
  NodeArray nodes_;
  FaceArray faces_;
  CellArray cells_;
  MeshInfo::CellType max_celltype_;
  
  // ##### Private Member Functions
  // ---- Init & Release
  void Init();
  
  // ##### Copy 
  // ---- Copy Function 
  bool Copy(const Mesh& mesh);	// prohibited
  
  // ---- Copy Operator 
  Mesh& operator=(const Mesh& mesh); // prohibited
  
  // ---- Copy Constructor 
  Mesh(const Mesh& mesh);	// prohibited
  
  // ##### Constructors
  Mesh();			// prohibited
  
public:
  Mesh(const int num_nodes,
       const int num_faces,
       const int num_cells,
       const MeshInfo::CellType max_celltype);
  
  // ##### Destructor
  virtual ~Mesh();
  
  // ##### Member Functions
  
  /// Check linking of cellnodes, cellfaces and facenodes.
  /// Before export, you should check links by using Check().
  void Check() const;

  /// Link cellfaces and facenodes.
  /// If you don't link, pointer array is still NULL.
  void Link();
  
  // ---- Getter
  const MeshInfo::CellType max_celltype() const;
  // access nodes
  NodeArray& nodes();
  const NodeArray& nodes()const;
  Node& nodes(const int index);
  const Node&  nodes(const int index)const;
  // acess faces
  FaceArray& faces();
  const FaceArray& faces()const;
  Face& faces(const int index);
  const Face&  faces(const int index)const;
  // access cells
  CellArray& cells();
  const CellArray& cells()const;
  Cell& cells(const int index);
  const Cell&  cells(const int index)const;

  // ---- Setter
  
  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _MESH_H_ */
