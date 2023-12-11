#pragma once


struct BB {
	float left;
	float right;
	float top;
	float bottom;
	float front;
	float back;
};


bool collide(const BB a, const BB b) {
	if (a.left > b.right) return false;
	if (a.right < b.left) return false;
	if (a.top < b.bottom) return false;
	if (a.bottom > b.top) return false;
	if (a.front < b.back) return false;
	if (a.back > b.front) return false;

	return true;
}