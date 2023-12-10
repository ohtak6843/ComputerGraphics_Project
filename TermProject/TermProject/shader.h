#pragma once
#include "common_functions.h"


#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>


#include <iostream>



class Shader {
private:
	char* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
	unsigned int vertexShader, fragmentShader; //--- 세이더 객체

public:
	unsigned int ID;


	Shader();


	Shader(const char* _vertex, const char* _fragment);


	~Shader();


	void make_vertexShader(const char* _vertex);


	void make_fragmentShader(const char* _fragment);


	void make_shaderProgram(const char* _vertex, const char* _fragment);
};