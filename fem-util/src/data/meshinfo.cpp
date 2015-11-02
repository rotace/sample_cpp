//----------------------------------------------------------------------
/**
   @file meshinfo.cpp
   @brief メッシュ情報クラス
   
   @author Shibata
   @date 2014-12-20(土) 12:59:42
   
***********************************************************************/

#include "meshinfo.hpp"

#include <assert.h>

// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //

/// Get Mesh Infomation Method
MeshInfo::CellType MeshInfo::GetFaceType(const CellType celltype)
{
  CellType facetype;
  switch(celltype){
  case TRIA3:
    facetype = TRIA3;
    break;
  case QUAD4:
    facetype = QUAD4;
    break;
  case TETRA4:
    facetype = TRIA3;
    break;
  case HEXA8:
    facetype = QUAD4;
    break;
  }
  return facetype;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
bool MeshInfo::GetHasRotBoundary(const CellType celltype)
{
  bool has_rot;
  switch(celltype){
  case TRIA3:
    has_rot = true;
    break;
  case QUAD4:
    has_rot = true;
    break;
  case TETRA4:
    has_rot = false;
    break;
  case HEXA8:
    has_rot = false;
    break;
  }
  return has_rot;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
std::string MeshInfo::GetBdfCellName(const CellType celltype)
{
  std::string cellname;
  switch(celltype){
  case TRIA3:
    cellname = "CTRIA3";
    break;
  case QUAD4:
    cellname = "CQUAD4";
    break;
  case TETRA4:
    cellname = "CTETRA";
    break;
  case HEXA8:
    cellname = "CHEXA";
    break;
  }
  return cellname;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
int MeshInfo::GetNumOf(const CellType celltype, const InfoType infotype)
{
  int num_cellnodes;
  int num_cellfaces;
  int num_facenodes;
  int num_cornernodes;

  int num=0;
  
  switch(celltype){
  case TRIA3:
    num_cellnodes = 3;
    num_cellfaces = 1;
    num_facenodes = 3;
    num_cornernodes = 3;
    break;
  case QUAD4:
    num_cellnodes = 4;
    num_cellfaces = 1;
    num_facenodes = 4;
    num_cornernodes = 4;
    break;
  case TETRA4:
    num_cellnodes = 4;
    num_cellfaces = 4;
    num_facenodes = 3;
    num_cornernodes = 4;
    break;
  case HEXA8:
    num_cellnodes = 8;
    num_cellfaces = 6;
    num_facenodes = 4;
    num_cornernodes = 8;
    break;
  }
  switch(infotype){
  case CELLNODES:
    num = num_cellnodes;
    break;
  case CELLFACES:
    num = num_cellfaces;
    break;
  case FACENODES:
    num = num_facenodes;
    break;
  case CORNERNODES:
    num = num_cornernodes;
    break;
  }
  return num;
}

// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Function
// ---- Copy Constructor
// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
// MeshInfo::MeshInfo()
// {
// }
// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
// MeshInfo::~MeshInfo()
// {
// }
// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
// ---- Setter
// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //

