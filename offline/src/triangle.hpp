#ifndef TRIANGLE
#define TRIANGLE

#include <glm/glm.hpp>
#include <vector>
#include <cassert>
//#include <iostream>
using namespace glm;

class Triangle
{
private:
	mat3 _v;
	vec3 _norm;
public:
	Triangle(std::vector<vec3> v)
	{
		assert(v.size() >= 3);
		_v = mat3(v[0], v[1], v[2]);
		_norm = normalize(cross(_v[1] - _v[0], _v[2] - _v[0]));
	}

	bool Intersect(Ray ray, vec3& point, vec3& norm)
	{
		vec3 e1 = _v[1] - _v[0];
		vec3 e2 = _v[2] - _v[0];
		
		vec3 p = cross(ray.dir, e2);
		float determinant = dot(p, e1);
		vec3 t;
		if(determinant > 0)
		{
			t = ray.origin - _v[0];
		}
		else
		{
			t = _v[0] - ray.origin;
			determinant = -determinant;
		}
		if(determinant < 0.0001f)
		{
			return false;
		}

		float beta = dot(p, t);
		if(beta < 0 || beta > determinant)
		{
			return false;
		}

		vec3 q = cross(t, e1);
		float gamma = dot(q, ray.dir);
		if(gamma < 0 || gamma + beta > determinant)
		{
			return false;
		}

		float tt = dot(q, e2) / determinant;
		if(tt <= 1)
		{
			return false;
		}
		point = ray.at(tt);
		norm = _norm;
		return true;
	}

	bool Intersect(Ray ray)
	{
		// https://www.cnblogs.com/samen168/p/5162337.html
		vec3 e1 = _v[1] - _v[0];
		vec3 e2 = _v[2] - _v[0];
		
		vec3 p = cross(ray.dir, e2);
		float determinant = dot(p, e1);
		vec3 t;
		if(determinant > 0)
		{
			t = ray.origin - _v[0];
		}
		else
		{
			t = _v[0] - ray.origin;
			determinant = -determinant;
		}
		if(determinant < 0.0001f)
		{
			return false;
		}

		float beta = dot(p, t);
		if(beta < 0 || beta > determinant)
		{
			return false;
		}

		vec3 q = cross(t, e1);
		float gamma = dot(q, ray.dir);
		if(gamma < 0 || gamma + beta > determinant)
		{
			return false;
		}

		float tt = dot(q, e2) / determinant;
		if(tt <= 1)
		{
			return false;
		}
		return true;
	}
};

#endif