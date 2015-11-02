//----------------------------------------------------------------------
/**
   @file mateuser1.hpp
   @brief Materialサブクラス USER1
   
   @author Shibata
   @date 2015-10-08(木) 19:18:52
   
***********************************************************************/

#ifndef _MATEUSER1_H_
#define _MATEUSER1_H_

#include "material.hpp"


/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
class MateUser1 :public Material
{
public:
  // ##### enum
  // ##### Static Data Members
  // ##### Static Member Functions
private:
  // ##### Private Data Members
	double rho_;
	double c_;

  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy
  // ---- Copy Function
  bool Copy(const MateUser1& mateuser1 );	// prohibited
  
  // ---- Copy Operator
  MateUser1& operator=(const MateUser1& mateuser1 );		// prohibited
  
  // ---- Copy Constructor
  MateUser1(const MateUser1& mateuser1 );			// prohibited
  
public:
  // ##### Constructors
  MateUser1();
  
  // ##### Destructor
  virtual ~MateUser1();
  
  // ##### Member Functions
  // ---- Getter
  virtual const double rho()const;
  virtual const double c()const;

  // ---- Setter
  virtual void SetRho(const double rho);
  virtual void SetC(const double c);
  
  // ##### Member Operators
};
/*--------------------------------------------------------------------*
  Class Declaration (END)
  *--------------------------------------------------------------------*/
// ### typedef


// * * * * * * * * * * Inline Functions   * * * * * * * * * * * * * * //

#endif /* _MATEUSER1_H_ */
