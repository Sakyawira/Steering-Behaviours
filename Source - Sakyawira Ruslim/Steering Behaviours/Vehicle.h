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
		void process(Behaviour steer, std::vector<Vehicle*>& v_boids, glm::vec3 target_location, int window_width, int window_height, int player_size, float delta_time);
		void RandomOn();
		void limit(glm::vec3& _vector3,float _maxMagnitude);
		void apply_force(glm::vec3 _force);
		void seek(glm::vec3 _target);
		glm::vec3 get_seek(glm::vec3 _target);
		void arrive(glm::vec3 _target, float delta_time);
		glm::vec3 get_arrive(glm::vec3 _target, float delta_time);
		void wander(float delta_time);
		void containment(float width, float height, float d);
		glm::vec3 separate(std::vector<Vehicle*>& v_boids);
		glm::vec3 alignment(std::vector<Vehicle*>& v_boids);
		glm::vec3 cohesion(std::vector<Vehicle*>& v_boids);
		void flock(std::vector<Vehicle*>& v_boids);
		void lead_following(std::vector<Vehicle*>& v_boids, glm::vec3 target_location, float delta_time);
	
	private:
		glm::vec3 m_acceleration = glm::vec3(0.0f, 0.0f, 0.0f);;
		glm::vec3 m_velocity = glm::vec3(0.0f, 0.1f, 0.0f);
	
		bool m_bool_dir = false;
		bool m_bool_vertical = false;
		bool m_bool_random_move = false;

		float r = 6.0f;
		float m_max_force = 0.05f;    // Maximum steering force
		float m_max_speed = 3.0f;     // Maximum speed

		float m_wander_theta = 0.0f;
	
		int m_wander_counter = 10;
};
