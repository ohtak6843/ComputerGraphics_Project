#pragma once
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>


class Display {
private:
	glm::mat4 view_matrix = glm::mat4(1.0f);
	glm::mat4 proj_matrix;  // ���� ��ȯ

public:
	glm::vec3 cameraPos;  //---ī�޶���ġ
	glm::vec3 cameraDirection;  //---ī�޶�ٶ󺸴¹���
	glm::vec3 cameraUp;  //---ī�޶����ʹ���

	Display();


	~Display();


	void updateSetting(const int _shader);


	void rotatePos(const float _degree, glm::vec3 _dir);


	void translatePos(glm::vec3 _move);
};