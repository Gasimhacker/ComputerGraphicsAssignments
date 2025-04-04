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


void draw_curves() 
{
    int i;
    GLfloat x, y, t, angle, increment = 0.125;

    glColor3f(0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat shifts[3][2] = {
        {0.0f, -0.5f},
        {0.6f, 0.0f},
        {-0.6f, 0.0f}
    };

    
    for (i = 0; i < 3; i++)
    {
        glBegin(GL_LINE_STRIP);
        for (t = 1.5; t >= 0; t -= increment)
        {
            angle = t * M_PI;
            x = 0.3f * cos(angle) + shifts[i][0];
            y = 0.3f * sin(angle) + shifts[i][1];
            glVertex2f(x, y);
        }
        glEnd();

        increment *= 2;
    }
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
    glutDisplayFunc(draw_curves);
    glutMainLoop();
    return 0;
}
