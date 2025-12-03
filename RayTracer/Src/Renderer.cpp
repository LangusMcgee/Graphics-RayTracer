#include "Renderer.h"
#include <thread>

void renderer::init(glm::vec2 _winSize)
{
	// Initialises SDL and OpenGL and sets up a framebuffer
	winX = _winSize.x;
	winY = _winSize.y;
	if (!m_gcp_framework.Init(_winSize))
	{
		throw std::exception("failed to init gcpframework \n");
	}

	camera.setResolution(winX, winY);

	// Get thread count
	m_thread_count = std::thread::hardware_concurrency();
	std::cout << m_thread_count << " concurrent threads are supported.\n";
}

void renderer::renderScene()
{
	for (int i = 0; i < winX; i++)
	{
		for (int j = 0; j < winY; j++)
		{
			// Determine pixel colour
			glm::vec3 colour = m_ray_tracer.trace_ray(camera.createRay(glm::ivec2(i, j)));

			// Draws shaded pixel
			m_gcp_framework.DrawPixel(glm::ivec2(i, j), colour);
		}
	}
	m_gcp_framework.RenderFrame();
}