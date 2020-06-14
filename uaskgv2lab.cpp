// uaskgv2lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glut.h>
#include <cmath>

// Colors
GLfloat WHITE[] = { 1, 1, 1 };
GLfloat RED[] = { 1, 0, 0 };
GLfloat GREEN[] = { 0, 1, 0 };
GLfloat MAGENTA[] = { 1, 0, 1 };

//Variable
double a = 7, b = 4, c = 5;
double direction = -1; double temp, temp2;
double r1 = 1, r2 = 1.5, r3 = 0.4;

class Camera {
    double theta;      
    double y;          
    double dTheta;     
    double dy;         
public:
    Camera() : theta(0), y(3), dTheta(0.04), dy(0.2) {}
    double getX() { return 10 * cos(theta); }
    double getY() { return y; }
    double getZ() { return 10 * sin(theta); }
    void moveRight() { theta += dTheta; }
    void moveLeft() { theta -= dTheta; }
    void moveUp() { y += dy; }
    void moveDown() { if (y > dy) y -= dy; }
};


void Ball(double r, double h, double x, double z) {
    glPushMatrix();
    glTranslated(x, h, z);
    glutSolidSphere(r, 30, 30);
    glPopMatrix();
}



Camera camera;


void init() {
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL); //mewarnai benda 

}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glColor3f(0, 1, 0);
    Ball(r1, 7, a, 1);
    glColor3f(0, 0, 1);
    Ball(r2, 6, b, 4);
    glColor3f(1, 1, 0);
    Ball(r3, 5, c, 7);
    glPopMatrix();

    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
        8, 0.0, 8,
        0.0, 1.0, 0.0);
    glFlush();
    glutSwapBuffers();
}


void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}


void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, v);
}


void special(int key, int, int) {
    switch (key) {
    case GLUT_KEY_LEFT: camera.moveLeft(); break;
    case GLUT_KEY_RIGHT: camera.moveRight(); break;
    case GLUT_KEY_UP: camera.moveUp(); break;
    case GLUT_KEY_DOWN: camera.moveDown(); break;
    }
    glutPostRedisplay();
}
void keyboard1(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':

    case 's':
        temp = a;
        a += direction * 0.05;
        if (a > temp) {
            a = temp; direction = -1;
        }
        else if (a < r1) {
            a = r1; direction = 1;
        }
        temp = b;
        b += direction * 0.05;
        if (b > temp) {
            b = temp; direction = -1;
        }
        else if (b < r2) {
            b = r2; direction = 1;
        }
        break;
    case 27:
        exit(0);
        break;
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bouncing Balls");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard1);
    glutSpecialFunc(special);
    glutTimerFunc(100, timer, 0);
    init();
    glutMainLoop();
}
