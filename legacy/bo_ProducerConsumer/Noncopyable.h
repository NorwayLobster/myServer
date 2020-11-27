 ///
 /// @file    Noncopyable.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-03-10 21:17:22
 ///
#ifndef Noncopyable
#define Noncopyable
using namespace std;
class Noncopyable{
public:
	Noncopyable()=default;
	~Noncopyable()=default;
	Noncopyable(const Noncopyable &)=delete;
	Noncopyable & operator=(const Noncopyable & )=delete;
};
#endif 
