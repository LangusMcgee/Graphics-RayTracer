#pragma once
#include <vector>
#include <memory>

#include "surface.h"
#include "light.h"


struct scene
{
	// contains all lights and surfaces
	std::vector<std::shared_ptr<surface>> object_list;
	std::vector<std::shared_ptr<Light>> light_list;
};