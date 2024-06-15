#include <iostream>
#include <cstdlib>
#include "sdltemplate.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "aabb.h"

vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, MAXFLOAT, rec)) {
		ray scattered;
		vec3 attenuation;
		if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth+1);
		} else {
			return vec3(0,0,0);
		}
	} else {
		vec3 unit_dir = unit_vector(r.direction());
		float t = 0.5*(unit_dir.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0); //lerp between 2 colors	
	}
}

hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n+1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	/*
	for(int a = -4; a < 4; a++) {
		for(int b = -4; b < 4; b++) {
				float choose_mat = drand48();
				vec3 center(a+0.9*drand48(), 0.2, b+0.9*drand48());
				if (choose_mat < 0.8) {
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
				} else if (choose_mat < 0.95) {
					list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48())), 0.5*(1+drand48())));
				} else {
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
		}	
	}*/
	list[i++] = new sphere(vec3(0,1,0), 1 , new dielectric(1.5));
	list[i++] = new sphere(vec3(-4,1,0), 1 , new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4,1,0), 1, new metal(vec3(0.7, 0.6, 0.5), 0));
	return new hitable_list(list, i);
	
}

int main(int argc, char** argv){

	
	int width = 800;
	int height = 400;
	int ns = 80;
	if (argc >1) {ns = std::atoi(argv[1]);} 

	
	
	std::cout << "P3\n" << width << " " << height << "\n255\n";
	sdltemplate::sdl("Ray Tracer", width, height);
	sdltemplate::loop();
	

	/*
	hitable *list[5];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(1.0, 0.0, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5,new metal(vec3(0.8, 0.6, 0.2), 0.2));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	
	hitable *world = new hitable_list(list, 5);*/
	//camera cam;
	/*
	hitable *list[2];
	float R = cos(M_PI/4);
	list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0,0,1)));
	list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1,0,0)));
	
	hitable *world = new hitable_list(list, 2);*/
	hitable *world = random_scene();
	vec3 lookfrom(13,2,3);
	vec3 lookat(0,0,0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;
	
	camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(width)/float(height), aperture, dist_to_focus);
	for(int y = height-1; y >= 0; y--){
		for(int x = 0; x < width; x++){
			vec3 col(0,0,0);
			for (int s = 0; s < ns; s++){
				float u = float(x + drand48()) / float(width);
				float v = float(y + drand48()) / float(height);
				ray r = cam.get_ray(u,v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}
			col /= ns;
			col = vec3(sqrt(col.r()),sqrt(col.g()), sqrt(col.b()));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			if (x % width == 1) sdltemplate::loop();
			//std::cout << ir << " " << ig << " " << ib << "\n";
			sdltemplate::setDrawColor(sdltemplate::createColor(ir, ig, ib, 255));
			sdltemplate::drawPoint(x,height - 1 - y);
		}
		
		
	}
	while(sdltemplate::running) {
		sdltemplate::loop();
	}

}
