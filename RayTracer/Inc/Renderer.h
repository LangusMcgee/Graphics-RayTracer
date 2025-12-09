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
	bool init(glm::vec2 _winSize);
	void set_scene(scene _scene) { m_ray_tracer.set_scene(_scene); }
	void set_cam(std::shared_ptr<Camera> _cam)
	{
		m_camera = _cam;
		m_camera->setResolution(winX, winY);
	};
	void renderScene();
	void drawRow(int _colum);

private:

	int winX;
	int winY;
	unsigned int m_thread_count;
	std::mutex pixelMutex;

	GCP_Framework m_gcp_framework;

	ray_tracer m_ray_tracer;

	glm::vec2 m_win_size;
	std::shared_ptr<Camera> m_camera;
};