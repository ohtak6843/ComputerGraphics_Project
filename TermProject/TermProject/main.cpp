#define STB_IMAGE_IMPLEMENTATION

#include "basic_data.h"
#include "common_functions.h"
#include "display.h"
#include "light.h"
#include "shader.h"
#include "shape.h"
#include "stb_image.h"
#include "struct.h"


#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>


#include <iostream>
#include <stdlib.h>
#include <random>
#include <math.h>
#include <vector>
#include <algorithm>

bool collCheakGroundsPlayer();


enum GroundState {
	common = 0,
	stop,
	descending,
};


class Player : public Shape {
private:

public:
	float y, ySpeed;
	Player() {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;
		y = 0.0;
		ySpeed = 0.0;
		bb = { -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f };
	}

	Player(std::vector<GLfloat> _vertex, std::vector<GLfloat> _normal, std::vector<GLfloat> _color, std::vector<GLfloat> _texCoord) {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;
		y = 0.0;
		ySpeed = 0.0;
		vertex = _vertex;
		normal = _normal;
		color = _color;
		texCoord = _texCoord;

		bb = { -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f };
	}

	Player(const char* _obj) {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;
		y = 0.0;
		ySpeed = 0.0;
		Shape::read_obj(_obj);

		bb = { -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f };
	}
	void jump() {
		if (collCheakGroundsPlayer()) {
		ySpeed = 0.6;
		y += ySpeed;
		initMatrix(5);
		translate(5, { 0.0f, y, 0.0f });
		}
	}
	void updateData() {
		Shape::updateData();

		
		if (collCheakGroundsPlayer()) {
			ySpeed = 0;

		}
		y += ySpeed;
		ySpeed -= 0.05;
		initMatrix(5);
		translate(5, { 0.0f, y, 0.0f });
	}
};


class Ground : public Shape {
private:

public:
	int time = 300;

	GroundState state = common;
	int gravity_time = 5;

	Ground() {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

		bb = { -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f };
	}

	Ground(std::vector<GLfloat> _vertex, std::vector<GLfloat> _normal, std::vector<GLfloat> _color, std::vector<GLfloat> _texCoord) {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

		vertex = _vertex;
		normal = _normal;
		color = _color;
		texCoord = _texCoord;

		bb = { -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f };
	}

	Ground(const char* _obj) {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

		Shape::read_obj(_obj);

		bb = { -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f };
	}


	void updateData() {
		Shape::translate(2, { 0.0f, 0.0f, 0.5f });
		--time;

		if (state == descending) {
			Shape::translate(2, { 0.0f, -0.5f, 0.0f });
			--gravity_time;
		}
	}
};


class Meteor : public Shape {
private:

public:
	int time = 100;

	Meteor() {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

		bb = { -2.0f, 2.0f, 2.0f, -2.0f, 2.0f, -2.0f };
	}

	Meteor(std::vector<GLfloat> _vertex, std::vector<GLfloat> _normal, std::vector<GLfloat> _color, std::vector<GLfloat> _texCoord) {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

		vertex = _vertex;
		normal = _normal;
		color = _color;
		texCoord = _texCoord;

		bb = { -2.0f, 2.0f, 2.0f, -2.0f, 2.0f, -2.0f };
	}

	Meteor(const char* _obj) {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

		Shape::read_obj(_obj);

		bb = { -2.0f, 2.0f, 2.0f, -2.0f, 2.0f, -2.0f };
	}


	void updateData() {
		Shape::translate(2, { 0.0f, 0.0f, 2.0f });
		--time;
	}
};


class Item : public Shape {
private:

public:
	int time;

	Item() {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

		bb = { -2.0f, 2.0f, 2.0f, -2.0f, 2.0f, -2.0f };
	}

	Item(std::vector<GLfloat> _vertex, std::vector<GLfloat> _normal, std::vector<GLfloat> _color, std::vector<GLfloat> _texCoord) {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

		vertex = _vertex;
		normal = _normal;
		color = _color;
		texCoord = _texCoord;

		bb = { -2.0f, 2.0f, 2.0f, -2.0f, 2.0f, -2.0f };
	}

