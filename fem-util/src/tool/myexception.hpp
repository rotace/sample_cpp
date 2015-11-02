//----------------------------------------------------------------------
/**
   @file myexception.hpp
   @brief My Exception Class
   
   @author Shibata
   @date 2015-01-03(土) 11:10:29
   
***********************************************************************/

#ifndef _MYEXCEPTION_H_
#define _MYEXCEPTION_H_

#include <string>
#include <exception>
#include <boost/throw_exception.hpp>
#include <boost/exception/all.hpp>

namespace tool
{

  typedef boost::error_info<struct tagname, std::string> errmsg_info;
  /*--------------------------------------------------------------------*
    Class Declaration (BEGIN)
    *--------------------------------------------------------------------*/
  class MyException
    :public boost::exception,
     public std::exception
  {
  private:
    // ##### Private Data Members
    std::string msg_;
  
  public:
    // ##### Constructors
    MyException()
      :std::exception(),
       msg_("Default Error")
    {}

    MyException(const std::string msg)
      :std::exception(),
       msg_(msg)
    {}
  
    // ##### Destructor
    ~MyException() throw(){}
  
    // ##### Member Functions
    virtual const char* what() const throw();
  };
  /*--------------------------------------------------------------------*
    Class Declaration (END)
    *--------------------------------------------------------------------*/

  /*--------------------------------------------------------------------*
    Derived Class Declaration
    *--------------------------------------------------------------------*/
  
  // RuntimeError
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  /*--------------------------------------------*
    Runtime Error
    実装以外の問題からくるエラーの処理
    例：入出力エラー，メモリーのオーバーフロー
   *--------------------------------------------*/
  class RuntimeError : public MyException {
  public:
    RuntimeError()
      :MyException("Runtime Error"){}
    RuntimeError(const std::string& e)
      :MyException("Runtime Error/ " + e){}
  };

  /*--------------------------------------------*
    IOError
    入出力エラーの処理
    例：
    ・ファイルが読み込めない
    ・ノード数とセル数が合わない
   *--------------------------------------------*/
  class IOError : public RuntimeError {
  public:
    IOError()
      :RuntimeError("IO Error"){}
    IOError(const std::string& e)
      :RuntimeError("IO Error/ " + e){}
  };


  
  // LogicError
  // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

  /*--------------------------------------------*
    LogicError
    実装の問題からくるエラーの処理
    例：
    ・バグによるエラー
    ・事前・事後条件のチェック
    ・未実装エラー

    ※これらのエラーは，基本的にassertで処理すること．
    プログラム停止を回避したい時のみ，例外処理を行う．
   *--------------------------------------------*/
  class LogicError : public MyException {
  public:
    LogicError()
      :MyException("Logic Error"){}
    LogicError(const std::string& e)
      :MyException("Logic Error/ " + e){}
  };

  

} // end namespace tool

#endif /* _MYEXCEPTION_H_ */

