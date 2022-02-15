// для компилирования с mingw надо добавить ключ компиляции `-lgdi32`
#define _CRT_SEQURE_NO_WARNINGS
#define _USE_MATH_DIFINES
// Библиотеки для OpenGL
#include <GLFW/glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include<iostream>
#include<Windows.h>
#include<cmath>
using namespace std;

#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color 

int figurePosition = 0;
const float DEG2RAD = M_PI / 180;

typedef struct RGB
{
    float r;
    float g;
    float b;
};


namespace Geometry
{

    struct RGB colorConverter(int hexValue)
    {
        struct RGB rgbColor;
        rgbColor.b = ((hexValue >> 16) & 0xFF) / 255.0;
        rgbColor.g = ((hexValue >> 8) & 0xFF) / 255.0;
        rgbColor.r = ((hexValue) & 0xFF) / 255.0;

        return rgbColor;
    }

    enum Color
    {
        red = 0x000000FF,
        green = 0x0000FF00,
        blue = 0x00FF0000,
        yellow = 0x0000FFFF,

        console_red = 0xCC,
        console_green = 0xAA,
        console_blue = 0x99,
        console_yellow = 0xEE,
        console_default = 0x07
    };

    class Shape
    {
        protected:
        Color color;
        unsigned int start_x;
        unsigned int start_y;
        unsigned int line_width;
        public:
        Color get_color() const { return color; }
        unsigned int get_start_x() const { return start_x; }
        unsigned int get_start_y() const { return start_y; }
        unsigned int get_line_width() const { return line_width; }
        void set_start_x(unsigned int start_x)
        {
            if (start_x > 800) start_x = 800;
            this->start_x = start_x;
        }
        void set_start_y(unsigned int start_y)
        {
            if (start_y > 800) start_y = 800;
            this->start_y = start_y;
        }
        void set_line_width(unsigned int line_width)
        {
            if (line_width > 50) line_width = 50;
            this->line_width = line_width;
        }
        Shape(SHAPE_TAKE_PARAMETERS):color(color)
        {
            set_start_x(start_x);
            set_start_y(start_y);
            set_line_width(line_width);
        }
        virtual ~Shape() {}

        virtual double get_area() const = 0;
        virtual double get_perimeter() const = 0;
        virtual void draw() const = 0;
        virtual void drawOpenGL() const = 0;

        void info() const
        {
            cout << "Площадь фигуры: " << get_area() << endl;
            cout << "Периметр фигуры: " << get_perimeter() << endl;
            draw();
        }
    };

    class Square: public Shape
    {
        double side;
        public:
        double get_side() const { return this->side; }
        void set_side(double side)
        {
            if (side <= 0) side = 10;
            this->side = side;
        }
        Square(double side, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
        {
            set_side(side);
        }
        ~Square() {}

        double get_area() const
        {
            return side*side;
        }

        double get_perimeter() const
        {
            return side*4;
        }

        void draw() const // методе отрисовки через цикл.
        {
    //        char command[20] = "color ";
    //        char str[10]{};
    //        system(strcat(command, itoa(get_color(), str, 10)));
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, get_color());
            for (int i = 0; i < side; i++)
            {
                for (int i = 0; i < side; i++)
                {
                    cout << "* ";
                }
                cout << endl;
            }
            SetConsoleTextAttribute(hConsole, Color::console_default);
        }

        void drawOpenGL() const
        {

            glClear(GL_COLOR_BUFFER_BIT);
            RGB rgbColor = Geometry::colorConverter(get_color());
            glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);

            glBegin(GL_QUADS);
            glVertex2f(start_x-side/2, start_y + side/2);
            glVertex2f(start_x-side/2, start_y - side/2);
            glVertex2f(start_x+side/2, start_y - side/2);
            glVertex2f(start_x+side/2, start_y + side/2);
            glEnd();
        }

