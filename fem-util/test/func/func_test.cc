//----------------------------------------------------------------------
/**
   @file func_test.cc
   @brief Func Unit Test Program
   
   @author Shibata
   @date 2015-01-03(土) 20:36:16
   
***********************************************************************/

#include "func.hpp"
#include "gtest/gtest.h"

#include <cmath>
#include "iodata.hpp"
#include "func.hpp"
#include "mymath.hpp"
#include "gauss.hpp"


class FuncTotalTest : public testing::Test {
protected:
  typedef std::vector<std::pair<int,double> > NearPair;

  FuncTotalTest()
    :send_contact_surflag(1,MyBool(false)),
     reci_contact_surflag(1,MyBool(false)),
     send_contact_nodeflag(1,MyBool(false)), 
     reci_contact_nodeflag(1,MyBool(false)),
     send_test_value(1,-1.0),
     reci_test_value(1,-1.0),
     reci_integ_value(1,XYZ(0,0,0))
  {}

  virtual void SetUp() {
    // define ********************
    // default
    sendfile_ =std::string("000acousticmesh.vtk");
    recifile_ =std::string("001acousticmesh.vtk");
    outsfile_ =std::string("contact000.vtk");
    outrfile_ =std::string("contact001.vtk");
    // import
    send_data.ImportVtk(sendfile_);
    reci_data.ImportVtk(recifile_);
    send_func.SetMesh(send_data.mesh());
    reci_func.SetMesh(reci_data.mesh());
    // num
    send_num_faces = send_data.mesh().faces().size();
    send_num_nodes = send_data.mesh().nodes().size();  
    reci_num_faces = reci_data.mesh().faces().size();
    reci_num_nodes = reci_data.mesh().nodes().size();
    // test value
    send_test_value
      = DoubleValueArray(send_num_nodes,
			 0.0,
			 Object("send_test_value",
				Object::NODE,
				Object::DOUBLE
				)
			 );

    reci_test_value
      = DoubleValueArray(reci_num_nodes,
			 0.0,
			 Object("reci_test_value",
				Object::NODE,
				Object::DOUBLE
				)
			 );
    
    dvalue.resize(reci_num_nodes);

    // integ value
    reci_integ_value
      = XYZValueArray(reci_num_nodes,
			XYZ(0,0,0),
			Object("reci_integ_value",
				 Object::NODE,
				 Object::XYZ
				 )
			);
  }

  void SerchSurfaceTest(){
    std::cout << std::endl;
    std::cout << "##################### PHASE1: Search send face near the node"
	      << std::endl;
    
    
    // contact surflag ************
    send_contact_surflag = send_func.GetFaceSurflag(); 
    reci_contact_surflag = reci_func.GetFaceSurflag();

    Func::GetContactSurflag
      ( send_func,
	reci_func,
	&send_contact_surflag,
	&reci_contact_surflag);

    send_contact_nodeflag
      = send_func.ConvertFlagFaceToNode(send_contact_surflag);
    reci_contact_nodeflag
      = reci_func.ConvertFlagFaceToNode(reci_contact_surflag);

    
    // search send_face near the_node**********
    // define... first: nearest send_face_index, second: distance
    // first == -1 means no pair
    rdist_array.resize(reci_num_nodes);
    for(size_t i=0; i<rdist_array.size(); i++){
      rdist_array[i] = std::make_pair(-1, 1e7);
    }
      
    for(int irnode=0; irnode<reci_num_nodes; irnode++){
      if( reci_contact_nodeflag[irnode] ){

	for(int isface=0; isface<send_num_faces; isface++){
	  if( send_contact_surflag[isface] ){
	  
	    double dist = Func::GetDistanceOf
	      (reci_data.mesh().nodes(irnode),
	       send_data.mesh().faces(isface) );
	    
	    if( dist < rdist_array[irnode].second ){
	      rdist_array[irnode].first = isface;
	      rdist_array[irnode].second = dist;
	    }
	  
	  } // end if 
	} // end for isface
      }	// end if
    } // end for irnode
    
  }

  void InterpolateTest(){
    std::cout << std::endl;
    std::cout << "##################### PHASE2: Interpolate values"
	      << std::endl;

    // calc test_value************************
    // interpolate test_value
    for(int irnode=0; irnode<reci_num_nodes; irnode++){
      if( reci_contact_nodeflag[irnode] ){
	
	int near_isface = rdist_array[irnode].first;
	XYZ the_node = reci_data.mesh().nodes(irnode).grid();
	
	int num_s_facenodes
	  = send_data.mesh().faces(near_isface).node_ptrs().size();
      
	std::vector<XYZ> grids(num_s_facenodes);
	std::vector<double> test_value(num_s_facenodes);

	double max_value = 0;
	double min_value = 1e7;
	for(int i=0; i<num_s_facenodes; i++){
	  int isnode = send_data.mesh().faces(near_isface).nodes(i).index();
	  grids[i]   = send_data.mesh().nodes(isnode).grid();
	  test_value[i]  = send_test_value[isnode];
	  max_value = fmax(max_value, test_value[i]);
	  min_value = fmin(min_value, test_value[i]);
	}
	dvalue[irnode] = max_value - min_value;
      
	double the_test_value
	  = MyMath<double>::Interpolate(the_node,grids,test_value);
      
	reci_test_value.SetValue(irnode,the_test_value);
      }
    }
    
  }

