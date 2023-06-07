#include <cmath>;

const float degrees_to_radians = 3.14159265358979323846f / 180.0f;
const float M_PI = 3.14159265358979323846f;

//-----------------------------------------------
//-----------------------------------------------
	// Định nghĩa kiểu vector 2D

class vec2
{
public:
	union {
		struct { float x, y; };
		struct { float s, t; };
		struct { float r, g; };
	};

		// tạo tử
	vec2() : x(0.0f), y(0.0f) {}
	~vec2() {}
	vec2(float num) : x(num), y(num) {}
	vec2(float x, float y) : x(x), y(y) {}
	vec2(const vec2& u) : x(u.x), y(u.y) {}

		// toán tử gán
	vec2& operator = (const vec2& u) 
	{ 
		x = u.x; 
		y = u.y; 
		return *this; 
	}

		// toán tử âm
	vec2 operator - () 
	{ 
		return vec2(-x, -y); 
	}

		// toán tử lấy địa chỉ
	float* operator & () 
	{ 
		return (float*)this; 
	}

		// toán tử cộng gán với float
	vec2& operator += (float num) 
	{ 
		x += num; 
		y += num; 
		return *this; 
	}

		// toán tử cộng gán với vec2
	vec2& operator += (const vec2& u) 
	{ 
		x += u.x; 
		y += u.y; 
		return *this; 
	}

		// toán tử trừ gán với float
	vec2& operator -= (float num) 
	{ 
		x -= num; 
		y -= num; 
		return *this; 
	}

		// toán tử trừ gán với vec2
	vec2& operator -= (const vec2& u) 
	{ 
		x -= u.x; 
		y -= u.y; 
		return *this; 
	}

		// toán tử nhân gán với float
	vec2& operator *= (float num) 
	{ 
		x *= num; 
		y *= num; 
		return *this; 
	}

		// toán tử nhân gán với vec2
	vec2& operator *= (const vec2& u) 
	{ 
		x *= u.x; 
		y *= u.y; 
		return *this; 
	}

		// toán tử chia gán với float
	vec2& operator /= (float num) 
	{ 
		x /= num; 
		y /= num; 
		return *this; 
	}

		// toán tử chia gán với vec2
	vec2& operator /= (const vec2& u) 
	{ 
		x /= u.x; 
		y /= u.y; 
		return *this; 
	}

		// toán tử cộng vec2 với float
	friend vec2 operator + (const vec2& u, float num) 
	{ 
		return vec2(u.x + num, u.y + num); 
	}

		// toán tử cộng float với vec2
	friend vec2 operator + (float num, const vec2& u) 
	{ 
		return vec2(num + u.x, num + u.y); 
	}

		// toán tử cộng vec2 với vec2 
	friend vec2 operator + (const vec2& u, const vec2& v) 
	{ 
		return vec2(u.x + v.x, u.y + v.y); 
	}

		// toán tử trừ vec2 với float
	friend vec2 operator - (const vec2& u, float num) 
	{ 
		return vec2(u.x - num, u.y - num); 
	}

	friend vec2 operator - (float num, const vec2& u) 
	{ 
		return vec2(num - u.x, num - u.y); 
	}

		// toán tử trừ vec2 với vec2
	friend vec2 operator - (const vec2& u, const vec2& v) 
	{ 
		return vec2(u.x - v.x, u.y - v.y); 
	}

		// toán tử nhân vec2 với float
	friend vec2 operator * (const vec2& u, float num) 
	{ 
		return vec2(u.x * num, u.y * num); 
	}

		// toán tử nhân float với vec2
	friend vec2 operator * (float num, const vec2& u) 
	{ 
		return vec2(num * u.x, num * u.y); 
	}

		// toán tử nhân vec2 với vec2
	friend vec2 operator * (const vec2& u, const vec2& v) 
	{ 
		return vec2(u.x * v.x, u.y * v.y); 
	}

		// toán tử chia vec2 với float
	friend vec2 operator / (const vec2& u, float num) 
	{ 
		return vec2(u.x / num, u.y / num); 
	}

		// toán tử chia float với vec2
	friend vec2 operator / (float num, const vec2& u) 
	{ 
		return vec2(num / u.x, num / u.y); 
	}

		// toán tử chia vec2 với vec2
	friend vec2 operator / (const vec2& u, const vec2& v) 
	{ 
		return vec2(u.x / v.x, u.y / v.y); 
	}
};
	// các hàm
float dot(const vec2& u, const vec2& v);
float length(const vec2& u);
float length2(const vec2& u);
vec2 mix(const vec2& u, const vec2& v, float a);
vec2 normalize(const vec2& u);
vec2 reflect(const vec2& i, const vec2& n);
vec2 refract(const vec2& i, const vec2& n, float eta);
vec2 rotate(const vec2& u, float angle);

	// tích vô hướng
float dot(const vec2& u, const vec2& v)
{
	return u.x * v.x + u.y * v.y;
}

	// độ dài
float length(const vec2& u)
{
	return sqrt(u.x * u.x + u.y * u.y);
}

	// độ dài bp
float length2(const vec2& u)
{
	return u.x * u.x + u.y * u.y;
}

	//
vec2 mix(const vec2& u, const vec2& v, float a)
{
	return u * (1.0f - a) + v * a;
}

	// chuẩn hóa
vec2 normalize(const vec2& u)
{
	return u / sqrt(u.x * u.x + u.y * u.y);
}

	//
vec2 reflect(const vec2& i, const vec2& n)
{
	return i - 2.0f * dot(n, i) * n;
}

	//
vec2 refract(const vec2& i, const vec2& n, float eta)
{
	vec2 r;

	float ndoti = dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);

	if (k >= 0.0f)
	{
		r = eta * i - n * (eta * ndoti + sqrt(k));
	}

	return r;
}

	//
vec2 rotate(const vec2& u, float angle)
{
	angle = angle / 180.0f * (float)M_PI;

	float c = cos(angle), s = sin(angle);

	return vec2(u.x * c - u.y * s, u.x * s + u.y * c);
}

	// Hết định nghĩa kiểu vector 2D
//-----------------------------------------------


	// Định nghĩa kiểu vector 3D

class vec3
{
public:
	union {
		struct { float x, y, z; };
		struct { float s, t, p; };
		struct { float r, g, b; };
	};

	// tạo tử
	vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	~vec3() {}
	vec3(float num) : x(num), y(num), z(num) {}
	vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	vec3(const vec2& u, float z) : x(u.x), y(u.y), z(z) {}
	vec3(const vec3& u) : x(u.x), y(u.y), z(u.z) {}

		// toán tử gán
	vec3& operator = (const vec3& u) 
	{ 
		x = u.x; 
		y = u.y; 
		z = u.z; 
		return *this; 
	}

		// toán tử âm
	vec3 operator - () 
	{ 
		return vec3(-x, -y, -z); 
	}

		// toán tử lấy địa chỉ
	float* operator & () 
	{ 
		return (float*)this; 
	}

		// toán tử cộng gán với float
	vec3& operator += (float num) 
	{ 
		x += num; 
		y += num; 
		z += num; 
		return *this; 
	}

