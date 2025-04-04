#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


int half_w_width = 500, half_w_height = 500;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-half_w_width, half_w_width, -half_w_height, half_w_height);  // Set coordinate system
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

    int viewport[4], x, y;
    int winX1, winY1, width, height;

    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw coordinate system
    drawCordinateSystem();

    // Draw Original Rectangle
    glColor3f(0.3, 0.3, 0.3);  // Dark gray
    glRecti(50, 100, 200, 150);
    glFlush();
    glFinish();  // Ensure drawing is complete

    // Convert from world to window coordinates
    
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    // Map the rectangle coordinates to window coordinates
    winX1 = ((50 + half_w_width) * viewport[2]) / 1000;
    winY1 = ((100 + half_w_height) * viewport[3]) / 1000;
    width = ((200 - 50) * viewport[2]) / 1000;
    height = ((150 - 100) * viewport[3]) / 1000;

    // Draw rotated rectangle at (-150, 50)
    glRasterPos2i(-25, 100);
    // Perform the copy
    glReadBuffer(GL_FRONT);
    glDrawBuffer(GL_FRONT);

    glPixelZoom(-0.5, 1);

    glCopyPixels(winX1, winY1, width, height, GL_COLOR);
    
    // Draw the arrow
    glColor3f(0.0, 0.0, 0.0);  // Black arrow
    drawArrow();
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Scaling and reflecting a rectangle using OpenGL");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}