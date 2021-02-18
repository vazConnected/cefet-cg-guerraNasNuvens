#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "telas.h"

#define MARGEM_DA_TELA 10

void inicio_desenhaCena(){
    glColor3f(0.4, 0.7647, 0.996); // RGB: 102 195 154
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(  0,   0, 0);
        glVertex3f(300,   0, 0);
        glVertex3f(300, 400, 0);
        glVertex3f(  0, 400, 0);
    glEnd();
}

void jogo_desenhaCena(){}
void fimDeJogo_desenhaCena(){}

