#include "Renderer.h"
#include <thread>

void renderer::init(glm::vec2 _winSize)
{
	// Initialises SDL and OpenGL and sets up a framebuffer
	if (!m_gcpFramework.Init(_winSize))
	{
		throw std::exception("failed to init gcpframework \n");
	}
	// Get thread count
	thread_count = std::thread::hardware_concurrency();
	std::cout << thread_count << " concurrent threads are supported.\n";
}