	Item(const char* _obj) {
		vao = vbo[0] = vbo[1] = vbo[2] = vbo[3] = NULL;

		Shape::read_obj(_obj);

		bb = { -2.0f, 2.0f, 2.0f, -2.0f, 2.0f, -2.0f };
	}


	void updateData() {
		Shape::translate(2, { 0.0f, 0.0f, 1.0f });
		--time;
	}
};


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dist_rand(0, 100);
std::uniform_real_distribution<> dist(-4.0f, 4.0f);
std::uniform_real_distribution<> dist_scale(0.1, 0.2f);
std::uniform_real_distribution<> dist_trans(-2.5f, 2.5f);


GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid SpecialKey(int key, int x, int y);
GLvoid TimerFunction(int value);


// 전역변수
Shader shader;
Shader Tshader;


GLfloat rColor = 0.0f;
GLfloat gColor = 0.0f;
GLfloat bColor = 0.0f;

Display display;

Light light;

Player cube(cube_vertex, cube_normal, cube_color, cube_texCoord);

std::vector<std::vector<Ground>> Bgrounds;
std::vector<std::vector<Ground>> Tgrounds;
std::vector<std::vector<Ground>> Lgrounds;
std::vector<std::vector<Ground>> Rgrounds;


std::vector<Meteor> meteors;


unsigned int texture;
int widthImage, heightImage, numberOfChannel;
unsigned char* data;


glm::vec4 Cground_color = { 0.0f, 1.0f, 1.0f, 1.0f };
glm::vec4 Sground_color = { 0.0f, 1.0f, 1.0f, 0.3f };

int updateSpeed = 50;


