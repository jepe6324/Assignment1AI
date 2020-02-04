//VECTOR_H_INCLUDED 

// MADE BY PEACE

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cmath>
#include <iostream>

struct Vector2 {
	Vector2() { x_ = 0.0f; y_ = 0.0f; }
	Vector2(float x, float y) { x_ = x; y_ = y; }

	float x_;
	float y_;

   void normalize() {
      //std::cout << x_ << std::endl;
      float x = powf(x_, 2);
      float y = powf(y_, 2);
      float total = x + y;
      float magnitude = _CMATH_::sqrt(total);
      x /= magnitude;
      y /= magnitude;
      x_ = x;
      y_ = y;
   }
	float dot(Vector2 first, Vector2 second) {
		first.normalize();
		second.normalize();
		return first.x_ * second.x_ + first.y_, second.y_;
	}
	Vector2 operator+(Vector2 other) {
		return Vector2(x_ + other.x_, y_ + other.y_);
	}
	Vector2 operator-(Vector2 other) {
		return Vector2(x_ - other.x_, y_ - other.y_);
	}
	Vector2 operator/(float divider) {
		return Vector2(x_ / divider, y_ / divider);
	}
	Vector2 operator*(float multiplier) {
		return Vector2(x_ * multiplier, y_ * multiplier);
	}
};

#endif // !VECTOR_H_INCLUDED
