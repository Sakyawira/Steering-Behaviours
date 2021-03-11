#include "Vehicle.h"
#include <ctime>
#include <utility>

Vehicle::Vehicle(Shader * _shader, Mesh * _mesh, std::vector<Texture*>& _textures, float _initial_x, float _initial_y)
{
	m_shader = _shader;
	m_mesh = _mesh;
	m_xPos = _initial_x;
	m_yPos = _initial_y;
	// This creates a copy (even though was passed a s a reference) and therefore did not work
	// m_camera = _camera;
	m_textures = _textures;

	m_objPosition = glm::vec3(m_xPos, m_yPos, 0.0f);
	m_translationMatrix = glm::translate(glm::mat4(), m_objPosition);
	m_modelMatrix = m_translationMatrix * m_rotationZ * m_scaleMatrix;

	// Pick a start direction (positive / negative)
	int negate = rand() % 2;
	m_bool_dir = (negate == 0 ? false : true);

	// Pick a start direction (vetical / horizontal)
	negate = rand() % 2;
	m_bool_vertical = (negate == 0 ? false : true);
}

//void Vehicle::Process(int WINDOW_WIDTH, int WINDOW_HEIGHT, int player_size, float delta_time)
//{
//	if (m_bool_random_move == true)
//	{
//		int negate = rand() % 260;
//		m_bool_vertical = (negate == 0 ? !m_bool_vertical : m_bool_vertical);
//
//		negate = rand() % 260;
//		m_bool_dir = (negate == 0 ? !m_bool_dir : m_bool_dir);
//		
//	}
//
//	if (m_bool_vertical)
//	{
//		if (static_cast<int>(m_yPos) == WINDOW_HEIGHT - (static_cast<int>(m_scale) + 150) || static_cast<int>(m_yPos) == - WINDOW_HEIGHT + (static_cast<int>(m_scale) + 150))
//		{
//			m_bool_dir = !m_bool_dir;
//		}
//		if (m_bool_dir)
//		{
//			Move(MOVE_UP, 1.0f * delta_time);
//		}
//		else
//		{
//			Move(MOVE_DOWN, 1.0f * delta_time);
//		}
//	}
//	else
//	{
//		if (static_cast<int>(m_xPos) == WINDOW_WIDTH - (static_cast<int>(m_scale) + 150) || static_cast<int>(m_xPos) == -WINDOW_WIDTH + (static_cast<int>(m_scale) + 150))
//		{
//			m_bool_dir = !m_bool_dir;
//		}
//		if (m_bool_dir)
//		{
//			Move(MOVE_RIGHT, 1.0f * delta_time);
//		}
//		else
//		{
//			Move(MOVE_LEFT, 1.0f * delta_time);
//		}
//	}
//}

void Vehicle::process(const behaviour steer, std::vector<Vehicle*>& v_boids, glm::vec3 target_location, const int window_width, const int window_height, int player_size, const float delta_time)
{
	if (steer == SEEK)
	{
		seek(target_location);
	}

	else if (steer == ARRIVE)
	{
		//m_max_force *= 2.0f;
		arrive(target_location, delta_time);
		//m_max_force /= 2.0f;
	}

	else if (steer == CONTAINMENT)
	{
		containment(static_cast<float>(window_width)* 1.4f, static_cast<float>(window_height)* 1.4f, 400.0f* 1.4f);
	}

	else if (steer == WANDER)
	{
		wander(delta_time);
		m_max_force *= 1.4f;
		containment(static_cast<float>(window_width) , static_cast<float>(window_height), 400.0f );
		m_max_force /= 1.4f;
	}

	else if (steer == FLOCK)
	{
		m_max_force *= 1.2f;
		containment(static_cast<float>(window_width), static_cast<float>(window_height), 400.0f);
		m_max_force /= 1.2f;
		flock(v_boids);
	}

	else if (steer == LEAD_FOLLOWING)
	{
		lead_following(v_boids, target_location, delta_time);
	}
	// Update velocity
	m_velocity += m_acceleration;
	
	// Limit speed
	limit(m_velocity, m_max_speed);
	
	m_objPosition += m_velocity * delta_time;
	
	// Reset acceleration to 0 each cycle
	m_acceleration *= 0;

	// Update Model Matrix
	m_translationMatrix = glm::translate(glm::mat4(), m_objPosition);
	m_modelMatrix = m_translationMatrix * m_rotationZ * m_scaleMatrix;
}

void Vehicle::RandomOn()
{
	m_bool_random_move = true;
}

void Vehicle::limit(glm::vec3& _vector3, float _maxMagnitude)
{
	if (glm::length(_vector3) > _maxMagnitude) 
	{
		_vector3 = glm::normalize(_vector3);
		_vector3 *= _maxMagnitude;
	}
}

