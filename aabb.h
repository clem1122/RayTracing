#pragma once
#include "interval.h"

class aabb {
public:
	interval x,y,z;
	
	aabb();
	
	aabb(const interval& x_, const interval& y_, const interval& z_) : x(x_), y(y_), z(z_) {}
	
	aabb(const vec3& a, const vec3& b) {
		x = (a[0] <= b[0]) ? interval(a[0], b[0]) : interval(b[0], a[0]);
		y = (a[1] <= b[1]) ? interval(a[1], b[1]) : interval(b[1], a[1]);
		z = (a[2] <= b[2]) ? interval(a[2], b[2]) : interval(b[2], a[2]);
	}
	
	const interval& axis_interval(int n) const {
		if (n == 0) return x;
		if (n == 1) return y;
		return z;
	}
	
	bool hit(const ray& r, interval ray_t) const {
		const vec3& origin = r.origin();
		const vec3& direction = r.direction();
		
		for(int axis = 0; axis < 3; axis++) {
			const interval& ax = axis_interval(axis);
			
			double t0 = (ax.min - origin[axis]) / direction[axis];
			double t1 = (ax.max - origin[axis]) / direction[axis];
			
			if (t0 < t1) {
				if (t0 > ray_t.min) ray_t.min = t0;
				if (t1 < ray_t.max) ray_t.max = t1;
			} else {
				if (t1 > ray_t.min) ray_t.min = t1;
				if (t0 < ray_t.max) ray_t.max = t0;
			}	
			
			if (ray_t.max <= ray_t.min) 
				return false;		
		}
		
		return true;
	
	}




};
