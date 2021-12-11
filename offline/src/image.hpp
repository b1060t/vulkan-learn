#ifndef IMAGE
#define IMAGE

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <common.hpp>

void write_ppm(
	const std::string & filename,
	const std::vector<unsigned char> & data,
	const int width,
	const int height,
	const int num_channels)
{
	std::ofstream file;
	file.open(filename);
	if(num_channels == 3)
	{
		file << "P3" << std::endl;
		file << width << " " << height << std::endl;
		for(int h = 0; h < height; h++)
		{
			for(int w = 0; w < width; w++)
			{
				int ptr = 3 * (width * h + w);
				file << std::to_string(data[ptr+2]) << " " << std::to_string(data[ptr]) << " " << std::to_string(data[ptr+1]) << " ";
			}
			file << std::endl;
		}
	}
	else
	{
		file << "P2" << std::endl;
		file << width << " " << height << std::endl;
		for(int h = 0; h < height; h++)
		{
			for(int w = 0; w < width; w++)
			{
				int ptr = width * h + w;
				file << std::to_string(data[ptr]) << " ";
			}
			file << std::endl;
		}
	}
	file.close();
}

void gl_render(
	const std::vector<unsigned char> & data,
	const int width,
	const int height)
{
	tide::Context context("Result", width, height);
	glfwSetInputMode(context.getWindow(), GLFW_STICKY_KEYS, GL_TRUE);
	std::string vert = R"(#version 330 core
					layout(location = 0) in vec2 vert_pos;
					layout(location = 1) in vec2 tex_pos;

					out vec2 texPos;

					void main()
					{
					    gl_Position = vec4(vert_pos.x, vert_pos.y, 0.0f, 1.0f);
					    texPos = tex_pos;
					})";

	std::string frag = R"(#version 330 core

					in vec2 texPos;

					out vec4 fragColor;

					uniform sampler2D tex;

					uniform float width;
					uniform float height;

					void main()
					{
					    fragColor = texture(tex, texPos);
					})";

	tide::Shader tex_shader(vert, frag);
	tide::Element element(const_cast<GLfloat*>(&tide::ImageVertices[0]), const_cast<GLint*>(&tide::ImageIndices[0]), 16*sizeof(GLfloat), 6*sizeof(GLint), tide::TWOD_TEXTURE_ATTR);
	element.attachShader(&tex_shader);
	element.setClearFlag(GL_COLOR_BUFFER_BIT);
	tide::Texture texture(data, width, height);
	element.texdic["tex"] = texture.handle;
	do
	{
		element.render();
		context.loop();
	}
	while(context.shouldClose(GLFW_KEY_ESCAPE));
}


#endif