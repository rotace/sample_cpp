//----------------------------------------------------------------------
/**
   @file func.hpp
   @brief ファンクションクラス
   
   @author Shibata
   @date 2014-12-25(木) 10:20:08
   
***********************************************************************/

#ifndef _FUNC_H_
#define _FUNC_H_

#include "mesh.hpp"
#include "value.hpp"

/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class Func
{
public:
  // ##### enum
  // ##### Static Data Members
  
  // ##### Static Member Functions
  static double GetDistanceOf(const XYZ& grid1, const XYZ& grid2);
  
  static double GetDistanceOf(const Node& node1, const Node& node2);

  static double GetDistanceOf(const XYZ& grid1, const Face& face2);
  
  static double GetDistanceOf(const Node& node1, const Face& face2);

  static double GetDistanceOf(const Face& face1, const Face& face2);

  static XYZ GetNormalOf(const Face& face);
  
  static double GetAreaOf(const Face& face);

  static double GetModelLengthOf(const Face& face);

  static void GetContactSurflag	
  (Func& func1,
   Func& func2,
   BoolValueArray* contact_surflag1,
   BoolValueArray* contact_surflag2);




private:
  // ##### Private Data Members
  Mesh* mesh_ptr_;
  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy
  // ---- Copy Function
  bool Copy(const Func& func);	// prohibited
  
  // ---- Copy Operator
  Func& operator=(const Func& func);		// prohibited
  
  // ---- Copy Constructor
  Func(const Func& func);			// prohibited
  
public:
  // ##### Constructors
  Func();
  Func(Mesh& mesh);
  
  // ##### Destructor
  // virtual ~Func();
  
  // ##### Member Functions
  
  // get normal direction
  XYZValueArray GetFaceNormal();
  XYZValueArray GetNodeNormal();

  // get center position
  XYZValueArray GetFaceCenter();
  XYZValueArray GetCellCenter();

  // get surface flag
  BoolValueArray GetNodeSurflag();
  BoolValueArray GetFaceSurflag();
  BoolValueArray GetCellSurflag();

  // convert flag
  BoolValueArray ConvertFlagFaceToNode
  (const BoolValueArray& face_surflag );

  // check mesh
  void Check() const;

  // ---- Getter
  const Mesh& mesh() const;
  // ---- Setter
  void SetMesh(Mesh& mesh);
  
  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _FUNC_H_ */
