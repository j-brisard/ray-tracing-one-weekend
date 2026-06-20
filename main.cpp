#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

//SPHERE
const point3 S_CENTER = {0, 0, -2};
const double S_RADIUS = 0.5;

double hit_sphere(const point3& center, const double radius, const ray& r){
    //Returns -1 if ray r doesn't hit the sphere
    //Else, return the t values of the nearest hit point

    vec3 qc = center - r.origin();
    const vec3 d = r.direction();
    double a = dot(d, d);
    double b = dot(-2*d,qc);
    double c = dot(qc,qc)-radius*radius;
    double delta = b*b-4*a*c;
    
    if (delta < 0.0) { // No intersection
        return -1.0;
    } else {
        return (-b - std::sqrt(delta)) / (2.0 * a); // plus petite solution
    }

}

color ray_color(const ray& r) {
    double t = hit_sphere(S_CENTER,S_RADIUS, r);
    if (t>0){
        vec3 n = unit_vector(r.at(t)-S_CENTER);
        return 0.5*color(n.x()+1, n.y()+1, n.z()+1);
    }

    auto norm_dir = unit_vector(r.direction());
    auto indicator = 0.5*(norm_dir.y()+1.);
    return (1-indicator)*color(1.0,1.0,1.0)+indicator*color(0.5, 0.7, 1.0);
}

int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0; //Distance between VP and Camera
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);//Horizontal
    auto viewport_v = vec3(0, -viewport_height, 0);//Vertical

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {

            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);

            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}