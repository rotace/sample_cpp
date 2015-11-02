//----------------------------------------------------------------------
/**
   @file gauss.hpp
   @brief ガウス積分計算
   
   @author Shibata
   @date 2014-12-25(木) 22:08:49
   
***********************************************************************/

#ifndef _GAUSS_H_
#define _GAUSS_H_

#include <vector>

#include "mesh.hpp"
#include "myexception.hpp"


typedef const std::vector<std::vector<double> > ValueField;

/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class Gauss
{
public:
  // ##### enum
  enum FaceType
    {
      TRIA3,
      QUAD4,
    };
  
  // ##### Static Data Members
  // ##### Static Member Functions
  static FaceType GetFaceType(const MeshInfo::CellType celltype);

private:
  // ##### Private Data Members
  const Face& face_;
  int m_;			/// row number of gauss points
  int n_;			/// column number of gauss points
  std::vector<double> Wi_,Wj_;	/// wighting values
  std::vector<double> xi_,et_;	/// generalized coordinate
  int num_facenodes_;
  MeshInfo::CellType celltype_;
  FaceType facetype_;
  
  // ##### Private Member Functions
  // ---- Init & Release
  void Init();
  
  // ##### Copy
  // ---- Copy Function
  bool Copy(const Gauss& gauss);	// prohibited
  
  // ---- Copy Operator
  Gauss& operator=(const Gauss& gauss);		// prohibited
  
  // ---- Copy Constructor
  Gauss(const Gauss& gauss);			// prohibited
  
  // ##### Constructors
  Gauss();			// prohibited
  
public:
  Gauss(const Face& face, const int m, const int n);
  
  // ##### Destructor
  virtual ~Gauss();
  
  // ##### Member Functions

  /// Gauss Integral
  /// Please set each value at the each gauss points as "values".
  std::vector<XYZ> Integrate(const ValueField values);

  double ShapeFunction
  (const int facenode_index,
   const double xi,
   const double eta) throw(tool::MyException);

  XYZ GetGaussPoint(const int i, const int j);
  
  // ---- Getter
  // ---- Setter
  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _GAUSS_H_ */
