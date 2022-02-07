#include<iostream>
#include<cmath>

using namespace std;

#define PI 3.14159

class GeometricFigure
{
    public:
    virtual double get_perimeter() = 0;
    virtual double get_square() = 0;  
    virtual void draw() = 0;  
    virtual void info() const = 0;
};

class Triangle: public GeometricFigure
{
    double size_a;
    double size_b;
    double size_c;
    // считаем что треугольник прямоугольный, тогда гипотенузу считаем по формуле гипотенузы
    public:
    double get_size_a() const { return size_a; }
    double get_size_b() const { return size_b; }
    double get_size_c() const { return size_c; }

    void set_size_a(double size_a)
    {
        if (size_a == 0) this->size_a = 1;
        else this->size_a = size_a;
    }
    void set_size_b(double size_b)
    {
        if (size_b == 0) this->size_b = 1;
        else this->size_b = size_b;
    }
    void set_size_c(double size_c)
    {
        if (size_c == 0) this->size_c = 1;
        else this->size_c = size_c;
    }
    
    Triangle(double size_a, double size_b) :size_a(size_a), size_b(size_b), size_c(sqrt(size_a*size_a + size_b*size_b)) 
    {
        cout << "TriangleConstructor:\t" << this << endl;
    }
    ~Triangle()
    {
        cout << "TriangleDestructor:\t" << this << endl;
    }
    double get_perimeter() 
    {
        return size_a + size_b + size_c;
    }
    double get_square() 
    {
        return (size_a * size_b)/2;
    }
    void draw()
    {
        cout << "Drawing a Triangle:" << endl;
        cout << "  perimeter: " << get_perimeter() << endl;
        cout << "  square:    " << get_square() << endl;
    }
    void info() const
    {
        cout << "Dimension of triangle:" << endl;
        cout << "  size a: " << get_size_a() << endl;
        cout << "  size b: " << get_size_b() << endl;
        cout << "  size c: " << get_size_c()<< endl;
    }

};

class Circle: public GeometricFigure
{
    double radius;
    public:
    double get_radius() const { return radius; }

    void set_radius(double radius)
    {
        if (radius == 0) this->radius = 1;
        else this->radius = radius;
    } 

    Circle(double radius): radius(radius)
    {
        cout << "CircleConstructor:\t" << this << endl;
    }
    ~Circle()
    {
        cout << "CircleDestructor:\t" << this << endl;
    }
    double get_perimeter() 
    {
        return 2 * PI * radius;
    }
    double get_square() 
    {
        return PI * (radius *radius);
    }
    void draw()
    {
        cout << "Drawing a Circle" << endl;
        cout << "  perimeter: " << get_perimeter() << endl;
        cout << "  square:    " << get_square() << endl;
    }
    void info() const
    {
        cout << "Dimension of circle:" << endl;
        cout << "  size radius: " << get_radius() << endl;
    }
};

class Rectangle: public GeometricFigure
{
    double size_a;
    double size_b;
    public:

    double get_size_a() const { return size_a; }
    double get_size_b() const { return size_b; }

    void set_size_a(double size_a) 
    { 
        if (size_a == 0) this->size_a = 1; 
        else this->size_a = size_a;
    }
    void set_size_b(double size_b)
    {
        if (size_b == 0) this->size_b = 1;
        else this->size_b = size_b;
    }

    Rectangle(double size_a, double size_b)
    {
        set_size_a(size_a);
        set_size_b(size_b);
        cout << "RectangleConstructor:\t" << this << endl;
    }
    ~Rectangle()
    {
        cout << "RectangleDestructor:\t" << this << endl;
    }
    double get_perimeter() 
    {
        return 2 * (size_a + size_b);
    }
    double get_square() 
    {
        return size_a * size_b;
    }
    virtual void draw()
    {
        cout << "Drawing a Rectangle" << endl;
        cout << "  perimeter: " << get_perimeter() << endl;
        cout << "  square:    " << get_square() << endl;
    }
    void info() const
    {
        cout << "Dimension of rectangle:" << endl;
        cout << "  size a: " << get_size_a() << endl;
        cout << "  size b: " << get_size_b() << endl;
    }
};

class Square: public Rectangle
{
    double size;
    public:

    double get_size() const { return size; }

    void get_size(double size)
    {
        if (size == 0) this->size = 1;
        else this->size = size;
    }

    Square(double size):Rectangle(size, size)
    {
        cout << "SquareConstructor:\t" << this << endl;
    }
    ~Square()
    {
        cout << "SquareDestructor:\t" << this << endl;
    }
    double get_perimeter() 
    {
        return Rectangle::get_perimeter();
    }
    double get_square() 
    {
        return Rectangle::get_square();
    }
    void draw()
    {
        cout << "Drawing a Square" << endl;
        cout << "  perimeter: " << get_perimeter() << endl;
        cout << "  square:    " << get_square() << endl;
    }
    void info() const
    {
        cout << "Dimension of square:" << endl;
        cout << "  size a: " << get_size() << endl;
    }
};


int main()
{

    setlocale(LC_ALL, "");



    Triangle triangle(rand() % 10, rand() % 10);
    triangle.draw();
    triangle.info();


    Square square(rand() % 100);
    square.draw();
    square.info();

    Rectangle rectangle(rand() % 10, rand() % 20);
    rectangle.draw();
    rectangle.info();

    Circle circle(rand() % 100);
    circle.draw();
    circle.info();

    return 0;
}
