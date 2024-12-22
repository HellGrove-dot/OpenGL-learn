#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <glad/glad.h>

namespace Render
{
class ShaderProgram
{
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ShaderProgram();
    private:
        bool m_isCompiled;
        GLuint m_ID;

};

};

#endif