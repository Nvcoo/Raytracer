/*
** EPITECH PROJECT, 2026
** Cone
** File description:
** Cone
*/

#include "../include/primitives/Cone.hpp"
#include "../include/HitRecord.hpp"
#include "../include/Math.hpp"
#include <cmath>
#include <cstdlib>
#include <limits>

namespace RayTracer {
// A cone is similar to a cylinder, except it narrows to a point at the top.
// That point is called Apex.
//
// It has 2 parts:
//      - 1 Body
//      - 1 Base cap
//
// BODY:
//  The cone equation is: x² + z² = (r/h)² * (y - apex)²
//  Where apex = center.y + height (the tip of the cone)
//  And (r/h) is the slope, how fast the cone widens going down.
//
//  Substitute ray into cone equation -> we get the typical ax² + bx + c = 0
//  Things to take into account:
//      dx = ray.origin.x - center.x
//      dy = ray.origin.y - apex
//      dz = ray.origin.z - center.z
//      slope = r/h
//      k = slope²
//  a = Dx² + Dz² - k * Dy²
//  b = 2*(dx*Dx + dz*Dz - k*dy*Dy)
//  c = dx² + dz² - k*dy²
//  After finding t, check Y is within [center.y, apex] (base to tip)
//
// BASE CAP:
//  The base cap is a plane at y = center.y
//  After finding t, check X and Z are within the circle radius.
//
// We keep the nearest valid hit across the body and base cap.

bool Cone::is_height(const Math::Point3 &point) const
{
    double apex = _center.y + _height;

    return point.y >= _center.y && point.y <= apex;
}

bool Cone::is_cap(const Math::Point3 &point) const
{
    double dx = point.x - _center.x;
    double dz = point.z - _center.z;

    return (dx * dx + dz * dz) <= (_radius * _radius);
}

HitRecord Cone::intersect_body(const Ray &ray, double tMin, double tMax) const
{
    double slope = _radius / _height;
    double apex = _center.y + _height;
    double ox = ray.origin.x - _center.x;
    double oy = ray.origin.y - apex;
    double oz = ray.origin.z - _center.z;
    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z - (slope * slope) * ray.direction.y * ray.direction.y;
    double b = 2 * (ox * ray.direction.x + oz * ray.direction.z - (slope * slope) * oy * ray.direction.y);
    double c = ox * ox + oz * oz - (slope * slope) * oy * oy;
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
            hit_point.x - _center.x,
            slope * std::sqrt((hit_point.x - _center.x) * (hit_point.x - _center.x) + (hit_point.z - _center.z) * (hit_point.z - _center.z)),
            hit_point.z - _center.z
        };
    normal = normal.normalized();
    return HitRecord(hit_point, normal, t, true, _color);
}

HitRecord Cone::intersect_cap(const Ray &ray, double tMin, double tMax, double cap_y) const
{
    const double eps = 1e-8;
    double t;

    if (std::abs(ray.direction.y) < eps)
        return HitRecord();
    t = (cap_y - ray.origin.y) / ray.direction.y;
    if (t <= tMin || t >= tMax)
        return HitRecord();
    Math::Point3 hit_point = ray.at(t);
    if (!is_cap(hit_point))
        return HitRecord();
    Math::Vector3 normal = {0, -1, 0};
    return HitRecord(hit_point, normal, t, true, _color);
}

HitRecord Cone::intersect(const Ray &ray, double tMin, double tMax) const
{
    // transform ray into object local space by applying the inverse rotation
    Math::Vector3 localO(ray.origin.x - _center.x, ray.origin.y - _center.y, ray.origin.z - _center.z);
    Math::Vector3 localD = ray.direction;
    localO.rotateZ(-_rotation.z).rotateY(-_rotation.y).rotateX(-_rotation.x);
    localD.rotateZ(-_rotation.z).rotateY(-_rotation.y).rotateX(-_rotation.x);
    const Ray localRay(
        Math::Point3(_center.x + localO.x, _center.y + localO.y, _center.z + localO.z),
        localD
    );

    double min_t = std::numeric_limits<double>::infinity();
    HitRecord body_hit = intersect_body(localRay, tMin, tMax);
    HitRecord base_hit = intersect_cap(localRay, tMin, tMax, _center.y);
    HitRecord nearest;

    if (body_hit.hit && body_hit.t < min_t) {
        nearest = body_hit;
        min_t = body_hit.t;
    }
    if (base_hit.hit && base_hit.t < min_t) {
        nearest = base_hit;
        min_t = base_hit.t;
    }
    if (!nearest.hit)
        return nearest;
    // rotate normal back to world space and correct hit point from original ray
    nearest.normal.rotateX(_rotation.x).rotateY(_rotation.y).rotateZ(_rotation.z);
    nearest.point = ray.at(nearest.t);
    return nearest;
}
}