		// toán tử cộng gán với vec3
	vec3& operator += (const vec3& u) 
	{ 
		x += u.x; 
		y += u.y; 
		z += u.z; 
		return *this; 
	}

		// toán tử trừ gán với float
	vec3& operator -= (float num) 
	{ 
		x -= num; 
		y -= num; 
		z -= num; 
		return *this; 
	}

		// toán tử trừ gán với vec3
	vec3& operator -= (const vec3& u) 
	{ 
		x -= u.x; 
		y -= u.y; 
		z -= u.z; 
		return *this; 
	}

		// toán tử nhân gán với float
	vec3& operator *= (float num) 
	{ 
		x *= num; 
		y *= num; 
		z *= num; 
		return *this; 
	}

		// toán tử nhân gán với vec3
	vec3& operator *= (const vec3& u) 
	{ 
		x *= u.x; 
		y *= u.y; 
		z *= u.z; 
		return *this; 
	}

		// toán tử chia gán với float
	vec3& operator /= (float num) 
	{ 
		x /= num; 
		y /= num; 
		z /= num; 
		return *this; 
	}

		// toán tử chia gán với vec3
	vec3& operator /= (const vec3& u) 
	{ 
		x /= u.x; 
		y /= u.y; 
		z /= u.z; 
		return *this; 
	}

		// toán tử cộng vec3 với float
	friend vec3 operator + (const vec3& u, float num) 
	{ 
		return vec3(u.x + num, u.y + num, u.z + num); 
	}

		// toán tử cộng float với vec3
	friend vec3 operator + (float num, const vec3& u) 
	{ 
		return vec3(num + u.x, num + u.y, num + u.z); 
	}

		// toán tử cộng vec3 với vec3
	friend vec3 operator + (const vec3& u, const vec3& v) 
	{ 
		return vec3(u.x + v.x, u.y + v.y, u.z + v.z); 
	}

		// toán tử trừ vec3 với float
	friend vec3 operator - (const vec3& u, float num) 
	{ 
		return vec3(u.x - num, u.y - num, u.z - num); 
	}

		// toán tử trừ float với vec3
	friend vec3 operator - (float num, const vec3& u) 
	{ 
		return vec3(num - u.x, num - u.y, num - u.z); 
	}

		// toán tử trừ vec3 với vec3
	friend vec3 operator - (const vec3& u, const vec3& v) 
	{ 
		return vec3(u.x - v.x, u.y - v.y, u.z - v.z); 
	}

		// toán tử nhân vec3 với float
	friend vec3 operator * (const vec3& u, float num) 
	{ 
		return vec3(u.x * num, u.y * num, u.z * num); 
	}

		// toán tử nhân float với vec3
	friend vec3 operator * (float num, const vec3& u) 
	{ 
		return vec3(num * u.x, num * u.y, num * u.z); 
	}
		
		// toán tử nhân vec3 với vec3
	friend vec3 operator * (const vec3& u, const vec3& v) 
	{ 
		return vec3(u.x * v.x, u.y * v.y, u.z * v.z); 
	}

		// toán tử chia vec3 với float
	friend vec3 operator / (const vec3& u, float num) 
	{ 
		return vec3(u.x / num, u.y / num, u.z / num); 
	}

		// toán tử chia float với vec3
	friend vec3 operator / (float num, const vec3& u) 
	{ 
		return vec3(num / u.x, num / u.y, num / u.z); 
	}

		// toán tử chia vec3 với vec3
	friend vec3 operator / (const vec3& u, const vec3& v) 
	{ 
		return vec3(u.x / v.x, u.y / v.y, u.z / v.z); 
	}
};
	// các hàm
vec3 cross(const vec3& u, const vec3& v);
float dot(const vec3& u, const vec3& v);
float length(const vec3& u);
float length2(const vec3& u);
vec3 mix(const vec3& u, const vec3& v, float a);
vec3 normalize(const vec3& u);
vec3 reflect(const vec3& i, const vec3& n);
vec3 refract(const vec3& i, const vec3& n, float eta);
vec3 rotate(const vec3& u, float angle, const vec3& v);

	// tích chéo
vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

	// tích điểm
