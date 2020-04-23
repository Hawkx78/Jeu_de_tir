#ifndef POINT_HH
#define POINT_HH

class Point{
	
	private:
	
	float abs;
	float ord;
	
	public:
	
	Point(float, float);
	~Point();
	float getAbs();
	float getOrd();
	void setAbs(float);
	void setOrd(float);
	Point getPoint();
	bool operator==(Point const&);
	
	};




#endif
