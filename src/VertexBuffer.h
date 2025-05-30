#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	~VertexBuffer();
	void Reset();
	void SetDataSize(const void* data, unsigned int size);
	void Bind() const;
	void Unbind() const;
};
