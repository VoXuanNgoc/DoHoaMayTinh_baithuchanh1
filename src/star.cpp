#include <GL/glut.h>
#include <math.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Vẽ ngôi sao vàng
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // tâm

    int numPoints = 5;
    float R = 0.8f;  // bán kính ngoài
    float r = 0.3f;  // bán kính trong

    for (int i = 0; i <= numPoints * 2; i++) {
        float angle = i * M_PI / numPoints;
        float radius = (i % 2 == 0) ? R : r;
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }

    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("⭐ Ngôi sao 2D - OpenGL");
    glClearColor(0.0, 0.0, 0.0, 1.0); // nền đen
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