float dot(const vec3& u, const vec3& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

	// độ dài
float length(const vec3& u)
{
	return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

	// độ dài bp
float length2(const vec3& u)
{
	return u.x * u.x + u.y * u.y + u.z * u.z;
}

	//
vec3 mix(const vec3& u, const vec3& v, float a)
{
	return u * (1.0f - a) + v * a;
}

	//
vec3 normalize(const vec3& u)
{
	return u / sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
}

	// 
vec3 reflect(const vec3& i, const vec3& n)
{
	return i - 2.0f * dot(n, i) * n;
}

	//
vec3 refract(const vec3& i, const vec3& n, float eta)
{
	vec3 r;

	float ndoti = dot(n, i), k = 1.0f - eta * eta * (1.0f - ndoti * ndoti);

	if (k >= 0.0f)
	{
		r = eta * i - n * (eta * ndoti + sqrt(k));
	}

	return r;
}

/*vec3 rotate(const vec3& u, float angle, const vec3& v)
{
	return *(vec3*)&(rotate(angle, v) * vec4(u, 1.0f));
}*/
// Hết định nghĩa kểu vector 3D
//-----------------------------------------------

	// Định nghĩa kiểu vector 4D

class vec4
{
public:
	union {
		struct { float x, y, z, w; };
		struct { float s, t, p, q; };
		struct { float r, g, b, a; };
	};
		// tạo tử
	vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	~vec4() {}
	vec4(float num) : x(num), y(num), z(num), w(num) {}
	vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	vec4(const vec2& u, float z, float w) : x(u.x), y(u.y), z(z), w(w) {}
	vec4(const vec3& u, float w) : x(u.x), y(u.y), z(u.z), w(w) {}
	vec4(const vec4& u) : x(u.x), y(u.y), z(u.z), w(u.w) {}

		// toán tử gán vec4 cho vec4
	vec4& operator = (const vec4& u) 
	{ 
		x = u.x; 
		y = u.y; 
		z = u.z; 
		w = u.w; 
		return *this; 
	}

		// toán tử âm
	vec4 operator - () 
	{ 
		return vec4(-x, -y, -z, -w); 
	}

		// toán tử lấy địa chỉ
	float* operator & () 
	{ 
		return (float*)this; 
	}

		// toán tử cộng gán với float
	vec4& operator += (float num) 
	{ 
		x += num; 
		y += num; 
		z += num; 
		w += num; 
		return *this; 
	}

		// toán tử cộng gán với vec4
	vec4& operator += (const vec4& u) 
	{ 
		x += u.x; 
		y += u.y; 
		z += u.z; 
		w += u.w; 
		return *this; 
	}

		// toán tử trừ gán với float
	vec4& operator -= (float num) 
	{ 
		x -= num; 
		y -= num; 
		z -= num; 
		w -= num; 
		return *this; 
	}

		// toán tử trừ gán với vec4
	vec4& operator -= (const vec4& u) 
	{ 
		x -= u.x; 
		y -= u.y; 
		z -= u.z; 
		w -= u.w; 
		return *this; 
	}

		// toán tử nhân gán với float
	vec4& operator *= (float num) 
	{ 
		x *= num; 
		y *= num; 
		z *= num; 
		w *= num; 
		return *this; 
	}

		// toán tử nhân gán với vec4
	vec4& operator *= (const vec4& u) 
	{ 
		x *= u.x; 
		y *= u.y; 
		z *= u.z; 
		w *= u.w; 
		return *this; 
	}

		// toán tử chia gán với float
	vec4& operator /= (float num) 
	{ 
		x /= num; 
		y /= num; 
		z /= num; 
		w /= num; 
		return *this; 
	}

		// toán tử chia gán với vec4
	vec4& operator /= (const vec4& u) 
	{ 
		x /= u.x; 
		y /= u.y; 
		z /= u.z; 
		w /= u.w; 
		return *this; 
	}

		// toán tử cộng vec4 với float
	friend vec4 operator + (const vec4& u, float num) 
	{ 
		return vec4(u.x + num, u.y + num, u.z + num, u.w + num); 
	}

		// toán tử cộng float với vec4
	friend vec4 operator + (float num, const vec4& u) 
	{ 
		return vec4(num + u.x, num + u.y, num + u.z, num + u.w); 
	}

		// toán tử cộng vec4 với vec4
	friend vec4 operator + (const vec4& u, const vec4& v) 
	{ 
		return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w); 
	}

		// toán tử trừ vec4 với float
	friend vec4 operator - (const vec4& u, float num) 
	{ 
		return vec4(u.x - num, u.y - num, u.z - num, u.w - num); 
	}

		// toán tử trừ float với vec4
	friend vec4 operator - (float num, const vec4& u) 
	{ 
		return vec4(num - u.x, num - u.y, num - u.z, num - u.w); 
	}

		// toán tử trừ vec4 với vec4
	friend vec4 operator - (const vec4& u, const vec4& v) 
	{ 
		return vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w); 
	}

		// toán tử nhân vec4 với float
	friend vec4 operator * (const vec4& u, float num) 
	{ 
		return vec4(u.x * num, u.y * num, u.z * num, u.w * num); 
	}

		// toán tử nhân float với vec4
	friend vec4 operator * (float num, const vec4& u) 
	{ 
		return vec4(num * u.x, num * u.y, num * u.z, num * u.w); 
	}

		// toán tử nhân vec4 với vec4
	friend vec4 operator * (const vec4& u, const vec4& v) 
	{ 
		return vec4(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w); 
	}

		// toán tử chia vec4 với float
	friend vec4 operator / (const vec4& u, float num) 
	{ 
		return vec4(u.x / num, u.y / num, u.z / num, u.w / num); 
	}

		// toán tử chia float với vec4
	friend vec4 operator / (float num, const vec4& u) 
	{ 
		return vec4(num / u.x, num / u.y, num / u.z, num / u.w); 
	}

		// toán tử chia vec4 với vec4
	friend vec4 operator / (const vec4& u, const vec4& v) 
	{ 
		return vec4(u.x / v.x, u.y / v.y, u.z / v.z, u.w / v.w); 
	}
};

// Hết định nghĩa kiểu vector 4D
//-----------------------------------------------

// khai báo các lớp sẽ tạo
class mat2;
class mat3;
class mat4;

//----------------------------------------------- 
//Định nghĩa kiểu ma trận 2x2
class mat2
{
public:

	float m[4];

	mat2();
	~mat2();
	mat2(const mat2& a);
	mat2(const vec2& a, const vec2& b);
	mat2(float a0, float a1, float a2, float a3);
	explicit mat2(const mat3& a);
	explicit mat2(const mat4& a);

	mat2& operator = (const mat2& a);
	float& operator [] (int i);
	float* operator & ();
	friend mat2 operator * (const mat2& a, const mat2& b);
	friend vec2 operator * (const mat2& a, const vec2& u);
};
mat2 inverse(const mat2& a);
mat2 transpose(const mat2& b);

	// tạo mat2 đơn vị
mat2::mat2()
{
	m[0] = 1.0f;	m[2] = 0.0f;
	m[1] = 0.0f;	m[3] = 1.0f;
}

	// hủy tử
mat2::~mat2()
{
}

	// tạo mat2 từ mat2
mat2::mat2(const mat2& a)
{
	for (int i = 0; i < 4; i++)
	{
		m[i] = a.m[i];
	}
}

	// tạo mat2 từ 2 vec2
mat2::mat2(const vec2& a, const vec2& b)
{
	m[0] = a.x;		m[2] = b.x;
	m[1] = a.y;		m[3] = b.y;
}

	// tạo mat2 từ 4 float
mat2::mat2(float a0, float a1, float a2, float a3)
{
	m[0] = a0;	m[2] = a2;
	m[1] = a1;	m[3] = a3;
}

/*mat2::mat2(const mat3& a)
{
	m[0] = a.m[0]; m[2] = a.m[3];
	m[1] = a.m[1]; m[3] = a.m[4];
}*/

/*mat2::mat2(const mat4& a)
{
	m[0] = a.m[0]; m[2] = a.m[4];
	m[1] = a.m[1]; m[3] = a.m[5];
}*/

	// toán tử gán
mat2& mat2::operator = (const mat2& a)
{
	for (int i = 0; i < 4; i++)
	{
		m[i] = a.m[i];
	}

	return *this;
}

	// toán tử lấy giá trị 1 phần tử
float& mat2::operator [] (int i)
{
	return m[i];
}

	// toán tử lấy địa chỉ
float* mat2::operator & ()
{
	return (float*)this;
}

	// toán tử nhân mat2 với mat2
	/*
		a = [a0, a1, a2, a3]
		b = [b0, b1, b2, b3]

		a0	a2		b0	b2		a0*b0 + a2*b1	a0*b2 + a2*b3
				x			=
		a1	a3		b1	b3		a1*b0 + a3*b1	a1*b2 + a3*b3	

		c = [a0*b0 + a2*b1, a1*b0 + a3*b1, a0*b2 + a2*b3, a1*b2 + a3*b3]
	*/
mat2 operator * (const mat2& a, const mat2& b)
{
	mat2 m3;

	m3.m[0] = a.m[0] * b.m[0] + a.m[2] * b.m[1];	m3.m[2] = a.m[0] * b.m[2] + a.m[2] * b.m[3];
	m3.m[1] = a.m[1] * b.m[0] + a.m[3] * b.m[1];	m3.m[3] = a.m[1] * b.m[2] + a.m[3] * b.m[3];	

	return m3;
}

	// toán tử nhân mat2 với vec2
	/*
		a = [a0, a1, a2, a3]
		b = [x, y]

		a0	a2		x			a0*x + a2*y	
				x			=
		a1	a3		y			a1*x + a3*y	

		c = [a0*x + a2*y, a1*x + a3*y]
	*/
vec2 operator * (const mat2& m, const vec2& u)
{
	vec2 v;

	v.x = m.m[0] * u.x + m.m[2] * u.y;
	v.y = m.m[1] * u.x + m.m[3] * u.y;

	return v;
}
	// Hết định nghĩa kiểu ma trận 2x2
//-----------------------------------------------

