#pragma once
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>


class Display {
private:
	glm::mat4 view_matrix = glm::mat4(1.0f);
	glm::mat4 proj_matrix;  // 투영 변환

public:
	glm::vec3 cameraPos;  //---카메라위치
	glm::vec3 cameraDirection;  //---카메라바라보는방향
	glm::vec3 cameraUp;  //---카메라위쪽방향

	Display();


	~Display();


	void updateSetting(const int _shader);


	void rotatePos(const float _degree, glm::vec3 _dir);


	void translatePos(glm::vec3 _move);
};