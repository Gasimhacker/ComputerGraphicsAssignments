#include <GL/glut.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);  // Set coordinate system
}

void drawRectangle(float x, float y) {
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 150, y);
        glVertex2f(x + 150, y + 50);
        glVertex2f(x, y + 50);
    glEnd();
}

void drawArrow() {
    float x, y, angle, t;
    // Draw the arc arrow
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (t = 2.0; t >= 1.0; t -= 0.1) {
        angle = t * M_PI;  // 0 to 180 degrees
        x = 50 * cos(angle);
        y = 50 * sin(angle) + 90;
        glVertex2f(x, y);
    }
    glEnd();
    
    // Draw arrowhead at the end of the arc
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 8, y);
        glVertex2f(x + 8, y);
        glVertex2f(x, y + 8);
    glEnd();
}

void drawCordinateSystem() {
    // Draw coordinate system
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(-200, 0);
        glVertex2f(200, 0);
        glVertex2f(0, -50);
        glVertex2f(0, 250);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw coordinate system
    drawCordinateSystem();

    // Draw Original Rectangle
    glColor3f(0.3, 0.3, 0.3);  // Dark gray
    glRecti(50, 100, 200, 150);
    glFlush();
    glFinish();  // Ensure drawing is complete


    // Draw Translated Rectangle
    glPushMatrix();
    glScalef(-0.5, 1.0, 1.0);  // Scale by -0.5 in x-axis
    glRecti(50, 100, 200, 150);
    glPopMatrix();

    // Draw Arrow
    glColor3f(0, 0, 0);  // Black color
    drawArrow();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scaling Example");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
