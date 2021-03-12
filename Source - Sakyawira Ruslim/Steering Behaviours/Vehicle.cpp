#include "Vehicle.h"
#include <iostream>
#include <chrono>
#include <ctime>    
#include <utility>

Vehicle::Vehicle(Shader * _shader, Mesh * _mesh, std::vector<Texture*>& _textures, float _initial_x, float _initial_y)
{
	auto start = std::chrono::system_clock::now();

	std::time_t t = std::chrono::system_clock::to_time_t(start);

	std::time_t* iTime = new time_t(t);

	srand(time(iTime));

	delete iTime;

	shader = _shader;
	mesh = _mesh;
	xPos = _initial_x;
	yPos = _initial_y;
	// This creates a copy (even though was passed a s a reference) and therefore did not work
	// m_camera = _camera;
	textures = _textures;

	objPosition = glm::vec3(xPos, yPos, 0.0f);
	translationMatrix = glm::translate(glm::mat4(), objPosition);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;

	// Pick a start direction (positive / negative)
	int negate = rand() % 2;
	m_bool_dir = (negate == 0 ? false : true);

	// Pick a start direction (vetical / horizontal)
	negate = rand() % 2;
	m_bool_vertical = (negate == 0 ? false : true);
}

void Vehicle::Process(const Behaviour steer, std::vector<Vehicle*>& v_boids, glm::vec3 target_location, const int window_width, const int window_height, int player_size, const float delta_time)
{
	if (steer == SEEK)
	{
		Seek(target_location);
	}

	else if (steer == ARRIVE)
	{
		Arrive(target_location, delta_time);
	}

	else if (steer == CONTAINMENT)
	{
		Containment(static_cast<float>(window_width)* 1.4f, static_cast<float>(window_height)* 1.4f, 400.0f* 1.4f);
	}

	else if (steer == WANDER)
	{
		Wander(delta_time);
		m_max_force *= 1.4f;
		Containment(static_cast<float>(window_width) , static_cast<float>(window_height), 400.0f );
		m_max_force /= 1.4f;
	}

	else if (steer == FLOCK)
	{
		m_max_force *= 1.2f;
		Containment(static_cast<float>(window_width), static_cast<float>(window_height), 400.0f);
		m_max_force /= 1.2f;
		Flock(v_boids);
	}

	else if (steer == LEAD_FOLLOWING)
	{
		LeadFollowing(v_boids, target_location, delta_time);
	}
	// Update velocity
	m_velocity += m_acceleration;
	
	// Limit speed
	Limit(m_velocity, m_max_speed);
	
	objPosition += m_velocity * delta_time;
	
	// Reset acceleration to 0 each cycle
	m_acceleration *= 0;

	// Update Model Matrix
	translationMatrix = glm::translate(glm::mat4(), objPosition);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;
}

void Vehicle::RandomOn()
{
	m_bool_random_move = true;
}

void Vehicle::Limit(glm::vec3& _vector3, float _maxMagnitude)
{
	if (glm::length(_vector3) > _maxMagnitude) 
	{
		_vector3 = glm::normalize(_vector3);
		_vector3 *= _maxMagnitude;
	}
}

void Vehicle::ApplyForce(glm::vec3 _force)
{
	m_acceleration += _force;
}

void Vehicle::Seek(glm::vec3 _target)
{
	// A vector pointing from the location to the target
	glm::vec3 desired = _target - objPosition;  

   // Normalize desired and scale to maximum speed
	if (glm::length(desired) > 0.0f)
	{
		desired = glm::normalize(desired);
	}
	
	desired *= m_max_speed;
	
	// Steering = Desired minus velocity
	glm::vec3 steer = desired - m_velocity;

	// Limit to maximum steering force
	Limit(steer,m_max_force);  

	ApplyForce(steer);
}

glm::vec3 Vehicle::GetSeek(glm::vec3 _target)
{
	// A vector pointing from the location to the target
	glm::vec3 desired = _target - objPosition;  

   // Normalize desired and scale to maximum speed
	if (glm::length(desired) > 0.0f)
	{
		desired = glm::normalize(desired);
	}

	desired *= m_max_speed;

	// Steering = Desired minus velocity
	glm::vec3 steer = desired - m_velocity;

	// Limit to maximum steering force
	Limit(steer, m_max_force);  
	
	return steer;
}

void Vehicle::Arrive(glm::vec3 _target, float delta_time)
{
	// A vector pointing from the location to the target
	glm::vec3 desired = _target - objPosition;

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
	Limit(steer, (m_max_force * m_max_speed));  
	ApplyForce(steer);
}

glm::vec3 Vehicle::GetArrive(glm::vec3 _target, float delta_time)
{
	// A vector pointing from the location to the target
	glm::vec3 desired = _target - objPosition;

	
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
	Limit(steer, (m_max_force * m_max_speed));  // Limit to maximum steering force
	return steer;
}