//--- 윈도우 출력하고 콜백함수 설정
void main(int argc, char** argv) {

	//--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성	(윈도우 이름)

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";


	shader.make_shaderProgram("vertex.glsl", "fragment.glsl");
	Tshader.make_shaderProgram("T_vertex.glsl", "T_fragment.glsl");


	glEnable(GL_DEPTH_TEST); // 은면 제거
	glDisable(GL_CULL_FACE); // 뒷면 제거
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);


	display.cameraPos = { 0.0f, 3.0f, 20.0f };
	light.setPos({ 0.0f, 0.0f, -5.0f });
	cube.scale(0, { 0.5,0.5,0.5 });

	for (int i = 0; i < 5; i++) {
		Bgrounds.push_back(std::vector<Ground>());
		Tgrounds.push_back(std::vector<Ground>());
		Lgrounds.push_back(std::vector<Ground>());
		Rgrounds.push_back(std::vector<Ground>());
	}

	for (int i = 0; i < Bgrounds.size(); i++) {
		for (int j = 0; j < 50; j++) {
			Bgrounds[i].push_back(Ground(squ_vertex, squ_normal, squ_color, squ_texCoord));
			Tgrounds[i].push_back(Ground(squ_vertex, squ_normal, squ_color, squ_texCoord));
			Lgrounds[i].push_back(Ground(squ_vertex, squ_normal, squ_color, squ_texCoord));
			Rgrounds[i].push_back(Ground(squ_vertex, squ_normal, squ_color, squ_texCoord));
		}
	}

	for (int i = 0; i < Bgrounds.size(); i++) {
		for (int j = 0; j < Bgrounds[i].size(); j++) {
			Bgrounds[i][j].setColor(Cground_color);
			Bgrounds[i][j].rotate(1, -90.0f, { 1.0f, 0.0f, 0.0f });
			Bgrounds[i][j].translate(2, { 0.0f, -5.0f, 0.0f });
			Bgrounds[i][j].translate(2, { 0.0f, 4.5f, 0.0f });
			Bgrounds[i][j].translate(2, { 2.0f * i, 0.0f, -2.0f * j });
			Bgrounds[i][j].translate(2, { -2.0f * float(5 - 1) / 2, 0.0f, 0.0f });
		}
	}

	for (int i = 0; i < Tgrounds.size(); i++) {
		for (int j = 0; j < Tgrounds[i].size(); j++) {
			Tgrounds[i][j].setColor(Cground_color);
			Tgrounds[i][j].rotate(1, 90.0f, { 1.0f, 0.0f, 0.0f });
			Tgrounds[i][j].translate(2, { 0.0f, 5.0f, 0.0f });
			Tgrounds[i][j].translate(2, { 0.0f, 4.5f, 0.0f });
			Tgrounds[i][j].translate(2, { 2.0f * i, 0.0f, -2.0f * j });
			Tgrounds[i][j].translate(2, { -2.0f * float(5 - 1) / 2, 0.0f, 0.0f });
		}
	}

	for (int i = 0; i < Lgrounds.size(); i++) {
		for (int j = 0; j < Lgrounds[i].size(); j++) {
			Lgrounds[i][j].setColor(Cground_color);
			Lgrounds[i][j].rotate(1, 90.0f, { 0.0f, 1.0f, 0.0f });
			Lgrounds[i][j].translate(2, { -5.0f, 0.0f, 0.0f });
			Lgrounds[i][j].translate(2, { 0.0f, 4.5f, 0.0f });
			Lgrounds[i][j].translate(2, { 0.0f, 2.0f * i, -2.0f * j });
			Lgrounds[i][j].translate(2, { 0.0f, -2.0f * float(5 - 1) / 2, 0.0f });
		}
	}

	for (int i = 0; i < Rgrounds.size(); i++) {
		for (int j = 0; j < Rgrounds[i].size(); j++) {
			Rgrounds[i][j].setColor(Cground_color);
			Rgrounds[i][j].rotate(1, -90.0f, { 0.0f, 1.0f, 0.0f });
			Rgrounds[i][j].translate(2, { 5.0f, 0.0f, 0.0f });
			Rgrounds[i][j].translate(2, { 0.0f, 4.5f, 0.0f });
			Rgrounds[i][j].translate(2, { 0.0f, 2.0f * i, -2.0f * j });
			Rgrounds[i][j].translate(2, { 0.0f, -2.0f * float(5 - 1) / 2, 0.0f });
		}
	}
	glutTimerFunc(0, TimerFunction, 1);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("alpha.bmp", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);


	glutTimerFunc(updateSpeed, TimerFunction, 1);
	glutTimerFunc(updateSpeed * 2, TimerFunction, 2);
	glutTimerFunc(3000, TimerFunction, 3);


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutMainLoop(); // 이벤트 처리 시작
}


