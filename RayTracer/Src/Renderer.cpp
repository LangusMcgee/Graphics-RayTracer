#include "Renderer.h"
#include <thread>

bool renderer::init(glm::vec2 _winSize)
{
	m_win_size = _winSize;
	// Initialises SDL and OpenGL and sets up a framebuffer
	winX = _winSize.x;
	winY = _winSize.y;
	std::cout << "initialising \n";
	if (!m_gcp_framework.Init(_winSize))
	{
		std::cout << "failed to init gcpframework \n";
		return false;
		//throw std::exception("failed to init gcpframework \n");
	}
	std::cout << "initialised \n";

	// Get thread count
	m_thread_count = std::thread::hardware_concurrency();
	std::cout << m_thread_count << " concurrent threads are supported.\n";
}

void renderer::renderScene()
{
	m_gcp_framework.SetAllPixels(glm::vec3(1, 0, 1));
	m_gcp_framework.RenderFrame();
	m_gcp_framework.SetAllPixels(glm::vec3(0.8, 0.9, 1));
	if (m_camera != nullptr)
	{
		for (int i = 0; i < winX; i++)
		{
			for (int j = 0; j < winY; j++)
			{
				// Determine pixel colour
				Ray ray = m_camera->createRay(glm::ivec2(i, j));
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
	else
	{
		std::cout << "NO CAMERA SELECTED!\n";
		//m_gcp_framework.ShowAndHold();
	}
}