#pragma once

struct FFramebufferSpec
{
	unsigned int width;
	unsigned int height;

	unsigned int samples = 1;

	bool swapChainTarget = false;

	FFramebufferSpec()
	{
		width = 0;
		height = 0;
	}

	FFramebufferSpec(unsigned int width, unsigned int height)
	{
		this->width = width;
		this->height = height;
	}
};

class Framebuffer
{
public:
	Framebuffer();
	Framebuffer(const FFramebufferSpec& spec);
	Framebuffer(unsigned int width, unsigned int height);

	~Framebuffer();

	void SetSpec(const FFramebufferSpec& spec);
	void SetSpec(unsigned int width, unsigned int height);

	unsigned int GetColorAttachment() const { return colorAttachment; }
	unsigned int GetDepthAttachment() const { return depthAttachment; }

	void Bind() const;
	void Unbind() const;

	static void CheckFramebufferStatus();

private:
	unsigned int rendererID;
	unsigned int colorAttachment;
	unsigned int depthAttachment;

	FFramebufferSpec spec;

	void Build();
};