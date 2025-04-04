#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>


const GLdouble twoPi = 6.283185;

class scrPt {
    public:
        GLint x, y;
};

GLsizei winWidth = 400, winHeight = 300; // Initial display window size.
GLsizei world_width = 400, world_height = 400; // World coordinates.


void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, world_width, 0.0, world_height);
}

void pieChart (void)
{
    scrPt circCtr, piePt;
    GLint radius = world_width / 2.5; // Circle radius.
    GLdouble sliceAngle, previousSliceAngle = 0.0;
    GLint k, nSlices = 12; // Number of slices.
    GLfloat dataValues[12] = {10.0, 7.0, 13.0, 5.0, 13.0, 14.0,
    3.0, 16.0, 5.0, 3.0, 17.0, 8.0};
    GLfloat dataSum = 0.0;
    // Vibrant & smooth color palette (pastel and saturated hues)
    GLfloat colors[12][3] = {
        {0.95f, 0.26f, 0.21f}, // Red
        {0.16f, 0.68f, 0.37f}, // Green
        {0.25f, 0.32f, 0.71f}, // Deep Blue
        {1.00f, 0.76f, 0.03f}, // Yellow
        {0.89f, 0.39f, 0.13f}, // Orange
        {0.56f, 0.27f, 0.68f}, // Purple
        {0.20f, 0.72f, 0.97f}, // Light Blue
        {0.76f, 0.60f, 0.42f}, // Brown
        {0.60f, 0.80f, 0.20f}, // Olive Green
        {1.00f, 0.41f, 0.71f}, // Pink
        {0.40f, 0.40f, 0.40f}, // Dark Gray
        {0.00f, 0.59f, 0.53f}  // Teal
    };
    circCtr.x = world_width / 2; // Circle center position.
    circCtr.y = world_height / 2;

    for (k = 0; k < nSlices; k++)
        dataSum += dataValues[k];

        for (k = 0; k < nSlices; k++)
        {
            glColor3fv(colors[k]);  // Set beautiful slice color
    
            GLdouble startAngle = previousSliceAngle;
            GLdouble endAngle = twoPi * dataValues[k] / dataSum + previousSliceAngle;
            GLdouble angle;
    
            glBegin(GL_TRIANGLE_FAN);
            glVertex2i(circCtr.x, circCtr.y); // Center of the pie
    
            // Add points along the arc
            for (angle = startAngle; angle <= endAngle; angle += 0.001)
            {
                piePt.x = circCtr.x + radius * cos(angle);
                piePt.y = circCtr.y + radius * sin(angle);
                glVertex2i(piePt.x, piePt.y);
            }
    
            // Last point at endAngle to close the slice
            piePt.x = circCtr.x + radius * cos(angle);
            piePt.y = circCtr.y + radius * sin(angle);
            glVertex2i(piePt.x, piePt.y);
            glEnd();
    
            previousSliceAngle = endAngle;
        }
}

void displayFcn (void)
{
    glClear (GL_COLOR_BUFFER_BIT); // Clear display window.
    glColor3f (0.0, 0.0, 0.0); // Set color to black.
    pieChart ( );
    glFlush ( );
}


int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Pie Chart");
    init ( );
    glutDisplayFunc (displayFcn);
    
    glutMainLoop ( );

    return 0;
}