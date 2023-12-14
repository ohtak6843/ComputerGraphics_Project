#pragma once
#include "common_functions.h"


#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>


#include <iostream>



class Shader {
private:
	char* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
	unsigned int vertexShader, fragmentShader; //--- ���̴� ��ü

public:
	unsigned int ID;


	Shader();


	Shader(const char* _vertex, const char* _fragment);


	~Shader();


	void make_vertexShader(const char* _vertex);


	void make_fragmentShader(const char* _fragment);


	void make_shaderProgram(const char* _vertex, const char* _fragment);
};