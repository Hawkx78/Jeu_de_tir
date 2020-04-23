#include "Point.h"



    Point::Point(float x, float y):abs(x), ord(y){}
	
	Point::~Point(){}
	
	float Point::getAbs(){return this->abs;}
	
	float Point::getOrd(){return this->ord;}
	
	void Point::setAbs(float x){this->abs = x;}
	
	void Point::setOrd(float y){this->ord = y;}
	
	Point Point::getPoint(){return *this;}
	
	bool Point::operator ==(Point const &p1){
		
		if (p1.abs == this->abs && p1.ord == this->ord) return true;
		
		return false;
		
		}
