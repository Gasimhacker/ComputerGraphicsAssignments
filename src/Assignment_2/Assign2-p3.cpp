#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

struct screenPt
{
    GLint x;
    GLint y;
};

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef enum { limacon = 1, cardioid, threeLeaf, fourLeaf, spiral } curveName;
GLfloat shifts[5] = {950.0, 600.0, 100.0, -300.0, -700.0};
GLsizei winWidth = 600, winHeight = 500; // Initial display window size.

// Colors for each curve
GLfloat curveColors[5][3] = {
    {1.0, 0.0, 0.0},  // Red for limacon
    {0.0, 1.0, 0.0},  // Green for cardioid
    {0.0, 0.0, 1.0},  // Blue for threeLeaf
    {1.0, 1.0, 0.0},  // Yellow for fourLeaf
    {1.0, 0.0, 1.0}   // Magenta for spiral
};

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 2000.0, 0.0, 2000.0);
}

void fillCurve (GLint curveNum)
{
    const GLdouble twoPi = 6.283185;
    const GLint a = 175, b = 60;
    GLfloat r, theta, dtheta = 1.0 / float (a);
    GLint x0 = 1000, y0 = 1000; // Set center position.
    std::vector<screenPt> points;
    
    // Add center point for polygon filling
    screenPt centerPt;
    centerPt.x = x0 - shifts[curveNum - 1];
    centerPt.y = y0;
    
    // Set curve color
    glColor3fv(curveColors[curveNum - 1]);
    
    // Start filling polygon
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(centerPt.x, centerPt.y);  // Center point
    
    // Calculate points around the curve
    theta = 0.0;
    while (theta <= twoPi)
    {
        switch (curveNum)
        {
            case limacon:
                r = a * cos(theta) + b; break;
            case cardioid:
                r = a * (1 + cos(theta)); break;
            case threeLeaf:
                r = a * cos(3 * theta); break;
            case fourLeaf:
                r = a * cos(2 * theta); break;
            case spiral:
                r = (a / 4.0) * theta; break;
            default: break;
        }
        
        GLint x = x0 + r * cos(theta) - shifts[curveNum - 1];
        GLint y = y0 + r * sin(theta);
        glVertex2i(x, y);
        
        theta += dtheta;
    }
    
    // Close the loop
    switch (curveNum)
    {
        case limacon:
            r = a * cos(0) + b; break;
        case cardioid:
            r = a * (1 + cos(0)); break;
        case threeLeaf:
            r = a * cos(0); break;
        case fourLeaf:
            r = a * cos(0); break;
        case spiral:
            r = 0; break;
        default: break;
    }
    
    GLint x = x0 + r * cos(0) - shifts[curveNum - 1];
    GLint y = y0 + r * sin(0);
    glVertex2i(x, y);
    
    glEnd();
    
    // Draw outline in black
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    
    theta = 0.0;
    while (theta <= twoPi)
    {
        switch (curveNum)
        {
            case limacon:
                r = a * cos(theta) + b; break;
            case cardioid:
                r = a * (1 + cos(theta)); break;
            case threeLeaf:
                r = a * cos(3 * theta); break;
            case fourLeaf:
                r = a * cos(2 * theta); break;
            case spiral:
                r = (a / 4.0) * theta; break;
            default: break;
        }
        
        GLint x = x0 + r * cos(theta) - shifts[curveNum - 1];
        GLint y = y0 + r * sin(theta);
        glVertex2i(x, y);
        
        theta += dtheta;
    }
    
    glEnd();
}

void displayFcn (void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
    
    // Draw each curve with a different color
    for (int i = 1; i <= 5; i++)
    {
        fillCurve(i);
    }
    
    glFlush();
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Filled Polar Curves");
    init();
    glutDisplayFunc(displayFcn);
    glutMainLoop();

    return 0;
}