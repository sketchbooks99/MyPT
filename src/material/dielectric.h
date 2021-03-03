#pragma once

#include "../core/material.h"

namespace mypt {

struct HitRecord;

inline Float schlick(Float cosine, Float ior) {
    auto r0 = (1-ior) / (1+ior);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}

class Dielectric final : public Material {
public:
    explicit Dielectric(Float ri) : albedo(vec3(1.0f)), ior(ri) {}
    explicit Dielectric(vec3 a, Float ri) : albedo(a), ior(ri) {}

    bool scatter(const Ray& r_in, SurfaceInteraction& si) const override;
    Float scattering_pdf(const Ray& /* r_in */, const SurfaceInteraction& /* si */) const override
    {
        return 1.0f;
    }

    std::string to_string() const override {
        std::ostringstream oss;
        oss << "Dielectric : {" << std::endl;
        oss << "\tAlbedo : " << albedo << "," <<  std::endl;
        oss << "\tIndex of Refraction : " << ior << std::endl;
        oss << "}";
        return oss.str();
    }

    MatType type() const override { return MatType::Dielectric; }

private:
    vec3 albedo;
    Float ior;
};

}