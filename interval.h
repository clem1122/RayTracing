#include <limits>

const float infinity = std::numeric_limits<float>::infinity();
const float neg_infinity = -std::numeric_limits<float>::infinity();

class interval {
public:
	float min, max;
	
	interval() : min(infinity), max(neg_infinity) {}
	interval(float m, float M) : min(m), max(M) {}
	interval(const interval& a, const interval& b){
		min = (a.min <= b.min) ? a.min : b.min;
		max = (a.max >= b.max) ? a.max : b.max;
	}
	
	float size() const {return max - min;}
	bool contains(float x) {return (x >= min && x <= max);}
	bool surrounds(float x){return (x >  min && x < max);}
	
	interval expland(float delta) const {
		float padding = delta/2;
		return interval(min - padding, max + padding);
	}
	
	static const interval empty;
	static const interval universe;

};

const interval interval::empty = interval(infinity, neg_infinity);
const interval interval::universe = interval(neg_infinity, infinity);


