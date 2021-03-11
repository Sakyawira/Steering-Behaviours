// Path Following
// Daniel Shiffman <http://www.shiffman.net>
// The Nature of Code
// Library Includes
#include <vector>

// Dependency Includes
#include <glew.h>
#include <gtc/type_ptr.hpp>
#include <glm.hpp>
#include <mat4x2.hpp>

class Path /*: public GameObject*/
{

public:
	Path() = default;
	~Path() = default;

	// Add a point to the path
	void addPoint(float x, float y)
	{
		points.emplace_back(x, y, 0.0f);
	}

	// Draw the path
	void display()
	{

	}

private:
	
	// A Path is an arraylist of points (PVector objects)
	std::vector<glm::vec3> points;
	// A path has a radius, i.e how far is it ok for the boid to wander off
	float radius = 20;
};



