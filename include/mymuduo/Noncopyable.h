 ///
 /// @file    Noncopyable.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-03-17 11:39:50
 ///
 
#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__


namespace wd
{

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}

	//禁止复制
	Noncopyable(const Noncopyable &) = delete;
	Noncopyable & operator=(const Noncopyable &) = delete;
};

}

#endif
