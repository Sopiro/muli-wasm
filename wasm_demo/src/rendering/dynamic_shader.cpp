#include "dynamic_shader.h"

namespace muli
{

std::unique_ptr<DynamicShader> DynamicShader::Create()
{
    return std::unique_ptr<DynamicShader>(new DynamicShader);
}

DynamicShader::DynamicShader()
    : Shader(
          // Vertex shader
          R"(
        #version 100

        attribute vec2 pos;

        uniform mat4 view;
        uniform mat4 proj;
        uniform mat4 model;

        void main()
        {
           mat4 mvp = proj * view * model;
           gl_PointSize = 5.0;
           gl_Position = mvp * vec4(pos, 0.0, 1.0);
        }
    )",
          // Fragment shader
          R"(
        #version 100
        precision mediump float;

        uniform vec3 color;

        void main()
        {
            gl_FragColor = vec4(color, 1.0);
        }
    )")
{
    uniformMap.insert({ "color", glGetUniformLocation(shaderHandle, "color") });
    uniformMap.insert({ "model", glGetUniformLocation(shaderHandle, "model") });
    uniformMap.insert({ "view", glGetUniformLocation(shaderHandle, "view") });
    uniformMap.insert({ "proj", glGetUniformLocation(shaderHandle, "proj") });
}

} // namespace muli