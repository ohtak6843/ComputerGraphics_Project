#pragma once
#include "struct.h"

#define _CRT_SECURE_NO_WARNINGS
#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000

// window ��ǥ�� openGL ��ǥ�� ��ȯ
void convertXY(int x, int y, float* ox, float* oy);


// ���� �о����
char* filetobuf(const char* file);


bool collide(const BB a, const BB b);