  void IntegrateTest(){
    std::cout << std::endl;
    std::cout << "##################### PHASE3: Integrate values"
	      << std::endl;

    for(int irface=0; irface<reci_num_faces; irface++ ){
      if( reci_contact_surflag[irface] ){

	Gauss gauss_face(reci_data.mesh().faces(irface),2,2);

	int num_r_facenodes
	  = reci_data.mesh().faces(irface).node_ptrs().size();
	double test_value=0;

	// average
	for(int i=0; i<num_r_facenodes; i++){
	  int irnode = reci_data.mesh().faces(irface).nodes(i).index();
	  test_value += reci_test_value[irnode];
	}
	test_value = test_value / (double)num_r_facenodes;


	ValueField tv_val(2,std::vector<double>(2,test_value));

	std::vector<XYZ> integ_value = gauss_face.Integrate(tv_val);
      
	for(int i=0; i<num_r_facenodes; i++){
	  int irnode = reci_data.mesh().faces(irface).nodes(i).index();
	  reci_integ_value[irnode] += integ_value[i];
	}
      
      } // endif reci
    } // endfor reci
    
  }
  
  virtual void TearDown() {
    // output vtk
    send_data.ExportVtk(outsfile_);
    reci_data.ExportVtk(outrfile_);
  }
  
protected:
  // file name
  std::string sendfile_;
  std::string recifile_;
  std::string outsfile_;
  std::string outrfile_;
  // data
  IOData send_data;
  IOData reci_data;
  // func
  Func send_func;
  Func reci_func;
  // num
  int send_num_faces;
  int send_num_nodes;
  int reci_num_faces;
  int reci_num_nodes;
  // contact flag
  BoolValueArray send_contact_surflag;
  BoolValueArray reci_contact_surflag;
  BoolValueArray send_contact_nodeflag;
  BoolValueArray reci_contact_nodeflag;
  // test value
  DoubleValueArray send_test_value;
  DoubleValueArray reci_test_value;
  // difference value in a face ( max_value - min_value )
  std::vector<double> dvalue;
  // near pair
  NearPair rdist_array;
  // integ value
  XYZValueArray reci_integ_value;
};

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

/// ContactSurfaceTest
TEST_F(FuncTotalTest, ContactSurfaceTest){

  SerchSurfaceTest();
  
  // check ******************************
  BoolValueArray send_check_surflag = send_func.GetFaceSurflag();
  XYZValueArray send_face_normal = send_func.GetFaceNormal();
  for(int i=0; i<send_num_faces; i++){
    if( send_check_surflag[i] == true ){
      XYZ normal = send_face_normal[i];
      normal = normal / sqrt( normal * normal);
      if( normal * XYZ(1,0,0) < 0.8 )
	send_check_surflag[i] = false;
    }
  }
  
  for(int i=0; i<send_num_faces; i++){
    // EXPECT TEST
    EXPECT_EQ( send_check_surflag[i] , send_contact_surflag[i] );
  }
  
  BoolValueArray reci_check_surflag = reci_func.GetFaceSurflag();
  XYZValueArray reci_face_normal = reci_func.GetFaceNormal();
  for(int i=0; i<reci_num_faces; i++){
    if( reci_check_surflag[i] == true ){
      XYZ normal = reci_face_normal[i];
      normal = normal / sqrt( normal * normal);
      if( normal * XYZ(-1,0,0) < 0.8 )
	reci_check_surflag[i] = false;
    }
  }
  for(int i=0; i<reci_num_faces; i++){
    // EXPECT TEST
    EXPECT_EQ( reci_check_surflag[i] , reci_contact_surflag[i] );
  }
  
  // convert check_node_flag ************
  BoolValueArray send_check_nodeflag
    = send_func.ConvertFlagFaceToNode(send_check_surflag);
  BoolValueArray reci_check_nodeflag
    = reci_func.ConvertFlagFaceToNode(reci_check_surflag);

  send_check_nodeflag.SetName("check_nodeflag");
  reci_check_nodeflag.SetName("check_nodeflag");
  
  // output *****************************
  // set flag
  send_data.SetValues(send_contact_nodeflag);
  reci_data.SetValues(reci_contact_nodeflag);

  send_data.SetValues(send_check_nodeflag);
  reci_data.SetValues(reci_check_nodeflag);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

/// InterpolateTest
TEST_F(FuncTotalTest, InterpolateTest){

  SerchSurfaceTest();

  for(int i=0; i<(int)send_test_value.size(); i++){
    XYZ the_grid = send_data.mesh().nodes(i).grid();
    send_test_value.SetValue(i, the_grid * the_grid ); // |r|^2
  }

  InterpolateTest();
  
  // check ******************************
  for(int i=0; i<reci_num_nodes; i++){
    if( reci_contact_nodeflag[i] ){
      XYZ the_grid = reci_data.mesh().nodes(i).grid();
      double true_value = the_grid * the_grid; // |r|^2
      double test_value = reci_test_value[i];
      double error = true_value - test_value;
      double dx =
	Func::GetModelLengthOf(send_data.mesh().faces(rdist_array[i].first));
      double dv = dvalue[i];
      // EXPECT TEST
      EXPECT_LT( fabs(error) , 0.005 * (dv/dx) );
    }
  }

  // output *****************************
  // set flag
  send_data.SetValues(send_contact_nodeflag);
  reci_data.SetValues(reci_contact_nodeflag);

  send_data.SetValues(send_test_value);
  reci_data.SetValues(reci_test_value);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// GaussIntegrateTest
TEST_F(FuncTotalTest, GaussIntegrateTest){

  SerchSurfaceTest();
  
  for(int i=0; i<(int)send_test_value.size(); i++){
    XYZ the_grid = send_data.mesh().nodes(i).grid();
    send_test_value.SetValue(i, 1.0 ); // 1.0
  }

  InterpolateTest();
  IntegrateTest();

  // check ******************************
  // TODO: should be implimented !
  
  // output *****************************
  // set flag
  send_data.SetValues(send_contact_nodeflag);
  reci_data.SetValues(reci_contact_nodeflag);

  reci_data.SetValues(reci_integ_value);
}

