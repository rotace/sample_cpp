//----------------------------------------------------------------------
/**
   @file mymath.cpp
   @brief My Math Library
   
   @author Shibata
   @date 2015-01-02(金) 21:37:35
   
***********************************************************************/

#include "mymath.hpp"

#include <assert.h>
#include <cmath>

// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //
template <typename T>
T MyMath<T>::Interpolate(const XYZ grid,
		      const std::vector<XYZ>& grids,
		      const std::vector<T>& values)
  throw(tool::MyException)
{
  // Pre- condition
  assert( grids.size() == values.size() );
  
  int num_values = values.size();
  std::vector<XYZ>   tmp_grids = grids;
  std::vector<T>    tmp_values = values;
  std::vector<double> dist(num_values);
  T value;

  // wighted by distance
  for(size_t i=0; i<dist.size(); i++){
    XYZ tmp_xyz = grid - grids[i];
    dist[i] = sqrt( tmp_xyz * tmp_xyz );
  }

  if( num_values <= 0 ){	// n<=0
    BOOST_THROW_EXCEPTION( tool::MyException("num_values <= 0") );

  }else if( num_values ==1  ){	// n=1
    value = values[0];

  }else if( num_values ==2 ){	// n=2
    value = (dist[1]*values[0] + dist[0]*values[1] )/(dist[0]+dist[1]);
    
  }else if( num_values > 3 ){	// n>=3
    for(int i=0; i<3; i++){	// select 3 nodes near the grid
      for(int j=i+1; j<num_values; j++){
	if( dist[i] > dist[j] ){
	  XYZ tmp_grid    =  tmp_grids[i] ; 
	  T tmp_value  = tmp_values[i] ;
	  double tmp_dist =   dist[i] ;

	  tmp_grids[i]  =  tmp_grids[j] ;
	  tmp_values[i] = tmp_values[j] ;
	  dist[i]       =   dist[j] ;

	  tmp_grids[j]  =  tmp_grid ;
	  tmp_values[j] = tmp_value ;
	  dist[j]       =  tmp_dist ;
	}
      }
    }
    double rate0 = dist[1]*dist[2];
    double rate1 = dist[2]*dist[0];
    double rate2 = dist[0]*dist[1];

    value = (  rate0*tmp_values[0]
	     + rate1*tmp_values[1]
	     + rate2*tmp_values[2]
	    ) / (rate0+rate1+rate2);
  }
  return value;
}

// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Operator
// ---- Copy Constructor
// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
// ---- Getter
// ---- Setter
// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //
// * * * * * * * * * * * Explicit Instantation  * * * * * * * * * * * //
template class MyMath<double>;
