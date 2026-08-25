/*
** EPITECH PROJECT, 2026
** Sphere
** File description:
** Sphere
*/

#include "../include/primitives/Sphere.hpp"
#include "../include/HitRecord.hpp"
#include "../include/Math.hpp"
#include <cmath>

namespace RayTracer {
// This not short, so to remember it I'll add stepz to it
//
// A ray is a line: P(t) = Origin + t * Direction
// We want to find 't' where the ray touches the sphere
//
// Substituting the ray into the sphere equation gives us:
// at² + bt + c = 0
//
// That is clearly a quadratic equation
// We solve it by using the discriminant:
// d = b² - 4ac
//
// If d < 0, it means the ray misses the sphere completely
// If d = 0, it means the ray has hit the sphere but there's only 1 possible 't' value
// If d > 0, it means the ray has hit the sphere and there's 2 possible 't' values
//
// If there's 2 possible 't' values, we will always select the smallest one

HitRecord Sphere::intersect(const Ray &ray, double tMin, double tMax) const
{
    Math::Vector3 oc = ray.origin - _center;
    double a = ray.direction.dot(ray.direction);
    double b = 2 * oc.dot(ray.direction);
    double c = oc.dot(oc) - (_radius * _radius);
    double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0)
        return HitRecord();

    double sqrt_discriminant = std::sqrt(discriminant);
    double t = (-b - sqrt_discriminant) / (2 * a);

    if (t < tMin || t > tMax) {
        t = (-b + sqrt_discriminant) / (2 * a);
        if (t < tMin || t > tMax)
            return HitRecord();
    }
    Math::Point3 hit_point = ray.at(t);
    Math::Vector3 normal = (hit_point - _center).normalized();
    return HitRecord(hit_point, normal, t, true, _color);
}
}