float playerMoveRate = 0.0f;
float moveXCheak = 1.0;
float moveYCheak = 0.0;
int playerStandingGround = 0;
void moveObjects(float moveRate) {
	playerMoveRate += moveRate;
	if (playerMoveRate > 4.5) {
		playerMoveRate = -4.5;
		for (auto& m : meteors) {
			m.rotate(4, 90.0f, { 0.0f, 0.0f, 1.0f });	
		}
		for (auto& column_Bground : Bgrounds) {
			for (auto& row_Bround : column_Bground) {
				row_Bround.rotate(4, 90.0f, { 0.0f, 0.0f, 1.0f });
			}
		}

		for (auto& column_Tground : Tgrounds) {
			for (auto& row_Tround : column_Tground) {
				row_Tround.rotate(4, 90.0f, { 0.0f, 0.0f, 1.0f });
			}
		}

		for (auto& column_Lground : Lgrounds) {
			for (auto& row_Lround : column_Lground) {
				row_Lround.rotate(4, 90.0f, { 0.0f, 0.0f, 1.0f });
			}
		}

		for (auto& column_Rground : Rgrounds) {
			for (auto& row_Rround : column_Rground) {
				row_Rround.rotate(4, 90.0f, { 0.0f, 0.0f, 1.0f });
			}
		}
		if (moveXCheak >= 1.0) {
			playerStandingGround = 1;
			moveXCheak = 0.0;
			moveYCheak = -1.0;
		}
		else if (moveYCheak <= -1.0) {
			playerStandingGround = 2;
			moveXCheak = -1.0;
			moveYCheak = 0.0;
		}
		else if (moveXCheak <= -1.0) {
			playerStandingGround = 3;
			moveXCheak = 0.0;
			moveYCheak = 1.0;
		}
		else if (moveYCheak >= 1.0) {
			playerStandingGround = 0;
			moveXCheak = 1.0;
			moveYCheak = 0.0;
		}
	}
	else if (playerMoveRate < -4.5) {
		playerMoveRate = 4.5;
		for (auto& m : meteors) {
			m.rotate(4, 90.0f, { 0.0f, 0.0f, 1.0f });
		}
		for (auto& column_Bground : Bgrounds) {
			for (auto& row_Bround : column_Bground) {
				row_Bround.rotate(4, -90.0f, { 0.0f, 0.0f, 1.0f });
			}
		}

		for (auto& column_Tground : Tgrounds) {
			for (auto& row_Tround : column_Tground) {
				row_Tround.rotate(4, -90.0f, { 0.0f, 0.0f, 1.0f });
			}
		}

		for (auto& column_Lground : Lgrounds) {
			for (auto& row_Lround : column_Lground) {
				row_Lround.rotate(4, -90.0f, { 0.0f, 0.0f, 1.0f });
			}
		}

		for (auto& column_Rground : Rgrounds) {
			for (auto& row_Rround : column_Rground) {
				row_Rround.rotate(4, -90.0f, { 0.0f, 0.0f, 1.0f });
			}
		}
		if (moveXCheak >= 1.0) {
			playerStandingGround = 3;
			moveXCheak = 0.0;
			moveYCheak = 1.0;
		}
		else if (moveYCheak <= -1.0) {
			playerStandingGround = 0;
			moveXCheak = 1.0;
			moveYCheak = 0.0;
		}
		else if (moveXCheak <= -1.0) {
			playerStandingGround = 1;
			moveXCheak = 0.0;
			moveYCheak = -1.0;
		}
		else if (moveYCheak >= 1.0) {
			playerStandingGround = 2;
			moveXCheak = -1.0;
			moveYCheak = 0.0;
		}
	}
	else {
		for (auto& m : meteors) {
			m.translate(3, { moveXCheak * moveRate, moveYCheak * moveRate, 0.0f });
		}
		for (auto& column_Bground : Bgrounds) {
			for (auto& row_Bround : column_Bground) {
				row_Bround.translate(3, { moveXCheak * moveRate, moveYCheak * moveRate, 0.0f });
			}
		}

		for (auto& column_Tground : Tgrounds) {
			for (auto& row_Tround : column_Tground) {

				row_Tround.translate(3, { moveXCheak * moveRate, moveYCheak * moveRate, 0.0f });
			}
		}

		for (auto& column_Lground : Lgrounds) {
			for (auto& row_Lround : column_Lground) {

				row_Lround.translate(3, { moveXCheak * moveRate, moveYCheak * moveRate, 0.0f });
			}
		}

		for (auto& column_Rground : Rgrounds) {
			for (auto& row_Rround : column_Rground) {

				row_Rround.translate(3, { moveXCheak * moveRate, moveYCheak * moveRate, 0.0f });
			}
		}
	}
}

bool collCheakGroundsPlayer() {
	switch (playerStandingGround) {
	case 0:
		for (auto& column_Bground : Bgrounds) {
			for (auto& row_Bround : column_Bground) {
				if (collide(row_Bround.get_bb(), cube.get_bb())) {
					if (row_Bround.state == stop) {
						row_Bround.state = descending;
					}
					return true;
				}

			}
		}
		break;
	case 1:
		for (auto& column_Lground : Lgrounds) {
			for (auto& row_Lround : column_Lground) {
				if (collide(row_Lround.get_bb(), cube.get_bb())) {
					if (row_Lround.state == stop) {
						row_Lround.state = descending;
					}
					return true;
				}
			}
		}
		break;
	case 2:
		for (auto& column_Tground : Tgrounds) {
			for (auto& row_Tround : column_Tground) {
				if (collide(row_Tround.get_bb(), cube.get_bb())) {
					if (row_Tround.state == stop) {
						row_Tround.state = descending;
					}
					return true;
				}
			}
		}
		break;
	case 3:
		for (auto& column_Rground : Rgrounds) {
			for (auto& row_Rround : column_Rground) {
				if (collide(row_Rround.get_bb(), cube.get_bb())) {
					if (row_Rround.state == stop) {
						row_Rround.state = descending;
					}
					return true;
				}
			}
		}
		break;
	default:
		return false;
		break;
	}
	return false;
}




