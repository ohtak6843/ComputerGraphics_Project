#pragma once
#include "struct.h"

#define _CRT_SECURE_NO_WARNINGS
#define WIN_WIDTH 1024
#define WIN_HEIGHT 764

// window 좌표를 openGL 좌표로 변환
void convertXY(int x, int y, float* ox, float* oy);


// 파일 읽어오기
char* filetobuf(const char* file);


bool collide(const BB a, const BB b);