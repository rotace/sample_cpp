//----------------------------------------------------------------------
/**
   @file matesolid.hpp
   @brief Materialサブクラス SOLID
   
   @author Shibata
   @date 2015-10-08(木) 19:22:45
   
***********************************************************************/

#ifndef _MATESOLID_H_
#define _MATESOLID_H_

#include "material.hpp"


/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class MateSolid :public Material
{
public:
  // ##### enum
  // ##### Static Data Members
  // ##### Static Member Functions
private:
  // ##### Private Data Members
	double rho_;
	double E_;
	double nu_;

  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy
  // ---- Copy Function
  bool Copy(const MateSolid& matesolid );	// prohibited
  
  // ---- Copy Operator
  MateSolid& operator=(const MateSolid& matesolid );		// prohibited
  
  // ---- Copy Constructor
  MateSolid(const MateSolid& matesolid );			// prohibited
  
public:
  // ##### Constructors
  MateSolid();
  
  // ##### Destructor
  virtual ~MateSolid();
  
  // ##### Member Functions
  // ---- Getter
  virtual const double rho()const;
  virtual const double E()const;
  virtual const double nu()const;

  // ---- Setter
  virtual void SetRho(const double rho);
  virtual void SetE(const double E);
  virtual void SetNu(const double nu);
  
  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _MATESOLID_H_ */
