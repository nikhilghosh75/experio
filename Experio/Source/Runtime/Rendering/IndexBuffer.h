#pragma once

class IndexBuffer
{
private:
	unsigned int rendererID;
	unsigned int* data;
	unsigned int count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void SetData(unsigned int* data, unsigned int count);
	void MoveData(unsigned int* data, unsigned int count);

	void Bind() const;
	void Unbind() const;

	unsigned int GetCount() const;

	unsigned int* GetData() const;
};