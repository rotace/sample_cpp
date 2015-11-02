//----------------------------------------------------------------------
/**
   @file meshinfo.hpp
   @brief メッシュ情報クラス
   
   @author Shibata
   @date 2014-12-20(土) 12:56:37
   
***********************************************************************/

#ifndef _MESHINFO_H_
#define _MESHINFO_H_

#include <string>
#include <vector>

#include "xyz.hpp"

/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class MeshInfo
{
public:
  // ##### enum
  
  /// Unstructure Cell Types referenced to VTK File Formats v4.2 
  enum CellType
    {
      // POINT     = 1,
      // BAR2      = 3,
      TRIA3     = 5,
      QUAD4     = 9,
      TETRA4    = 10,
      HEXA8     = 12,
      // PYRAMID5  = 14,
      // BAR3      = 21,
      // TRIA6     = 22,
      // QUAD8     = 23,
      // TETRA10   = 24,
      // HEXA20    = 25,
    };

  /// Mesh Infomation Types
  enum InfoType
    {
      CELLNODES,
      CELLFACES,
      FACENODES,
      CORNERNODES,
    };

  // ##### Static Data Members
  // ##### Static Member Functions

  /// Get Mesh Infomation Method
  static CellType GetFaceType(const CellType celltype);
  static bool GetHasRotBoundary(const CellType celltype);
  static std::string GetBdfCellName(const CellType celltype);
  
  static int GetNumOf
  (const CellType celltype,
   const InfoType infotype);
  
private:
  // ##### Private Data Members
  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy 
  // ---- Copy Function
  bool Copy(const MeshInfo& meshinfo); // prohibited
  // ---- Copy Operator
  MeshInfo& operator=(const MeshInfo& meshinfo); // prohibited
  // ---- Copy Constructor
  MeshInfo(const MeshInfo& meshinfo); // prohibited
  
public:
  // ##### Constructors
  MeshInfo();
  // ##### Destructor
  virtual ~MeshInfo();
  // ##### Member Functions
  // ---- Getter
  // ---- Setter
  
  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _MESHINFO_H_ */
