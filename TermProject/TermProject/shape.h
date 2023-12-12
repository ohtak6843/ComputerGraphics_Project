#pragma once
#include "display.h"
#include "struct.h"

#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include <vector>


class Shape {
private:

protected:
	GLuint vao, vbo[4];
	std::vector<GLfloat> vertex;
	std::vector<GLfloat> normal;
	std::vector<GLfloat> texCoord;
	std::vector<glm::mat4> matrix;

	BB bb;

public:
	std::vector<GLfloat> color;


	Shape();


	Shape(std::vector<GLfloat> _vertex, std::vector<GLfloat> _normal, std::vector<GLfloat> _color, std::vector<GLfloat> _texCoord);


	Shape(const char* _obj);


	~Shape();


	void read_obj(const char* _obj);


	void setColor(glm::vec4 _color);


	void updateBuffer();


	void draw(const int _shader, const int _draw_mode);


	void scale(int _idx, glm::vec3 _size);


	void scale(int _idx, glm::mat4 _mat, glm::vec3 _size);


	void rotate(int _idx, float _degree, glm::vec3 _dir);


	void rotate(int _idx, glm::mat4 _mat, float _degree, glm::vec3 _dir);


	void translate(int _idx, glm::vec3 _move);


	void translate(int _idx, glm::mat4 _mat, glm::vec3 _move);


	void initMatrix();


	void initMatrix(const unsigned int _idx);

	BB get_bb();
};