#include "display.h"
#include "light.h"

#include <algorithm>


Light::Light() {
	lightPos = { 0.0f, 0.0f, 0.0f };
	lightColor = { 1.0f, 1.0f, 1.0f };
}


Light::~Light() {

}


void Light::setPos(glm::vec3 _position) {
	lightPos = _position;
}


void Light::setColor(glm::vec3 _color) {
	lightColor = _color;
}


void Light::lightUpDown(glm::vec3 _updown) {
	lightColor.x += _updown.x;
	lightColor.y += _updown.y;
	lightColor.z += _updown.z;

	if (lightColor.x < 0.0f) lightColor.x = 0.0f;
	else if (lightColor.x > 1.0f) lightColor.x = 1.0f;

	if (lightColor.y < 0.0f) lightColor.y = 0.0f;
	else if (lightColor.y > 1.0f) lightColor.y = 1.0f;

	if (lightColor.z < 0.0f) lightColor.z = 0.0f;
	else if (lightColor.z > 1.0f) lightColor.z = 1.0f;
}


void Light::updateSetting(const int _shader) {
	glUseProgram(_shader);

	unsigned int lightPosLocation = glGetUniformLocation(_shader, "lightPos");
	glUniform3f(lightPosLocation, lightPos.x, lightPos.y, lightPos.z);

	unsigned int lightColorLocation = glGetUniformLocation(_shader, "lightColor");
	glUniform3f(lightColorLocation, lightColor.r, lightColor.g, lightColor.b);
}


void Light::rotate(float _degree, glm::vec3 _dir) {
	glm::vec4 vec4_pos = { lightPos, 1.0f };
	vec4_pos = glm::rotate(glm::mat4(1.0f), glm::radians(_degree), _dir) * vec4_pos;
	lightPos = glm::vec3(vec4_pos);
}


void Light::translate(glm::vec3 _move){
	lightPos.x += _move.x;
	lightPos.y += _move.y;
	lightPos.z += _move.z;
}