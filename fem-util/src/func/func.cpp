//----------------------------------------------------------------------
/**
   @file func.cpp
   @brief ファンクションクラス
   
   @author Shibata
   @date 2014-12-25(木) 12:50:10
   
***********************************************************************/

#include "func.hpp"

#include <assert.h>
#include <cmath>
#include <vector>


// * * * * * * * * * * * *  Static Data Members * * * * * * * * * * * //
// * * * * * * * * * * *  Static Member Functions * * * * * * * * * * //


// * * * * * * * * * * * * * * * * * * * * *

double Func::GetDistanceOf(const XYZ& grid1, const XYZ& grid2)
{
  XYZ tmp;
  tmp = grid1 - grid2;
  return sqrt(tmp*tmp);
}

// * * * * * * * * * * * * * * * * * * * * *

double Func::GetDistanceOf(const Node& node1, const Node& node2)
{
  return GetDistanceOf( node1.grid(), node2.grid() );
}

// * * * * * * * * * * * * * * * * * * * * *

double Func::GetDistanceOf(const XYZ& grid1, const Face& face2)
{
  MeshInfo::CellType celltype = face2.celltype();
  MeshInfo::CellType facetype = MeshInfo::GetFaceType(celltype);
  int num_cornernodes = MeshInfo::GetNumOf(facetype, MeshInfo::CORNERNODES);

  std::vector<XYZ> grid2(num_cornernodes+1,XYZ(0,0,0));
  for(int i=0; i<num_cornernodes; i++){
    grid2.at(i)=face2.nodes(i).grid();
  }
  grid2.at(num_cornernodes)=grid2.at(0);

  XYZ normal = GetNormalOf( face2 );
  normal = normal / sqrt( normal * normal );

  bool inface=true;
  // d= ax+by+cz = (x,y,z)*(a,b,c) <- wall face
  for(int i=0; i<num_cornernodes; i++){
    XYZ side = grid2.at(i+1) - grid2.at(i);
    double d = grid2.at(i)*(side % normal); 
    double dd= grid1      *(side % normal);
    if( dd > d ){
      inface=false;
    }
  }
  
  if( inface == true ){
    // node1 is on face2
    double d = grid2.at(0)*normal; // projection onto normal vector
    double dd= grid1      *normal; // projection onto normal vector
    return fabs( dd - d );
  }else{
    // node1 isn't on face2
    double mindist=10e7;
    for(int i=0; i<num_cornernodes; i++){
      XYZ side = grid2.at(i+1) -grid2.at(i);
      double t;
      t= side * ( grid1 - grid2.at(i) ); // calc dividing point
      t= t / (side*side);
      if( t > 1 )
	t=1;
      else if(t < 0)
	t=0;
      double dist = GetDistanceOf( grid1, grid2.at(i)+t*side);
      mindist = std::min(mindist, dist);
    }
    return mindist;
  }
}

double Func::GetDistanceOf(const Node& node1, const Face& face2)
{
  return GetDistanceOf( node1.grid(), face2 );
}

double Func::GetDistanceOf(const Face& face1, const Face& face2)
{
  // calculate center
  int num_facenodes;
  XYZ center;

  // center1 average
  num_facenodes = face1.node_ptrs().size();
  center = XYZ(0,0,0);
  for(int jnode=0; jnode<num_facenodes; jnode++){
    center += face1.nodes(jnode).grid();
  }
  XYZ center1 = center/(double)num_facenodes;

  // center2 average
  num_facenodes = face2.node_ptrs().size();
  center = XYZ(0,0,0);
  for(int jnode=0; jnode<num_facenodes; jnode++){
    center += face2.nodes(jnode).grid();
  }
  XYZ center2 = center/(double)num_facenodes;

  double dist1 = GetDistanceOf( center1, face2 );
  double dist2 = GetDistanceOf( center2, face1 );

  return fmin(dist1, dist2);
}

// * * * * * * * * * * * * * * * * * * * * *

XYZ Func::GetNormalOf(const Face& face)
{
  const MeshInfo::CellType celltype = face.celltype();
  MeshInfo::CellType facetype = MeshInfo::GetFaceType(celltype);
    
  XYZ a,b,c,d,normal;
  switch(facetype){
  case MeshInfo::TRIA3:		// same process
  // case MeshInfo::TRIA6:		// same process
    
    a = face.nodes(1).grid() - face.nodes(0).grid(); // ab
    b = face.nodes(2).grid() - face.nodes(1).grid(); // bc
    normal = 0.5 * (b % -a);			   // 0.5*( bc%ba )
    break;

  case MeshInfo::QUAD4:		// same process
  // case MeshInfo::QUAD8:		// same process
    
    a = face.nodes(1).grid() - face.nodes(0).grid(); // ab
    b = face.nodes(2).grid() - face.nodes(1).grid(); // bc
    c = face.nodes(3).grid() - face.nodes(2).grid(); // cd
    d = face.nodes(0).grid() - face.nodes(3).grid(); // da
    normal = 0.5 * (b % -a) + 0.5 * (d % -c);	   // 0.5*( bc%ba + da%dc )
    break;
  case MeshInfo::TETRA4:
  case MeshInfo::HEXA8:
    std::cerr << "Error: facetype has incorrect! " << std::endl;
    assert(false);
    break;
  }
  return normal;
}

