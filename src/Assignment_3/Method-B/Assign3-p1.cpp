#include <GL/glut.h>

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);  // Set coordinate system
}

void drawArrow(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();

    // Draw arrowhead
    glBegin(GL_TRIANGLES);
        glVertex2f(x2 - 5, y2 - 2.15);
        glVertex2f(x2 + 10, y2 + 10);
        glVertex2f(x2 + 10, y2 - 10);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Original Rectangle
    glColor3f(0.3, 0.3, 0.3);  // Dark gray
    glRecti(50, 100, 200, 150);

    // Draw Translated Rectangle
    glPushMatrix();
    glTranslatef(-200.0, -50.0, 0);  // Move left and down
    glRecti(50, 100, 200, 150);
    glPopMatrix();

    // Draw Arrow
    glColor3f(0, 0, 0);  // Black color
    drawArrow(125, 125, -75, 75);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Translation Example");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