void Vehicle::apply_force(glm::vec3 _force)
{
	m_acceleration += _force;
}

void Vehicle::seek(glm::vec3 _target)
{
	// A vector pointing from the location to the target
	glm::vec3 desired = _target - m_objPosition;  

   // Normalize desired and scale to maximum speed
	if (glm::length(desired) > 0.0f)
	{
		desired = glm::normalize(desired);
	}
	
	desired *= m_max_speed;
	
	// Steering = Desired minus velocity
	glm::vec3 steer = desired - m_velocity;

	// Limit to maximum steering force
	limit(steer,m_max_force);  

	apply_force(steer);
}

glm::vec3 Vehicle::get_seek(glm::vec3 _target)
{
	// A vector pointing from the location to the target
	glm::vec3 desired = _target - m_objPosition;  

   // Normalize desired and scale to maximum speed
	if (glm::length(desired) > 0.0f)
	{
		desired = glm::normalize(desired);
	}

	desired *= m_max_speed;

	// Steering = Desired minus velocity
	glm::vec3 steer = desired - m_velocity;

	// Limit to maximum steering force
	limit(steer, m_max_force);  
	
	return steer;
}

void Vehicle::arrive(glm::vec3 _target, float delta_time)
{
	// A vector pointing from the location to the target
	glm::vec3 desired = _target - m_objPosition;

	// Get the magnitude of desired
	const float d = glm::length(desired);
	
	// Normalize desired
	if (glm::length(desired) > 0.0f)
	{
		desired = glm::normalize(desired);
	}

	// Map the speed depends on its distance to the target
	if (d < m_max_speed * 50.0f)
	{
		const float m = 0 + (m_max_speed - 0) * ((d -0)/(m_max_speed * 50.0f - 0)) ; //* delta_time;
		if (d <= m_max_speed * 15.0f)
		{
			desired *= (glm::floor(m) /** 1.0001f*/);
		}
		else
		{
			desired *= (glm::ceil(m));
		}
	}

	else 
	{
		desired *= m_max_speed;// * delta_time;
	}

	// Steering = Desired minus Velocity
	glm::vec3 steer = desired - m_velocity;
	// Limit to maximum steering force
	limit(steer, (m_max_force * m_max_speed));  
	apply_force(steer);
}

glm::vec3 Vehicle::get_arrive(glm::vec3 _target, float delta_time)
{
	// A vector pointing from the location to the target
	glm::vec3 desired = _target - m_objPosition;

	
	const float d = glm::length(desired);

	// Normalize desired
	if (glm::length(desired) > 0.0f)
	{
		desired = glm::normalize(desired);
	}

	// Map the speed depends on its distance to the target
	if (d < m_max_speed * 50.0f)
	{
		const float m = 0 + (m_max_speed - 0) * ((d - 0) / (m_max_speed * 50.0f - 0)); //* delta_time;
		if (d <= m_max_speed * 15.0f)
		{
			desired *= (glm::floor(m) /** 1.0001f*/);
		}
		else
		{
			desired *= (glm::ceil(m));
		}
	}

	else
	{
		desired *= m_max_speed;// * delta_time;
	}

	// Steering = Desired minus Velocity
	glm::vec3 steer = desired - m_velocity;
	limit(steer, (m_max_force * m_max_speed));  // Limit to maximum steering force
	return steer;
}

void Vehicle::wander(float delta_time)
{
	srand(time(nullptr));
	
	if (m_velocity == glm::vec3(0.0f, .0f, 0.0f))
	{
		m_velocity = glm::vec3(0.0f, 0.1f, 0.0f);
	}
	
	if (m_wander_counter == 0)
	{
		// Distance from vehicle to imaginary circle"
		const float wander_distance = 8.0f;         
		glm::vec3 target = m_objPosition + glm::normalize(m_velocity) * wander_distance;

		// Radius of our imaginary circle
		const float wander_radius = 1.0f;			

		// Get random point
		const int random_point = rand() % 45;
		const float theta = 2.0f * 3.1415926f * float(random_point) / float(45);
		// Calculate the x component 
		const float x = wander_radius * cosf(theta);
		// Calculate the y component
		const float y = wander_radius * sinf(theta);							

		target.x += x;
		target.y += y;

		//m_max_speed *= 2.0f;
		seek(target);
		//m_max_speed /= 2.0f;

		m_wander_counter = 2;
	}
	m_wander_counter--;
}

