#pragma once
#include "GameObject.h"

enum Behaviour
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
		Vehicle(Shader* _shader, Mesh* _mesh, std::vector<Texture*>& _textures, float _initial_x, float _initial_y);
		~Vehicle() = default;
		void Process(Behaviour steer, std::vector<Vehicle*>& v_boids, glm::vec3 target_location, int window_width, int window_height, int player_size, float delta_time);
		void RandomOn();
		void Limit(glm::vec3& _vector3,float _maxMagnitude);
		void ApplyForce(glm::vec3 _force);
		void Seek(glm::vec3 _target);
		glm::vec3 GetSeek(glm::vec3 _target);
		void Arrive(glm::vec3 _target, float delta_time);
		glm::vec3 GetArrive(glm::vec3 _target, float delta_time);
		void Wander(float delta_time);
		void Containment(float width, float height, float d);
		glm::vec3 Seperate(std::vector<Vehicle*>& v_boids);
		glm::vec3 Alignment(std::vector<Vehicle*>& v_boids);
		glm::vec3 Cohesion(std::vector<Vehicle*>& v_boids);
		void Flock(std::vector<Vehicle*>& v_boids);
		void LeadFollowing(std::vector<Vehicle*>& v_boids, glm::vec3 target_location, float delta_time);
	
	private:
		glm::vec3 m_acceleration = glm::vec3(0.0f, 0.0f, 0.0f);;
		glm::vec3 m_velocity = glm::vec3(0.0f, 0.1f, 0.0f);
	
		bool m_bool_dir = false;
		bool m_bool_vertical = false;
		bool m_bool_random_move = false;

		float r = 6.0f;
		float m_max_force = 0.05f;    // Maximum steering force
		float m_max_speed = 3.0f;     // Maximum speed

		float m_wander_theta = 0.5f;
	
		int m_wander_counter = 10;
};
