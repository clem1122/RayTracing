#include <limits>

const float infinity = std::numeric_limits<double>::infinity();
const float neg_infinity = -std::numeric_limits<double>::infinity();

class interval {
public:
	double min, max;
	
	interval() : min(infinity), max(neg_infinity) {}
	interval(double min, double max) : min(min), max(max) {}
	
	double size() const {return max - min;}
	bool contains(double x) {return (x >= min && x <= max);}
	bool surrounds(double x){return (x >  min && x < max);}
	
	static const interval empty;
	static const interval universe;

};

const interval interval::empty = interval(infinity, neg_infinity);
const interval interval::universe = interval(neg_infinity, infinity);


