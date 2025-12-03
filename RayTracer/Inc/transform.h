#pragma once

#include "glm/glm.hpp"

class Transform
{
public:
	Transform();

	void translate(glm::vec3 _movement);
	void rotate(glm::vec3 _rotation);

	//Setters
	void position(glm::vec3 _position);
	void rotation(glm::vec3 _rotation);
	void scale(glm::vec3 _scale);
	//Getters
	glm::vec3 position()
	{
		return m_position;
	}
	glm::vec3 rotation()
	{
		return m_rotation;
	}
	glm::vec3 scale()
	{
		return m_scale;
	}

	glm::mat4 model_matrix();

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};