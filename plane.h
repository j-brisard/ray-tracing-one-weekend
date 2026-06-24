#ifndef PLANE_H
#define PLANE_H

#include "hittable.h"

class plane: public hittable {
  public:
    plane(const point3& point, const vec3& normal) : point(point), normal(normal) {}

   bool hit(const ray& r, interval ray_t, hit_record& rec) const override {

        /*
        If the ray is perpendicular to the plane, we return no hit
        */
        if (std::abs(dot(r.direction(),normal)) < 1e-8) { // ==0 but 1e-8 to avoid floating point errors
          return false;
        }
        
        double root = (dot(point - r.origin(), normal))/dot(r.direction(),normal);
        if (!ray_t.surrounds(root)) { // Utilise ray_t.contains(root) selon l'implémentation de ta classe interval
        return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.set_face_normal(r, unit_vector(normal));

        return true;
    }

  private:
    point3 point;
    vec3 normal;
};

#endif