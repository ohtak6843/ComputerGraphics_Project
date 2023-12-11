#define STB_IMAGE_IMPLEMENTATION

#include "basic_data.h"
#include "common_functions.h"
#include "display.h"
#include "light.h"
#include "shader.h"
#include "shape.h"
#include "stb_image.h"


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


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dist(-2.0f, 2.0f);
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

Shape squ(squ_vertex, squ_normal, squ_color, squ_texCoord);
Shape test(squ_vertex, squ_normal, squ_color, squ_texCoord);

Shape cube(cube_vertex, cube_normal, cube_color, cube_texCoord);

Shape sphere("moon.obj");

std::vector<std::vector<Shape>> Bgrounds;
std::vector<std::vector<Shape>> Tgrounds;
std::vector<std::vector<Shape>> Lgrounds;
std::vector<std::vector<Shape>> Rgrounds;


unsigned int texture;
int widthImage, heightImage, numberOfChannel;
unsigned char* data;


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
	
	sphere.setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	sphere.scale(0, {0.25f, 0.25f, 0.25f});

	display.cameraPos = { 0.0f, 3.0f, 10.0f };
	light.setPos({ 0.0f, 0.0f, -5.0f });

	
	squ.scale(0, { 3.0f, 3.0f, 1.0f });
	squ.setColor({ 0.0f, 1.0f, 1.0f, 1.0f});

	test.scale(0, { 3.0f, 3.0f, 1.0f });
	test.translate(2, { 0.0f, 0.0f, 1.0f });


	for (int i = 0; i < 5; i++) {
		Bgrounds.push_back(std::vector<Shape>());
		Tgrounds.push_back(std::vector<Shape>());
		Lgrounds.push_back(std::vector<Shape>());
		Rgrounds.push_back(std::vector<Shape>());
	}

	for (int i = 0; i < Bgrounds.size(); i++) {
		for (int j = 0; j < 100; j++) {
			Bgrounds[i].push_back(Shape(squ_vertex, squ_normal, squ_color, squ_texCoord));
			Tgrounds[i].push_back(Shape(squ_vertex, squ_normal, squ_color, squ_texCoord));
			Lgrounds[i].push_back(Shape(squ_vertex, squ_normal, squ_color, squ_texCoord));
			Rgrounds[i].push_back(Shape(squ_vertex, squ_normal, squ_color, squ_texCoord));
		}
	}

	for (int i = 0; i < Bgrounds.size(); i++) {
		for (int j = 0; j < Bgrounds[i].size(); j++) {
			Bgrounds[i][j].setColor({ 0.0f, 1.0f, 1.0f, 1.0f });
			Bgrounds[i][j].rotate(1, -90.0f, { 1.0f, 0.0f, 0.0f });
			Bgrounds[i][j].translate(2, { 0.0f, -5.0f, 0.0f });
			Bgrounds[i][j].translate(2, { 2.0f * i, 0.0f, -2.0f * j });
			Bgrounds[i][j].translate(2, { -2.0f * float(5 - 1) / 2, 0.0f, 0.0f});
		}
	}

	for (int i = 0; i < Tgrounds.size(); i++) {
		for (int j = 0; j < Tgrounds[i].size(); j++) {
			Tgrounds[i][j].setColor({ 0.0f, 1.0f, 1.0f, 1.0f });
			Tgrounds[i][j].rotate(1, 90.0f, { 1.0f, 0.0f, 0.0f });
			Tgrounds[i][j].translate(2, { 0.0f, 5.0f, 0.0f });
			Tgrounds[i][j].translate(2, { 2.0f * i, 0.0f, -2.0f * j });
			Tgrounds[i][j].translate(2, { -2.0f * float(5 - 1) / 2, 0.0f, 0.0f });
		}
	}

	for (int i = 0; i < Lgrounds.size(); i++) {
		for (int j = 0; j < Lgrounds[i].size(); j++) {
			Lgrounds[i][j].setColor({ 0.0f, 1.0f, 1.0f, 1.0f });
			Lgrounds[i][j].rotate(1, 90.0f, { 0.0f, 1.0f, 0.0f });
			Lgrounds[i][j].translate(2, { -5.0f, 0.0f, 0.0f });
			Lgrounds[i][j].translate(2, { 0.0f, 2.0f * i, -2.0f * j });
			Lgrounds[i][j].translate(2, { 0.0f, -2.0f * float(5 - 1) / 2, 0.0f });
		}
	}

	for (int i = 0; i < Rgrounds.size(); i++) {
		for (int j = 0; j < Rgrounds[i].size(); j++) {
			Rgrounds[i][j].setColor({ 0.0f, 1.0f, 1.0f, 1.0f });
			Rgrounds[i][j].rotate(1, -90.0f, { 0.0f, 1.0f, 0.0f });
			Rgrounds[i][j].translate(2, { 5.0f, 0.0f, 0.0f });
			Rgrounds[i][j].translate(2, { 0.0f, 2.0f * i, -2.0f * j });
			Rgrounds[i][j].translate(2, { 0.0f, -2.0f * float(5 - 1) / 2, 0.0f });
		}
	}


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


	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutMainLoop(); // 이벤트 처리 시작
}

void moveGrounds(float x) {
	for (auto& column_Bground : Bgrounds) {
		for (auto& row_Bround : column_Bground) {
			row_Bround.initMatrix(3);
			row_Bround.translate(3, { x, 0.0f, 0.0f });
		}
	}

	for (auto& column_Tground : Tgrounds) {
		for (auto& row_Tround : column_Tground) {
			row_Tround.initMatrix(3);
			row_Tround.translate(3, { x, 0.0f, 0.0f });
		}
	}

	for (auto& column_Lground : Lgrounds) {
		for (auto& row_Lround : column_Lground) {
			row_Lround.initMatrix(3);
			row_Lround.translate(3, { x, 0.0f, 0.0f });
		}
	}

	for (auto& column_Rground : Rgrounds) {
		for (auto& row_Rround : column_Rground) {
			row_Rround.initMatrix(3);
			row_Rround.translate(3, { x, 0.0f, 0.0f });
		}
	}
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
		for (auto& row_Bround : column_Bground) {
			row_Bround.updateBuffer();
			row_Bround.draw(shader.ID, GL_TRIANGLES);
		}
	}

	for (auto& column_Tground : Tgrounds) {
		for (auto& row_Tround : column_Tground) {
			row_Tround.updateBuffer();
			row_Tround.draw(shader.ID, GL_TRIANGLES);
		}
	}

	for (auto& column_Lground : Lgrounds) {
		for (auto& row_Lround : column_Lground) {
			row_Lround.updateBuffer();
			row_Lround.draw(shader.ID, GL_TRIANGLES);
		}
	}

	for (auto& column_Rground : Rgrounds) {
		for (auto& row_Rround : column_Rground) {
			row_Rround.updateBuffer();
			row_Rround.draw(shader.ID, GL_TRIANGLES);
		}
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
		moveGrounds(0.5f);
		break;
	case 'd':
		moveGrounds(-0.5f);
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
	case 1:
		glutTimerFunc(50, TimerFunction, 1);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}