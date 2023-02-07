#pragma once

#ifdef __EMSCRIPTEN__
#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <emscripten/emscripten.h>
#else
#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <muli/muli.h>

#include <iostream>