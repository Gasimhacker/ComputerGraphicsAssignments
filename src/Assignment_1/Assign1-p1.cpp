#include <GL/glut.h>
#include <cstdio>


void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
}


void draw_stars() 
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set color to black
    glLineWidth(2.0);

    // Define points for the star
    GLfloat points[5][2] = {
        {0.5, 0.5},
        {-0.4, -0.15},
        {0.0, 0.75},
        {0.4, -0.15},
        {-0.5, 0.5}
    };

    // Define the first 4 points for the star
    glBegin(GL_LINES);
        for (int i = 0; i < 4; i++)
        {
            glVertex2f(points[i][0] - 3, points[i][1]);
        }
    glEnd();

    // Draw an uncompleted star
    glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 5; i++)
        {
            glVertex2fv(points[i]);
        }
    glEnd();

    // Draw a completed star
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 5; i++)
        {
            glVertex2f(points[i][0] + 3, points[i][1]);
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
    glutCreateWindow("Drawing a star using OpenGL");
    init();
    glutDisplayFunc(draw_stars);
    glutMainLoop();
    return 0;
}
