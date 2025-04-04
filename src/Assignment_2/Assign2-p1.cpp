#include <GL/glut.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}


void draw_curve() 
{
    GLfloat x, y, angle, t;
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_POLYGON);
    for (t = 0.0; t < 2; t += (2/6.0))
    {
        angle = t * M_PI;
        x = 0.3f * cos(angle);
        y = 0.3f * sin(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-600)/2,
                       (glutGet(GLUT_SCREEN_HEIGHT)-600)/2);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Approximating Curves with Line Segments");
    init();
    glutDisplayFunc(draw_curve);
    glutMainLoop();
    return 0;
}
