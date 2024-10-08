/*
Copyright (c) 2020 Chan Jer Shyan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __VEC2_H__
#define __VEC2_H__

#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif


template <class T>
class vec2 {
public:
	T x, y;
	
	vec2() :x(0), y(0) {}
	vec2(T x, T y) : x(x), y(y) {}
	vec2(const vec2& v) : x(v.x), y(v.y) {}
	
	vec2& operator=(const vec2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}
	
    vec2 operator+(const vec2& v) const {
		return vec2(x + v.x, y + v.y);
	}
    vec2 operator-(const vec2& v) const {
		return vec2(x - v.x, y - v.y);
	}
	
    vec2& operator+=(const vec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
    vec2& operator-=(const vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	
    vec2 operator+(const double s) const {
		return vec2(x + s, y + s);
	}
    vec2 operator-(const double s) const {
		return vec2(x - s, y - s);
	}
    vec2 operator*(const double s) const {
		return vec2(x * s, y * s);
	}
    vec2 operator/(const double s) const {
		return vec2(x / s, y / s);
	}
	
	
    vec2& operator+=(const double s) {
		x += s;
		y += s;
		return *this;
	}
    vec2& operator-=(const double s) {
		x -= s;
		y -= s;
		return *this;
	}
    vec2& operator*=(const double s) {
		x *= s;
		y *= s;
		return *this;
	}
    vec2& operator/=(const double s) {
		x /= s;
		y /= s;
		return *this;
	}
	
    void set(const T x, const T y) {
		this->x = x;
		this->y = y;
	}
	
    void rotate(const double deg) {
		double theta = deg / 180.0 * M_PI;
		double c = cos(theta);
		double s = sin(theta);
		double tx = x * c - y * s;
		double ty = x * s + y * c;
		x = tx;
		y = ty;
	}
	
	vec2& normalize() {
        if(length() == 0) return *this;
		*this *= (1.0 / length());
		return *this;
	}
	
    T dist(const vec2 v) const {
		vec2 d(v.x - x, v.y - y);
		return d.length();
	}
    T length() const {
		return std::sqrt(x * x + y * y);
	}
    void truncate(const double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}

    T angle() const { // 0 - 360
        const double radAngle = std::atan2(y, x);
        const double radAngle2 = radAngle < 0 ? 2*M_PI + radAngle : radAngle;
        const double degAngle = radAngle2 * 180 / M_PI;
        return degAngle;
    }
	
	vec2 ortho() const {
		return vec2(y, -x);
	}
	
    static T dot(const vec2& v1, const vec2& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
    static T cross(const vec2& v1, const vec2& v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
	
};

typedef vec2<float> vec2f;
typedef vec2<double> vec2d;


#endif
