#ifndef CUBE_TEXTURE_H
#define CUBE_TEXTURE_H

#include <GL/glew.h>
#include<GL/glut.h>
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <SOIL2/SOIL2.h>
#include <iostream>
#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern int cubeTextureMain(int argc, char* argv[]);

#endif