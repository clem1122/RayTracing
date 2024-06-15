#include "hitable.h"
#include "aabb.h"

class hitable_list: public hitable {
public:
	hitable **list;
	int list_size;
	aabb bbox;
	
	hitable_list() {};
	hitable_list(hitable **l, int n); 
	bool hit(const ray& r, interval ray_t, hit_record& rec) const override;
	aabb bounding_box() const override {return bbox;}

};

bool hitable_list::hit(const ray& r, interval ray_t, hit_record& rec) const{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = ray_t.max;
	for (int i =0; i < list_size; i++) {
		if (list[i]->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}

hitable_list::hitable_list(hitable **l, int n){
	list = l; 
	list_size = n;
	
	for(int i = 0; i < n; i++) {
		bbox = aabb(bbox, l[i]->bounding_box());
	}
}
