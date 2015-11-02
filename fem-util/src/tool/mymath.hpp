//----------------------------------------------------------------------
/**
   @file mymath.hpp
   @brief My Math Library
   
   @author Shibata
   @date 2015-01-02(金) 21:32:49
   
***********************************************************************/

#ifndef _MYMATH_H_
#define _MYMATH_H_

#include <vector>

#include "xyz.hpp"
#include "myexception.hpp"


/*--------------------------------------------------------------------*
  Class Declaration (BEGIN)
  *--------------------------------------------------------------------*/
template <typename T>
class MyMath
{
public:
  // ##### enum
  // ##### Static Data Members
  // ##### Static Member Functions
  static T Interpolate(const XYZ grid,
		       const std::vector<XYZ>& grids,
		       const std::vector<T>& values
		       ) throw(tool::MyException);
private:
  // ##### Private Data Members
  // ##### Private Member Functions
  // ---- Init & Release
  
  // ##### Copy
  // ---- Copy Function
  bool Copy(const MyMath& mymath); // prohibited
  
  // ---- Copy Operator
  MyMath& operator=(const MyMath& mymath); // prohibited
  
  // ---- Copy Constructor
  MyMath(const MyMath& mymath);	// prohibited
  

  // ##### Constructors
  MyMath();			// prohibited
  
public:  
  // ##### Destructor
  // virtual ~MyMath();


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

#endif /* _MYMATH_H_ */
