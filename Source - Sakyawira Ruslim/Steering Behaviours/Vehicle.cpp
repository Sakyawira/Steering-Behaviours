/***********************
  File Name   :   Vehicle.cpp
  Description :   contains definition of Vehicle class which control the steering behaviours of an object
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
#include "Vehicle.h" 
#include <utility>

/***********************
 Description :   Assign shaders, mesh, textures, initial position and direction
 Author      :   Sakyawira Nanda Ruslim
********************/
Vehicle::Vehicle(Shader * _shader, Mesh * _mesh, std::vector<Texture*>& _textures, float _initialX, float _initialY)
{
	shader = _shader;
	mesh = _mesh;
	xPos = _initialX;
	yPos = _initialY;
	textures = _textures;

	objPosition = glm::vec3(xPos, yPos, 0.0f);
	translationMatrix = glm::translate(glm::mat4(), objPosition);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;

	// Pick a start direction (positive / negative)
	int negate = rand() % 2;
	dir = (negate == 0 ? false : true);

	// Pick a start direction (vetical / horizontal)
	negate = rand() % 2;
	vertical = (negate == 0 ? false : true);
}

/***********************
 Description :   Process different behaviours
 Author      :   Sakyawira Nanda Ruslim
********************/
void Vehicle::Process(const Behaviour _steer, std::vector<Vehicle*>& _boids, glm::vec3 _targetLocation, const int _windowWidth, const int _windowHeight, int _playerSize, const float _deltaTime)
{
	switch (_steer) {
	case Behaviour::SEEK:
		Seek(_targetLocation);
		break;
	case Behaviour::ARRIVE:
		Arrive(_targetLocation, _deltaTime);
		break;
	case Behaviour::CONTAINMENT:
		Containment(static_cast<float>(_windowWidth) * 1.4f, static_cast<float>(_windowHeight) * 1.4f, 400.0f * 1.4f);
		break;
	case Behaviour::WANDER:
		Wander(_deltaTime);
		Containment(static_cast<float>(_windowWidth), static_cast<float>(_windowHeight), 400.0f);
		break;
	case Behaviour::FLOCK:
		Flock(_boids);
		Containment(static_cast<float>(_windowWidth), static_cast<float>(_windowHeight), 400.0f);
		break;
	case Behaviour::LEAD_FOLLOWING:
		LeadFollowing(_boids, _targetLocation, _deltaTime);
		break;
	}
	// Update velocity
	velocity += acceleration;
	// Limit speed
	Limit(velocity, maxSpeed);
	objPosition += velocity * _deltaTime;
	// Reset acceleration to 0 each cycle
	acceleration *= 0;
	// Update Model Matrix
	translationMatrix = glm::translate(glm::mat4(), objPosition);
	modelMatrix = translationMatrix * rotationZ * scaleMatrix;
}

/***********************
 Description :   Limits the passed in force to a certain passed in value
 Author      :   Sakyawira Nanda Ruslim
********************/
void Vehicle::Limit(glm::vec3& _vector3, float _maxMagnitude)
{
	if (glm::length(_vector3) > _maxMagnitude) 
	{
		_vector3 = glm::normalize(_vector3);
		_vector3 *= _maxMagnitude;
	}
}

/***********************
 Description :   Apply the force by adding it to the acceleration of the object
 Author      :   Sakyawira Nanda Ruslim
********************/
void Vehicle::ApplyForce(glm::vec3 _force)
{
	acceleration += _force;
}

/***********************
 Description :   Apply a force that moves the vehicle to a certain target
 Author      :   Sakyawira Nanda Ruslim
********************/
void Vehicle::Seek(glm::vec3 _target)
{ 
	ApplyForce(GetSeek(_target));
}

