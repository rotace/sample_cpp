//----------------------------------------------------------------------
/**
   @file node.hpp
   @brief ノードクラス
   
   @author Shibata
   @date 2014-12-20(土) 13:30:49
   
***********************************************************************/

#ifndef _NODE_H_
#define _NODE_H_

#include <vector>

#include "xyz.hpp"

/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class Node
{
public:
  // ##### enum
  // ##### Static Data Members
  // ##### Static Member Functions
private:
  // ##### Private Data Members
  XYZ grid_;			///< Node Coordinates
  int index_;			///< Index Number of Array
  int id_;			///< ID
  
  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy
  // ---- Copy Function 
  bool Copy(const Node& node);	// prohibited
  
  // ---- Copy Operator
  Node& operator=(const Node& node); // prohibited
  
public:  
  // ---- Copy Constructor
  Node(const Node& node);

  // ##### Constructors
  Node();
  Node(const XYZ grid, const int index, const int id=0);

  // ##### Destructor
  virtual ~Node();

  
  // ##### Member Functions
  // ---- Getter
  const XYZ grid() const;
  const int index() const;
  const int id() const;
  
  // ---- Setter
  void SetGrid(const XYZ grid);
  void SetIndex(const int index);
  void SetID(const int id);
  
  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef
typedef std::vector<Node*> NodePtrArray;
typedef std::vector<Node>  NodeArray;

// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _NODE_H_ */
