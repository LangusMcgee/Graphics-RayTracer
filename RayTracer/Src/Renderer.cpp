#include "Renderer.h"
//#include <thread>

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
	m_thread_count = 1;// std::thread::hardware_concurrency();
	std::cout << m_thread_count << " concurrent threads are supported.\n";
}

void renderer::renderScene()
{
	m_gcp_framework.SetAllPixels(glm::vec3(1, 0, 1));
	m_gcp_framework.RenderFrame();
	m_gcp_framework.SetAllPixels(glm::vec3(0.8, 0.9, 1));

	if (!m_camera) {
		std::cout << "NO CAMERA SELECTED!\n";
		return;
	}

	for (int i = 0; i < winX; i++)
	{
		//if (winX - i < 6)
		//{
		//	std::thread t1(&renderer::drawRow, this, i);
		//	t1.join();
		//	i++;
		//}
		std::thread t1(&renderer::drawRow, this, i);
		t1.join();
		i++;
		std::thread t2(&renderer::drawRow, this, i);
		t2.join();
		//i++;
		//std::thread t3(&renderer::drawRow, this, i);
		//t3.join();
		//i++;
		//std::thread t4(&renderer::drawRow, this, i);
		//t4.join();
		//i++;
		//std::thread t5(&renderer::drawRow, this, i);
		//t5.join();
		//i++;
		//std::thread t6(&renderer::drawRow, this, i);
		//t6.join();
		//i++;
		//std::thread t7(&renderer::drawRow, this, i);
		//t7.join();
	}


	//drawRow(10);

	/*
	std::vector<std::thread> rowWorkers;
	rowWorkers.reserve(m_thread_count);

	for (int row = 0; row < winY; row++)
	{
		rowWorkers.emplace_back(&renderer::drawRow, this, row);

		if (rowWorkers.size() == m_thread_count)
		{
			for (int i =0; rowWorkers.size() < i; i++)
			{
				rowWorkers[i].join();
			}

			rowWorkers.clear();
		}
		//drawRow(row);
		std::cout << "drawn row: " << row << "\n";
	}
	for (int i = 0; rowWorkers.size() < i; i++)
	{
		rowWorkers[i].join();
	}
	*/

	m_gcp_framework.ShowAndHold();
}


void renderer::drawRow(int _row)
{

	for (int pixel = 0; pixel < winX; pixel++)
	{
		// Determine pixel colour
		Ray ray = m_camera->createRay(glm::ivec2(pixel, _row));
		glm::vec3 colour(0);
		bool hit = m_ray_tracer.trace_ray(ray, colour);

		// Draws shaded pixel on hit
		if (hit)
		{
			//pixelMutex.lock();
			m_gcp_framework.DrawPixel(glm::ivec2(pixel, _row), colour);
			//pixelMutex.unlock();
		}
	}
}


