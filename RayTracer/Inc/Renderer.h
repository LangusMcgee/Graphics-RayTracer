#pragma once
#include <GCP_GFX_Framework.h>
#include <GLM/glm.hpp>
#include <memory>

#include "Sphere.h"
#include "RayTracer.h"
#include "Camera.h"

class renderer
{
public:
	void init(glm::vec2 _winSize);
	void addObject(std::shared_ptr<Sphere> _sphere) { m_ray_tracer.addSphere(_sphere); }
	void renderScene();

private:

	int winX;
	int winY;
	unsigned int m_thread_count;

	GCP_Framework m_gcp_framework;

	ray_tracer m_ray_tracer;
	Camera camera;
};