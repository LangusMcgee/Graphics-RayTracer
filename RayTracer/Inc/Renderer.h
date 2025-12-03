#pragma once
#include <GCP_GFX_Framework.h>
#include <GLM/glm.hpp>
#include "RayTracer.h"

class renderer
{
	void init(glm::vec2 _winSize);

private:

	unsigned int thread_count;
	GCP_Framework m_gcpFramework;
	
};