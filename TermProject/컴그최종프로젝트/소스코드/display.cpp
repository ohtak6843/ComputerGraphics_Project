#include "display.h"

Display::Display() {
	cameraPos = glm::vec3(0.0f, 2.0f, 5.0f);
	cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//proj_matrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);
	proj_matrix = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
}


Display::~Display() {

}


void Display::updateSetting(const int _shader) {
	glUseProgram(_shader);

	view_matrix = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	unsigned int viewLocation = glGetUniformLocation(_shader, "viewTransform");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view_matrix[0][0]);

	unsigned int projectionLocation = glGetUniformLocation(_shader, "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &proj_matrix[0][0]);

	unsigned int viewPosLocation = glGetUniformLocation(_shader, "viewPos");
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
}


void Display::rotatePos(const float _degree, glm::vec3 _dir) {
	cameraPos = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::radians(_degree), _dir) * glm::vec4(cameraPos, 1.0f));
}


void Display::translatePos(glm::vec3 _move) {
	cameraPos = glm::vec3(glm::translate(glm::mat4(1.0f), _move) * glm::vec4(cameraPos, 1.0f));
}