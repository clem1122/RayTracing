#pragma once
#include "hitable.h"

class material;


class sphere: public hitable {
public:
	vec3 center;
	float radius;
	material *mat_ptr;

	
	sphere();
	sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
	
	bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, interval ray_t, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = r.direction().length_squared(); // !!!
	float b = dot(oc, r.direction()); // b / 2.0 pour discriminant réduit
	float c = oc.length_squared() - radius * radius;
	
	float discriminant = b * b - a * c;
	if(discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (ray_t.surrounds(temp)) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (ray_t.surrounds(temp)) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}