/***********************
 Description :   Calculate a force that moves the vehicle to a certain target
 Author      :   Sakyawira Nanda Ruslim
********************/
glm::vec3 Vehicle::GetSeek(glm::vec3 _target)
{
	// A vector pointing from the location to the target
	glm::vec3 desired = _target - objPosition;  
    // Normalize desired and scale to maximum speed
	if (glm::length(desired) > 0.0f)
	{
		desired = glm::normalize(desired);
	}
	desired *= maxSpeed;
	// Steering = Desired minus velocity
	glm::vec3 steer = desired - velocity;
	// Limit to maximum steering force
	Limit(steer, maxForce);  
	return steer;
}

/***********************
 Description :   Apply a force that moves the vehicle to a certain target, slowing it down as it approaches the target
 Author      :   Sakyawira Nanda Ruslim
********************/
void Vehicle::Arrive(glm::vec3 _target, float _deltaTime)
{
	ApplyForce(GetArrive(_target, _deltaTime));
}

/***********************
 Description :   Calculate a force that moves the vehicle to a certain target, slowing it down as it approaches the target
 Author      :   Sakyawira Nanda Ruslim
********************/
glm::vec3 Vehicle::GetArrive(glm::vec3 _target, float _deltaTime)
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
	if (d < maxSpeed * 50.0f)
	{
		const float m = 0 + (maxSpeed - 0) * ((d - 0) / (maxSpeed * 50.0f - 0));
		if (d <= maxSpeed * 15.0f)
		{
			desired *= (glm::floor(m));
		}
		else
		{
			desired *= (glm::ceil(m));
		}
	}
	else
	{
		desired *= maxSpeed;
	}
	// Steering = Desired minus Velocity
	glm::vec3 steer = desired - velocity;
	Limit(steer, (maxForce * maxSpeed));  // Limit to maximum steering force
	return steer;
}

/***********************
 Description :   Apply a counter force when the vehicle approach the border of the map (defined by highest point, right most point, and the width/height of the bounding box)
 Author      :   Sakyawira Nanda Ruslim
********************/
void Vehicle::Containment(float _rightMost, float _topMost, float _d)
{
	glm::vec3 desired = glm::vec3(0.0f, 0.0f, 0.0f);
	if (objPosition.x < -_d)
	{
		desired = glm::vec3(maxSpeed, velocity.y, 0.0f);
	}
	else if (objPosition.x > _rightMost - _d) {
		desired = glm::vec3(-maxSpeed, velocity.y, 0.0f);
	}
	if (objPosition.y < -_d) {
		desired = glm::vec3(velocity.x, maxSpeed, 0.0f);
	}
	else if (objPosition.y > _topMost - _d) {
		desired = glm::vec3(velocity.x, -maxSpeed, 0.0f);
	}
	if (desired != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		desired = glm::normalize(desired);
		desired = desired * maxSpeed;
		glm::vec3 steer = desired - velocity;
		Limit(steer, maxForce);
		ApplyForce(steer);
	}
}

/***********************
 Description :   Calculates random position around the object to seek towards, and then seek to it
 Author      :   Sakyawira Nanda Ruslim
********************/
void Vehicle::Wander(float _deltaTime)
{	
	if (velocity == glm::vec3(0.0f, .0f, 0.0f))
	{
		velocity = glm::vec3(0.0f, 0.1f, 0.0f);
	}
	// Distance from vehicle to imaginary circle"
	const float wander_distance = 8.0f;         
	glm::vec3 target = objPosition + glm::normalize(velocity) * wander_distance;
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
	Seek(target);
}

