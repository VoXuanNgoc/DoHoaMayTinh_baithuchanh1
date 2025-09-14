#define FREEGLUT_STATIC
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>


float angle = 0.0f;

void initLighting() {
    GLfloat light_pos[] = {2.0f, 2.0f, 2.0f, 1.0f}; // vị trí nguồn sáng
    GLfloat light_amb[] = {0.2f, 0.2f, 0.2f, 1.0f}; // ánh sáng môi trường
    GLfloat light_dif[] = {0.8f, 0.8f, 0.8f, 1.0f}; // ánh sáng khuếch tán

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(3.0, 3.0, 3.0,   // mắt nhìn từ xa
              0.0, 0.0, 0.0,   // nhìn về tâm
              0.0, 1.0, 0.0);  // trục y là hướng lên

    glRotatef(angle, 1.0f, 1.0f, 0.0f);

    // Vẽ lập phương
    glBegin(GL_QUADS);

    // mặt trước (đỏ)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1, -1,  1);
    glVertex3f( 1, -1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f(-1,  1,  1);

    // mặt sau (xanh lá)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1,  1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f( 1, -1, -1);

    // mặt trên (xanh dương)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-1,  1, -1);
    glVertex3f(-1,  1,  1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1,  1, -1);

    // mặt dưới (vàng)
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-1, -1, -1);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1, -1,  1);
    glVertex3f(-1, -1,  1);

    // mặt phải (tím)
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f( 1, -1, -1);
    glVertex3f( 1,  1, -1);
    glVertex3f( 1,  1,  1);
    glVertex3f( 1, -1,  1);

    // mặt trái (xanh nhạt)
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1,  1);
    glVertex3f(-1,  1,  1);
    glVertex3f(-1,  1, -1);

    glEnd();

    glutSwapBuffers();
}

void timer(int value) {
    angle += 2.0f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Cube - OpenGL");

    initLighting();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.33, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
