#include "dynamic_shader.h"

namespace muli
{

DynamicShader::DynamicShader()
    : Shader(
          // Vertex shader
          R"(
        #version 100

        attribute vec2 pos;
        attribute vec4 color;

        varying vec4 f_color;

        uniform mat4 view;
        uniform mat4 proj;

        void main()
        {
           mat4 mvp = proj * view;

           f_color = color;
           gl_PointSize = 5.0;
           gl_Position = mvp * vec4(pos, 0.0, 1.0);
        }
    )",
          // Fragment shader
          R"(
        #version 100
        precision mediump float;

        varying vec4 f_color;

        void main()
        {
            gl_FragColor = f_color;
        }
    )")
{
    uniformMap.insert({ "color", glGetUniformLocation(shaderHandle, "color") });
    uniformMap.insert({ "model", glGetUniformLocation(shaderHandle, "model") });
    uniformMap.insert({ "view", glGetUniformLocation(shaderHandle, "view") });
    uniformMap.insert({ "proj", glGetUniformLocation(shaderHandle, "proj") });
}

} // namespace muli