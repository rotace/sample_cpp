//----------------------------------------------------------------------
/**
   @file gauss.cpp
   @brief ガウス積分計算
   
   @author Shibata
   @date 2014-12-25(木) 22:09:50
   
***********************************************************************/

#include "gauss.hpp"

#include <cmath>
#include <assert.h>

#include "func.hpp"

// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
Gauss::FaceType Gauss::GetFaceType
(const MeshInfo::CellType celltype)
{
  FaceType facetype;
  
  switch(celltype){
  case MeshInfo::TRIA3:
    facetype = TRIA3;
    break;
  case MeshInfo::QUAD4:
    facetype = QUAD4;
    break;
  case MeshInfo::TETRA4:
    facetype = TRIA3;
    break;
  case MeshInfo::HEXA8:
    facetype = QUAD4;
    break;
  }
  return facetype;
}

// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
void Gauss::Init()
{
  if( m_==2 && n_==2 ){
    Wi_.resize(2); Wj_.resize(2); xi_.resize(2); et_.resize(2);
    Wi_[0]=1; Wj_[0]=1; xi_[0]=-0.5773502692; et_[0]=-0.5773502692; 
    Wi_[1]=1; Wj_[1]=1; xi_[1]=+0.5773502692; et_[1]=+0.5773502692; 
  }else{
    std::cerr << "Error: not implimented ! " << std::endl;
    assert(false);
  }
  
  celltype_ = face_.celltype();
  facetype_ = GetFaceType(celltype_);
  num_facenodes_ = MeshInfo::GetNumOf(celltype_, MeshInfo::FACENODES);
}

// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Operator
// ---- Copy Constructor
// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
Gauss::Gauss(const Face& face, const int m, const int n)
  :face_(face),
   m_(m),
   n_(n)
{
  Init();
}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
Gauss::~Gauss()
{}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //

std::vector<XYZ> Gauss::Integrate(const ValueField values)
{
  // Pre- condition
  int m = values.size();
  int n = values[0].size();
  assert( m == m_ && n == n_ );

  // define
  std::vector<XYZ> force(num_facenodes_);
  
  // normal
  XYZ normal = Func::GetNormalOf(face_);
  // area
  double area = std::sqrt( normal * normal );
  // normalization
  normal = normal / std::sqrt( normal * normal );

  for(int inode=0; inode<num_facenodes_; inode++){
    for(int i=0; i<m; i++){
      for(int j=0; j<n; j++){
	XYZ tmp;
	tmp = -normal * area * 0.25 * Wi_[i] * Wj_[j];
	tmp = tmp * values[i][j];
	tmp = tmp * ShapeFunction(inode, xi_[i], et_[j]);
	force.at(inode) += tmp;
      }
    }
  }
  return force;
}

// * * * * * * * * * * * * * * * * * * * * *

double Gauss::ShapeFunction
(const int facenode_index,
 const double xi,
 const double eta)
  throw(tool::MyException)
{
  // Pre- condition
  assert( facenode_index > -1 && facenode_index < num_facenodes_ );
  
  double coef = 0;

  switch(facetype_){
  case TRIA3:
    BOOST_THROW_EXCEPTION( tool::MyException("Not Implimented") );
    break;
  case QUAD4:
    if( facenode_index == 0 ){
      coef = 0.25*(1.0-xi)*(1.0-eta);
    }else if( facenode_index ==1 ){
      coef = 0.25*(1.0+xi)*(1.0-eta);
    }else if( facenode_index ==2 ){
      coef = 0.25*(1.0+xi)*(1.0+eta);
    }else if( facenode_index ==3 ){
      coef = 0.25*(1.0-xi)*(1.0+eta);
    }
    break;
  }

  return coef;
}

// * * * * * * * * * * * * * * * * * * * * *

XYZ Gauss::GetGaussPoint(const int i, const int j)
{
  // Pre- condition
  assert( i > -1 && j > -1 );
  assert( i < m_ && j < n_ );

  XYZ grid(0,0,0);

  for(int inode=0; inode<num_facenodes_; inode++){
    grid += face_.nodes(inode).grid() * ShapeFunction(inode, xi_[i], et_[j]);
  }
  
  return grid;
}

// ---- Getter
// ---- Setter
// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //
// * * * * * * * * * * * Explicit Instantation  * * * * * * * * * * * //