void Vehicle::containment(float width, float height, float d)
{
	glm::vec3 desired = glm::vec3(0.0f, 0.0f, 0.0f);

	if (m_objPosition.x < /*width/2*/ - d)
	{
		desired = glm::vec3(m_max_speed, m_velocity.y, 0.0f);
	}
	else if (m_objPosition.x > width - d) {
		desired = glm::vec3(-m_max_speed, m_velocity.y, 0.0f);
	}

	if (m_objPosition.y < /*height/2*/ - d) {
		desired = glm::vec3(m_velocity.x, m_max_speed, 0.0f);
	}
	else if (m_objPosition.y > height - d) {
		desired = glm::vec3(m_velocity.x, -m_max_speed, 0.0f);
	}

	if (desired != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		desired = glm::normalize(desired);
		desired = desired * m_max_speed;
		glm::vec3 steer = desired - m_velocity;
		limit(steer, m_max_force);
		
		apply_force(steer);
	}
}

glm::vec3 Vehicle::separate(std::vector<Vehicle*>& v_boids)
{
	const float desired_separation = 137.5f;
	glm::vec3 steer = glm::vec3(0, 0, 0);
	int count = 0;
	// Check if any boid in the vector is too close
	for (auto boid : v_boids) 
	{
		float d = glm::length(m_objPosition - boid->GetLocation());
		// If the distance is greater than 0 and less than desired distance
		if ((this != boid) && (d < desired_separation))
		{
			// Calculate vector pointing away from neighbor
			glm::vec3 diff = m_objPosition - boid->GetLocation();
			diff = glm::normalize(diff);
			// Weight by distance
			diff /= d;       
			steer += diff;
			// Keep track of how many
			count++;            
		}
	}
	// Average
	if (count > 0) 
	{
		steer /= static_cast<float>(count);
	}

	// If the vector is greater than 0
	if (glm::length(steer) > 0) 
	{
		// Steering = Desired - Velocity
		steer = glm::normalize(steer);
		steer *= m_max_speed;
		steer -= m_velocity;
		limit(steer, m_max_force);
	}
	return steer;
}

glm::vec3 Vehicle::alignment(std::vector<Vehicle*>& v_boids)
{
	const float neighbor_dist = 75.0f;
	glm::vec3 sum = glm::vec3(0.0f, 0.0f, 0.0f);
	int count = 0;
	for (auto boid : v_boids) 
	{
		const float d = glm::length(m_objPosition - boid->GetLocation());
		if ((this != boid)/* && (d < neighbor_dist)*/)
		{
			sum += boid->m_velocity;
			count++;
		}
	}
	if (count > 0 && sum != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		sum /= static_cast<float>(count);
		sum = glm::normalize(sum);
		sum *= m_max_speed;
		glm::vec3 steer = sum - m_velocity;
		limit(steer, m_max_force);
		return steer;
	}
	else 
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

glm::vec3 Vehicle::cohesion(std::vector<Vehicle*>& v_boids)
{
	const float neighbor_dist = 75.0f;
	glm::vec3 sum = glm::vec3(0.0f, 0.0f, 0.0f);  
	int count = 0;
	for (auto boid : v_boids) 
	{
		float d = glm::length(m_objPosition - boid->GetLocation());
		if ((this != boid) /*&& (d < neighbor_dist)*/) 
		{
			// Add location
			sum += boid->m_objPosition; 
			count++;
		}
	}
	if (count > 0) 
	{
		sum /= static_cast<float>(count);
		// Return the steering force that seeks toward that location
		return get_seek(sum);  
	}
	else 
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void Vehicle::flock(std::vector<Vehicle*>& v_boids)
{
	// Calculate separation
	glm::vec3 sep = separate(v_boids);

	// Calculate alignment
	glm::vec3 ali = alignment(v_boids);
	
	// Calculate cohesion
	glm::vec3 coh = cohesion(v_boids);
	
	// Gives weight to these forces
	sep *= 1.5;
	ali *= 1.0;
	coh *= 1.0;
	// Add the forces to acceleration
	m_max_force *= 1.8f;
	apply_force(sep);
	m_max_force /= 1.8f;
	apply_force(ali);
	apply_force(coh);
}

void Vehicle::lead_following(std::vector<Vehicle*>& v_boids, glm::vec3 target_location, float delta_time)
{
	std::vector<Vehicle*>::iterator it;
	for (it = v_boids.begin(); it < v_boids.end(); ++it)
	{
		// First vehicle in the vector arrive to the target
		if (*it == v_boids[0])
		{
			(*it)->arrive((target_location * 0.91f), delta_time);
		}
		// The rest of the vehicle arrive to the negated velocity of the previous vehicle
		else
		{
			std::vector<Vehicle*>::iterator PrevIt = it - 1;
			(*it)->arrive(((*PrevIt)->GetLocation() - (*PrevIt)->m_velocity * -1.0f), delta_time);
			(*it)->apply_force((*it)->separate(v_boids));
		}
	}
}