// * * * * * * * * * * * * * * * * * * * * *

double Func::GetAreaOf(const Face& face)
{
  XYZ normal = GetNormalOf(face);
  return sqrt( normal * normal );
}

// * * * * * * * * * * * * * * * * * * * * *

double Func::GetModelLengthOf(const Face& face)
{
  double area = GetAreaOf(face);
  return sqrt( area );
}

// * * * * * * * * * * * * * * * * * * * * *

void Func::GetContactSurflag	
(Func& func1,
 Func& func2,
 BoolValueArray* contact_surflag1,
 BoolValueArray* contact_surflag2)
{
  // Pre-condition
  assert( func1.mesh().faces().size() == contact_surflag1->size() );
  assert( func2.mesh().faces().size() == contact_surflag2->size() );

  // define
  BoolValueArray output_surflag1 = func1.GetFaceSurflag();
  BoolValueArray output_surflag2 = func2.GetFaceSurflag();
  int size1 = output_surflag1.size();
  int size2 = output_surflag2.size();

  // define... first: nearest pairIndex, second: distance
  // first == -1 means no pair
  typedef std::vector<std::pair<int,double> > NearPair;
  NearPair dist_array1(size1,std::make_pair(-1,1e7));
  NearPair dist_array2(size2,std::make_pair(-1,1e7));
  XYZValueArray face_normal1 = func1.GetFaceNormal();
  XYZValueArray face_normal2 = func2.GetFaceNormal();
  const Mesh& mesh1 = func1.mesh();
  const Mesh& mesh2 = func2.mesh();

  // calc distance between faces
  for(int i1=0; i1<size1; i1++){
    if( output_surflag1[i1] == true ){
      for(int i2=0; i2<size2; i2++){
	if( output_surflag2[i2] == true ){
	  
	  // face1 normal vector and normalize
	  XYZ fn_i1 = face_normal1[i1];
	  fn_i1 = fn_i1 / sqrt( fn_i1 * fn_i1 );
	  // face2 normal vector and normalize
	  XYZ fn_i2 = face_normal2[i2];
	  fn_i2 = fn_i2 / sqrt( fn_i2 * fn_i2 );
	  
	  // inner product of face1 and face2
	  double vec_product = fn_i1 * fn_i2;
	  if ( vec_product < -0.9 ){

	    const Face& face1 = mesh1.faces(i1);
	    const Face& face2 = mesh2.faces(i2);

	    // calculate distance
	    double dist = GetDistanceOf( face1, face2 );

	    // get model length of faces
	    double facesize1 = GetModelLengthOf( face1 );
	    double facesize2 = GetModelLengthOf( face2 );
	    double facesize = fmin( facesize1, facesize2);
	    
	    // check for getting rid of faces in far field
	    if ( dist < facesize ){
	      // compare1
	      if( dist_array1[i1].second > dist ){
		dist_array1[i1].first = i2;
		dist_array1[i1].second = dist;
	      }
	      // compare2
	      if( dist_array2[i2].second > dist ){
		dist_array2[i2].first = i1;
		dist_array2[i2].second = dist;
	      }
	    }
	    
	  } // endif(vec_product < -0.9)
	} // endif
      }	// endfor
    } // endif
  } // endfor

  // set flag
  for(int i1=0; i1<size1; i1++){
    if( dist_array1[i1].first == -1 ){
      output_surflag1[i1] = false;
    }else{
      output_surflag1[i1] = true;
    }
  }
  for(int i2=0; i2<size2; i2++){
    if( dist_array2[i2].first == -1 ){
      output_surflag2[i2] = false;
    }else{
      output_surflag2[i2] = true;
    }
  }

  // output
  *contact_surflag1 = output_surflag1;
  *contact_surflag2 = output_surflag2;
}



// * * * * * * * * * * * Private Member Functions * * * * * * * * * * //
// ---- Init & Release
// * * * * * * * * * * * * * Copy Members * * * * * * * * * * * * * * //
// ---- Copy Function
// ---- Copy Operator
// ---- Copy Constructor
// * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //
Func::Func()
  :mesh_ptr_(NULL)
{}

