//----------------------------------------------------------------------
/**
   @file iodatafea.cpp
   @brief FEA入出力
   
   @author Shibata
   @date 2015-01-03(土) 13:58:19
   
***********************************************************************/

#include "iodata.hpp"

#include <assert.h>      // assert
#include <sstream>		// stringstream
#include <iostream>		// string
#include <fstream>		// fstream
#include <boost/format.hpp>	// format
#include <boost/algorithm/string.hpp> // iequals

#include "mateuser1.hpp"
#include "matesolid.hpp"

using std::cout;
using std::endl;

/*--------------------------------------------------------------------*
  Import Section
 *--------------------------------------------------------------------*/
void IOData::ImportFea(const std::string filename)
  throw(tool::IOError)
{
  cout << endl << endl;
  cout << "## IOData::ImportFea ##" << endl;

  // read and check
  std::ifstream ifs( filename.c_str() );
  if(ifs.fail()){
    BOOST_THROW_EXCEPTION( tool::IOError("Cannot Open File!") );
  }

  std::stringstream ss;
  while( !ifs.eof() ){
    std::string buf;
    getline( ifs, buf );
     // replace camma to space
    std::replace(buf.begin(), buf.end(), ',', ' ' );
    // remove commentout
    std::string buf_co = buf.substr(0, buf.find( "!", 0) );
    // remove space line
    bool blank = true;
    for(size_t i=0; i<buf_co.size();i++){
      // cout << (buf_co[i] != ' ' && buf_co[i] != '\t' && buf_co[i] != '\n');
      if(buf_co[i] != ' '
	 && buf_co[i] != '\t'
	 ) blank = false;
    }
    if( blank ){
      ss << endl;
      // cout << endl;
    }else{
      ss << buf_co << endl;
      // cout <<buf_co << endl;
    }
  }
  

  // initialize mesh
  InitMeshFea( ss );
  // read mesh
  ReadMeshFea( ss );
  // read value
  ReadBoundaryFea( ss );
  // read property
  ReadPropertyFea( ss );

  // information
  Info();
  // register import format type
  default_fmt_ = FEA;
}



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void IOData::InitMeshFea(std::stringstream& ifs)
  throw(tool::IOError)
{
// define
  std::string buffer;
  int num_nodes=0;
  int num_faces=0;
  int num_cells=0;
  int num_cellnodes=0;
  MeshInfo::CellType max_celltype = MeshInfo::TRIA3;
  
  
  // ### Count Mesh Elements ###
  // define
  bool read_header=false;

  // eof flag clear and rewind
  ifs.clear();
  ifs.seekg(0, std::ios::beg);
  
  while( getline(ifs, buffer) ){
    std::string head = buffer.substr(0,4);

    // Check Header
    if( strstr( head.c_str() , "FEAP") ){
      getline(ifs, buffer);
      std::string tmp_s;
      std::vector<int> tmp_i(6,0);
      std::istringstream tmp_stream(buffer);
      for(int i=0; i<6; i++){
    	  tmp_stream >> tmp_s;
    	  tmp_i.at(i) = atoi( tmp_s.c_str() );
      }
      // tmp_i[i]
      // 0: num_nodes
      // 1: num_cells
      // 2:
      // 3:
      // 4:
      // 5: num of nodes per cell
      num_nodes = tmp_i[0];
      num_cells = tmp_i[1];
      num_cellnodes = tmp_i[5];

      // set celltype and count num_faces
      if      (false){
	
      }else if(num_cellnodes==8){ // HEXA8
	max_celltype = MeshInfo::HEXA8;
	num_faces = num_cells*6;
	
      }else{			// error
	std::stringstream error;
	error << "Cannot Recognize CellType No."
	      << num_cellnodes;
	BOOST_THROW_EXCEPTION( tool::IOError(error.str()) );
      }
      // read flag
      read_header=true;
      
    } // endif
  } // endwhile

  
  // error information
  if( !read_header )
    BOOST_THROW_EXCEPTION( tool::IOError("cannot read_header!") );
  
  // ### Init ###
  Init(num_nodes, num_faces, num_cells, max_celltype);
    
// #ifndef NDEBUG
//     // information
//     cout << "NUM_NODES    : " << num_nodes << endl;
//     cout << "NUM_FACES    : " << num_faces << endl;
//     cout << "NUM_CELLS    : " << num_cells << endl;
//     cout << "MAX_CELLTYPE : " << max_celltype << endl;
// #endif
}




// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void IOData::ReadMeshFea(std::stringstream& ifs)
  throw(tool::IOError)
{
  // define
  std::string buffer;
  Mesh& mesh = *mesh_ptr_;
  const int num_nodes = mesh.nodes().size();
  const int num_cells = mesh.cells().size();
  const MeshInfo::CellType max_celltype = mesh.max_celltype();
  const int num_cellnodes
    = MeshInfo::GetNumOf(max_celltype,MeshInfo::CELLNODES);
  
  
  // ### Read Mesh Elements ###
  // define
  bool read_nodes=false;
  bool read_cells=false;
  int inode=0;
  int icell=0;
  // map<node_id,node_index>
  std::map<int,int> id_link;
  
  // ## READ NODES ------
  ifs.clear();
  ifs.seekg(0, std::ios::beg);
  
  while( getline(ifs, buffer) ){
    std::string head = buffer.substr(0,4);

    if( strstr( head.c_str() , "COOR") ){
      cout << "POINTS     ...reading";

      while(true){
	getline(ifs, buffer);
	if(buffer.empty()) break;
	if(inode >= num_nodes)
	  BOOST_THROW_EXCEPTION( tool::IOError("num_nodes Over Size!") );

	std::string waste;
	int node_id;
	XYZ tmp_grid;
	std::istringstream tmp_stream(buffer);
	tmp_stream >> node_id;    // 1
	tmp_stream >> waste;	  // 2
	tmp_stream >> tmp_grid.x; // 3
	tmp_stream >> tmp_grid.y; // 4
	tmp_stream >> tmp_grid.z; // 5

	id_link[node_id] = inode;
	mesh.nodes(inode).SetGrid(tmp_grid);
	mesh.nodes(inode).SetID(node_id);
	inode++;
      }
      
      read_nodes=true;
      cout << "  ...finished" << endl;
    } // endif
  } // endwhile

  // ## READ CELLS ------
  // ## SET CELLTYPE ----
  ifs.clear();
  ifs.seekg(0, std::ios::beg);
  
  while( getline(ifs, buffer) ){
    std::string head = buffer.substr(0,4);

    if( strstr( head.c_str() , "ELEM") ){
      cout << "CELLS      ...reading";

      while(true){
	getline(ifs, buffer);
	if(buffer.empty()) break;
	
	std::string waste;
	int cell_id;
	int node_id;
	std::istringstream tmp_stream(buffer);
	tmp_stream >> cell_id; // 1
	tmp_stream >> waste;   // 2
	tmp_stream >> waste;   // 3

	if(icell >= num_cells)
	  BOOST_THROW_EXCEPTION( tool::IOError("num_cells Over Size!") );

	int inode=-1;
	for(int jnode=0; jnode<num_cellnodes; jnode++){
	  tmp_stream >> node_id;
	  inode = id_link[node_id];

	  // linking
	  mesh.cells(icell).SetNodePtr(jnode, &(mesh.nodes(inode)) );
	}
	// set celltype
	mesh.cells(icell).SetCellType(max_celltype);
	// set id
	mesh.cells(icell).SetID(cell_id);
	icell++;
      }
      read_cells=true;
      cout << "  ...finished" << endl;
    } // endif
  } // endwhile

  // error information
  if( !read_nodes )
    BOOST_THROW_EXCEPTION( tool::IOError("cannot read_nodes!") );
  if( !read_cells )
    BOOST_THROW_EXCEPTION( tool::IOError("cannot read_cells!") );

  // linking
  mesh.Link();
}





// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void IOData::ReadBoundaryFea(std::stringstream& ifs)
  throw(tool::IOError)
{
  // define
  std::string buffer;
  Mesh& mesh = *mesh_ptr_;
  const int num_nodes = mesh.nodes().size();
  const MeshInfo::CellType max_celltype = mesh.max_celltype();

  
  // ### Read Boundary ###
  ifs.clear();
  ifs.seekg(0, std::ios::beg);
  
  while( getline(ifs, buffer) ){
    std::istringstream headline(buffer);
    std::string head;
    headline >> head;

    if( strstr( head.c_str() , "BOUN") ){
      cout << "BOUNDARY   ...reading";

      Object tmp_obj;
      tmp_obj.SetName("boundary_para");
      tmp_obj.SetDataType( Object::NODE );
      tmp_obj.SetValueType( Object::XYZ );
      XYZValueArray tmp_values_para(num_nodes, XYZ(0,0,0), tmp_obj, false);
      tmp_obj.SetName("boundary_rot");
      tmp_obj.SetDataType( Object::NODE );
      tmp_obj.SetValueType( Object::XYZ );
      XYZValueArray tmp_values_rot(num_nodes, XYZ(0,0,0), tmp_obj, false);

      while(true){
	getline(ifs, buffer);
	if(buffer.empty()) break;

	std::string waste;
	int node_id;
	XYZ tmp_xyz;
	std::istringstream tmp_stream(buffer);
	tmp_stream >> node_id; // 1
	node_id += -1;	  // [1~n] -> [0~n-1]
	tmp_stream >> waste ;	  // 2
	tmp_stream >> tmp_xyz.x;  // 3
	tmp_stream >> tmp_xyz.y;  // 4
	tmp_stream >> tmp_xyz.z;  // 5

	if(node_id >= num_nodes)
	  BOOST_THROW_EXCEPTION( tool::IOError("num_nodes Over Size!") );
	
	tmp_values_para.SetValue(node_id, tmp_xyz);
	tmp_values_para.SetFlag( node_id, true);

	if( MeshInfo::GetHasRotBoundary(max_celltype) ){
	  tmp_xyz = XYZ(0,0,0);
	  tmp_stream >> tmp_xyz.x;  // 6
	  tmp_stream >> tmp_xyz.y;  // 7
	  tmp_stream >> tmp_xyz.z;  // 8
	  tmp_values_rot.SetValue(node_id, tmp_xyz);
	  tmp_values_rot.SetFlag( node_id, true);
	}
	
      }	// end while
      
      // set to object dictionary
      SetValues( tmp_values_para );
      SetValues( tmp_values_rot );
      
      // end processing
      cout << "  ...finished" << endl;
    } // end if
  } // end while
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
void IOData::ReadPropertyFea(std::stringstream& ifs)
  throw(tool::IOError)
{
	// define
	std::string buffer;
	MatePtr mate_ptr;
	int id = 0;

	// ## READ PROPERTY ------
	ifs.clear();
	ifs.seekg(0, std::ios::beg);

	while(true){
		getline(ifs, buffer);
		if(buffer.empty()) break;
		std::istringstream headline(buffer);
		headline >> buffer;
		std::string head = buffer.substr(0,4);
		cout << buffer << endl;
		cout << head   << endl;

//		Material ID
		if      ( boost::iequals(head, std::string("mate")) ){
			cout << "MATErial   ...reading";
			headline >> id;
			cout << "  ...finished" << endl;


//		register Material
		}else if( boost::iequals(head, std::string("user")) ){
			cout << "User       ...reading";
			int uid;
			headline >> uid;

			if      ( uid == 1 ){
				// generate
				MateUser1* user1_ptr = new MateUser1();
				// shared_ptr initialize
				mate_ptr = MatePtr(dynamic_cast<Material*>(user1_ptr));
				// register
				mate_dict_.insert(std::make_pair(id, mate_ptr));

				mate_ptr->SetId(id);
				mate_ptr->SetType(Material::USER1);

			}else if( uid == 2 ){
				std::cerr << "Error: user2 not implemented!" << endl;
				assert(false);
			}
			cout << "  ...finished" << endl;

		}else if( boost::iequals(head, std::string("soli")) ){
			cout << "Solid      ...reading";
			// generate
			MateSolid* solid_ptr = new MateSolid();
			// shared_ptr initialize
			mate_ptr = MatePtr(dynamic_cast<Material*>(solid_ptr));
			// register
			mate_dict_.insert(std::make_pair(id, mate_ptr));

			mate_ptr->SetId(id);
			mate_ptr->SetType(Material::SOLID);
			cout << "  ...finished" << endl;


//		Input each data
		}else if( boost::iequals(head, std::string("dens")) ){
			cout << "Density    ...reading";
			double rho;
			headline >> buffer;  // waste name
			headline >> rho;
			mate_ptr->SetRho(rho);
			cout << "  ...finished" << endl;

		}else if( boost::iequals(head, std::string("elas")) ){
			cout << "Elastic    ...reading";
			double E;
			double nu;
			headline >> buffer;  // waste name ex)"Isotroopic"
			headline >> E;
			headline >> nu;
			mate_ptr->SetE(E);
			mate_ptr->SetNu(nu);
			cout << "  ...finished" << endl;

		}else if( boost::iequals(head, std::string("ucon")) ){
			cout << "Ucon       ...reading";
			headline >> head;
			head = head.substr(0,4);
			if      ( boost::iequals(head, std::string("acfl")) ){
				double c;
				headline >> c;
				mate_ptr->SetC(c);

			}else if( boost::iequals(head, std::string("bio1")) ){
				std::cerr << "Error: bio1 not implemented!" << endl;
				assert(false);

			}else if( boost::iequals(head, std::string("bio2")) ){
				std::cerr << "Error: bio2 not implemented!" << endl;
				assert(false);
			}
		}// endif

	}// endwhile
}

/*--------------------------------------------------------------------*
  Export Section
 *--------------------------------------------------------------------*/
void IOData::ExportFea(const std::string filename)
  throw(tool::IOError)
{
  cout << endl << endl;
  cout << "## IOData::ExportVtk ##" << endl;

  // define
  const Mesh& mesh = *mesh_ptr_;
  const int num_nodes = mesh.nodes().size();
  const int num_cells = mesh.cells().size();
  MeshInfo::CellType max_celltype = mesh.max_celltype();

  // mesh CHECK
  mesh.Check();
  // information
  Info();
  
  // OPEN
  std::ofstream ofs( filename.c_str() );


  // ## WRITE HEADER --------
  boost::format fmt_header("%10d,%10d,%3d,%3d,%3d,%3d");
  fmt_header % num_nodes % num_cells % 1 % 3 % 3;
  fmt_header % MeshInfo::GetNumOf( max_celltype, MeshInfo::CELLNODES);
  ofs << "FEAP  DATA" << endl;
  ofs << fmt_header << endl;;

  // ## WRITE MATErial ------
  for(MateDict::iterator it = mate_dict_.begin();
		  it != mate_dict_.end(); ++it){

	  MatePtr mate_ptr = it->second;
	  ofs << "MATErial,"<< mate_ptr->id() << endl;

	  switch( mate_ptr->type() ){
	  case Material::BLANK:
		  BOOST_THROW_EXCEPTION( tool::IOError("no material data!") );
		  break;
	  case Material::SOLID:
		  ofs << "  SOLId" << endl;
		  ofs << "    ELAStic ISOTropic "
				  << mate_ptr->E() << " " << mate_ptr->nu() << endl;
		  ofs << "    DENSity MASS " << mate_ptr->rho() << endl;
		  ofs << "    MASS CONSistent" << endl;
		  ofs << "                !Blank termination record" << endl;
		  break;
	  case Material::USER1:
		  ofs << "  USER, 1" << endl;
		  ofs << "    DENSity air " << mate_ptr->rho() << endl;
		  ofs << "    UCON  acfld " << mate_ptr->c()
					  << "  0.0  1000"<< endl;
		  ofs << "                !Blank termination record" << endl;
		  break;
	  case Material::USER2:
		  std::cerr << "Error: not implemented!" << endl;
		  assert(false);
		  break;
	  }
  }

  // ## WRITE NODES --------
  cout << "POINTS     ...writing";
  // set format
  boost::format fmt_node("%10d 0   %14E  %14E  %14E\n");
  // header
  ofs << "COORdinates" << endl;
  // write node
  for(int inode=0; inode<num_nodes; inode++){
    const XYZ tmp_grid = mesh.nodes(inode).grid();
    fmt_node % (inode+1);
    fmt_node % (float)tmp_grid.x % (float)tmp_grid.y % (float)tmp_grid.z;
    ofs << fmt_node;
  }
  ofs << "                !Blank termination record" << endl; 
  cout << "  ...finished" << endl;

  
  // ## WRITE CELLS --------
  cout << "CELLS      ...writing";
  // set format
  boost::format fmt_cell_head("%10d %2d %2d");
  // header
  ofs << "ELEMents" << endl;
  for(int icell=0; icell<num_cells; icell++){
    int num_cellnodes = mesh.cells(icell).node_ptrs().size();
    fmt_cell_head % (icell+1) % 1 % 1;
    ofs << fmt_cell_head;
    
    for(int jnode=0; jnode<num_cellnodes; jnode++){
      int inode = mesh.cells(icell).nodes(jnode).index();
      ofs << "  " << inode + 1;
    }
    ofs << endl;
  }
  ofs << "                !Blank termination record" << endl; 
  cout << "  ...finished" << endl;


  // ## WRITE BOUNDARY -------
  // set format
  boost::format fmt_boun_head("%10d 0");
  boost::format fmt_boun(" %2d %2d %2d");
  
  if ( name_dict_.find("boundary_para") != name_dict_.end() ){
    cout << "boundary ...writing";
    // header
    ofs << "BOUNdary restraints" << endl;

    ObjectPtr obj_ptr_para = name_dict_["boundary_para"];
    XYZValueArray values_para = *dynamic_cast<XYZValueArray*>(obj_ptr_para.get());
    if( num_nodes != (int)values_para.size() ){
      BOOST_THROW_EXCEPTION( tool::IOError("Data Mismatch!") );
    }

    for(int inode=0; inode<num_nodes; inode++){
      if (values_para.flag(inode) ){
	XYZ tmp_XYZ = values_para[inode];
	fmt_boun_head % (inode+1);	// [0~n-1] -> [1~n]
	fmt_boun % (int)tmp_XYZ.x % (int)tmp_XYZ.y % (int)tmp_XYZ.z;
	ofs << fmt_boun_head << fmt_boun;

	if( MeshInfo::GetHasRotBoundary(max_celltype) ){
	  XYZ tmp_XYZ = values_para[inode];
	  fmt_boun % (int)tmp_XYZ.x % (int)tmp_XYZ.y % (int)tmp_XYZ.z;
	  ofs << fmt_boun;
	}

	ofs << endl;
      }
    }
    ofs << "                !Blank termination record" << endl; 
    cout << "  ...finished" << endl;
  }
  
  ofs << "END" << endl;
  ofs << "STOP" << endl; 

}
