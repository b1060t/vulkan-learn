#ifndef SCREEN
#define SCREEN

#include <glm/glm.hpp>
#include <camera.hpp>
#include <ray.hpp>
using namespace glm;

class Screen
{
private:
	vec2 _size;
	vec3 _pos;
	uint32_t _pixelWidth;
	uint32_t _pixelHeight;
public:
	Screen(vec2 size, uint32_t pwidth, uint32_t pheight, vec3 originPos);
	~Screen();

	Ray Pixel2RayDirection(uint32_t x, uint32_t y, Camera cam);
};

Screen::Screen(vec2 size, uint32_t pwidth, uint32_t pheight, vec3 originPos)
	:_size(size),
	_pos(originPos),
	_pixelWidth(pwidth),
	_pixelHeight(pheight)
{
}

Screen::~Screen()
{
}

Ray Screen::Pixel2RayDirection(uint32_t x, uint32_t y, Camera cam)
{
	float u = _pos.x + _size.x * (x + 0.5f) / _pixelWidth;
	float v = _pos.y + _size.y * (y + 0.5f) / _pixelHeight;
	vec3 dir = vec3(u, v, _pos.z) - cam.Position();
	return Ray(cam.Position(), dir);
}

#endif // !SCREEN