#include "rigidbody_shader.h"

namespace muli
{

std::unique_ptr<RigidBodyShader> RigidBodyShader::Create()
{
    return std::unique_ptr<RigidBodyShader>(new RigidBodyShader);
}

RigidBodyShader::RigidBodyShader()
    : Shader(
          // Vertex shader
          R"(
        #version 100

        attribute vec3 pos;
        attribute vec2 _texCoord;

        varying vec2 texCoord;

        uniform mat4 view;
        uniform mat4 proj;
        uniform mat4 model;

        void main()
        {
           mat4 mvp = proj * view * model;
           gl_Position = mvp * vec4(pos, 1.0);

           texCoord = _texCoord;
        }
    )",
          // Fragment shader
          R"(
        #version 100
        precision mediump float;

        varying vec2 texCoord;

        uniform vec3 color;

        void main()
        {
            vec2 uv = texCoord; // barycentric coordinate
            
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