class mat3
{
public:
		//Dữ liệu nội bộ
		/* m[9] = [0, 1, 2, 3, 4, 5, 6, 7, 8]
		Biểu diễn dạng cột như sau:
		0  3  6
		1  4  7
		2  5  8
		*/
	float m[9];

	mat3();
	~mat3();
	mat3(const mat3& m1);
	mat3(const vec3& col1, const vec3& col2, const vec3& col3);
	mat3(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8);
	explicit mat3(const mat2& m1);
	explicit mat3(const mat4& m1);
	
	mat3& operator = (const mat3& m1);
	float& operator [] (int i);
	float* operator & ();
	friend mat3 operator * (const mat3& m1, const mat3& m2);
	friend vec3 operator * (const mat3& m1, const vec3& u);
};
mat3 inverse(const mat3& m1);
mat3 transpose(const mat3& m1);

	// tạo mat3 đơn vị	
mat3::mat3()
{
	m[0] = 1.0f;	m[3] = 0.0f;	m[6] = 0.0f;
	m[1] = 0.0f;	m[4] = 1.0f;	m[7] = 0.0f;
	m[2] = 0.0f;	m[5] = 0.0f;	m[8] = 1.0f;
}

	// hủy tử
mat3::~mat3()
{
}

	// tạo mat3 từ mat3
mat3::mat3(const mat3& a)
{
	for (int i = 0; i < 9; i++)
	{
		m[i] = a.m[i];
	}
}

	// tạo mat3 từ 3 vec3
mat3::mat3(const vec3& a, const vec3& b, const vec3& c)
{
	m[0] = a.x;		m[3] = b.x;		m[6] = c.x;
	m[1] = a.y;		m[4] = b.y;		m[7] = c.y;
	m[2] = a.z;		m[5] = b.z;		m[8] = c.z;
}

	// tạo mat3 từ 9 float
mat3::mat3(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8)
{
	m[0] = a0;	m[3] = a3;	m[6] = a6;
	m[1] = a1;	m[4] = a4;	m[7] = a7;
	m[2] = a2;	m[5] = a5;	m[8] = a8;
}

	// tạo mat3 từ mat2
mat3::mat3(const mat2& a)
{
	m[0] = a.m[0];		m[3] = a.m[2];		m[6] = 0.0f;
	m[1] = a.m[1];		m[4] = a.m[3];		m[7] = 0.0f;
	m[2] = 0.0f;		m[5] = 0.0f;		m[8] = 1.0f;
}

/*mat3::mat3(const mat4& m1)
{
	m[0] = m1.m[0]; m[3] = m1.m[4]; m[6] = m1.m[8];
	m[1] = m1.m[1]; m[4] = m1.m[5]; m[7] = m1.m[9];
	m[2] = m1.m[2]; m[5] = m1.m[6]; m[8] = m1.m[10];
}*/

	// toán tử gán
mat3& mat3::operator = (const mat3& a)
{
	for (int i = 0; i < 9; i++)
	{
		m[i] = a.m[i];
	}

	return *this;
}

	// toán tử lấy giá trị phần tử của mat3
float& mat3::operator [] (int i)
{
	return m[i];
}

	// toán tử lấy địa chỉ
float* mat3::operator & ()
{
	return (float*)this;
}

	// toán tử nhân mat3 với mat3
	/*
		a = [a0, a1, a2, a3, a4, a5, a6, a7, a8]
		b = [b0, b1, b2, b3, b4, b5, b6, b7, b8]

		a0	a3	a6		b0	b3	b6		a0*b0 + a3*b1 + a6*b2	a0*b3 + a3*b4 + a6*b5	a0*b6 + a3*b7 + a6*b8
									
		a1	a4	a7	x	b1	b4	b7	=	a1*b0 + a4*b1 + a7*b2	a1*b3 + a4*b4 + a7*b5	a1*b6 + a4*b7 + a7*b8

		a2	a5	a8		b2	b5	b8		a2*b0 + a5*b1 + a8*b2	a2*b3 + a5*b4 + a8*b5	a2*b6 + a5*b7 + a8*b8

		c = [a0*b0 + a3*b1 + a6*b2, a1*b0 + a4*b1 + a7*b2, a2*b0 + a5*b1 + a8*b2, a0*b3 + a3*b4 + a6*b5, a1*b3 + a4*b4 + a7*b5, a2*b3 + a5*b4 + a8*b5,a0*b6 + a3*b7 + a6*b8,a1*b6 + a4*b7 + a7*b8,a2*b6 + a5*b7 + a8*b8]
	*/
mat3 operator * (const mat3& a, const mat3& b)
{
	mat3 c;

	c.m[0] = a.m[0] * b.m[0] + a.m[3] * b.m[1] + a.m[6] * b.m[2];
	c.m[1] = a.m[1] * b.m[0] + a.m[4] * b.m[1] + a.m[7] * b.m[2];
	c.m[2] = a.m[2] * b.m[0] + a.m[5] * b.m[1] + a.m[8] * b.m[2];

	c.m[3] = a.m[0] * b.m[3] + a.m[3] * b.m[4] + a.m[6] * b.m[5];
	c.m[4] = a.m[1] * b.m[3] + a.m[4] * b.m[4] + a.m[7] * b.m[5];
	c.m[5] = a.m[2] * b.m[3] + a.m[5] * b.m[4] + a.m[8] * b.m[5];

	c.m[6] = a.m[0] * b.m[6] + a.m[3] * b.m[7] + a.m[6] * b.m[8];
	c.m[7] = a.m[1] * b.m[6] + a.m[4] * b.m[7] + a.m[7] * b.m[8];
	c.m[8] = a.m[2] * b.m[6] + a.m[5] * b.m[7] + a.m[8] * b.m[8];

	return c;
}

	// toán tử nhân mat3 với vec3
vec3 operator * (const mat3& a, const vec3& u)
{
	vec3 v;

	v.x = a.m[0] * u.x + a.m[3] * u.y + a.m[6] * u.z;
	v.y = a.m[1] * u.x + a.m[4] * u.y + a.m[7] * u.z;
	v.z = a.m[2] * u.x + a.m[5] * u.y + a.m[8] * u.z;

	return v;
}
// ------------------------------------------------------------------

float det2x2sub(const float* m, int i0, int i1, int i2, int i3)
{
	return m[i0] * m[i3] - m[i2] * m[i1];
}

mat3 inverse(const mat3& m1)
{
	const float* mp = m1.m;

	float det = 0.0f;

	det += mp[0] * det2x2sub(mp, 4, 5, 7, 8);
	det -= mp[3] * det2x2sub(mp, 1, 2, 7, 8);
	det += mp[6] * det2x2sub(mp, 1, 2, 4, 5);

	mat3 Inverse;

	Inverse.m[0] = det2x2sub(mp, 4, 5, 7, 8) / det;
	Inverse.m[1] = -det2x2sub(mp, 1, 2, 7, 8) / det;
	Inverse.m[2] = det2x2sub(mp, 1, 2, 4, 5) / det;
	Inverse.m[3] = -det2x2sub(mp, 3, 5, 6, 8) / det;
	Inverse.m[4] = det2x2sub(mp, 0, 2, 6, 8) / det;
	Inverse.m[5] = -det2x2sub(mp, 0, 2, 3, 5) / det;
	Inverse.m[6] = det2x2sub(mp, 3, 4, 6, 7) / det;
	Inverse.m[7] = -det2x2sub(mp, 0, 1, 6, 7) / det;
	Inverse.m[8] = det2x2sub(mp, 0, 1, 3, 4) / det;

	return Inverse;
}

