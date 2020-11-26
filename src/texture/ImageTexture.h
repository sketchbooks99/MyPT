#pragma once

#include "../core/Texture.h"
#include "../core/Image.h"

/// TODO: 
///  - Treatment of UV (clamp, Loop, etc...) should be configured

class ImageTexture final : public Texture, public Image<RGB> {
public:
    ImageTexture() : Image<RGB>(0, 0){}
    ImageTexture(const std::string& filename) : Image<RGB>(filename) {}

    virtual vec3 value(double u, double v, const vec3& p) const override;
};

