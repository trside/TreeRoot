#include "trpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <fstream>

namespace tr {
	OpenGLShader::OpenGLShader(const std::string& filePath)
	{
		m_RendererID = CompileShader(Preprocess(ReadFile(filePath)));
		size_t lastSlash = filePath.find_last_of("/\\") + 1;
		size_t lastDot = filePath.rfind('.');
		m_Name = filePath.substr(lastSlash, (lastDot != std::string::npos ? lastDot : filePath.size() - 1) - lastSlash);
	}
	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		m_RendererID = CompileShader(Preprocess(vertexSource, fragmentSource));
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationsCache.find(name) != m_UniformLocationsCache.end())
			return m_UniformLocationsCache[name];

		int location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			TR_CORE_WARN("{0} Shader Uniform: {1} is not exist.", GetName(), name);
		m_UniformLocationsCache.emplace(name, location);

		return location;
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath)
	{
		std::string result;
		std::ifstream file(filePath, std::ifstream::in | std::ifstream::binary);
		if (file)
		{
			file.seekg(0, file.end);
			result.resize(file.tellg());
			file.seekg(0, file.beg);

			file.read(result.data(), result.size());
			file.close();
		}
		else
		{
			TR_CORE_WARN("Failed to load shader filepath: {0}", filePath);
		}

		return result;
	}

	std::unordered_map<unsigned int, std::string> OpenGLShader::Preprocess(const std::string& source)
	{
		std::unordered_map<unsigned int, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);

		size_t pos = 0;
		std::string type;
		while (pos != std::string::npos)
		{
			pos = source.find_first_not_of("\r\n", pos) + typeTokenLength;
			pos = source.find_first_not_of(' ', pos);

			size_t eol = source.find_first_of("\r\n", pos);	// find_xxx_of 用于查找指定字符串中的任意一个字符而非整个字符串，找到任意字符即返回位置
			type = source.substr(pos, eol - pos);
			TR_CORE_ASSERT(GetShaderTypeFromString(type), "Unknown ShaderType!");

			size_t begin = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, begin);

			shaderSources[GetShaderTypeFromString(type)] = source.substr(begin, (pos == std::string::npos ? source.size() : pos) - begin);
			//TR_CORE_INFO("{0}:\n{1}", type, shaderSources[GetShaderTypeFromString(type)]);
		}

		return shaderSources;
	}

	std::unordered_map<unsigned int, std::string> OpenGLShader::Preprocess(const std::string& vertexSource, const std::string& fragmentSource)
	{
		std::unordered_map<unsigned int, std::string> shaderSources;
		shaderSources[GetShaderTypeFromString("vertex")] = vertexSource;
		shaderSources[GetShaderTypeFromString("fragment")] = fragmentSource;

		return shaderSources;
	}

	unsigned int OpenGLShader::CompileShader(const std::unordered_map<unsigned int, std::string>& shaderSources)
	{
		std::array<unsigned int, 2> shaderIDs;
		unsigned int shaderIDsIndex = 0;

		for (auto& shaderSource : shaderSources)
		{
			// Create an empty shader handle
			GLuint shader = glCreateShader(shaderSource.first);

			// Send the shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* source = (const GLchar*)shaderSource.second.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// Use the infoLog as you see fit.
				TR_CORE_ERROR("OpenGL Shader: {0}", infoLog.data());
				TR_CORE_ASSERT(false, "Failed to compile shader!");

				break;
			}
			shaderIDs[shaderIDsIndex++] = shader;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();

		// Attach our shaders to our program
		for (auto id : shaderIDs)
			glAttachShader(program, id);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			// Use the infoLog as you see fit.
			TR_CORE_ERROR("OpenGL Shader: {0}", infoLog.data());
			TR_CORE_ASSERT(false, "Failed to link shaders!");

			// In this simple program, we'll just leave
			return 0;
		}

		// Always detach shaders after a successful link.
		for (auto id : shaderIDs)
			glDetachShader(program, id);

		// Shader compilation is successful.

		return program;
	}

	unsigned int OpenGLShader::GetShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		else if (type == "fragment")
			return GL_FRAGMENT_SHADER;
		return 0;
	}

	void OpenGLShader::SetShaderParameter(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetShaderParameter(const std::string& name, const glm::vec2& vector2)
	{
		glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(vector2));
	}

	void OpenGLShader::SetShaderParameter(const std::string& name, const glm::vec4& vector4)
	{
		glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(vector4));
	}

	void OpenGLShader::SetShaderParameter(const std::string& name, const glm::mat4& matrix4f)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix4f));
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

}