#pragma once
#include "hitable.h"
#include "aabb.h"
#include "lib.h"

class hitable_list: public hitable {
public:
	std::vector<shared_ptr<hitable>> objects;
	aabb bbox;
	
	hitable_list() {};
	hitable_list(shared_ptr<hitable> object) { add(object); }
	bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
	aabb bounding_box() const override {return bbox;}
	
	void clear() { objects.clear(); }
	
	void add(shared_ptr<hitable> object) {
        objects.push_back(object);
    }
};

bool hitable_list::hit(const ray& r, interval ray_t, hit_record& rec) const{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = ray_t.max;
	for (const auto& object : objects) {
		if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}
