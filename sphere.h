#pragma once
#include "hitable.h"
#include "aabb.h"

class material;

class sphere: public hitable {
public:
	vec3 center;
	float radius;
	material *mat_ptr;
	aabb bbox;

	
	sphere();
	sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {
		vec3 radius_vector = vec3(radius, radius, radius);
		bbox = aabb(center - radius_vector, center + radius_vector);
	};
	
	bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
	aabb bounding_box() const override { return bbox; }
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
