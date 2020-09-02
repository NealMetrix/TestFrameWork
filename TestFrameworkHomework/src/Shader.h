#pragma once
#include<iostream>
#include<unordered_map>/*this is just a cache map which we will use to improve the efficiency of our getUniform location function*/
#include"glm/gtc/matrix_transform.hpp"
struct shadeComponents
{
	std::string Vertexsource;
	std::string Fragmentsource;
};
class shaders
{
private:
	const std::string m_filepath;
	unsigned int m_rendererID;
	std::unordered_map<std::string, int> m_uniformLocationCache;
public:
	shaders(const std::string& filepath);
	~shaders();

	void bind()const;
	void unbind()const;

	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name,float v0,float v1,float v2,float v3);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	shadeComponents parseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int CreateShader(const std::string& vertexShade, const std::string& fragmentShade);

	unsigned int getUniformLocation(const std::string& name);
};