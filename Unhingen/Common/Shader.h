#pragma once

#include <string>

class Shader {
	public:
		Shader ( const std::string& shaders );
		Shader ( const std::string& vertex, const std::string& fragment );
		virtual ~Shader ();
	private:
};