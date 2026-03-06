#ifndef SOFTACADEMY_SHAPES_HPP
#define SOFTACADEMY_SHAPES_HPP

#include <cstddef>
#include <stdexcept>

namespace softacademy {

class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};

class Circle final : public Shape {
public:
    explicit Circle(double radius); v

    double radius() const noexcept;

    double area() const override;
    double perimeter() const override;

private:
    double m_radius;
};

class Rectangle final : public Shape {
public:
    Rectangle(double width, double height);

    double width() const noexcept;
    double height() const noexcept;

    double area() const override;
    double perimeter() const override;

private:
    double m_width;
    double m_height;
};

class Triangle final : public Shape {
public:
    Triangle(double a, double b, double c);

    double a() const noexcept;
    double b() const noexcept;
    double c() const noexcept;

    double area() const override;
    double perimeter() const override;

private:
    double m_a;
    double m_b;
    double m_c;

private:
    bool valid_triangle(double a, double b, double c) const noexcept;
};

} // namespace softacademy

#endif // SOFTACADEMY_SHAPES_HPP
