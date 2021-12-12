#ifndef CAMERA
#define CAMERA 

#include <glm/glm.hpp>
using namespace glm;

class Camera
{
private:
	vec3 _pos;
public:
	Camera(vec3 originPos)
		:_pos(originPos)
	{

	}
	~Camera(){}

	vec3 Position()
	{
		return _pos;
	}
};

#endif // !CAMERA