#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
    public:
        sphere(const point3& center, const double radius) : center(center) , radius(std::fmax(0,radius)){};

        

        bool hit(const ray& r, interval ray_t, hit_record& rec) const {
            vec3 qc = center - r.origin();
            const vec3 d = r.direction();
            double a = dot(d, d);
            double b = dot(-2*d,qc);
            double c = dot(qc,qc)-radius*radius;
            double delta = b*b-4*a*c;
            
            if (delta < 0.0) { // No intersection
                return false;
            }

            double root = (-b - std::sqrt(delta)) / (2.0 * a);
            if (root<ray_t.min || ray_t.max<root){ //If the root is out of range
                root = (-b + std::sqrt(delta)) / (2.0 * a); //We consider the other root
                if (root<ray_t.min || ray_t.max<root){
                    return false;
                }
            }

            rec.t =  root; // smallest solution
            rec.p = r.at(rec.t);
            vec3 outward_normal = unit_vector(rec.p - center);
            rec.set_face_normal(r,outward_normal);
            return true;
        };

    private:
        point3 center;
        double radius;
};

#endif