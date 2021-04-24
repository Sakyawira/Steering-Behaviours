/***********************
  File Name   :   Vehicle.h
  Description :   contains declaration of Vehicle class which control the steering behaviours of an object
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#pragma once
#include "GameObject.h"

enum class Behaviour
{
	SEEK,
	ARRIVE,
	WANDER,
	CONTAINMENT,
	FLOCK,
	LEAD_FOLLOWING,
};

class Vehicle : public GameObject
{
	public:
		Vehicle(Shader* _shader, Mesh* _mesh, std::vector<Texture*>&& _textures, float _initialX, float _initialY);
		// ~Vehicle() = default;
		void Process(Behaviour _steer, std::vector<Vehicle*>& _boids, glm::vec3 _targetLocation, int _windowWidth, int _windowHeight, int _playerSize, float _deltaTime);
		void Limit(glm::vec3& _vector3,float _maxMagnitude);
		void ApplyForce(glm::vec3 _force);
		void Seek(glm::vec3 _target);
		glm::vec3 GetSeek(glm::vec3 _target);
		void Arrive(glm::vec3 _target, float _deltaTime);
		glm::vec3 GetArrive(glm::vec3 _target, float _deltaTime);
		void Containment(float _width, float _height, float _d);
		void Wander(float _deltaTime);
		glm::vec3 Separate(std::vector<Vehicle*>& _boids, const float _desiredSeparation = 137.5f);
		glm::vec3 Cohesion(std::vector<Vehicle*>& _boids);
		glm::vec3 Alignment(std::vector<Vehicle*>& _boids);
		void Flock(std::vector<Vehicle*>& _boids);
		void LeadFollowing(std::vector<Vehicle*>& _boids, glm::vec3 _targetLocation, float _deltaTime);
	
	private:
		glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);;
		glm::vec3 velocity = glm::vec3(0.0f, 0.1f, 0.0f);
	
		bool dir = false;
		bool vertical = false;
		bool randomMove = false;

		float r = 6.0f;
		const float maxForce = 0.05f;    // Maximum steering force
		const float maxSpeed = 3.0f;     // Maximum speed

		float wanderTheta = 0.5f;
};