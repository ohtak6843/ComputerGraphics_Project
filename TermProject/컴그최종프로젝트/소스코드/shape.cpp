#include "shape.h"

#include <iostream>
#include <fstream>
#include <string>


Shape::Shape() {
	vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

	bb = { 0 };
}


Shape::Shape(std::vector<GLfloat> _vertex, std::vector<GLfloat> _normal, std::vector<GLfloat> _color, std::vector<GLfloat> _texCoord) {
	vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

	vertex = _vertex;
	normal = _normal;
	color = _color;
	texCoord = _texCoord;

	bb = { 0 };
}


Shape::Shape(const char* _obj) {
	vao = vbo[0] = vbo[1] = vbo[2] = NULL;

	Shape::read_obj(_obj);

	bb = { 0 };
}


Shape::~Shape() {
	if (vao != NULL) {
		glDeleteVertexArrays(1, &vao);
		glDeleteVertexArrays(3, &vbo[0]);
	}
}


void Shape::read_obj(const char* _obj) {
	std::ifstream file(_obj);
	std::string line;

	if (!file.is_open()) {
		std::cerr << "ERROR: file open failed named \n" << _obj << std::endl;
		return;
	}

	std::vector<GLfloat> vList;
	std::vector<GLfloat> vtList;
	std::vector<GLfloat> vnList;
	std::vector<GLuint> v_idx_List;
	std::vector<GLuint> vt_idx_List;
	std::vector<GLuint> vn_idx_List;

	while (std::getline(file, line)) {

		if (line.substr(0, 2) == "v ") {
			float vertices[3] = {};
			sscanf_s(line.c_str(), "v %f %f %f", &vertices[0], &vertices[1], &vertices[2]);

			for (auto& _vertex : vertices)
				vList.push_back(_vertex);
		}
		else if (line.substr(0, 3) == "vt ") {
			float texCoords[3] = {};
			sscanf_s(line.c_str(), "vt %f %f %f", &texCoords[0], &texCoords[1], &texCoords[2]);

			for (auto& _texCoord : texCoords) {
				vtList.push_back(_texCoord);
			}
		}
		else if (line.substr(0, 3) == "vn ") {
			float normals[3] = {};
			sscanf_s(line.c_str(), "vn %f %f %f", &normals[0], &normals[1], &normals[2]);

			for (auto& _normal : normals) {
				vnList.push_back(_normal);
			}
		}
		else if (line.substr(0, 2) == "f ") {
			int v_idx[4] = { -1, -1, -1, -1 }, vt_idx[4] = { -1, -1, -1, -1 }, vn_idx[4] = { -1, -1, -1, -1 };
			sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
				&v_idx[0], &vt_idx[0], &vn_idx[0],
				&v_idx[1], &vt_idx[1], &vn_idx[1],
				&v_idx[2], &vt_idx[2], &vn_idx[2],
				&v_idx[3], &vt_idx[3], &vn_idx[3]);

			if (v_idx[3] == -1) {
				for (int i = 0; i < 3; i++) {
					v_idx_List.push_back(v_idx[i] - 1);
					vt_idx_List.push_back(vt_idx[i] - 1);
					vn_idx_List.push_back(vn_idx[i] - 1);
				}
			}
			else if (v_idx[3] != -1) {
				for (int i = 0; i < 3; i++) {
					v_idx_List.push_back(v_idx[i] - 1);
					vt_idx_List.push_back(vt_idx[i] - 1);
					vn_idx_List.push_back(vn_idx[i] - 1);
				}
				v_idx_List.push_back(v_idx[0] - 1);
				vt_idx_List.push_back(vt_idx[0] - 1);
				vn_idx_List.push_back(vn_idx[0] - 1);

				v_idx_List.push_back(v_idx[2] - 1);
				vt_idx_List.push_back(vt_idx[2] - 1);
				vn_idx_List.push_back(vn_idx[2] - 1);

				v_idx_List.push_back(v_idx[3] - 1);
				vt_idx_List.push_back(vt_idx[3] - 1);
				vn_idx_List.push_back(vn_idx[3] - 1);
			}

			//for (auto& v_index : v_idx) {
			//	v_idx_List.push_back(v_index - 1);
			//}

			//for (auto& vt_index : vt_idx) {
			//	vt_idx_List.push_back(vt_index - 1);
			//}

			//for (auto& vn_index : vn_idx) {
			//	vn_idx_List.push_back(vn_index - 1);
			//}

		}
	}

	file.close();

	for (auto& v_index : v_idx_List) {
		vertex.push_back(vList[v_index * 3]);
		vertex.push_back(vList[v_index * 3 + 1]);
		vertex.push_back(vList[v_index * 3 + 2]);
	}

	for (auto& vt_index : vt_idx_List) {
		texCoord.push_back(vtList[vt_index * 3]);
		texCoord.push_back(vtList[vt_index * 3 + 1]);
		texCoord.push_back(vtList[vt_index * 3 + 2]);
	}

	for (auto& vn_index : vn_idx_List) {
		normal.push_back(vnList[vn_index * 3]);
		normal.push_back(vnList[vn_index * 3 + 1]);
		normal.push_back(vnList[vn_index * 3 + 2]);
	}
}


