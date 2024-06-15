#pragma once 
#include "ray.h"
#include "aabb.h"


class material;


struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
};

class hitable{
public:
	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
	
	//virtual aabb bounding_box() const = 0;
};
