#include <iostream>
#include <memory>
#include <vector>

#include "kompute/Kompute.hpp"

const std::vector<unsigned char> comp = {
	#include "test.comp.spv.h"
};

int main()
{
	kp::Manager mgr;
	return 0;
}