#define _CRT_SECURE_NO_WARNINGS
#include "common_functions.h"
#include <iostream>

void convertXY(int x, int y, float* ox, float* oy) {
	int w = WIN_WIDTH;
	int h = WIN_HEIGHT;
	*ox = (float)(x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0));
	*oy = -(float)(y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0));
}


char* filetobuf(const char* file) {
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}


bool collide(const BB a, const BB b) {
	if (a.left > b.right) return false;
	if (a.right < b.left) return false;
	if (a.top < b.bottom) return false;
	if (a.bottom > b.top) return false;
	if (a.front < b.back) return false;
	if (a.back > b.front) return false;

	return true;
}