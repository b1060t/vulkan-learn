#ifndef RAY
#define RAY

#include <glm/glm.hpp>
using namespace glm;

class Ray
{
private:
	
public:
	vec3 origin;
	vec3 dir;
	Ray(vec3 origin, vec3 direction);
	~Ray();

	vec3 at(float t);
};

Ray::Ray(vec3 origin, vec3 direction)
	:origin(origin),
	dir(direction)
{
}

Ray::~Ray()
{
}

vec3 Ray::at(float t)
{
	return origin + t * dir;
}

#endif // !RAY