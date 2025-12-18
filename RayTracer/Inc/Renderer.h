#pragma once
#include <GCP_GFX_Framework.h>
#include <GLM/glm.hpp>
#include <memory>
#include <mutex>

#include "scene.h"
#include "surface.h"
#include "RayTracer.h"
#include "Camera.h"

class renderer
{
public:
	// sets up default values and initialises underlying framework.
	bool init(glm::vec2 _winSize);
	// Scene switcher - access to ray tracer set scene
	void set_scene(scene _scene) { m_ray_tracer.set_scene(_scene); }
	// set the thread count, has measures to ensure number in range
	bool set_thread_usage(int _threadCount);
	// Camera switcher, would be good for a game if it was real time.
	void set_cam(std::shared_ptr<Camera> _cam)
	{
		m_camera = _cam;
		m_camera->setResolution(winX, winY);
	};
	// Renders scene and prints time taken + set params
	void renderScene();

	void setAASamples(int _samples) { m_AA_Samples = _samples; }
	// Show the scene - seperation required for performance test iterations
	void show();


private:
	// Used in render function for multithreading
	void drawRows(int _startRow, int _endRow);
	int m_AA_Samples = 1; // Anti Ailasing samples.
	int winX;
	int winY;
	unsigned int m_thread_count;
	std::mutex pixelMutex;

	GCP_Framework m_gcp_framework;

	ray_tracer m_ray_tracer;

	glm::vec2 m_win_size;
	std::shared_ptr<Camera> m_camera;
};