#pragma once 

#include "../core/Shape.h"

class Plane final : public Shape {
public:
    enum class PlaneAxis { XY, YZ, XZ };
    Plane() {}
    Plane(vec2 min, vec2 max, PlaneAxis axis)
    : min(min), max(max), axis(axis) {}

    virtual bool intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
    virtual AABB bounding() const override;
private:
    vec2 min, max;  
    double k;       // Constant value of plane axis
    PlaneAxis axis;
};

bool Plane::intersect(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // XY: 0, YZ: 1, XZ: 2
    int const_axis = (static_cast<int>(axis) + 2) % 3; // Axis index of plane
    auto t = (k - r.origin()[const_axis]) / r.direction()[const_axis];
    if(t < t_min || t > t_max)
        return false;
    
    int a_axis = axis == PlaneAxis::XZ ? (const_axis + 2) % 3 : (const_axis + 1) % 3;
    int b_axis = axis == PlaneAxis::XZ ? (const_axis + 1) % 3 : (const_axis + 2) % 3;
    auto a = r.origin()[a_axis] + t * r.direction()[a_axis];
    auto b = r.origin()[b_axis] + t * r.direction()[b_axis];
    if(a < min[a_axis] || a > max[a_axis] || b < min[b_axis] || b > max[b_axis])
        return false;

    // Store ray information at intesection point
    rec.u = (a-min[0]) / (max[0]-min[0]);
    rec.v = (b-min[1]) / (max[1]-min[1]);
    rec.t = t;
    vec3 outward_normal;
    outward_normal[const_axis] = 1.0;
    rec.set_face_normal(r, outward_normal);
    rec.p = r.at(t);
    return true;
}

AABB Plane::bounding() const {
    int const_axis = (static_cast<int>(axis) + 2) % 3;
    int a_axis = axis == PlaneAxis::XZ ? (const_axis + 2) % 3 : (const_axis + 1) % 3;
    int b_axis = axis == PlaneAxis::XZ ? (const_axis + 1) % 3 : (const_axis + 2) % 3;

    vec3 _min, _max;
    double eps = 1e-5f;
    _min[const_axis] = k - eps;
    _min[a_axis] = min[0];
    _min[b_axis] = min[1];

    _max[const_axis] = k + eps;
    _max[a_axis] = max[0];
    _max[b_axis] = max[1];

    return AABB(_min, _max);
}