Func::Func(Mesh& mesh)
  :mesh_ptr_(&mesh)
{}

// * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * //
// Func::~Func()
// {}

// * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //
  
// ------------------------------------ get normal direction
XYZValueArray Func::GetFaceNormal()
{
  // define
  int num_faces = mesh().faces().size();
  
  // make value array
  Object tmp_obj;
  tmp_obj.SetName( "face_normal" );
  tmp_obj.SetDataType( Object::FACE );
  tmp_obj.SetValueType( Object::XYZ );
  XYZValueArray face_normal(num_faces, XYZ(0,0,0), tmp_obj);

  // get normal vector
  for(int iface=0; iface<num_faces; iface++){
    
    XYZ normal = GetNormalOf( mesh().faces(iface) );
    
    face_normal.SetValue(iface, normal);
  }

  return face_normal;
}

// * * * * * * * * * * * * * * * * * * * * *

XYZValueArray Func::GetNodeNormal()
{
  // define
  int num_nodes = mesh().nodes().size();
  int num_faces = mesh().faces().size();
  
  // make value array
  Object tmp_obj;
  tmp_obj.SetName( "node_normal" );
  tmp_obj.SetDataType( Object::NODE );
  tmp_obj.SetValueType( Object::XYZ );
  XYZValueArray node_normal(num_nodes, XYZ(0,0,0), tmp_obj);

  // get face normal vector
  XYZValueArray face_normal = GetFaceNormal();
  
  // calculate normal vector
  for(int iface=0; iface<num_faces; iface++){

    int num_facenodes = mesh().faces(iface).node_ptrs().size();

    for(int jnode=0; jnode<num_facenodes; jnode++){

      int inode = mesh().faces(iface).nodes(jnode).index();
      node_normal[inode] += face_normal[iface];
    }
  }

  // normalisation / cutoff
  for(int inode=0; inode<num_nodes; inode++){
    XYZ vec = node_normal[inode];
    double tmp = fabs(vec.x)+fabs(vec.y)+fabs(vec.z);
    double eps = 1.0e-7;
    
    if( tmp < eps ){		// cutoff
      node_normal[inode] = XYZ(0,0,0);
      
    }else{			// normalisation
      node_normal[inode] = vec / sqrt( vec * vec );
    }
  }

  return node_normal;
}

// * * * * * * * * * * * * * * * * * * * * *

// ------------------------------------ get center position
XYZValueArray Func::GetFaceCenter()
{
  // define
  int num_faces = mesh().faces().size();
  
  // make value array
  Object tmp_obj;
  tmp_obj.SetName( "face_center" );
  tmp_obj.SetDataType( Object::FACE );
  tmp_obj.SetValueType( Object::XYZ );
  XYZValueArray face_center(num_faces, XYZ(0,0,0), tmp_obj);

  // calculate center
  for(int iface=0; iface<num_faces; iface++){
      int num_facenodes = mesh().faces(iface).node_ptrs().size();
      XYZ center(0,0,0);

      for(int jnode=0; jnode<num_facenodes; jnode++){
	
	center += mesh().faces(iface).nodes(jnode).grid();
	if(jnode != 0)
	  center = 0.5*center;
      }
      face_center.SetValue(iface, center);
    }

  return face_center;
}


// * * * * * * * * * * * * * * * * * * * * *

XYZValueArray Func::GetCellCenter()
{
  // define
  int num_cells = mesh().cells().size();
  
  // make value array
  Object tmp_obj;
  tmp_obj.SetName( "cell_center" );
  tmp_obj.SetDataType( Object::CELL );
  tmp_obj.SetValueType( Object::XYZ );
  XYZValueArray cell_center(num_cells, XYZ(0,0,0), tmp_obj);

  // calculate center
  for(int icell=0; icell<num_cells; icell++){
      int num_cellnodes = mesh().cells(icell).node_ptrs().size();
      XYZ center(0,0,0);

      for(int jnode=0; jnode<num_cellnodes; jnode++){
	
	center += mesh().cells(icell).nodes(jnode).grid();
	if(jnode != 0)
	  center = 0.5*center;
      }
      cell_center.SetValue(icell, center);
    }

  return cell_center;
}


// * * * * * * * * * * * * * * * * * * * * *

