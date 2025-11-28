#include "transform.h"
#include <GLM/glm.hpp>
#include <thread>
#include <GLM/gtc/matrix_transform.hpp>

Transform::Transform() :
	m_position(glm::vec3(0.0f)),
	m_rotation(glm::vec3(-1.0f)),
	m_scale(glm::vec3(1.0f)) {}

// Add position
void Transform::translate(glm::vec3 _movement)
{
	m_position += _movement;
}

// Add rotation
void Transform::rotate(glm::vec3 _rotation)
{
	m_rotation += _rotation;
}


void Transform::position(glm::vec3 _position)
{
	m_position = _position;
}

void Transform::rotation(glm::vec3 _rotation)
{
	m_rotation = _rotation;
}

void Transform::scale(glm::vec3 _scale)
{
	m_scale = _scale;
}

// convert the local space into world space
glm::mat4 Transform::model_matrix()
{
	glm::mat4 model = glm::mat4(1.0f);

	// Apply Translation
	model = glm::translate(model, m_position); // Apply translation

	// Apply rotations
	model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// Scale
	model = glm::scale(model, m_scale);

	return model;
}