/***********************
 Description :   Calculate a force that separate the vehicle from all other vehicles in the group, make them not clashiing in the same space
 Author      :   Sakyawira Nanda Ruslim
********************/
glm::vec3 Vehicle::Separate(std::vector<Vehicle*>& _boids, const float _desiredSeparation)
{
	glm::vec3 steer = glm::vec3(0, 0, 0);
	int count = 0;
	// Check if any boid in the vector is too close
	for (auto boid : _boids) 
	{
		float d = glm::length(objPosition - boid->GetPosition());
		// If the distance less than desired distance and is greater than 0
		if ((this != boid) && (d < _desiredSeparation) && (d > 0.0f))
		{
			// Calculate vector pointing away from neighbor
			glm::vec3 diff = objPosition - boid->GetPosition();
			diff = glm::normalize(diff);
			// Weight by distance
			diff /= d;
			// Add to the total
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
		steer *= maxSpeed;
		steer -= velocity;
		Limit(steer, maxForce);
	}
	return steer;
}

/***********************
 Description :   Calculate a force that keeps the vehicle from straying a way too much from the group
 Author      :   Sakyawira Nanda Ruslim
********************/
glm::vec3 Vehicle::Cohesion(std::vector<Vehicle*>& _boids)
{
	const float neighbor_dist = 75.0f;
	glm::vec3 sum = glm::vec3(0.0f, 0.0f, 0.0f);
	int count = 0;
	for (auto boid : _boids)
	{
		float d = glm::length(objPosition - boid->GetPosition());
		if ((this != boid))
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

/***********************
 Description :   Calculates a force that makes the vehicle to move towards the average direction of all other vehicles in the group
 Author      :   Sakyawira Nanda Ruslim
********************/
glm::vec3 Vehicle::Alignment(std::vector<Vehicle*>& _boids)
{
	const float neighbor_dist = 75.0f;
	glm::vec3 sum = glm::vec3(0.0f, 0.0f, 0.0f);
	int count = 0;
	for (auto boid : _boids) 
	{
		const float d = glm::length(objPosition - boid->GetPosition());
		if ((this != boid))
		{
			sum += boid->velocity;
			count++;
		}
	}
	if (count > 0 && sum != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		sum /= static_cast<float>(count);
		sum = glm::normalize(sum);
		sum *= maxSpeed;
		glm::vec3 steer = sum - velocity;
		Limit(steer, maxForce);
		return steer;
	}
	else 
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

/***********************
 Description :   Calculates and scales separate, alignment, and cohesion. Then apply it to the vehicle.
 Author      :   Sakyawira Nanda Ruslim
********************/
void Vehicle::Flock(std::vector<Vehicle*>& _boids)
{
	// Calculate separation
	glm::vec3 sep = Separate(_boids);
	// Calculate alignment
	glm::vec3 ali = Alignment(_boids);
	// Calculate cohesion
	glm::vec3 coh = Cohesion(_boids);
	// Gives weight to these forces
	sep *= 1.5;
	ali *= 1.0;
	coh *= 1.0;

	// Add the forces to acceleration
	ApplyForce(sep);
	ApplyForce(ali);
	ApplyForce(coh);
}

/***********************
 Description :   Makes the vehicle to Arrive towards the previous vehicle in the vector or the player if it is the first vehicle in the vector
 Author      :   Sakyawira Nanda Ruslim
********************/
void Vehicle::LeadFollowing(std::vector<Vehicle*>& _boids, glm::vec3 _targetLocation, float _deltaTime)
{
	std::vector<Vehicle*>::iterator it;
	it = _boids.begin();
	// First vehicle in the vector arrive to the target
	if (this == (*it)) 
	{
		Arrive((_targetLocation * 0.9f), _deltaTime);
	}
	else 
	{
		for (it = _boids.begin() + 1; it < _boids.end(); ++it)
		{
			// The rest of the vehicle arrive to the negated velocity of the previous vehicle
			if (this == (*it))
			{
				std::vector<Vehicle*>::iterator PrevIt = it - 1;
				(*it)->Arrive(((*PrevIt)->GetPosition() * 0.9f /*- (*PrevIt)->velocity * -1.0f*/), _deltaTime);
			}
		}
	}
	// Calculate separation
	glm::vec3 sep = Separate(_boids);
	sep *= 1.5f;
	ApplyForce(sep);
}