#pragma once
#include <vector>
#include <memory>
#include "scene.h"
#include "surface.h"
#include "light.h"
#include <GLM/glm.hpp>
#include "Ray.h"
#include "scene.h"

class ray_tracer
{
public:
	// Shoots ray from camera to world to get first intersection
	bool trace_ray(Ray _ray, glm::vec3& _colour);
	// Sets scene
	void set_scene(scene _scene) { m_scene = _scene; };
private:
	scene m_scene;
};