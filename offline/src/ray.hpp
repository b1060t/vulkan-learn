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
	Ray(vec3 origin, vec3 direction)
		:origin(origin),
		dir(direction)
	{

	}
	~Ray(){}

	vec3 at(float t)
	{
		return origin + t * dir;
	}
};

#endif // !RAY