#pragma once
#include <vector>
#include <memory>

#include "surface.h"
#include "light.h"

// contains all lights and surfaces + sample parameters
struct scene
{
	std::vector<std::shared_ptr<surface>> object_list;
	std::vector<std::shared_ptr<light>> light_list;
	int shadowSamples;
	int indirectSamples;
};