#include "Dielectric.h"
#include "../core/bsdf.h"

namespace mypt {

#if 1
bool Dielectric::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) const  {
    srec.is_specular = true;
    srec.pdf = 0;
    srec.attenuation = albedo;
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    vec3 refracted;
    float ni_over_nt;
    float cosine;
    bool into = dot(r_in.direction(), rec.normal) < 0;
    if(!into) {
        std::cout << "from in to out" << std::endl;
        outward_normal = rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    } else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    
    float reflect_prob;
    if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) 
        reflect_prob = schlick(cosine, ref_idx);
    else 
        reflect_prob = 1.0;
    
    vec3 direction;
    bool is_reflect;
    if(random_double() < reflect_prob) {
        srec.specular_ray = Ray(rec.p, reflected);
        is_reflect = true;
        direction = reflected;
    } else {
        srec.specular_ray = Ray(rec.p, refracted);
        is_reflect = false;
        direction = refracted;
    }

    std::cout << "into:" << into << ",";
    std::cout << "p:" << rec.p << ","; 
    std::cout << "in:" << r_in.direction() << ",";
    std::cout << "dir:" << direction << ",";
    std::cout << "normal:" << rec.normal << ",";
    std::cout << "is_reflect:" << is_reflect << std::endl;
    
    return true;
} 
#else
bool Dielectric::scatter(
    const Ray& r_in, HitRecord& rec, ScatterRecord& srec
) const  {
    srec.is_specular = true;
    srec.pdf = 0;
    srec.attenuation = albedo;
    bool into = dot(r_in.direction(), rec.normal) < 0;
    float ni_over_nt = into ? 1.0 / ref_idx : ref_idx;
    auto outward_normal = into ? rec.normal : -rec.normal;
    
    float cosine = dot(-r_in.direction(), outward_normal);
    float sine = sqrt(1.0 - cosine*cosine);

    bool cannot_refract = ni_over_nt * sine > 1.0;

    float reflect_prob = schlick(cosine, ni_over_nt);
    if(cannot_refract || reflect_prob > random_double())
        srec.specular_ray = Ray(rec.p, reflect(r_in.direction(), rec.normal));
    else
        srec.specular_ray = Ray(rec.p, refract(r_in.direction(), outward_normal, ni_over_nt));
    return true;
}
#endif


}