void Shape::setColor(glm::vec4 _color) {
	while (vertex.size() * 4 > color.size() * 3) {
		color.push_back(0.0f);
	}

	for (int i = 0; i < color.size() / 4; i++) {
		color[i * 4] = _color.x;
		color[i * 4 + 1] = _color.y;
		color[i * 4 + 2] = _color.z;
		color[i * 4 + 3] = _color.w;
	}
}


void Shape::updateBuffer() {
	if (vao == NULL) {
		glGenVertexArrays(1, &vao);
		glGenBuffers(4, &vbo[0]);
	}


	glBindVertexArray(vao);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), &vertex[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(GLfloat), &normal[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(GLfloat), &color[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, texCoord.size() * sizeof(GLfloat), &texCoord[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(3);
}


void Shape::draw(const int _shader, const int _draw_mode) {
	glUseProgram(_shader);

	Shape::updateBuffer();

	glm::mat4 result_matrix = glm::mat4(1.0f);
	for (int i = 0; i < matrix.size(); i++) {
		result_matrix = matrix[i] * result_matrix;
	}

	unsigned int transformLocation = glGetUniformLocation(_shader, "modelTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(result_matrix));

	glBindVertexArray(vao);
	glDrawArrays(_draw_mode, 0, vertex.size() / 3);
}


void Shape::scale(int _idx, glm::vec3 _size) {
	while (matrix.size() <= _idx) {
		matrix.push_back(glm::mat4(1.0f));
	}

	matrix[_idx] = glm::scale(matrix[_idx], _size);
}


void Shape::scale(int _idx, glm::mat4 _mat, glm::vec3 _size) {
	while (matrix.size() <= _idx) {
		matrix.push_back(glm::mat4(1.0f));
	}

	matrix[_idx] = glm::scale(_mat, _size) * matrix[_idx];
}


void Shape::rotate(int _idx, float _degree, glm::vec3 _dir) {
	while (matrix.size() <= _idx) {
		matrix.push_back(glm::mat4(1.0f));
	}

	matrix[_idx] = glm::rotate(matrix[_idx], glm::radians(_degree), _dir);
}


void Shape::rotate(int _idx, glm::mat4 _mat, float _degree, glm::vec3 _dir) {
	while (matrix.size() <= _idx) {
		matrix.push_back(glm::mat4(1.0f));
	}

	matrix[_idx] = glm::rotate(_mat, glm::radians(_degree), _dir) * matrix[_idx];
}


void Shape::translate(int _idx, glm::vec3 _move) {
	while (matrix.size() <= _idx) {
		matrix.push_back(glm::mat4(1.0f));
	}

	matrix[_idx] = glm::translate(matrix[_idx], _move);
}


void Shape::translate(int _idx, glm::mat4 _mat, glm::vec3 _move) {
	while (matrix.size() <= _idx) {
		matrix.push_back(glm::mat4(1.0f));
	}

	matrix[_idx] = glm::translate(_mat, _move) * matrix[_idx];
}


void Shape::updateData() {

}


void Shape::initMatrix() {
	for (auto& mat : matrix) {
		mat = glm::mat4(1.0f);
	}
}


void Shape::initMatrix(const unsigned int _idx) {
	while (matrix.size() <= _idx) {
		matrix.push_back(glm::mat4(1.0f));
	}

	matrix[_idx] = glm::mat4(1.0f);
}


BB Shape::get_bb() {
	glm::vec3 LTF = { bb.left, bb.top, bb.front };  // Left, Top, Front
	glm::vec3 RBB = { bb.right, bb.bottom, bb.back };  // Right, Bottom, Back

	glm::mat4 result_matrix = glm::mat4(1.0f);
	for (int i = 0; i < matrix.size(); i++) {
		result_matrix = matrix[i] * result_matrix;
	}

	LTF = glm::vec3(result_matrix* glm::vec4(LTF, 1.0f));
	RBB = glm::vec3(result_matrix* glm::vec4(RBB, 1.0f));

	BB temp_bb = { LTF.x, RBB.x, LTF.y, RBB.y, LTF.z, RBB.z };
	if (LTF.x > RBB.x) {
		temp_bb.left = RBB.x;
		temp_bb.right = LTF.x;
	}

	if (LTF.y < RBB.y) {
		temp_bb.top = RBB.y;
		temp_bb.bottom = LTF.y;
	}

	if (LTF.z < RBB.z) {
		temp_bb.front = RBB.z;
		temp_bb.back = LTF.z;
	}

	return temp_bb;
}