        void info() const
        {
            cout << typeid(*this).name() << endl;
            cout << "Длина стороны: " << side << endl;
            Shape::info();
        }
    };


    class Rectangle: public Shape
    {
        double width;
        double length;
        public:
        double get_width()const { return width; }
        double get_length()const { return length; }
        void set_width(double width)
        {
            if (width <= 0) width = 20;
            this->width = width;
        }
        void set_length(double length)
        {
            if (length <=0) length=10;
            this->length = length;
        }
        Rectangle(double width, double length, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
        {
            set_width(width);
            set_length(length);
        }
        ~Rectangle(){}
        double get_area()const
        {
            return width*length;
        }
        double get_perimeter()const
        {
            return 2 * (length + width);
        }
        void draw()const
        {
            HWND hwnd = GetConsoleWindow();
            HDC hdc = GetDC(hwnd);

            HPEN hPen = CreatePen(PS_SOLID, line_width, color);
            HBRUSH hBrush = CreateSolidBrush(color);

            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            ::Rectangle(hdc, start_x, start_x, start_x+width, start_y+length);

            DeleteObject(hBrush);
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc);
        }
        void drawOpenGL() const
        {

            glClear(GL_COLOR_BUFFER_BIT);
            RGB rgbColor = Geometry::colorConverter(get_color());
            glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);

            glBegin(GL_QUADS);
            glVertex2f(start_x-length/2, start_y + width/2);
            glVertex2f(start_x-length/2, start_y - width/2);
            glVertex2f(start_x+length/2, start_y - width/2);
            glVertex2f(start_x+length/2, start_y + width/2);
            glEnd();
        }

        void info()const
        {
            cout << typeid(*this).name() << endl;
            cout << "Ширина прямоугольника: " << width << endl;
            cout << "Длина прямоугольника: " << length << endl;
            Shape::info();
        }
    };

    class Circle: public Shape
    {
        double radius;
        public:
        double get_radius()const { return radius; }
        void set_radius(double radius)
        {
            if (radius <= 0 || radius > 500) radius = 500;
            this->radius = radius;
        }
        Circle(double radius, SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS)
        {
            set_radius(radius);
        }
        ~Circle(){}
        double get_area()const
        {
            return M_PI * pow(radius,2); 
        }
        double get_perimeter() const
        {
            return 2 * M_PI * radius;
        }
        double get_diameter()const
        {
            return radius * 2;
        }

        void draw() const
        {
            HWND hwnd = GetConsoleWindow();
            HDC hdc = GetDC(hwnd);

            HPEN hPen = CreatePen(PS_SOLID, line_width, color);
            HBRUSH hBrush = CreateSolidBrush(color);

            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

            DeleteObject(hPen);
            DeleteObject(hBrush);

            ReleaseDC(hwnd, hdc);
        }
        void drawOpenGL() const
        {

            glClear(GL_COLOR_BUFFER_BIT);
            RGB rgbColor = Geometry::colorConverter(get_color());
            glColor3f(rgbColor.r, rgbColor.g, rgbColor.b);

            glBegin(GL_POLYGON);
            for(int i = 0; i<360; i++)
            {
                float degInRad = i * DEG2RAD;
                glVertex2f(cos(degInRad)*radius, sin(degInRad)*radius);
            }
            glEnd();
        }
        void info() const
        {
            cout << typeid(*this).name() << endl;
            cout << "Радиус круга: " << get_radius() << endl;
            cout << "Диаметр круга: " << get_diameter() << endl;
            Shape::info();

        }
    };
    class Triangle:public Shape
    {
        public:
        Triangle(SHAPE_TAKE_PARAMETERS):Shape(SHAPE_GIVE_PARAMETERS) {}
        ~Triangle(){}

        virtual double get_height() const = 0;
    };

    class EquilateralTriangle:public Triangle
    {
        double side;
        public:
        EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS):Triangle(SHAPE_GIVE_PARAMETERS)
        {
            set_side(side);
        }
        ~EquilateralTriangle() {}
        void set_side(double side)
        {
            if (side < 20) side = 20;
            if (side > 500) side = 500;
            this->side = side;
        }
        double get_side() const { return side; }
        double get_height() const { return side * cos(30*M_PI/180); }
        double get_area() const { return get_height() * side / 4; }
        double get_perimeter() const { return side * 3; }
        void draw() const
        {
            HWND hwnd = GetConsoleWindow();
            HDC hdc = GetDC(hwnd);

            HPEN hPen = CreatePen(PS_SOLID, line_width, color);
            HBRUSH hBrush = CreateSolidBrush(color);

            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            POINT points[] = 
            {
                {start_x, start_y+side},
                {start_x + side, start_y + side},
                {start_x + side/2, start_y + side - get_height()}
            
            };

            Polygon(hdc, points, sizeof(points)/sizeof(POINT));

            DeleteObject(hBrush);
            DeleteObject(hPen);
            ReleaseDC(hwnd, hdc);
        }
        void info() const
        {
            cout << typeid(*this).name() << endl;
            cout << "Длина стороны: " << get_side() << endl;
            cout << "Высота: " << get_height() << endl;
            Shape::info();
        }
    };
    class IsoscalesTriangle: public Triangle
    {
        double base;
        double base_angle;
        public:
        IsoscalesTriangle(double base, double base_angle, SHAPE_TAKE_PARAMETERS):Triangle(SHAPE_GIVE_PARAMETERS)
        {
            set_base(base);
            set_angle(base_angle);
        }
        ~IsoscalesTriangle() {}
        void set_base(double base)
        {
            if (base < 20) base = 20;
            if (base > 200) base = 200;
            this->base = base;
        }
        void set_angle(double angle)
        {
            this->base_angle = angle;
        }
        double get_base() const { return base; }
        double get_side() const { return get_height() / sin(base_angle * M_PI / 180); }
        double get_base_angle() const { return base_angle; }
        double get_height() const { return base /2 * tan(base_angle * M_PI / 180); }
        double get_area() const { return base/2 * get_height(); }
        double get_perimeter() const { return get_side() * 2 + base; }
        void draw() const
        {
            HWND hwnd = GetConsoleWindow();
            HDC hdc = GetDC(hwnd);

            HPEN hPen = CreatePen(PS_SOLID, line_width, color);
            HBRUSH hBrush = CreateSolidBrush(color);
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            POINT points[] = 
            {
                {start_x, start_y + get_side()},
                {start_x + base, start_y + get_side()},
                {start_x+base/2, start_y+get_side() - get_height()}
            };
            Polygon(hdc, points, sizeof(points)/sizeof(POINT));

            DeleteObject(hBrush);
            DeleteObject(hPen);

            ReleaseDC(hwnd, hdc);
        }
        void info() const
        {
            cout << typeid(*this).name() << endl;
            cout << "Основание треугольника: " << get_base() << endl;
            cout << "Сторона треугольника: " << get_side() << endl;
            cout << "Угол между основанием и стороной: " << get_base_angle() << endl;
            cout << "Высота треугольника: " << get_height() << endl;
            Shape::info();
        }
   };
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    if (key == GLFW_KEY_ESCAPE && mods == 0)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_SPACE && mods == 0) 
        if (figurePosition == 2) figurePosition = 0;
        else figurePosition++; 
}

int main()
{
    setlocale(LC_ALL,"");

    if(!glfwInit())
    {
        cout << "Не получилось инициализировать GLFW" << endl;
        exit(EXIT_FAILURE);
    }

    

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(600, 600, "Abstract geometry", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        cout << "Не удалось инициализировать окно GLFW" << endl;
        exit(EXIT_FAILURE);
    }
  
    glfwSetKeyCallback(window, key_callback); 
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    Geometry::Shape* figures[] =
    {
        new Geometry::Square(0.4, 0, 0, 1, Geometry::Color::red),
        new Geometry::Rectangle(0.5, 0.2, 0.1, 0.1, 1, Geometry::Color::blue),
        new Geometry::Circle(0.2, 0, 0, 1, Geometry::Color::yellow)
    };

    const char *winTitle[] = 
    {
        "Square",
        "Rectangle",
        "Circle"
    };

    while(!glfwWindowShouldClose(window))
    {
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        figures[figurePosition]->drawOpenGL();

        glfwSetWindowTitle(window, winTitle[figurePosition]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (int i = 0; i < sizeof(figures)/sizeof(Geometry::Shape); i++)
    {
        delete figures[i];
    }
    delete[] figures;

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

}
