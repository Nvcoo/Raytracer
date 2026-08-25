/*
** EPITECH PROJECT, 2026
** Cylinder
** File description:
** Cylinder
*/


#include "../include/primitives/Cylinder.hpp"
#include "../include/HitRecord.hpp"
#include "../include/Math.hpp"
#include <cmath>
#include <cstdlib>
#include <limits>

namespace RayTracer {
// A cylinder is a circle extended along the Y axis.
//
// It has 3 parts:
//      - 1 Body
//      - 2 Flat circular caps
//
// BODY:
//  Substitute ray into x² + z² = R² -> we will get the typical ax² + bx + c = 0
//  The final thing would be (Dx² + Dz²)*t² + (2*Ox*Dx + 2*Oz*Dz)*t + (Ox² + Oz² - R²) = 0
//  a = Dx² + Dz²
//  b = 2*((Ox-Cx)*Dx + (Oz-Cz)*Dz)
//  c = (Ox-Cx)² + (Oz-Cz)² - R²
//  After finding t, check Y is within [center.y - h/2, center.y + h/2]
//
// CAPS:
//  Each cap is a plane at y = center.y +- height/2
//  After finding t, check X and Z are within the circle radius
//
// We keep the nearest valid hit across the body and both caps, just like in any other shape.

bool Cylinder::is_height(const Math::Point3 &point) const
{
    double half_cylinder = _height / 2;

    return point.y >= (_center.y - half_cylinder) && point.y <= (_center.y + half_cylinder);
}

bool Cylinder::is_cap(const Math::Point3 &point) const
{
    double dx = point.x - _center.x;
    double dz = point.z - _center.z;

    return (dx * dx + dz * dz) <= (_radius * _radius);
}

HitRecord Cylinder::intersect_body(const Ray &ray, double tMin, double tMax) const
{
    double ox = ray.origin.x - _center.x;
    double oz = ray.origin.z - _center.z;
    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    double b = 2 * (ox * ray.direction.x + oz * ray.direction.z);
    double c = ox * ox + oz * oz - (_radius * _radius);
    double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0)
        return HitRecord();

    double sqrt_discriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2 * a);
    double t2 = (-b + sqrt_discriminant) / (2 * a);
    double t;

    if (t1 >= tMin && t1 <= tMax && is_height(ray.at(t1)))
        t = t1;
    else if (t2 >= tMin && t2 <= tMax && is_height(ray.at(t2)))
        t = t2;
    else
        return HitRecord();
    Math::Point3 hit_point = ray.at(t);
    Math::Vector3 normal =
        {
            (hit_point.x - _center.x) / _radius,
            0,
            (hit_point.z - _center.z) / _radius
        };
    return HitRecord(hit_point, normal, t, true, _color);
}

HitRecord Cylinder::intersect_cap(const Ray &ray, double tMin, double tMax, double cap_y) const
{
    const double eps = 1e-8;
    double t;

    if (std::abs(ray.direction.y) < eps)
        return HitRecord();
    t = (cap_y - ray.origin.y) / ray.direction.y;
    if (t < tMin || t > tMax)
        return HitRecord();
    Math::Point3 hit_point = ray.at(t);
    if (!is_cap(hit_point))
        return HitRecord();
    Math::Vector3 normal;
    if (cap_y > _center.y)
        normal = {0, 1, 0};
    else
        normal = {0, -1, 0};
    return HitRecord(hit_point, normal, t, true, _color);
}

HitRecord Cylinder::intersect(const Ray &ray, double tMin, double tMax) const
{
    // transform ray into object local space by applying the inverse rotation
    // (inverse of X->Y->Z order is -Z, -Y, -X applied to the offset origin and direction)
    Math::Vector3 localO(ray.origin.x - _center.x, ray.origin.y - _center.y, ray.origin.z - _center.z);
    Math::Vector3 localD = ray.direction;
    localO.rotateZ(-_rotation.z).rotateY(-_rotation.y).rotateX(-_rotation.x);
    localD.rotateZ(-_rotation.z).rotateY(-_rotation.y).rotateX(-_rotation.x);
    const Ray localRay(
        Math::Point3(_center.x + localO.x, _center.y + localO.y, _center.z + localO.z),
        localD
    );

    const double middle = _height / 2;
    double min_t = std::numeric_limits<double>::infinity();
    HitRecord body_hit   = intersect_body(localRay, tMin, tMax);
    HitRecord top_hit    = intersect_cap(localRay, tMin, tMax, _center.y + middle);
    HitRecord bottom_hit = intersect_cap(localRay, tMin, tMax, _center.y - middle);
    HitRecord nearest;

    if (body_hit.hit && body_hit.t < min_t) {
        nearest = body_hit;
        min_t = body_hit.t;
    }
    if (top_hit.hit && top_hit.t < min_t) {
        nearest = top_hit;
        min_t = top_hit.t;
    }
    if (bottom_hit.hit && bottom_hit.t < min_t) {
        nearest = bottom_hit;
        min_t = bottom_hit.t;
    }
    if (!nearest.hit)
        return nearest;
    // rotate normal back to world space and correct hit point from original ray
    nearest.normal.rotateX(_rotation.x).rotateY(_rotation.y).rotateZ(_rotation.z);
    nearest.point = ray.at(nearest.t);
    return nearest;
}
}
