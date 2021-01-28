#include "Dielectric.h"
#include "../core/bsdf.h"

namespace mypt {

bool Dielectric::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) {
    srec.is_specular = true;
    srec.pdf = 0;
    srec.attenuation = is_normal ? abs(rec.normal) : albedo;

    // Re-calculate ior and normal according to whether a ray comes into the sphere, or not.
    bool into = dot(r_in.direction(), rec.normal) < 0;
    float ni_over_nt = into ? 1.0 / ref_idx : ref_idx;
    auto outward_normal = into ? rec.normal : -rec.normal;
    
    float cosine = fmin(dot(-normalize(r_in.direction()), outward_normal), 1.0);
    float sine = sqrt(1.0 - cosine*cosine);

    bool cannot_refract = ni_over_nt * sine > 1.0;

    float reflect_prob = schlick(cosine, ref_idx);
    bool is_reflect = false;
    vec3 direction;

    // if(into) rec.p -= rec.normal * 0.01;
    // else     rec.p += rec.normal * 0.01;

    if(cannot_refract || reflect_prob > random_double()) {
        direction = reflect(r_in.direction(), outward_normal);
        srec.scattered = Ray(rec.p, direction, r_in.time(), r_in.color());
        is_reflect = true;
    }
    else {
        direction = refract(r_in.direction(), outward_normal, ni_over_nt);
        srec.scattered = Ray(rec.p, direction, r_in.time(), r_in.color());
    }

    /// MEMO: Normal of Triangle was not correct ...?
    #if 0
    std::cout << "into:" << into;
    std::cout << ",is_reflect:" << is_reflect;
    stream_intersection(r_in, rec, srec);
    #endif 
    
    return true;
}

}