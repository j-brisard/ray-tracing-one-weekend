#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "plane.h"
#include "camera.h"

int main() {

     // World

    hittable_list world;

    /*
    //Materials
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_left   = make_shared<metal>(color(0.2, 0.2, 0.8),0.2);
    auto material_center = make_shared<lambertian>(color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<dielectric>(1.5);//1.5/1 is the refraction index of glass inside of air
    auto material_bubble  = make_shared<dielectric>(1.0/1.5);//1.0/1.5 is the refraction index of air inside of glass

    //Spheres
    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));//Glass sphere
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.4, material_bubble));//Adds an air sphere inside the glass sphere
    
    //Planes
    //world.add(make_shared<plane>(point3(-3.0,    0.0, -1.0), vec3(1,,0), material_right));
    //world.add(make_shared<plane>(point3( 3.0,    0.0, -1.0), vec3(-1,0,0), material_left));
    */

    auto R = std::cos(pi/4);

    auto material_left  = make_shared<lambertian>(color(0,0,1));
    auto material_right = make_shared<lambertian>(color(1,0,0));

    world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
    world.add(make_shared<sphere>(point3( R, 0, -1), R, material_right));

    camera cam;

    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 100;

    cam.vfov = 20;
    
    cam.render(world);
}