#include "Renderer.h"
#include <thread>

void renderer::init(glm::vec2 _winSize)
{
	// Initialises SDL and OpenGL and sets up a framebuffer
	winX = _winSize.x;
	winY = _winSize.y;
	std::cout << "initialising \n";
	if (!m_gcp_framework.Init(_winSize))
	{
		std::cout << "failed to init gcpframework \n";
		throw std::exception("failed to init gcpframework \n");
	}
	std::cout << "initialised \n";

	camera.setResolution(winX, winY);

	// Get thread count
	m_thread_count = std::thread::hardware_concurrency();
	std::cout << m_thread_count << " concurrent threads are supported.\n";
}

void renderer::renderScene()
{
	m_gcp_framework.SetAllPixels(glm::vec3(0.8, 0.9, 1));
	m_gcp_framework.RenderFrame();
	for (int i = 0; i < winX; i++)
	{
		for (int j = 0; j < winY; j++)
		{
			// Determine pixel colour
			Ray ray = camera.createRay(glm::ivec2(i, j));
			glm::vec3 colour(0);
			bool hit = m_ray_tracer.trace_ray(ray, colour);

			// Draws shaded pixel on hit
			if (hit)
			{
				m_gcp_framework.DrawPixel(glm::ivec2(i, j), colour);
			}
		}
	}
	m_gcp_framework.ShowAndHold();
}