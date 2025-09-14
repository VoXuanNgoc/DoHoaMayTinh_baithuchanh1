#include <GL/glut.h>
#include <math.h>

void drawStar(float x, float y, float R, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.01f); // Tâm sao nhô lên 1 chút
    int numPoints = 5;
    for (int i = 0; i <= numPoints * 2; i++) {
        float angle = i * M_PI / numPoints - M_PI / 2; // xoay sao cho thẳng đứng
        float radius = (i % 2 == 0) ? R : r;
        glVertex3f(x + radius * cos(angle), y + radius * sin(angle), 0.01f);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Vẽ hình chữ nhật đỏ (lá cờ)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-1.5f, -1.0f, 0.0f);
        glVertex3f( 1.5f, -1.0f, 0.0f);
        glVertex3f( 1.5f,  1.0f, 0.0f);
        glVertex3f(-1.5f,  1.0f, 0.0f);
    glEnd();

    // Vẽ ngôi sao vàng
    glColor3f(1.0f, 1.0f, 0.0f);
    drawStar(0.0f, 0.0f, 0.6f, 0.25f);

    glutSwapBuffers();
}

void init() {
    glClearColor(0.2, 0.2, 0.2, 1.0); // nền xámB
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 4.0,   // mắt nhìn từ z=4
              0.0, 0.0, 0.0,   // nhìn về gốc
              0.0, 1.0, 0.0);  // hướng "up"
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("🇻🇳 Vietnam Flag 3D - OpenGL");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