//--- 콜백 함수: 그리기 콜백 함수
GLvoid drawScene() {
	glClearColor(rColor, gColor, bColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	display.updateSetting(shader.ID);
	light.updateSetting(shader.ID);

	display.updateSetting(Tshader.ID);
	light.updateSetting(Tshader.ID);

	for (auto& column_Bground : Bgrounds) {
		for (auto& row_Bground : column_Bground) {
			row_Bground.draw(shader.ID, GL_TRIANGLES);
		}
	}

	for (auto& column_Tground : Tgrounds) {
		for (auto& row_Tground : column_Tground) {
			row_Tground.draw(shader.ID, GL_TRIANGLES);
		}
	}

	for (auto& column_Lground : Lgrounds) {
		for (auto& row_Lground : column_Lground) {
			row_Lground.draw(shader.ID, GL_TRIANGLES);
		}
	}

	for (auto& column_Rground : Rgrounds) {
		for (auto& row_Rground : column_Rground) {
			row_Rground.draw(shader.ID, GL_TRIANGLES);
		}
	}


	for (auto& meteor : meteors) {
		meteor.draw(shader.ID, GL_TRIANGLES);
	}

	glBindTexture(GL_TEXTURE_2D, texture);

	cube.draw(Tshader.ID, GL_TRIANGLES);

	glutSwapBuffers(); // 화면에 출력하기
}

//--- 콜백 함수: 다시 그리기 콜백 함수
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}


GLvoid Mouse(int button, int state, int x, int y) {
}


GLvoid Motion(int x, int y) {
	glutPostRedisplay();
}


GLvoid Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'm':
		light.setColor({ 1.0f, 1.0f, 1.0f });
		break;
	case 'M':
		light.setColor({ 0.1f, 0.1f, 0.1f, });
		break;
	case 'y':
		display.rotatePos(5.0f, { 0.0f, 1.0f, 0.0f });
		break;
	case 'Y':
		display.rotatePos(-5.0f, { 0.0f, 1.0f, 0.0f });
		break;
	case 'q':
		exit(0);
		break;
	case 'a':
		moveObjects(0.2f);
		break;
	case 'd':
		moveObjects(-0.2f);
		break;
	case 'w':
		cube.jump();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


GLvoid SpecialKey(int key, int x, int y) {
	switch (key) {
	default:
		break;
	}

	glutPostRedisplay();
}


