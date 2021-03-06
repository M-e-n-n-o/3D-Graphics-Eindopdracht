#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"

namespace shaders
{
	ShaderProgram::ShaderProgram(std::string& vertexShader, std::string& fragmentShader)
	{
		vertexShaderID = loadShader(vertexShader, GL_VERTEX_SHADER);
		fragmentShaderID = loadShader(fragmentShader, GL_FRAGMENT_SHADER);
		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
	}

	void ShaderProgram::init()
	{
		setAttributes();
		glLinkProgram(programID);
		glValidateProgram(programID);
		getAllUniformLocations();
	}

	// This method will start the shaders
	void ShaderProgram::start() const
	{
		glUseProgram(programID);
	}

	// This method will stop the shaders
	void ShaderProgram::stop() const
	{
		glUseProgram(0);
	}

	// This method will clean up all the shaders
	void ShaderProgram::cleanUp() const
	{
		stop();
		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(programID);
	}

	// This method sets an input variabele into the shaders
	void ShaderProgram::setAttribute(const GLuint attribute, const char* variableName) const
	{
		glBindAttribLocation(programID, attribute, variableName);
	}

	void ShaderProgram::loadFloat(GLuint location, GLfloat value) const
	{
		glUniform1f(location, value);
	}

	void ShaderProgram::loadInt(GLuint location, GLint value) const
	{
		glUniform1i(location, value);
	}

	void ShaderProgram::loadVector(GLuint location, glm::vec3 vector) const
	{
		glUniform3fv(location, 1, glm::value_ptr(vector));
	}

	void ShaderProgram::loadVector(GLuint location, glm::vec4 vector) const
	{
		glUniform4fv(location, 1, glm::value_ptr(vector));
	}

	void ShaderProgram::loadMatrix(GLuint location, glm::mat4 matrix) const
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	GLuint ShaderProgram::getUniformLocation(const GLchar* uniformName) const
	{
		return glGetUniformLocation(programID, uniformName);
	}

	// This method loads a shader into openGL
	GLuint ShaderProgram::loadShader(const std::string& shaderString, const GLuint type) const
	{
		const char* shaderText = shaderString.c_str();
		const GLuint shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &shaderText, NULL);
		glCompileShader(shaderID);
		
		GLint succes = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succes);
		if (succes == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
			for (std::vector<GLchar>::const_iterator i = errorLog.begin(); i != errorLog.end(); ++i)
			{
				std::cout << *i;
			}
			std::cout << std::endl;
			std::cerr << "Could not compile shader" << std::endl;
			cleanUp();
			std::exit(-1);
		}

		return shaderID;
	}
}
