#ifndef CAMERA
#define CAMERA 

#include <glm/glm.hpp>
using namespace glm;

class Camera
{
private:
	vec3 _pos;
public:
	Camera(vec3 origin);
	~Camera();

	vec3 Position();
};

Camera::Camera(vec3 originPos)
	:_pos(originPos)
{
}

Camera::~Camera()
{
}

vec3 Camera::Position()
{
	return _pos;
}

#endif // !CAMERA