GLvoid TimerFunction(int value) {
	switch (value) {
		// 데이터 업데이트
	case 1:
		for (int i = 0; i < Bgrounds.size(); i++) {
			for (int j = 0; j < Bgrounds[i].size(); j++) {
				Bgrounds[i][j].updateData();
				if (Bgrounds[i][j].time < 0) {
					Bgrounds[i].erase(Bgrounds[i].begin() + j);
				}
			}
		}

		for (int i = 0; i < Tgrounds.size(); i++) {
			for (int j = 0; j < Tgrounds[i].size(); j++) {
				Tgrounds[i][j].updateData();
				if (Tgrounds[i][j].time < 0) {
					Tgrounds[i].erase(Tgrounds[i].begin() + j);
				}
			}
		}

		for (int i = 0; i < Lgrounds.size(); i++) {
			for (int j = 0; j < Lgrounds[i].size(); j++) {
				Lgrounds[i][j].updateData();
				if (Lgrounds[i][j].time < 0) {
					Lgrounds[i].erase(Lgrounds[i].begin() + j);
				}
			}
		}

		for (int i = 0; i < Rgrounds.size(); i++) {
			for (int j = 0; j < Rgrounds[i].size(); j++) {
				Rgrounds[i][j].updateData();
				if (Rgrounds[i][j].time < 0) {
					Rgrounds[i].erase(Rgrounds[i].begin() + j);
				}
			}
		}

		for (int i = 0; i < meteors.size(); i++) {
			meteors[i].updateData();
			if (meteors[i].time < 0) {
				meteors.erase(meteors.begin() + i);
			}
		}

		cube.updateData();
		glutTimerFunc(updateSpeed, TimerFunction, 1);
		break;
		// 바닥 생성하기
	case 2:
		for (int i = 0; i < Bgrounds.size(); i++) {
			int randint = dist_rand(gen);
			// common 바닥 생성
			if (randint < 40) {
				Ground tempG(squ_vertex, squ_normal, squ_color, squ_texCoord);
				tempG.state = common;
				tempG.setColor(Cground_color);
				tempG.matrix = Bgrounds[i][0].matrix;
				tempG.initMatrix(2);
				tempG.translate(2, { 0.0f, -5.0f, 0.0f });
				tempG.translate(2, { 0.0f, 4.5f, 0.0f });
				tempG.translate(2, { 2.0f * i, 0.0f, 0.0f });
				tempG.translate(2, { -2.0f * float(5 - 1) / 2, 0.0f, 0.0f });
				tempG.translate(2, { 0.0f, 0.0f, -100.0f });
				Bgrounds[i].push_back(tempG);
			}
			// 떨어지는 바닥 생성
			else if (randint < 60) {
				Ground tempG(squ_vertex, squ_normal, squ_color, squ_texCoord);
				tempG.state = stop;
				tempG.setColor(Sground_color);
				tempG.matrix = Bgrounds[i][0].matrix;
				tempG.initMatrix(2);
				tempG.translate(2, { 0.0f, -5.0f, 0.0f });
				tempG.translate(2, { 0.0f, 4.5f, 0.0f });
				tempG.translate(2, { 2.0f * i, 0.0f, 0.0f });
				tempG.translate(2, { -2.0f * float(5 - 1) / 2, 0.0f, 0.0f });
				tempG.translate(2, { 0.0f, 0.0f, -100.0f });
				Bgrounds[i].push_back(tempG);
			}
		}

		for (int i = 0; i < Tgrounds.size(); i++) {
			int randint = dist_rand(gen);
			// common 바닥 생성
			if (randint < 30) {
				Ground tempG(squ_vertex, squ_normal, squ_color, squ_texCoord);
				tempG.state = common;
				tempG.setColor(Cground_color);
				tempG.matrix = Tgrounds[i][0].matrix;
				tempG.initMatrix(2);
				tempG.translate(2, { 0.0f, 5.0f, 0.0f });
				tempG.translate(2, { 0.0f, 4.5f, 0.0f });
				tempG.translate(2, { 2.0f * i, 0.0f, 0.0f });
				tempG.translate(2, { -2.0f * float(5 - 1) / 2, 0.0f, 0.0f });
				tempG.translate(2, { 0.0f, 0.0f, -100.0f });
				Tgrounds[i].push_back(tempG);
			}
			// 떨어지는 바닥 생성
			else if (randint < 50) {
				Ground tempG(squ_vertex, squ_normal, squ_color, squ_texCoord);
				tempG.state = stop;
				tempG.setColor(Sground_color);
				tempG.matrix = Tgrounds[i][0].matrix;
				tempG.initMatrix(2);
				tempG.translate(2, { 0.0f, 5.0f, 0.0f });
				tempG.translate(2, { 0.0f, 4.5f, 0.0f });
				tempG.translate(2, { 2.0f * i, 0.0f, 0.0f });
				tempG.translate(2, { -2.0f * float(5 - 1) / 2, 0.0f, 0.0f });
				tempG.translate(2, { 0.0f, 0.0f, -100.0f });
				Tgrounds[i].push_back(tempG);
			}
		}

		for (int i = 0; i < Lgrounds.size(); i++) {
			int randint = dist_rand(gen);
			// common 바닥 생성
			if (randint < 30) {
				Ground tempG(squ_vertex, squ_normal, squ_color, squ_texCoord);
				tempG.state = common;
				tempG.setColor(Cground_color);
				tempG.matrix = Lgrounds[i][0].matrix;
				tempG.initMatrix(2);
				tempG.translate(2, { -5.0f, 0.0f, 0.0f });
				tempG.translate(2, { 0.0f, 4.5f, 0.0f });
				tempG.translate(2, { 0.0f, 2.0f * i, 0.0f });
				tempG.translate(2, { 0.0f, -2.0f * float(5 - 1) / 2, 0.0f });
				tempG.translate(2, { 0.0f, 0.0f, -100.0f });
				Lgrounds[i].push_back(tempG);
			}
			// 떨어지는 바닥 생성
			else if (randint < 50) {
				Ground tempG(squ_vertex, squ_normal, squ_color, squ_texCoord);
				tempG.state = stop;
				tempG.setColor(Sground_color);
				tempG.matrix = Lgrounds[i][0].matrix;
				tempG.initMatrix(2);
				tempG.translate(2, { -5.0f, 0.0f, 0.0f });
				tempG.translate(2, { 0.0f, 4.5f, 0.0f });
				tempG.translate(2, { 0.0f, 2.0f * i, 0.0f });
				tempG.translate(2, { 0.0f, -2.0f * float(5 - 1) / 2, 0.0f });
				tempG.translate(2, { 0.0f, 0.0f, -100.0f });
				Lgrounds[i].push_back(tempG);
			}
		}

		for (int i = 0; i < Rgrounds.size(); i++) {
			int randint = dist_rand(gen);
			// common 바닥 생성
			if (randint < 30) {
				Ground tempG(squ_vertex, squ_normal, squ_color, squ_texCoord);
				tempG.state = common;
				tempG.setColor(Cground_color);
				tempG.matrix = Rgrounds[i][0].matrix;
				tempG.initMatrix(2);
				tempG.translate(2, { 5.0f, 0.0f, 0.0f });
				tempG.translate(2, { 0.0f, 4.5f, 0.0f });
				tempG.translate(2, { 0.0f, 2.0f * i, 0.0f });
				tempG.translate(2, { 0.0f, -2.0f * float(5 - 1) / 2, 0.0f });
				tempG.translate(2, { 0.0f, 0.0f, -100.0f });
				Rgrounds[i].push_back(tempG);
			}
			// 떨어지는 바닥 생성
			else if (randint < 50) {
				Ground tempG(squ_vertex, squ_normal, squ_color, squ_texCoord);
				tempG.state = stop;
				tempG.setColor(Sground_color);
				tempG.matrix = Rgrounds[i][0].matrix;
				tempG.initMatrix(2);
				tempG.translate(2, { 5.0f, 0.0f, 0.0f });
				tempG.translate(2, { 0.0f, 4.5f, 0.0f });
				tempG.translate(2, { 0.0f, 2.0f * i, 0.0f });
				tempG.translate(2, { 0.0f, -2.0f * float(5 - 1) / 2, 0.0f });
				tempG.translate(2, { 0.0f, 0.0f, -100.0f });
				Rgrounds[i].push_back(tempG);
			}
		}
		glutTimerFunc(updateSpeed * 2, TimerFunction, 2);
		break;

		// 메테오 생성하기
	case 3:
	{
		Meteor temp("moon.obj");
		temp.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		temp.matrix = Bgrounds[0][0].matrix;
		temp.initMatrix(0);
		temp.initMatrix(1);
		temp.initMatrix(2);
		temp.scale(0, { 0.5f, 0.5f, 0.5f });
		temp.translate(2, { 0.0f, 4.5f, 0.0f });
		temp.translate(2, { dist(gen), dist(gen), -100.0f });
		meteors.push_back(temp);
		glutTimerFunc(3000, TimerFunction, 3);
		break;
	}
	default:
		break;
	}
	glutPostRedisplay();
}