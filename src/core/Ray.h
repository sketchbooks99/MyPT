#pragma once

#include "MathUtil.h"

namespace mypt {

class Ray {
public:
    Ray() {}
    Ray(const vec3& origin, const vec3& direction, double time = 0.0)
    : orig(origin), dir(direction), tm(time)
    {}
    
    vec3 origin() const     { return orig; }
    vec3 direction() const  { return dir; }
    double time() const     { return tm; }
    
    vec3 at(double t) const {
        return orig + t * dir;
    }
    
private:
    vec3 orig;
    vec3 dir;
    double tm;
};

}

