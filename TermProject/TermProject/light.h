#pragma once
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>


class Light {
private:
	glm::vec3 lightPos;
	glm::vec3 lightColor;

public:
	Light();


	~Light();


	void setPos(glm::vec3 _position);


	void setColor(glm::vec3 _color);


	void lightUpDown(glm::vec3 _updown);


	void updateSetting(const int _shader);


	void rotate(float _degree, glm::vec3 _dir);


	void translate(glm::vec3 _move);
};