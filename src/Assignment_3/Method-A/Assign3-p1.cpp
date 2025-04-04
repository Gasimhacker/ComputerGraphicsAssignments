#include <GL/glut.h>
#include <stdio.h>

int half_w_width = 500, half_w_height = 500;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-half_w_width, half_w_width, -half_w_height, half_w_height);  // Set coordinate system
}

void drawArrow(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();

    // Draw arrowhead
    glBegin(GL_TRIANGLES);
        glVertex2f(x2 - 10, y2);
        glVertex2f(x2, y2 + 7);  // Adjusted for better visibility
        glVertex2f(x2, y2 - 7);
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

    int viewport[4];
    int winX1, winY1, width, height;
    GLubyte pixels[150 * 50 * 3];
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
    
    // Set raster position for the translated rectangle
    glRasterPos2i(-150, 50);
    
    // Perform the copy
    glReadBuffer(GL_FRONT);
    glDrawBuffer(GL_FRONT);

    glCopyPixels(winX1, winY1, width, height, GL_COLOR);

    // Draw the arrow
    glColor3f(0.0, 0.0, 0.0);  // Black arrow
    drawArrow(125, 125, -75, 75);
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Translation Using glCopyPixels");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}