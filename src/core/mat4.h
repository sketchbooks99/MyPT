#pragma once

#include "vec3.h"
#include "vec4.h"

struct mat4 {
public:
    mat4();
    mat4(double m[4][4]);
    mat4(double e00, double e01, double e02, double e03,
         double e10, double e11, double e12, double e13,
         double e20, double e21, double e22, double e23,
         double e30, double e31, double e32, double e33);

    double mat[4][4];
};

inline mat4 operator*(const mat4& m1, const mat4& m2) {
    mat4 m;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            m.mat[i][j] = m1.mat[i][0]*m2.mat[0][j];
            m.mat[i][j] += m1.mat[i][1]*m2.mat[1][j];
            m.mat[i][j] += m1.mat[i][2]*m2.mat[2][j];
            m.mat[i][j] += m1.mat[i][3]*m2.mat[3][j];
        }
    }
    return m;
}

inline vec3 operator*(const mat4 m, const vec3 v) {
    double x = m.mat[0][0]*v.x + m.mat[0][1]*v.y + m.mat[0][2]*v.z + m.mat[0][3];
    double y = m.mat[1][0]*v.x + m.mat[1][1]*v.y + m.mat[1][2]*v.z + m.mat[1][3];
    double z = m.mat[2][0]*v.x + m.mat[2][1]*v.y + m.mat[2][2]*v.z + m.mat[2][3];
    double w = m.mat[3][0]*v.x + m.mat[3][1]*v.y + m.mat[3][2]*v.z + m.mat[3][3];
    ASSERT(w == 0, "This mat4 doesn't have proper value!\n");
    if(w == 1) {
        return vec3(x, y, z);
    } else {
        return vec3(x, y, z) / w;
    }
}

inline vec4 operator*(const mat4 m, const vec4 v) {
    double x = m.mat[0][0]*v.x + m.mat[0][1]*v.y + m.mat[0][2]*v.z + m.mat[0][3];
    double y = m.mat[1][0]*v.x + m.mat[1][1]*v.y + m.mat[1][2]*v.z + m.mat[1][3];
    double z = m.mat[2][0]*v.x + m.mat[2][1]*v.y + m.mat[2][2]*v.z + m.mat[2][3];
    double w = m.mat[3][0]*v.x + m.mat[3][1]*v.y + m.mat[3][2]*v.z + m.mat[3][3];
    ASSERT(w == 0, "This mat4 doesn't have proper value!\n");
    return vec4(x, y, z, w);
}

// Very complicated calculation ... :<
inline mat4 inverse(const mat4& m) {
    return mat4();
}

inline mat4 transpose(const mat4& m) {
    return mat4(
        m.mat[0][0], m.mat[1][0], m.mat[2][0], m.mat[3][0],
        m.mat[0][1], m.mat[1][1], m.mat[2][1], m.mat[3][1],
        m.mat[0][2], m.mat[1][2], m.mat[2][2], m.mat[3][2],
        m.mat[0][3], m.mat[1][3], m.mat[2][3], m.mat[3][3]
    );
}