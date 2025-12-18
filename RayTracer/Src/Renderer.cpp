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
	m_thread_count = std::thread::hardware_concurrency();
	std::cout << m_thread_count << " concurrent threads are supported.\n";
}

bool renderer::set_thread_usage(int _threadCount)
{
	// Safe method to set the threadcount
	int available_threads = std::thread::hardware_concurrency();
	if (_threadCount > available_threads || _threadCount <= 0)
	{
		std::cout << "Thread count out of range. Max = " << m_thread_count << "\n";
		return false;
	}
	else
	{
		m_thread_count = _threadCount;
		return true;
	}
}

void renderer::renderScene()
{
	auto start = std::chrono::high_resolution_clock::now();

	m_gcp_framework.SetAllPixels(glm::vec3(1, 0, 1));
	m_gcp_framework.RenderFrame();
	m_gcp_framework.SetAllPixels(glm::vec3(0.8, 0.9, 1));

	if (!m_camera) {
		std::cout << "NO CAMERA SELECTED!\n";
		return;
	}

	int rowsPerThread = winY / m_thread_count;
	int remainder = winY % m_thread_count;

	std::vector<std::thread> rowWorkers(m_thread_count);

	int startRow = 0;

	for (int i = 0; i < m_thread_count; i++)
	{
		int endRow = startRow + rowsPerThread;

		if (i < remainder)
			endRow++;

		if (endRow > winY)
			endRow = winY;

		rowWorkers[i] = std::thread([this, startRow, endRow]()
			{
				drawRows(startRow, endRow);
			});

		startRow = endRow;
	}

	for (std::thread& t : rowWorkers)
		t.join();

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "Rendering time(ms) : " << duration.count() << "\n";
}

void renderer::show()
{
	m_gcp_framework.ShowAndHold();
}

void renderer::drawRows(int _startRow, int _endRow)
{
	for (int row = _startRow; row < _endRow; row++)
	{
		for (int pixel = 0; pixel < winX; pixel++)
		{
			glm::vec3 accumulatedColour(0.0f);
			int hitCount = 0;

			// Supersampling grid
			for (int sy = 0; sy < m_AA_Samples; sy++)
			{
				for (int sx = 0; sx < m_AA_Samples; sx++)
				{
					// Sub-pixel offset in range
					float offsetX = (sx + 0.5f) / m_AA_Samples;
					float offsetY = (sy + 0.5f) / m_AA_Samples;

					// Create ray with sub-pixel offset
					Ray ray = m_camera->createRay(glm::vec2(pixel + offsetX, row + offsetY)
					);

					glm::vec3 colour(0.0f);
					if (m_ray_tracer.trace_ray(ray, colour))
					{
						accumulatedColour += colour;
						hitCount++;
					}
				}
			}

			if (hitCount > 0)
			{
				accumulatedColour /= float(m_AA_Samples * m_AA_Samples);
				m_gcp_framework.DrawPixel(glm::ivec2(pixel, row),accumulatedColour);
			}
		}
	}

	m_gcp_framework.RenderFrame();
}



