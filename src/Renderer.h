#pragma once
#include "GL/glew.h"
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
// THIS FILE IS FOR DEBUGING PURPOSES
#define space " "
#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};