void Vehicle::Wander(float delta_time)
{	
	if (m_velocity == glm::vec3(0.0f, .0f, 0.0f))
	{
		m_velocity = glm::vec3(0.0f, 0.1f, 0.0f);
	}
	
	/*if (m_wander_counter == 0)
	{*/
		// Distance from vehicle to imaginary circle"
		const float wander_distance = 8.0f;         
		glm::vec3 target = objPosition + glm::normalize(m_velocity) * wander_distance;

		// Radius of our imaginary circle
		const float wander_radius = 1.0f;			

		// Get random point

		const int random_point = rand() % 45;

		std::cout << random_point << std::endl;

		const float theta = 2.0f * 3.1415926f * float(random_point) / float(45);
		// Calculate the x component 
		const float x = wander_radius * cosf(theta);
		// Calculate the y component
		const float y = wander_radius * sinf(theta);							

		target.x += x;
		target.y += y;

		//m_max_speed *= 2.0f;
		Seek(target);
		//m_max_speed /= 2.0f;

	//	m_wander_counter = 2;
	//}
	//m_wander_counter--;
}

void Vehicle::Containment(float width, float height, float d)
{
	glm::vec3 desired = glm::vec3(0.0f, 0.0f, 0.0f);

	if (objPosition.x < /*width/2*/ - d)
	{
		desired = glm::vec3(m_max_speed, m_velocity.y, 0.0f);
	}
	else if (objPosition.x > width - d) {
		desired = glm::vec3(-m_max_speed, m_velocity.y, 0.0f);
	}

	if (objPosition.y < /*height/2*/ - d) {
		desired = glm::vec3(m_velocity.x, m_max_speed, 0.0f);
	}
	else if (objPosition.y > height - d) {
		desired = glm::vec3(m_velocity.x, -m_max_speed, 0.0f);
	}

	if (desired != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		desired = glm::normalize(desired);
		desired = desired * m_max_speed;
		glm::vec3 steer = desired - m_velocity;
		Limit(steer, m_max_force);
		
		ApplyForce(steer);
	}
}

glm::vec3 Vehicle::Seperate(std::vector<Vehicle*>& v_boids)
{
	const float desired_separation = 137.5f;
	glm::vec3 steer = glm::vec3(0, 0, 0);
	int count = 0;
	// Check if any boid in the vector is too close
	for (auto boid : v_boids) 
	{
		float d = glm::length(objPosition - boid->GetLocation());
		// If the distance is greater than 0 and less than desired distance
		if ((this != boid) && (d < desired_separation))
		{
			// Calculate vector pointing away from neighbor
			glm::vec3 diff = objPosition - boid->GetLocation();
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
		Limit(steer, m_max_force);
	}
	return steer;
}

glm::vec3 Vehicle::Alignment(std::vector<Vehicle*>& v_boids)
{
	const float neighbor_dist = 75.0f;
	glm::vec3 sum = glm::vec3(0.0f, 0.0f, 0.0f);
	int count = 0;
	for (auto boid : v_boids) 
	{
		const float d = glm::length(objPosition - boid->GetLocation());
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
		Limit(steer, m_max_force);
		return steer;
	}
	else 
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

glm::vec3 Vehicle::Cohesion(std::vector<Vehicle*>& v_boids)
{
	const float neighbor_dist = 75.0f;
	glm::vec3 sum = glm::vec3(0.0f, 0.0f, 0.0f);  
	int count = 0;
	for (auto boid : v_boids) 
	{
		float d = glm::length(objPosition - boid->GetLocation());
		if ((this != boid) /*&& (d < neighbor_dist)*/) 
		{
			// Add location
			sum += boid->objPosition; 
			count++;
		}
	}
	if (count > 0) 
	{
		sum /= static_cast<float>(count);
		// Return the steering force that seeks toward that location
		return GetSeek(sum);  
	}
	else 
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

void Vehicle::Flock(std::vector<Vehicle*>& v_boids)
{
	// Calculate separation
	glm::vec3 sep = Seperate(v_boids);

	// Calculate alignment
	glm::vec3 ali = Alignment(v_boids);
	
	// Calculate cohesion
	glm::vec3 coh = Cohesion(v_boids);
	
	// Gives weight to these forces
	sep *= 1.5;
	ali *= 1.0;
	coh *= 1.0;
	// Add the forces to acceleration
	m_max_force *= 1.8f;
	ApplyForce(sep);
	m_max_force /= 1.8f;
	ApplyForce(ali);
	ApplyForce(coh);
}

void Vehicle::LeadFollowing(std::vector<Vehicle*>& v_boids, glm::vec3 target_location, float delta_time)
{
	std::vector<Vehicle*>::iterator it;
	for (it = v_boids.begin(); it < v_boids.end(); ++it)
	{
		// First vehicle in the vector arrive to the target
		if (*it == v_boids[0])
		{
			(*it)->Arrive((target_location * 0.91f), delta_time);
		}
		// The rest of the vehicle arrive to the negated velocity of the previous vehicle
		else
		{
			std::vector<Vehicle*>::iterator PrevIt = it - 1;
			(*it)->Arrive(((*PrevIt)->GetLocation() - (*PrevIt)->m_velocity * -1.0f), delta_time);
			(*it)->ApplyForce((*it)->Seperate(v_boids));
		}
	}
}


