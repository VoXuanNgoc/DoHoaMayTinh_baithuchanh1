#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

struct Point {
    float x, y;
};

vector<Point> triangle = { {100,100}, {200,100}, {150,200} };
vector<Point> transformed;

// ====== Các hàm biến đổi ======
Point translate(Point p, float tx, float ty) {
    return { p.x + tx, p.y + ty };
}

Point scale(Point p, float sx, float sy, float x0, float y0) {
    return { x0 + (p.x - x0) * sx,
             y0 + (p.y - y0) * sy };
}

Point rotate(Point p, float theta, float x0, float y0) {
    float rad = theta * M_PI / 180.0;
    float x = p.x - x0;
    float y = p.y - y0;
    return { x0 + x * cos(rad) - y * sin(rad),
             y0 + x * sin(rad) + y * cos(rad) };
}

// Công thức trực tiếp đối xứng qua đường y = ax + b
Point reflect(Point p, float a, float b) {
    float d = (p.x + (p.y - b) * a) / (1 + a*a);
    float x_ref = 2*d - p.x;
    float y_ref = 2*d*a - p.y + 2*b;
    return { x_ref, y_ref };
}

// ====== Vẽ ======
void drawPolygon(const vector<Point>& poly, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (auto p : poly) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Vẽ hình gốc màu xanh
    drawPolygon(triangle, 0, 0, 1);

    // Vẽ hình đã biến đổi màu đỏ
    if (!transformed.empty()) {
        drawPolygon(transformed, 1, 0, 0);
    }

    glFlush();
}

// ====== Menu ======
void menu(int option) {
    transformed.clear();
    switch(option) {
        case 1: // Tịnh tiến
            for (auto p : triangle) transformed.push_back(translate(p, 100, 50));
            break;
        case 2: // Tỉ lệ
            for (auto p : triangle) transformed.push_back(scale(p, 1.5, 1.5, 150, 150));
            break;
        case 3: // Quay
            for (auto p : triangle) transformed.push_back(rotate(p, 45, 150, 150));
            break;
        case 4: // Đối xứng qua y = x (a=1, b=0)
            for (auto p : triangle) transformed.push_back(reflect(p, 1, 0));
            break;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(1,1,1,1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 400);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("LAB 03 - Bien doi 2D");

    init();
    glutDisplayFunc(display);

    // Tạo menu chuột phải
    glutCreateMenu(menu);
    glutAddMenuEntry("Tinh tien", 1);
    glutAddMenuEntry("Ti le", 2);
    glutAddMenuEntry("Quay", 3);
    glutAddMenuEntry("Doi xung (y=x)", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
