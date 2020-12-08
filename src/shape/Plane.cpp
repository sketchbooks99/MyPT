#include "Plane.h"

bool Plane::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    auto t = -r.origin().y / r.direction().y;
    if(t < t_min || t > t_max) 
        return false;
    
    double x = r.origin().x + t * r.direction().x;
    double z = r.origin().z + t * r.direction().z;
    if(x < min[0] || x > max[0] || z < min[1] || z > max[1]) 
        return false;

    // Store ray information at intesection point
    rec.u = (x-min[0]) / (max[0]-min[0]);
    rec.v = (z-min[1]) / (max[1]-min[1]);
    rec.t = t;
    vec3 outward_normal(0, 1, 0);
    rec.set_face_normal(r, outward_normal);
    double eps = 1e-6f;
    rec.p = r.at(t) + eps * rec.normal;

    return true;
}

AABB Plane::bounding() const {
    double eps = 1e-6f;
    vec3 _min(min[0], -eps, min[1]);
    vec3 _max(max[0],  eps, max[1]);

    return AABB(_min, _max);
}

std::shared_ptr<Shape> createPlaneShape(const vec2& min, const vec2& max)
{
    return std::make_shared<Plane>(min, max);
}