// ------------------------------------ get surface flag
BoolValueArray Func::GetNodeSurflag()
{
  // define
  int num_nodes = mesh().nodes().size();
  
  // make value array
  Object tmp_obj;
  tmp_obj.SetName( "node_surflag" );
  tmp_obj.SetDataType( Object::NODE );
  tmp_obj.SetValueType( Object::BOOL );
  BoolValueArray node_surflag(num_nodes, false, tmp_obj);

  // get node normal vector
  XYZValueArray node_normal = GetNodeNormal();

  // check surface
  // normalisation / cutoff
  for(int inode=0; inode<num_nodes; inode++){
    XYZ vec = node_normal[inode];
    double tmp = fabs(vec.x)+fabs(vec.y)+fabs(vec.z);
    double eps = 1.0e-7;
    
    if( tmp < eps ){		// cutoff
      node_normal[inode] = XYZ(0,0,0);
      
    }else{			// normalisation
      node_normal[inode] = vec / sqrt( vec * vec );
      node_surflag[inode] = true;
    }
  }
  
  return node_surflag;
}

// * * * * * * * * * * * * * * * * * * * * *

BoolValueArray Func::GetFaceSurflag()
{
  // define
  int num_faces = mesh().faces().size();
  
  // make value array
  Object tmp_obj;
  tmp_obj.SetName( "face_surflag" );
  tmp_obj.SetDataType( Object::FACE );
  tmp_obj.SetValueType( Object::BOOL );
  BoolValueArray face_surflag(num_faces, false, tmp_obj);

  // get node surflag
  BoolValueArray node_surflag = GetNodeSurflag();

  // check surface
  for(int iface=0; iface<num_faces; iface++){
    int num_facenodes=mesh().faces(iface).node_ptrs().size();
    bool check = true;

    for(int jnode=0; jnode<num_facenodes; jnode++){
      int inode = mesh().faces(iface).nodes(jnode).index();
      check = check && node_surflag[inode];
    }
    face_surflag[iface] = check;
  }

  return face_surflag;
}

// * * * * * * * * * * * * * * * * * * * * *

BoolValueArray Func::GetCellSurflag()
{
  // define
  int num_cells = mesh().cells().size();
  
  // make value array
  Object tmp_obj;
  tmp_obj.SetName( "cell_surflag" );
  tmp_obj.SetDataType( Object::CELL );
  tmp_obj.SetValueType( Object::BOOL );
  BoolValueArray cell_surflag(num_cells, false, tmp_obj);

  // get node surflag
  BoolValueArray face_surflag = GetFaceSurflag();

  // check surface
  for(int icell=0; icell<num_cells; icell++){
    int num_cellfaces=mesh().cells(icell).face_ptrs().size();
    bool check = true;

    for(int jface=1; jface<num_cellfaces; jface++){
      int iface = mesh().cells(icell).faces(jface).index();
      check = check && face_surflag[iface];
    }
    cell_surflag[icell] = check;
  }

  return cell_surflag;
}

// * * * * * * * * * * * * * * * * * * * * *

BoolValueArray Func::ConvertFlagFaceToNode
(const BoolValueArray& face_surflag )
{
  // Pre- condition
  assert( mesh().faces().size() == face_surflag.size() );
  // define
  int num_nodes = mesh().nodes().size();
  int num_faces = mesh().faces().size();

    // make value array
  Object tmp_obj;
  tmp_obj.SetName( "node_surflag" );
  tmp_obj.SetDataType( Object::NODE );
  tmp_obj.SetValueType( Object::BOOL );
  BoolValueArray node_surflag(num_nodes, false, tmp_obj);

  for(int iface=0; iface<num_faces; iface++){
    int num_facenodes = mesh().faces(iface).node_ptrs().size();
    bool has_face = face_surflag[iface];

    if( has_face == true){
      for(int jnode=0; jnode<num_facenodes; jnode++){
	int inode = mesh().faces(iface).nodes(jnode).index();
	node_surflag[inode] = true;
      }
    }
  }
  return node_surflag;
}


// check
void Func::Check() const
{
  if( mesh_ptr_ == NULL ){
    std::cerr << "ERROR: class Func don't has mesh pointer!" << std::endl;
    assert(false);
  }
}

// ---- Getter
const Mesh& Func::mesh() const
{
  Check();
  return *mesh_ptr_;
}

// ---- Setter
void Func::SetMesh(Mesh& mesh)
{
  if( mesh_ptr_ != NULL ){
    std::cerr << "ERROR: class Func already has mesh pointer!" << std::endl;
    assert(false);
  }
  mesh_ptr_ = &mesh;
}

// * * * * * * * * * * * * Member Operators * * * * * * * * * * * * * //
// * * * * * * * * * * Template Specializations * * * * * * * * * * * //
// * * * * * * * * * * * Explicit Instantation  * * * * * * * * * * * //
