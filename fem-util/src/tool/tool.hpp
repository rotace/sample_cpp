//----------------------------------------------------------------------
/**
   @file tool.hpp
   @brief ツール

   コーディングに用いる関数などを書き留める
   
   @author Shibata
   @date 2014-12-20(土) 21:07:52
   
***********************************************************************/

#ifndef _TOOL_H_
#define _TOOL_H_

namespace tool
{

  // trim
  inline std::string trim(const std::string& string, const char* trimCharacterList = " \t\v\r\n")
  {
    std::string result;
    std::string::size_type left = string.find_first_not_of(trimCharacterList);
    if(left != std::string::npos)
      {
	std::string::size_type right = string.find_last_not_of(trimCharacterList);
	result = string.substr(left, right-left+1);
      }
    return result;
  }

  // split
  inline std::vector<std::string> split(const std::string &str, char delim){
    std::istringstream iss(str);
    std::string tmp;
    std::vector<std::string> res;
    while(getline(iss, tmp, delim)) res.push_back(tmp);
    return res;
  }

  // get extention
  inline std::string GetExtension(const std::string &path){
    std::string ext;
    size_t pos1 = path.rfind('.');
    if(pos1 != std::string::npos){
      ext = path.substr(pos1+1, path.size()-pos1);
      std::string::iterator itr= ext.begin();
      while(itr != ext.end()){
	*itr = std::tolower(*itr);
	itr++;
      }
      itr = ext.end()-1;
      while(itr != ext.begin()){ // パスの最後に\0やスペースがある時の対策
	if(*itr ==0 || *itr ==32){
	  ext.erase(itr--);
	}
	else{
	  itr--;
	}
      }
    }

    return ext;
  }

}

#endif /* _TOOL_H_ */