mat3 transpose(const mat3& m1)
{
	mat3 t;

	t.m[0] = m1.m[0];
	t.m[1] = m1.m[3];
	t.m[2] = m1.m[6];
	t.m[3] = m1.m[1];
	t.m[4] = m1.m[4];
	t.m[5] = m1.m[7];
	t.m[6] = m1.m[2];
	t.m[7] = m1.m[5];
	t.m[8] = m1.m[8];

	return t;
}

	// tạo ma trận 0
mat3 zero_mat3() {
	return mat3(
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f);
}

//Hết định nghĩa kiểu ma trận 3x3
// ----------------------------------------------

	// Định nghĩa kiểu ma trận 4x4

class mat4
{
public:
	//Dữ liệu nội bộ
	/* m[16] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	OpenGL đọc vào dạng cột:
	0  4  8 12
	1  5  9 13
	2  6 10 14
	3  7 11 15
	*/
	float m[16];

		// tạo tử và hủy tử
	mat4();
	~mat4();
	mat4(const mat4& a);
	mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d);
	mat4(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11, float a12, float a13, float a14, float a15);
	explicit mat4(const mat2& a);
	explicit mat4(const mat3& a);
	
		// toán tử
	mat4& operator = (const mat4& a);
	float& operator [] (int i);
	float* operator & ();
	friend mat4 operator * (const mat4& a, const mat4& b);
	friend vec4 operator * (const mat4& a, const vec4& u);
};
extern mat4 BiasMatrix;
extern mat4 BiasMatrixInverse;

	// khởi tạo mat4 đơn vị
mat4::mat4()
{
	m[0] = 1.0f;	m[4] = 0.0f;	m[8] = 0.0f;	m[12] = 0.0f;
	m[1] = 0.0f;	m[5] = 1.0f;	m[9] = 0.0f;	m[13] = 0.0f;
	m[2] = 0.0f;	m[6] = 0.0f;	m[10] = 1.0f;	m[14] = 0.0f;
	m[3] = 0.0f;	m[7] = 0.0f;	m[11] = 0.0f;	m[15] = 1.0f;
}

	// hủy tử
mat4::~mat4()
{
}

	// tạo mat4 từ mat4
mat4::mat4(const mat4& a)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = a.m[i];
	}
}

	// tạo mat4 từ 4 vec4
mat4::mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d)
{
	m[0] = a.x;		m[4] = b.x;		m[8] = c.x;		m[12] = d.x;
	m[1] = a.y;		m[5] = b.y;		m[9] = c.y;		m[13] = d.y;
	m[2] = a.z;		m[6] = b.z;		m[10] = c.z;	m[14] = d.z;
	m[3] = a.w;		m[7] = b.w;		m[11] = c.w;	m[15] = d.w;
}

	// tạo mat4 từ 16 giá trị thực
mat4:: mat4(float a0,	float a1,	float a2,	float a3,
			float a4,	float a5,	float a6,	float a7,
			float a8,	float a9,	float a10,	float a11,
			float a12,	float a13,	float a14,	float a15)
{
	// opengl đọc dạng cột, 4 phần tử liên tiếp trong mảng 1 chiều tạo thành 1 cột
	m[0] = a0;		m[4] = a4;		m[8] = a8;		m[12] = a12;
	m[1] = a1;		m[5] = a5;		m[9] = a9;		m[13] = a13;
	m[2] = a2;		m[6] = a6;		m[10] = a10;	m[14] = a14;
	m[3] = a3;		m[7] = a7;		m[11] = a11;	m[15] = a15;
}

	// tạo mat4 từ 1 mat2
mat4::mat4(const mat2& a)
{
	m[0] = a.m[0];		m[4] = a.m[2];		m[8] = 0.0f;	m[12] = 0.0f;
	m[1] = a.m[1];		m[5] = a.m[3];		m[9] = 0.0f;	m[13] = 0.0f;
	m[2] = 0.0f;		m[6] = 0.0f;		m[10] = 1.0f;	m[14] = 0.0f;
	m[3] = 0.0f;		m[7] = 0.0f;		m[11] = 0.0f;	m[15] = 1.0f;
}

	// tạo mat4 từ 1 mat3
mat4::mat4(const mat3& a)
{
	m[0] = a.m[0];		m[4] = a.m[3];		m[8]  = a.m[6];		m[12] = 0.0f;
	m[1] = a.m[1];		m[5] = a.m[4];		m[9]  = a.m[7];		m[13] = 0.0f;
	m[2] = a.m[2];		m[6] = a.m[5];		m[10] = a.m[8];		m[14] = 0.0f;
	m[3] = 0.0f;		m[7] = 0.0f;		m[11] = 0.0f;		m[15] = 1.0f;
}

	// toán tử gán mat4 cho mat4
mat4& mat4::operator = (const mat4& a)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = a.m[i];
	}

	return *this;
}

	// toán tử lấy giá trị phần tử mat4[i]
float& mat4::operator [] (int i)
{
	return m[i];
}

	// toán tử lấy địa chỉ
float* mat4::operator & ()
{
	return (float*)this;
}

	// tạo mat4 0
mat4 zero_mat4() {
	return mat4(
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f);
}

