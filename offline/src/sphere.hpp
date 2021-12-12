#ifndef SPHERE
#define SPHERE

#include <glm/glm.hpp>
using namespace glm;

class Sphere
{
private:
	vec3 _pos;
	float _radius;
public:
	Sphere(vec3 pos, float radius)
		:_pos(pos),
		_radius(radius)
	{

	}
	~Sphere(){}
	
	bool Intersect(Ray ray, vec3& point, vec3& norm)
	{
		vec3 oc = ray.origin - _pos;
		float a = dot(ray.dir, ray.dir);
		float half_b = dot(ray.dir, oc);
		float c = dot(oc, oc) - _radius * _radius;
		float discriminant = half_b * half_b - a * c;
		if(discriminant < 0)
		{
			return false;
		}
		else
		{
			float root = sqrtf(discriminant);
			float t = (-half_b - root) / a;
			if(t > 1)
			{
				point = ray.at(t);
				norm = (point - _pos) / _radius;
				return true;
			}
			t = (-half_b + root) / a;
			if(t > 1)
			{
				point = ray.at(t);
				norm = (point - _pos) / _radius;
				return true;
			}
			return false;
		}
	}
	bool Intersect(Ray ray)
	{
		vec3 oc = ray.origin - _pos;
		float a = dot(ray.dir, ray.dir);
		float half_b = dot(ray.dir, oc);
		float c = dot(oc, oc) - _radius * _radius;
		float discriminant = half_b * half_b - a * c;
		if(discriminant < 0)
		{
			return false;
		}
		else
		{
			float root = sqrtf(discriminant);
			float t = (-half_b - root) / a;
			if(t > 1)
			{
				return true;
			}
			t = (-half_b + root) / a;
			if(t > 1)
			{
				return true;
			}
			return false;
		}
	}
};

#endif