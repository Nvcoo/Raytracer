/*
** EPITECH PROJECT, 2026
** Sphere
** File description:
** Sphere
*/

#ifndef INCLUDED_SPHERE_HPP
    #define INCLUDED_SPHERE_HPP

#include "Color.hpp"
#include "IPrimitive.hpp"
#include "Math.hpp"

namespace RayTracer {
class Sphere : public IPrimitive
{
    private:
        Math::Point3D _center;
        double _radius;
        Color _color;
    public:
        Sphere(const Math::Point3D &center, double radius, const Color &color) : _center(center), _radius(radius), _color(color) {};
        ~Sphere() = default;
        HitRecord intersect(const Ray &ray, double tMin, double tMax) const override;
};
}

#endif
