#include <GL/glut.h>

void display() {
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Reset transformations
    glLoadIdentity();
    
    // Set the camera position
    gluLookAt(
        2.0, 2.0, 2.0,  // Eye position
        0.5, 0.5, 0.5,  // Look at position (center of cube)
        0.0, 0.0, 1.0   // Up vector
    );
    
    // Draw the coordinate axes
    glBegin(GL_LINES);
        // X-axis (red)
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.5, 0.0, 0.0);
        
        // Y-axis (green)
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.5, 0.0);
        
        // Z-axis (blue)
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.5);
    glEnd();
    
    // Draw cube (filled with light blue color)
    glColor3f(0.5, 0.7, 0.9);  // Light blue color
    
    glBegin(GL_QUADS);
        // Front face
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        glVertex3f(1.0, 1.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
        
        // Back face
        glVertex3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(1.0, 0.0, 1.0);
        
        // Left face
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 1.0, 1.0);
        glVertex3f(0.0, 0.0, 1.0);
        
        // Right face
        glVertex3f(1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, 0.0);
        
        // Top face
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(1.0, 1.0, 0.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(0.0, 1.0, 1.0);
        
        // Bottom face
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);
        glVertex3f(1.0, 0.0, 1.0);
        glVertex3f(1.0, 0.0, 0.0);
    glEnd();
    
    // Draw outline of the cube in black
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        // Bottom face edges
        glVertex3f(0.0, 0.0, 0.0); glVertex3f(1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0); glVertex3f(1.0, 1.0, 0.0);
        glVertex3f(1.0, 1.0, 0.0); glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        
        // Top face edges
        glVertex3f(0.0, 0.0, 1.0); glVertex3f(1.0, 0.0, 1.0);
        glVertex3f(1.0, 0.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0); glVertex3f(0.0, 1.0, 1.0);
        glVertex3f(0.0, 1.0, 1.0); glVertex3f(0.0, 0.0, 1.0);
        
        // Connecting edges
        glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0, 0.0, 1.0);
        glVertex3f(1.0, 0.0, 0.0); glVertex3f(1.0, 0.0, 1.0);
        glVertex3f(1.0, 1.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(0.0, 1.0, 0.0); glVertex3f(0.0, 1.0, 1.0);
    glEnd();
    
    glutSwapBuffers();
}

void init() {
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    
    // Set clear color to white
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void reshape(int width, int height) {
    // Set the viewport to the entire window
    glViewport(0, 0, width, height);
    
    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / height, 0.1, 100.0);
    
    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Cube");
    
    // Register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    // Initialize OpenGL
    init();
    
    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}