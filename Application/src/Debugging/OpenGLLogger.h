#pragma once

#include <iostream>
#include "glad/glad.h"

void GLClearErrors() {
    while (glGetError());
}

bool GLLogCall(const char* function, const char* file, int line) {
    if (uint32_t error = glGetError())
    {
        std::cout << "[OpenGL Error]: " << error << " : " << function << " in " << file << " at line " << line << std::endl;
        return false;
    }

    return true;
}

GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        const char* error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default: error = "UNKNOWN_ERROR"; break;
        }

        std::cout << error << " | " << file << "(" << line << ")" << std::endl;
    }

    return errorCode;
}

#ifdef DEBUG_MODE
    #define ASSERT(x) if (!(x)) __debugbreak();
    #define GLCall(x) GLClearErrors(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__));
    #define glCheckError() glCheckError_(__FILE__, __LINE__)
#else
    #define GLCall(x) x;
    #define glCheckError();
#endif