#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

int x0_, y0_, x1_, y1_;
int shape = 1; // 1: line, 2: circle, 3: ellipse, 4: parabola, 5: hyperbola, 6: sin, 7: cos
int clickCount = 0;

void putPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// =============== Bresenham Line =================
void bresenhamLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        putPixel(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }
    }
}

// =============== Midpoint Circle ================
void midpointCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;
    while (x <= y) {
        putPixel(xc+x, yc+y);
        putPixel(xc-x, yc+y);
        putPixel(xc+x, yc-y);
        putPixel(xc-x, yc-y);
        putPixel(xc+y, yc+x);
        putPixel(xc-y, yc+x);
        putPixel(xc+y, yc-x);
        putPixel(xc-y, yc-x);
        x++;
        if (p < 0) p += 2*x + 1;
        else { y--; p += 2*(x-y)+1; }
    }
}

// =============== Midpoint Ellipse ===============
void midpointEllipse(int xc, int yc, int a, int b) {
    int x = 0, y = b;
    long a2 = a*a, b2 = b*b;
    long d = b2 - a2*b + a2/4;
    long dx = 2*b2*x, dy = 2*a2*y;

    while (dx < dy) {
        putPixel(xc+x, yc+y); putPixel(xc-x, yc+y);
        putPixel(xc+x, yc-y); putPixel(xc-x, yc-y);
        if (d < 0) { x++; dx += 2*b2; d += dx + b2; }
        else { x++; y--; dx += 2*b2; dy -= 2*a2; d += dx - dy + b2; }
    }

    d = b2*(x+0.5)*(x+0.5) + a2*(y-1)*(y-1) - a2*b2;
    while (y >= 0) {
        putPixel(xc+x, yc+y); putPixel(xc-x, yc+y);
        putPixel(xc+x, yc-y); putPixel(xc-x, yc-y);
        if (d > 0) { y--; dy -= 2*a2; d += a2 - dy; }
        else { y--; x++; dx += 2*b2; dy -= 2*a2; d += dx - dy + a2; }
    }
}

// =============== Parabola =======================
void drawParabola(int xc, int yc, int a) {
    int x = 0, y = 0;
    int xmax = 200;
    while (x <= xmax) {
        y = (x*x)/(4*a);
        putPixel(xc+x, yc+y);
        putPixel(xc-x, yc+y);
        x++;
    }
}

// =============== Hyperbola ======================
void drawHyperbola(int xc, int yc, int a, int b) {
    int x = a, y = 0;
    int xmax = 200;
    while (x <= xmax) {
        y = (int)(b*sqrt((x*x)/(double)(a*a) - 1));
        putPixel(xc+x, yc+y);
        putPixel(xc-x, yc+y);
        putPixel(xc+x, yc-y);
        putPixel(xc-x, yc-y);
        x++;
    }
}

// =============== Sin(x), Cos(x) =================
void drawSin(int xc, int yc) {
    for (int x = -200; x <= 200; x++) {
        int y = (int)(50 * sin(x * 0.05));
        putPixel(xc+x, yc+y);
    }
}
void drawCos(int xc, int yc) {
    for (int x = -200; x <= 200; x++) {
        int y = (int)(50 * cos(x * 0.05));
        putPixel(xc+x, yc+y);
    }
}

// =============== Mouse Click ====================
void mouseHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (clickCount == 0) {
            x0_ = x; y0_ = 480 - y;
            clickCount = 1;
        } else {
            x1_ = x; y1_ = 480 - y;
            int r, a, b;
            switch (shape) {
                case 1: bresenhamLine(x0_, y0_, x1_, y1_); break;
                case 2: r = (int)sqrt((x1_-x0_)*(x1_-x0_)+(y1_-y0_)*(y1_-y0_));
                        midpointCircle(x0_, y0_, r); break;
                case 3: a = abs(x1_-x0_); b = abs(y1_-y0_);
                        midpointEllipse(x0_, y0_, a, b); break;
                case 4: drawParabola(x0_, y0_, 30); break;
                case 5: drawHyperbola(x0_, y0_, 30, 20); break;
                case 6: drawSin(x0_, y0_); break;
                case 7: drawCos(x0_, y0_); break;
            }
            clickCount = 0;
        }
    }
}

// =============== Menu ===========================
void menuHandler(int option) {
    shape = option;
}

// =============== Display ========================
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab01 - Bresenham & Midpoint");

    gluOrtho2D(0, 640, 0, 480);

    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glPointSize(2);

    glutDisplayFunc(display);
    glutMouseFunc(mouseHandler);

    glutCreateMenu(menuHandler);
    glutAddMenuEntry("Line (Bresenham)", 1);
    glutAddMenuEntry("Circle (Midpoint)", 2);
    glutAddMenuEntry("Ellipse (Midpoint)", 3);
    glutAddMenuEntry("Parabola", 4);
    glutAddMenuEntry("Hyperbola", 5);
    glutAddMenuEntry("Sin(x)", 6);
    glutAddMenuEntry("Cos(x)", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
