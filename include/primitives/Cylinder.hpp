/*
** EPITECH PROJECT, 2026
** Cylinder
** File description:
** Cylinder
*/

#ifndef INCLUDED_CYLINDER_HPP
    #define INCLUDED_CYLINDER_HPP

#include "Color.hpp"
#include "IPrimitive.hpp"
#include "Math.hpp"

namespace RayTracer {
class Cylinder : public IPrimitive
{
    private:
        Math::Point3 _center;
        double _radius;
        double _height;
        Color _color;
        Math::Vector3 _rotation;

        HitRecord intersect_body(const Ray &ray, double tMin, double tMax) const;
        HitRecord intersect_cap(const Ray &ray, double tMin, double tMax, double cap_y) const;
        bool is_cap(const Math::Point3 &point) const;
        bool is_height(const Math::Point3 &point) const;
    public:
        Cylinder(const Math::Point3 &center, double radius, double height, const Color &color,
                 const Math::Vector3 &rotation = Math::Vector3(0, 0, 0))
            : _center(center), _radius(radius), _height(height), _color(color), _rotation(rotation) {};
        ~Cylinder() = default;
        HitRecord intersect(const Ray &ray, double tMin, double tMax) const override;
};
}

#endif