// tạo mat4 đơn vị
mat4 identity_mat4() {
	return mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
	// toán tử nhân mat4 với mat4
	/*
		a = [a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15 ]
		b = [b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15 ]

		a0	a4	a8		a12				b0	b4	b8		b12		

		a1	a5	a9		a13				b1	b5	b9		b13	
								x
		a2	a6	a10		a14				b2	b6	b10		b14

		a3	a7	a11		a15				b3	b7	b11		b15


	*/
mat4 operator * (const mat4& a, const mat4& b)
{
	mat4 m3;

	m3.m[0]  = a.m[0] * b.m[0]  + a.m[4] * b.m[1]  + a.m[8]   * b.m[2]  + a.m[12] * b.m[3];
	m3.m[1]  = a.m[1] * b.m[0]  + a.m[5] * b.m[1]  + a.m[9]   * b.m[2]  + a.m[13] * b.m[3];
	m3.m[2]  = a.m[2] * b.m[0]  + a.m[6] * b.m[1]  + a.m[10]  * b.m[2]  + a.m[14] * b.m[3];
	m3.m[3]  = a.m[3] * b.m[0]  + a.m[7] * b.m[1]  + a.m[11]  * b.m[2]  + a.m[15] * b.m[3];

	m3.m[4]  = a.m[0] * b.m[4]  + a.m[4] * b.m[5]  + a.m[8]   * b.m[6]  + a.m[12] * b.m[7];
	m3.m[5]  = a.m[1] * b.m[4]  + a.m[5] * b.m[5]  + a.m[9]   * b.m[6]  + a.m[13] * b.m[7];
	m3.m[6]  = a.m[2] * b.m[4]  + a.m[6] * b.m[5]  + a.m[10]  * b.m[6]  + a.m[14] * b.m[7];
	m3.m[7]  = a.m[3] * b.m[4]  + a.m[7] * b.m[5]  + a.m[11]  * b.m[6]  + a.m[15] * b.m[7];

	m3.m[8]  = a.m[0] * b.m[8]  + a.m[4] * b.m[9]  + a.m[8]   * b.m[10] + a.m[12] * b.m[11];
	m3.m[9]  = a.m[1] * b.m[8]  + a.m[5] * b.m[9]  + a.m[9]   * b.m[10] + a.m[13] * b.m[11];
	m3.m[10] = a.m[2] * b.m[8]  + a.m[6] * b.m[9]  + a.m[10]  * b.m[10] + a.m[14] * b.m[11];
	m3.m[11] = a.m[3] * b.m[8]  + a.m[7] * b.m[9]  + a.m[11]  * b.m[10] + a.m[15] * b.m[11];

	m3.m[12] = a.m[0] * b.m[12] + a.m[4] * b.m[13] + a.m[8]   * b.m[14] + a.m[12] * b.m[15];
	m3.m[13] = a.m[1] * b.m[12] + a.m[5] * b.m[13] + a.m[9]   * b.m[14] + a.m[13] * b.m[15];
	m3.m[14] = a.m[2] * b.m[12] + a.m[6] * b.m[13] + a.m[10]  * b.m[14] + a.m[14] * b.m[15];
	m3.m[15] = a.m[3] * b.m[12] + a.m[7] * b.m[13] + a.m[11]  * b.m[14] + a.m[15] * b.m[15];

	return m3;
}
/* cách 2
mat4 operator*(const mat4& a) {
	mat4 r = zero_mat4();
	int r_index = 0;
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 4; row++)
		{
			float sum = 0.0f;
			for (int i = 0; i < 4; i++) {
				sum += a.m[i + col * 4] * m[row + i * 4];
			}
			r.m[r_index] = sum;
			r_index++;
		}
	}
	return r;
}*/

	// toán tử nhân mat4 với vec4
vec4 operator * (const mat4& a, const vec4& u)
{
	vec4 v;

	v.x = a.m[0] * u.x + a.m[4] * u.y + a.m[8]  * u.z + a.m[12] * u.w;
	v.y = a.m[1] * u.x + a.m[5] * u.y + a.m[9]  * u.z + a.m[13] * u.w;
	v.z = a.m[2] * u.x + a.m[6] * u.y + a.m[10] * u.z + a.m[14] * u.w;
	v.w = a.m[3] * u.x + a.m[7] * u.y + a.m[11] * u.z + a.m[15] * u.w;

	return v;
}

// ----------------------------------------------------------------------------------------------------------------------------

mat4 BiasMatrix = mat4(0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f);
mat4 BiasMatrixInverse = mat4(2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, -1.0f, -1.0f, -1.0f, 1.0f);

// --------------------------------------------------------------------

float det3x3sub(const float* m, int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
{
	float det = 0.0f;

	det += m[i0] * det2x2sub(m, i4, i5, i7, i8);
	det -= m[i3] * det2x2sub(m, i1, i2, i7, i8);
	det += m[i6] * det2x2sub(m, i1, i2, i4, i5);

	return det;
}

mat4 inverse(const mat4& m1)
{
	const float* mp = m1.m;

	float det = 0.0f;

	det += mp[0] * det3x3sub(mp, 5, 6, 7, 9, 10, 11, 13, 14, 15);
	det -= mp[4] * det3x3sub(mp, 1, 2, 3, 9, 10, 11, 13, 14, 15);
	det += mp[8] * det3x3sub(mp, 1, 2, 3, 5, 6, 7, 13, 14, 15);
	det -= mp[12] * det3x3sub(mp, 1, 2, 3, 5, 6, 7, 9, 10, 11);

	mat4 Inverse;

	Inverse.m[0] = det3x3sub(mp, 5, 6, 7, 9, 10, 11, 13, 14, 15) / det;
	Inverse.m[1] = -det3x3sub(mp, 1, 2, 3, 9, 10, 11, 13, 14, 15) / det;
	Inverse.m[2] = det3x3sub(mp, 1, 2, 3, 5, 6, 7, 13, 14, 15) / det;
	Inverse.m[3] = -det3x3sub(mp, 1, 2, 3, 5, 6, 7, 9, 10, 11) / det;
	Inverse.m[4] = -det3x3sub(mp, 4, 6, 7, 8, 10, 11, 12, 14, 15) / det;
	Inverse.m[5] = det3x3sub(mp, 0, 2, 3, 8, 10, 11, 12, 14, 15) / det;
	Inverse.m[6] = -det3x3sub(mp, 0, 2, 3, 4, 6, 7, 12, 14, 15) / det;
	Inverse.m[7] = det3x3sub(mp, 0, 2, 3, 4, 6, 7, 8, 10, 11) / det;
	Inverse.m[8] = det3x3sub(mp, 4, 5, 7, 8, 9, 11, 12, 13, 15) / det;
	Inverse.m[9] = -det3x3sub(mp, 0, 1, 3, 8, 9, 11, 12, 13, 15) / det;
	Inverse.m[10] = det3x3sub(mp, 0, 1, 3, 4, 5, 7, 12, 13, 15) / det;
	Inverse.m[11] = -det3x3sub(mp, 0, 1, 3, 4, 5, 7, 8, 9, 11) / det;
	Inverse.m[12] = -det3x3sub(mp, 4, 5, 6, 8, 9, 10, 12, 13, 14) / det;
	Inverse.m[13] = det3x3sub(mp, 0, 1, 2, 8, 9, 10, 12, 13, 14) / det;
	Inverse.m[14] = -det3x3sub(mp, 0, 1, 2, 4, 5, 6, 12, 13, 14) / det;
	Inverse.m[15] = det3x3sub(mp, 0, 1, 2, 4, 5, 6, 8, 9, 10) / det;

	return Inverse;
}

	// chuyển vị
mat4 transpose(const mat4& a)
{
	mat4 t;

	t.m[0] = a.m[0];
	t.m[1] = a.m[4];
	t.m[2] = a.m[8];
	t.m[3] = a.m[12];
	t.m[4] = a.m[1];
	t.m[5] = a.m[5];
	t.m[6] = a.m[9];
	t.m[7] = a.m[13];
	t.m[8] = a.m[2];
	t.m[9] = a.m[6];
	t.m[10] = a.m[10];
	t.m[11] = a.m[14];
	t.m[12] = a.m[3];
	t.m[13] = a.m[7];
	t.m[14] = a.m[11];
	t.m[15] = a.m[15];

	return t;
}

//---------------------------------------------------------------
/* m[16] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	OpenGL đọc vào dạng cột:
	0  4  8 12
	1  5  9 13
	2  6 10 14
	3  7 11 15
	*/
// Hàm tạo ma trận tịnh tiến với đầu vào là vec3(x y z)
	// cách 1
mat4 translate(const vec3& tv) {
	return mat4(
		1.0f,		0.0f,		0.0f,		0.0f,
		0.0f,		1.0f,		0.0f,		0.0f,
		0.0f,		0.0f,		1.0f,		0.0f,
		tv.x,		tv.y,		tv.z,		1.0);

	/* opengl đọc
		1.0f		0.0f	0.0f	tv.v[0]
		0.0f		1.0f	0.0f	tv.v[1]
		0.0f		0.0f	1.0f	tv.v[2]
		0.0f		0.0f	0.0f	1.0f
	*/
}
	// cách 2
/*mat4 translate(const mat4& m, const vec3& v) {
	mat4 m_t = identity_mat4();
	m_t.m[12] = v.v[0];
	m_t.m[13] = v.v[1];
	m_t.m[14] = v.v[2];
	return m_t * m;
}*/
//---------------------------------------------------------------

/* m[16] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	OpenGL đọc vào dạng cột:
	0  4  8 12
	1  5  9 13
	2  6 10 14
	3  7 11 15
	*/
// Hàm quay tạo ma trận quanh trục x 4x4 với góc quay tính bằng độ
/*		1.0,	0.0,			 0.0f,		0.0f,
		0.0,	cosf(deg),	-sinf(deg),		0.0f,
		0.0f,	sinf(deg),	 cosf(deg),		0.0f,
		0.0f,	0.0f,			 0.0f,		1.0f */

mat4 rotate_x(float deg) {
	return mat4(
		1.0f,	0.0f,								0.0f,								0.0f,
		0.0f,	cosf(deg * degrees_to_radians),		sinf(deg * degrees_to_radians),		0.0f,
		0.0f,	-sinf(deg * degrees_to_radians),	cosf(deg * degrees_to_radians),		0.0f,
		0.0f,	0.0f,								0.0f,								1.0f);
}
	/* opengl đọc
		1.0f		0.0f							0.0f							0.0f
		0.0f		cosf(deg * degrees_to_radians)	-sinf(deg * degrees_to_radians)	0.0f
		0.0f		sinf(deg * degrees_to_radians)	cosf(deg * degrees_to_radians)	0.0f
		0.0f		0.0f							0.0f							1.0f
	*/

	/*/ cách 2
mat4 rotate_x_deg(const mat4& m, float deg) {
	float rad = deg * degrees_to_radians;
	mat4 m_r;
	m_r.m[5] = cos(rad);
	m_r.m[6] = sin(rad);
	m_r.m[9] = -sin(rad);	
	m_r.m[10] = cos(rad);
	return m_r * m;
}*/
//---------------------------------------------------------------
/* m[16] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	OpenGL đọc vào dạng cột:
	0  4  8 12
	1  5  9 13
	2  6 10 14
	3  7 11 15
	*/
// Hàm quay tạo ma trận quanh trục y 4x4 với góc quay tính bằng độ
/*	cosf(deg),	0.0,	sinf(deg),	0.0f,
	0.0,		1.0,	0.0f,		0.0f,
	-sinf(deg),	0.0f,	cosf(deg),	0.0f,
	0.0f,		0.0f,	0.0f,		1.0f */

mat4 rotate_y(float deg) {
	return mat4(
		cosf(deg * degrees_to_radians),		0.0f,	-sinf(deg * degrees_to_radians),	0.0f,
		0.0f,								1.0f,	0.0f,								0.0f,
		sinf(deg * degrees_to_radians),		0.0f,	cosf(deg * degrees_to_radians),		0.0f,
		0.0f,								0.0f,	0.0f,								1.0f);
	/* opengl đọc
		cosf(deg * degrees_to_radians)		0.0f	sinf(deg * degrees_to_radians)	0.0f
		0.0f								1.0f	0.0f							0.0f
		-sinf(deg * degrees_to_radians)		0.0f	cosf(deg * degrees_to_radians)	0.0f
		0.0f								0.0f	0.0f							1.0f
	*/
}
	/*/ cách 2
mat4 rotate_y_deg(const mat4& m, float deg) {
	float rad = deg * degrees_to_radians;
	mat4 m_r;
	m_r.m[0] = cos(rad);
	m_r.m[2] = -sin(rad);
	m_r.m[8] = sin(rad);	
	m_r.m[10] = cos(rad);
	return m_r * m;
}*/
//---------------------------------------------------------------
/* m[16] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	OpenGL đọc vào dạng cột:
	0  4  8 12
	1  5  9 13
	2  6 10 14
	3  7 11 15
	*/
// Hàm quay tạo ma trận quanh trục z 4x4 với góc quay tính bằng độ
/*	cosf(deg),	-sinf(deg),	0.0f,	0.0f,
	sinf(deg),	cosf(deg),	0.0f,	0.0f,
	0.0f,		0.0f,		1.0f,	0.0f,
	0.0f,		0.0f,		0.0f,	1.0f */

mat4 rotate_z(float deg) {
	return mat4(
		cosf(deg * degrees_to_radians),		sinf(deg * degrees_to_radians),		0.0f,	0.0f,
		-sinf(deg * degrees_to_radians),	cosf(deg * degrees_to_radians),		0.0f,	0.0f,
		0.0f,								0.0f,								1.0f,	0.0f,
		0.0f,								0.0f,								0.0f,	1.0f);
	/* opengl đọc
		cosf(deg * degrees_to_radians)		-sinf(deg * degrees_to_radians)	0.0f	0.0f
		sinf(deg * degrees_to_radians)		cosf(deg * degrees_to_radians)	0.0f	0.0f
		0.0f								0.0f							1.0f	0.0f
		0.0f								0.0f							0.0f	1.0f
	*/
}
	/*/ cách 2
mat4 rotate_z_deg(const mat4& m, float deg) {
	float rad = deg * degrees_to_radians;
	mat4 m_r;
	m_r.m[0] = cos(rad);
	m_r.m[1] = sin(rad);
	m_r.m[4] = -sin(rad);	
	m_r.m[5] = cos(rad);
	return m_r * m;
}*/



//---------------------------------------------------------------
/* m[16] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	OpenGL đọc vào dạng cột:
	0  4  8 12
	1  5  9 13
	2  6 10 14
	3  7 11 15
	*/
// Hàm tạo ma trận biến đổi tỷ lệ 4x4 với hệ số tỷ lệ trong mảng [x, y, z]
	/*	uSx, 0.0, 0.0, 0.0,
		0.0, uSy, 0.0, 0.0,
		0.0, 0.0, uSz, 0.0,
		0.0, 0.0, 0.0, 1.0)
	*/
mat4 scale(const vec3& sv) {
	return mat4(
		sv.x,		0.0f,		0.0f,		0.0f,
		0.0f,		sv.y,		0.0f,		0.0f,
		0.0f,		0.0f,		sv.z,		0.0f,
		0.0f,		0.0f,		0.0f,		1.0f);
}
	/*/ cách 2
mat4 _scale(const mat4& m, const vec3& v) {
	mat4 a;
	a.m[0] = v.x;
	a.m[5] = v.y;
	a.m[10] = v.z;
	return a * m;
}*/
		

// Hết định nghĩa kiểu ma trận 4x4
//-----------------------------------------------


/*-----------------------VIRTUAL CAMERA MATRIX FUNCTIONS----------------------*/
// returns a view matrix using the opengl lookAt style. COLUMN ORDER.

// Camera
/* m[16] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	OpenGL đọc vào dạng cột:
	0  4  8 12
	1  5  9 13
	2  6 10 14
	3  7 11 15
	*/
mat4 lookat(vec3& eye, vec3& at, const vec3& up) {
	vec3 n = normalize(eye - at);		// n(z)
	vec3 u = normalize(cross(n, up));	// u(x) là tích có hướng của n(z) và up
	vec3 v = normalize(cross(u, n));	// v(y) là tích có hướng của n(z) và u(x)
	return mat4(
		u.x,											v.x,											n.x,											0.0f,
		u.y,											v.y,											n.y,											0.0f,
		u.z,											v.z,											n.z,											0.0f,
		-eye.x * u.x - eye.y * u.y - eye.z * u.z,		-eye.x * v.x - eye.y * v.y - eye.z * v.z,		-eye.x * n.x - eye.y * n.y - eye.z * n.z,		1.0f);

	/* opengl đọc
		u.v[0]		u.v[1]		u.v[2]		-eye.v[0] * u.v[0] - eye.v[1] * u.v[1] - eye.v[2] * u.v[2]
		v.v[0]		v.v[1]		v.v[2]		-eye.v[0] * v.v[0] - eye.v[1] * v.v[1] - eye.v[2] * v.v[2]
		n.v[0]		n.v[1]		n.v[2]		-eye.v[0] * n.v[0] - eye.v[1] * n.v[1] - eye.v[2] * n.v[2]
		0.0f		0.0f		0.0f		1.0f
	*/

}
	// cách 2
mat4 lookat2(const vec3& eye, const vec3& center, const vec3& up)
{
	vec3 Z = normalize(eye - center);
	vec3 X = normalize(cross(up, Z));
	vec3 Y = cross(Z, X);

	mat4 m1;

	m1.m[0] = X.x;
	m1.m[1] = Y.x;
	m1.m[2] = Z.x;
	m1.m[4] = X.y;
	m1.m[5] = Y.y;
	m1.m[6] = Z.y;
	m1.m[8] = X.z;
	m1.m[9] = Y.z;
	m1.m[10] = Z.z;
	m1.m[12] = -dot(X, eye);
	m1.m[13] = -dot(Y, eye);
	m1.m[14] = -dot(Z, eye);

	return m1;
}

	// cách 3
mat4 lookat3(vec3& eye, vec3& at, const vec3& up) {
	mat4 t = translate(vec3(-eye.x, -eye.y, -eye.z));
	vec3 z = normalize(at - eye);		// z là khoảng cách từ eye đến at. Dùng at - eye thì phải đảo dấu z trong ma trận
	vec3 x = normalize(cross(z, up));	// x là tích có hướng của z và up
	vec3 y = normalize(cross(x, z));	// y là tích có hướng của x và z
	mat4 r;
	r.m[0] = x.x; r.m[1] = y.x; r.m[2] = -z.x;
	r.m[4] = x.y; r.m[5] = y.y; r.m[6] = -z.y;
	r.m[8] = x.z; r.m[9] = y.z; r.m[10] = -z.z;
	return r * t;
}


/* m[16] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	OpenGL đọc vào dạng cột:
	0  4  8 12
	1  5  9 13
	2  6 10 14
	3  7 11 15
	*/
// Phép chiếu phối cảnh
mat4 perspective(float fov, float aspect, float znear, float zfar) {
	float top = znear * tan(fov * degrees_to_radians / 2);
	float right = top * aspect;
	return mat4(
		znear / right,	0.0f,			0.0f,										0.0f,
		0.0f,			znear / top,	0.0f,										0.0f,
		0.0f,			0.0f,			-(zfar + znear) / (zfar - znear),			-1.0f,
		0.0f,			0.0f,			-(2.0f * zfar * znear) / (zfar - znear),	0.0f);

	/* opengl đọc
		znear / right	0.0f			0.0f										tv.v[0]
		0.0f			znear / top		0.0f										tv.v[1]
		0.0f			0.0f			-(zfar + znear) / (zfar - znear)			-1.0f
		0.0f			0.0f			-(2.0f * zfar * znear) / (zfar - znear)		0.0f
	*/
}


/* cách 2
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif
mat4 perspective(float fovy, float aspect, float n, float f)
{
	mat4 m1 = zero_mat4();

	float coty = 1.0f / tan(fovy * (float)M_PI / 360.0f);

	m1.m[0] = coty / aspect;
	m1.m[5] = coty;
	m1.m[10] = (n + f) / (n - f);
	m1.m[11] = -1.0f;
	m1.m[14] = 2.0f * n * f / (n - f);
	m1.m[15] = 0.0f;

	return m1;
}
*/


/* m[16] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	OpenGL đọc vào dạng cột:
	0  4  8 12
	1  5  9 13
	2  6 10 14
	3  7 11 15
	*/
// Frustum
mat4 frustum(float left, float right, float bottom, float top, float znear, float zfar) {
	return mat4(
		2 * znear / (right - left),				0.0f,								0.0f,										0.0f,
		0.0f,									2 * znear / (top - bottom),			0.0f,										0.0f,
		(right + left) / (right - left),		(top + bottom) / (top - bottom),	-(zfar + znear) / (zfar - znear),			-1.0f,
		0.0f,									0.0f,								-(2.0f * zfar * znear) / (zfar - znear),	0.0f);
}


/* m[16] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	OpenGL đọc vào dạng cột:
	0  4  8 12
	1  5  9 13
	2  6 10 14
	3  7 11 15
	*/
// Phép chiếu trực giao
mat4 ortho(float left, float right, float bottom, float top, float znear, float zfar)
{
	return mat4(
		2.0f / (right - left),				0.0f,								0.0f,								0.0f,
		0.0f,								2.0f / (top - bottom),				0.0f,								0.0f,
		0.0f,								0.0f,								-2.0f / (zfar - znear),				0.0f,
		-(left + right) / (right - left),	-(top + bottom) / (top - bottom),	-(zfar + znear) / (zfar - znear),	1.0f);
	
	/* opengl đọc
		2.0f / (right - left)		0.0f					0.0f					-(left + right) / (right - left)
		0.0f						2.0f / (top - bottom)	0.0f					-(top + bottom) / (top - bottom)
		0.0f						0.0f					-2.0f / (zfar - znear)	-(zfar + znear) / (zfar - znear)
		0.0f						0.0f					0.0f					1.0f
	*/
}

	// cách 2
mat4 or_tho(float left, float right, float bottom, float top, float n, float f)
{
	mat4 m1;

	m1.m[0]  = 2.0f / (right - left);
	m1.m[5]  = 2.0f / (top - bottom);
	m1.m[10] = -2.0f / (f - n);
	m1.m[12] = -(right + left) / (right - left);
	m1.m[13] = -(top + bottom) / (top - bottom);
	m1.m[14] = -(f + n) / (f - n);

	return m1;
}
