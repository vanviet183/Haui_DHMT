// thư viện tải hình ảnh
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"	// Sean Barrett's image loader - http://nothings.org/#include <iostream>

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <GL/vector_matrix.h>


using namespace std;

typedef struct
{
	float xyzw[4];
	float rgba[4];
	float normal[4];
	float texture[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

Vertex Vertices[] =
{
	// v4-v7-v6 (back - user)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 0.0f, 0.0f } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 1.0f, 0.0f } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 1.0f, 1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 1.0f, 1.0f } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 0.0f, 1.0f } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0,-1, 0 },{ 0.0f, 0.0f } },

	// v2-v3-v0 (front - user)
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 0.0f } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 0.0f } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 1.0f } },
	// v0-v1-v2
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 1.0f, 1.0f } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 1.0f } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 0, 1, 0 },{ 0.0f, 0.0f } },

	//v1-v0-v5 (top)
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 0.0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 0.0f } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 1.0f } },
	//v5-v6-v1 
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 1.0f, 1.0f } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 1.0f } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0, 1, 0, 0 },{ 0.0f, 0.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 0.0f, 0.0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 1.0f, 0.0f } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 1.0f, 1.0f } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 1.0f, 1.0f } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 0.0f, 1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 0,-1, 0, 0 },{ 0.0f, 0.0f } },

	// v3-v4-v5 (right)
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 0.0f } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 0.0f } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 1.0f } },
	// v5-v0-v3 
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 1.0f, 1.0f } },
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 1.0f } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ 1, 0, 0, 0 },{ 0.0f, 0.0f } },

	// v7-v2-v1 (left)
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 0.0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 0.0f } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 1.0f } },
	// v1-v6-v7 
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 1.0f, 1.0f } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.0f, 1.0f },{ -1, 0, 0, 0 },{ 0.0f, 0.0f } }

};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba);
const size_t TextureOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba) + sizeof(Vertices[1].normal);


class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;

public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

int
CurrentWidth = 800,
CurrentHeight = 600;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

MatrixStack  mvstack;

mat4 model_mat_cpp,
model_fan_wall,
model_fan_ceil,
model_fan_stand,
view_mat_cpp,
projection_mat_cpp;


GLuint texture;

int
model_mat_location,
view_mat_location,
projection_mat_location;

GLfloat rotateAll = 0;

// Dùng để tạo ma trận projection
float
znear = 0.1f,
zfar = 100.0f,
fov = 67.0f,
aspect = (float)CurrentWidth / (float)CurrentHeight;

// Dùng cho di chuyển camera
float
cam_move_speed = 0.2f,					// 1 đơn vị/giây
cam_y_rotate_speed = 10.0f,				// 10 độ/giây
cam_position[] = { 0.0f, 0.0f, 2.0f },	// phải khác (0, 0, 0)   (look at)
cam_y_rotate = 0.0f,					// góc quay quanh trục y tính theo độ

cam_x_rotate_speed = 10.0f,				// 10 độ/giây
cam_x_rotate = 0.0f;					// góc quay quanh trục x tính theo độ

// Biến kiểm tra di chuyển camera
bool cam_moved = false;

// Biến dùng để tính ma trận model
mat4 T, R, P;

const char* BLACK = "images/black.jpg";
const char* BEIGE = "images/beige.jpg";
const char* BLUE_BLUR = "images/blue_blur.jpg";
const char* BROWN = "images/brown.jpg";
const char* GRAY = "images/gray.jpg";
const char* YELLOW = "images/yellow.jpg";
const char* YELLOW_GREEN = "images/yellow_green.jpg";
const char* WHITE = "images/white.jpg";
const char* WHITE_50 = "images/white_50.jpg";
const char* APPLE = "images/apple.jpg";
const char* WOOD_FLOOR = "images/wood_floor.jpg";
const char* CEIL = "images/ceil.jpg";
const char* WALL = "images/wall.jpg";

// --------------------------------------
bool CompileShader(GLuint shaderID) {
	cout << "Compiling shader" << shaderID << "..." << endl;
	glCompileShader(shaderID);
	int result = -1;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		cout << "Shader " << shaderID << " compile failed" << endl;
		int maxLength = 2048;
		int realLength = 0;
		char log[2048];
		glGetShaderInfoLog(shaderID, maxLength, &realLength, log);
		cout << log << endl;
		return false;
	}
	cout << "Shader " << shaderID << " compile successful" << endl;
	return true;
}


bool LoadTexture(const char* file_name, GLuint* texture) {
	int x, y, n;
	int force_channels = 4;
	stbi_set_flip_vertically_on_load(true);

	// lấy vị trí của tệp ảnh đầu vào
	// x: chiều rộng
	// y: chiều cao
	// : số kênh màu
	unsigned char* image_data = stbi_load(file_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}
	// NPOT check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf(stderr, "WARNING: texture %s is not power-of-2 dimensions\n",
			file_name);
	}

	// tham chiếu kết cấu
	// 1: số lượng kết cấu muốn lưu trữ
	// texture: lưu trữ
	glGenTextures(1, texture);
	glActiveTexture(GL_TEXTURE0);

	// ràng buộc kết cấu
	glBindTexture(GL_TEXTURE_2D, *texture);

	// nạp dữ liệu vào texture
	// GL_TEXTURE_2D: mục tiêu kết cấu
	// 0: cấp độ mipmap, cấp độ cơ bản 0
	// GL_RGBA: định dạng lưu kết cấu
	// x, y: chiều rộng, chiều cao
	// 0: một số công cụ kế thừa???
	// GL_RGBA, GL_UNSIGNED_BYTE: định dạng và kiểu dữ liệu của ảnh nguồn
	// image_data: dữ liệu hình ảnh đã nạp trước đó
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	GLfloat max_aniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);

	// set the maximum!
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);
	return true;
}

// ------------------------------------------
// room
mat4 model_room;
void room()
{
	mvstack.push(model_room);
	(LoadTexture(GRAY, &texture));
	mat4 dat = identity_mat4() * translate(vec3(0, -0.52, 0)) * rotate_z(180) * scale(vec3(20.0, 0.01, 20.0));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_room * dat).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	(LoadTexture(WOOD_FLOOR, &texture));
	mat4 san = identity_mat4() * translate(vec3(0, -0.5, 0)) * rotate_z(180) * scale(vec3(2.0, 0.01, 2.5));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_room * san).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	(LoadTexture(CEIL, &texture));
	mat4 tran = identity_mat4() * translate(vec3(0, 1, 0)) * scale(vec3(2.0, 0.01, 2.5));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_room * tran).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	(LoadTexture(WALL, &texture));
	mat4 lung = translate(vec3(0, 0.25, -1.25)) * rotate_y(180) * scale(vec3(2.0, 1.5, 0.01));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_room * lung).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	mat4 trai = translate(vec3(1.0, 0.25, 0)) * scale(vec3(0.01, 1.5, 2.5));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_room * trai).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	mat4 phai = translate(vec3(-1.0, 0.25, 0)) * rotate_y(180) * scale(vec3(0.01, 1.5, 2.5));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_room * phai).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	mat4 cua = translate(vec3(0, 0.25, 1.25)) * rotate_y(180) * scale(vec3(2.0, 1.5, 0.01));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_room * cua).m);
	model_room = mvstack.pop();
}
//-----------------------------------------
// Quat tuong
#define BASE_FAN_WALL_WIDTH 0.03f
#define BASE_FAN_WALL_HEIGHT 0.14f
#define BASE_FAN_WALL_DEPTH 0.01f

#define BODY_FAN_WALL_WIDTH 0.01f
#define BODY_FAN_WALL_HEIGHT 0.15f
#define BODY_FAN_WALL_DEPTH 0.01f

#define HEAD_FAN_WALL_WIDTH 0.1f
#define HEAD_FAN_WALL_HEIGHT 0.06f
#define HEAD_FAN_WALL_DEPTH 0.06f

#define PROPERLLER_FAN_WALL_WIDTH 0.25f
#define PROPERLLER_FAN_WALL_HEIGHT 0.09f
#define PROPERLLER_FAN_WALL_DEPTH 0.005f

mat4 model_head_fan_wall = identity_mat4();
GLfloat quat_tuong_quay = 0;
GLfloat quat_tuong_quay_status = 0;
GLint quat_tuong_quay_trai = 0;

GLfloat quat_tuong_quay_canh = 0;
GLuint quat_tuong_quay_canh_status = 0;
//ve phan chan 
void quat_tuong_de() {
	mat4 instance = identity_mat4();
	instance = rotate_y(90) * scale(vec3(BASE_FAN_WALL_WIDTH, BASE_FAN_WALL_HEIGHT, BASE_FAN_WALL_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_wall * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve than quat
void quat_tuong_than() {
	mat4 instance = identity_mat4();
	model_fan_wall = model_fan_wall * translate(vec3(BODY_FAN_WALL_HEIGHT / (2 * 1.4), BASE_FAN_WALL_HEIGHT / 2, 0.0f));
	instance = rotate_z(-45) * scale(vec3(BODY_FAN_WALL_WIDTH, BODY_FAN_WALL_HEIGHT, BODY_FAN_WALL_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_wall * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve phan dau quat
void quat_tuong_dau() {
	mat4 instance = identity_mat4();
	model_head_fan_wall = model_head_fan_wall * translate(vec3(BODY_FAN_WALL_WIDTH * 5, BODY_FAN_WALL_HEIGHT / (2 * 1.4), 0.0)) * rotate_z(-45);
	instance = scale(vec3(HEAD_FAN_WALL_WIDTH, HEAD_FAN_WALL_HEIGHT, HEAD_FAN_WALL_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_wall * model_head_fan_wall * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve truc quat
void quat_tuong_truc() {
	mat4 instance = identity_mat4();
	model_head_fan_wall = model_head_fan_wall * translate(vec3(HEAD_FAN_WALL_WIDTH / 2 + 0.015, 0.0f, 0.0f));
	instance = scale(vec3(0.06f, 0.015f, 0.015f));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_wall * model_head_fan_wall * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve canh quat
void quat_tuong_canh(GLfloat rotate) {
	mat4 instance = identity_mat4();
	instance = rotate_z(rotate) * rotate_z(quat_tuong_quay_canh) * scale(vec3(PROPERLLER_FAN_WALL_WIDTH, PROPERLLER_FAN_WALL_HEIGHT, PROPERLLER_FAN_WALL_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_wall * model_head_fan_wall * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve cac canh quat
void quat_tuong_he_canh() {
	model_head_fan_wall = model_head_fan_wall * rotate_y(90) * translate(vec3(0.0f, 0.0f, 0.02));
	quat_tuong_canh(0);
	quat_tuong_canh(90);
}

//ve quat
void fan_wall() {
	mvstack.push(model_fan_wall);
	(LoadTexture(BROWN, &texture));
	model_fan_wall = model_fan_wall * scale(vec3(1.0f, 1.0f, 1.0f));
	quat_tuong_de();
	(LoadTexture(WHITE, &texture));
	quat_tuong_than();
	(LoadTexture(GRAY, &texture));
	model_head_fan_wall = identity_mat4() * rotate_y(quat_tuong_quay);
	quat_tuong_dau();
	(LoadTexture(BLACK, &texture));
	quat_tuong_truc();
	(LoadTexture(BLUE_BLUR, &texture));
	quat_tuong_he_canh();
	model_fan_wall = mvstack.pop();
}

//-----------------------------------------
// Quat tran
#define BASE_FAN_CEIL_WIDTH 0.08f
#define BASE_FAN_CEIL_HEIGHT 0.08f
#define BASE_FAN_CEIL_DEPTH 0.08f

#define BODY_FAN_CEIL_WIDTH 0.01f
#define BODY_FAN_CEIL_HEIGHT 0.2f
#define BODY_FAN_CEIL_DEPTH 0.01f

#define HEAD_FAN_CEIL_WIDTH 0.1f
#define HEAD_FAN_CEIL_HEIGHT 0.02f
#define HEAD_FAN_CEIL_DEPTH 0.1f

#define PROPERLLER_FAN_CEIL_WIDTH 0.5f
#define PROPERLLER_FAN_CEIL_HEIGHT 0.09f
#define PROPERLLER_FAN_CEIL_DEPTH 0.005f

mat4 model_head_fan_ceil = identity_mat4();

GLfloat quat_tran_quay_canh = 0;
GLuint quat_tran_quay_canh_status = 0;
//ve phan chan 
void quat_tran_de() {
	mat4 instance = identity_mat4();
	instance = rotate_y(90) * scale(vec3(BASE_FAN_CEIL_WIDTH, BASE_FAN_CEIL_HEIGHT, BASE_FAN_CEIL_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_ceil * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve than quat
void quat_tran_than() {
	mat4 instance = identity_mat4();
	model_fan_ceil = model_fan_ceil * translate(vec3(0.0f, -BODY_FAN_CEIL_HEIGHT / 2, 0.0f));
	instance = scale(vec3(BODY_FAN_CEIL_WIDTH, BODY_FAN_CEIL_HEIGHT, BODY_FAN_CEIL_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_ceil * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve phan dau quat
void quat_tran_dau() {
	mat4 instance = identity_mat4();
	model_head_fan_ceil = model_head_fan_ceil * translate(vec3(0.0f, -BODY_FAN_CEIL_HEIGHT / 2, 0.0));
	instance = scale(vec3(HEAD_FAN_CEIL_WIDTH, HEAD_FAN_CEIL_HEIGHT, HEAD_FAN_CEIL_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_ceil * model_head_fan_ceil * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve canh quat
void quat_tran_canh(GLfloat rotate) {
	mat4 instance = identity_mat4();
	instance = rotate_z(rotate) * scale(vec3(PROPERLLER_FAN_CEIL_WIDTH, PROPERLLER_FAN_CEIL_HEIGHT, PROPERLLER_FAN_CEIL_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_ceil * model_head_fan_ceil * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

//ve cac canh quat
void quat_tran_he_canh() {
	model_head_fan_ceil = model_head_fan_ceil * rotate_x(90) * translate(vec3(0.0f, 0.0f, 0.02));
	quat_tran_canh(0);
	quat_tran_canh(90);
}

//ve quat
void fan_ceil() {
	mvstack.push(model_fan_ceil);
	(LoadTexture(BROWN, &texture));
	model_fan_ceil = model_fan_ceil * scale(vec3(1.0f, 1.0f, 1.0f));
	quat_tran_de();
	(LoadTexture(WHITE, &texture));
	quat_tran_than();
	(LoadTexture(GRAY, &texture));
	model_head_fan_ceil = identity_mat4() * rotate_y(quat_tran_quay_canh);
	quat_tran_dau();
	(LoadTexture(BLUE_BLUR, &texture));
	quat_tran_he_canh();
	model_fan_ceil = mvstack.pop();
}


//-----------------------------------------
// Ve quat cay
#define BASE_FAN_STAND_WIDTH 0.15f
#define BASE_FAN_STAND_HEIGHT 0.06f
#define BASE_FAN_STAND_DEPTH 0.15f

#define BODY_FAN_STAND_WIDTH 0.015f
#define BODY_FAN_STAND_HEIGHT 0.3f
#define BODY_FAN_STAND_DEPTH 0.015f

#define HEAD_FAN_STAND_WIDTH 0.1f
#define HEAD_FAN_STAND_HEIGHT 0.06f
#define HEAD_FAN_STAND_DEPTH 0.06f

#define PROPERLLER_FAN_STAND_WIDTH 0.25f
#define PROPERLLER_FAN_STAND_HEIGHT 0.09f
#define PROPERLLER_FAN_STAND_DEPTH 0.005f

mat4 model_head_fan_stand = identity_mat4();
GLfloat quat_cay_quay = 0;
GLfloat quat_cay_quay_status = 0;
GLint quat_cay_quay_trai = 0;

GLfloat quat_cay_quay_canh = 0;
GLuint quat_cay_quay_canh_status = 0;
void quat_cay_de() {
	mat4 instance = identity_mat4();
	instance = scale(vec3(BASE_FAN_STAND_WIDTH, BASE_FAN_STAND_HEIGHT, BASE_FAN_STAND_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_stand * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve than quat
void quat_cay_than() {
	mat4 instance = identity_mat4();
	model_fan_stand = model_fan_stand * translate(vec3(0.0f, BODY_FAN_STAND_HEIGHT / 2, 0.0f));
	instance = scale(vec3(BODY_FAN_STAND_WIDTH, BODY_FAN_STAND_HEIGHT, BODY_FAN_STAND_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_stand * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve phan dau quat
void quat_cay_dau() {
	mat4 instance = identity_mat4();
	model_head_fan_stand = model_head_fan_stand * translate(vec3(0.02, BODY_FAN_STAND_HEIGHT / 2, 0.0f)) * rotate_z(-10);
	instance = scale(vec3(HEAD_FAN_STAND_WIDTH, HEAD_FAN_STAND_HEIGHT, HEAD_FAN_STAND_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_stand * model_head_fan_stand * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve truc quat
void quat_cay_truc() {
	mat4 instance = identity_mat4();
	model_head_fan_stand = model_head_fan_stand * translate(vec3(HEAD_FAN_STAND_WIDTH / 2 + 0.015, 0.0f, 0.0f));
	instance = scale(vec3(0.06f, 0.015f, 0.015f));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_stand * model_head_fan_stand * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve canh quat
void quat_cay_canh(GLfloat rotate) {
	mat4 instance = identity_mat4();
	instance = rotate_z(rotate) * rotate_z(quat_cay_quay_canh) * scale(vec3(PROPERLLER_FAN_STAND_WIDTH, PROPERLLER_FAN_STAND_HEIGHT, PROPERLLER_FAN_STAND_DEPTH));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_fan_stand * model_head_fan_stand * instance).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
//ve cac canh quat
void quat_cay_he_canh() {
	model_head_fan_stand = model_head_fan_stand * rotate_y(90) * translate(vec3(0.0f, 0.0f, 0.02));
	quat_cay_canh(0);
	quat_cay_canh(90);
}

//ve quat
void fan_stand() {
	mvstack.push(model_fan_stand);
	(LoadTexture(BROWN, &texture));
	model_fan_stand = model_fan_stand * scale(vec3(1.0f, 1.0f, 1.0f));
	quat_cay_de();
	(LoadTexture(WHITE, &texture));
	quat_cay_than();
	(LoadTexture(GRAY, &texture));
	model_head_fan_stand = identity_mat4() * rotate_y(quat_cay_quay);
	quat_cay_dau();
	(LoadTexture(BLACK, &texture));
	quat_cay_truc();
	(LoadTexture(BLUE_BLUR, &texture));
	quat_cay_he_canh();
	model_fan_stand = mvstack.pop();
}

// Vẽ bục để quạt cây
mat4 model_buc_de_quat;
void buc_de_quat_1()
{
	mvstack.push(model_buc_de_quat);
	(LoadTexture(YELLOW, &texture));
	mat4 buc_de_quat = identity_mat4();
	buc_de_quat = translate(vec3(-0.7, -0.4, -0.75)) * scale(vec3(0.6, 0.2, 1));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_buc_de_quat * buc_de_quat).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_buc_de_quat = mvstack.pop();
}

void buc_de_quat_2()
{
	mvstack.push(model_buc_de_quat);
	(LoadTexture(BEIGE, &texture));
	mat4 buc_de_quat = identity_mat4();
	buc_de_quat = translate(vec3(-0.85, -0.2, -0.75)) * scale(vec3(0.3, 0.2, 1));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_buc_de_quat * buc_de_quat).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_buc_de_quat = mvstack.pop();
}

mat4 model_thu_ngan;
#define THU_NGAN_WIDTH 0.8f
#define THU_NGAN_HEIGHT 0.4f
#define THU_NGAN_DEPTH 0.2f
void thu_ngan() {
	mvstack.push(model_thu_ngan);
	(LoadTexture(BEIGE, &texture));
	mat4 ban_thu_ngan = identity_mat4();
	ban_thu_ngan = scale(vec3(THU_NGAN_WIDTH, THU_NGAN_HEIGHT, THU_NGAN_DEPTH));
	model_thu_ngan = model_thu_ngan * translate(vec3(1.0f - THU_NGAN_WIDTH / 2, -(0.5f - THU_NGAN_HEIGHT / 2), 1.25f - THU_NGAN_DEPTH / 2));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_thu_ngan * ban_thu_ngan).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	mat4 ban_thu_ngan_2 = scale(vec3(THU_NGAN_WIDTH/2, THU_NGAN_HEIGHT, THU_NGAN_DEPTH));
	model_thu_ngan = model_thu_ngan * rotate_y(90) * translate(vec3(THU_NGAN_WIDTH/4, 0.0f, -THU_NGAN_WIDTH/2 + THU_NGAN_DEPTH /2));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_thu_ngan * ban_thu_ngan_2).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_thu_ngan = mvstack.pop();
}

void may_tinh() {
	mvstack.push(model_thu_ngan);
	(LoadTexture(APPLE, &texture));
	mat4 may_tinh = identity_mat4();
	may_tinh = translate(vec3(0.75f, -0.05f, 1.2f)) * scale(vec3(0.15f, 0.12f, 0.01f));
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, (model_thu_ngan * may_tinh).m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_thu_ngan = mvstack.pop();
}

// ------------------------------------------
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}
// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0); // position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); // color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); // normal
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)TextureOffset); // texture

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
}
// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

// ------------------------------------------
void DisplayFunc(void)
{
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");

	// Tạo ma trận view
	T = translate(vec3(-cam_position[0], -cam_position[1], -cam_position[2]));
	R = rotate_y(-cam_y_rotate);
	P = rotate_x(-cam_x_rotate);
	view_mat_cpp = R * P * T;
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	// Tạo ma trận projection
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	// Khi di chuyển camera --> tính lại các ma trận model, view
	if (cam_moved) {
		model_mat_cpp = model_mat_cpp * R;
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);

		T = translate(vec3(-cam_position[0], -cam_position[1], -cam_position[2]));
		R = rotate_y(-cam_y_rotate);
		P = rotate_x(-cam_x_rotate);
		view_mat_cpp = R * P * T;
		glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);
	}


	glEnable(GL_DEPTH_TEST);
	glClearColor(0.39f, 0.7f, 0.90f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mvstack.push(model_mat_cpp);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_room);
	model_room = rotate_y(rotateAll);
	room();
	model_room = mvstack.pop();

	mvstack.push(model_thu_ngan);
	model_thu_ngan = rotate_y(rotateAll);
	thu_ngan();
	may_tinh();
	model_thu_ngan = mvstack.pop();

	mvstack.push(model_buc_de_quat);
	model_buc_de_quat = rotate_y(rotateAll);
	buc_de_quat_1();

	model_buc_de_quat = rotate_y(rotateAll);
	buc_de_quat_2();
	model_buc_de_quat = mvstack.pop();

	mvstack.push(model_fan_wall);
	model_fan_wall = rotate_y(rotateAll);
	model_fan_wall = model_fan_wall * translate(vec3(-0.98f, 0.0f, 0.5f));
	fan_wall();
	model_fan_wall = model_fan_wall * translate(vec3(0.0f, 0.0f, 0.35f));
	fan_wall();
	model_fan_wall = model_fan_wall * translate(vec3(0.0f, 0.35f, 0.0f));
	fan_wall();
	model_fan_wall = model_fan_wall * translate(vec3(0.0f, 0.0f, -0.35f));
	fan_wall();
	model_fan_wall = mvstack.pop();

	mvstack.push(model_fan_ceil);
	model_fan_ceil = rotate_y(rotateAll);
	model_fan_ceil = model_fan_ceil * translate(vec3(-0.35f, 1.0f, 0.0f));
	fan_ceil();
	model_fan_ceil = model_fan_ceil * translate(vec3(0.7f, 0.0f, 0.0f));
	fan_ceil();
	model_fan_ceil = mvstack.pop();

	mvstack.push(model_fan_stand);
	model_fan_stand = rotate_y(rotateAll);
	model_fan_stand = model_fan_stand * translate(vec3(-0.8f, -0.07f, -0.5f));
	fan_stand();
	model_fan_stand = model_fan_stand * translate(vec3(0.0f, 0.0f, -0.4f));
	fan_stand();
	model_fan_stand = model_fan_stand * translate(vec3(0.25f, -0.2f, 0.0f));
	fan_stand();
	model_fan_stand = model_fan_stand * translate(vec3(0.0f, 0.0f, 0.4f));
	fan_stand();
	model_fan_stand = mvstack.pop();

	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
}
// ------------------------------------------
void IdleFunc(void)
{
	// quay quat tuong
	quat_tuong_quay_canh -= quat_tuong_quay_canh_status * 10;
	if (quat_tuong_quay_canh <= -360) {
		quat_tuong_quay_canh += 360;
	}
	if (quat_tuong_quay_status) {
		if (quat_tuong_quay_trai) {
			quat_tuong_quay += 1.5;
			if (quat_tuong_quay >= 35) {
				quat_tuong_quay_trai = false;
			}
		}
		else {
			quat_tuong_quay -= 1.5;
			if (quat_tuong_quay <= -35) {
				quat_tuong_quay_trai = true;
			}
		}
	}

	// quay tran tran
	quat_tran_quay_canh -= quat_tran_quay_canh_status * 10;
	if (quat_tran_quay_canh <= -360) {
		quat_tran_quay_canh += 360;
	}

	// quay quat cay
	quat_cay_quay_canh -= quat_cay_quay_canh_status * 10;
	if (quat_cay_quay_canh <= -360) {
		quat_cay_quay_canh += 360;
	}
	if (quat_cay_quay_status) {
		if (quat_cay_quay_trai) {
			quat_cay_quay += 1.5;
			if (quat_cay_quay >= 35) {
				quat_cay_quay_trai = false;
			}
		}
		else {
			quat_cay_quay -= 1.5;
			if (quat_cay_quay <= -35) {
				quat_cay_quay_trai = true;
			}
		}
	}

	glutPostRedisplay();
}
// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS); break;
	case 'a':
		cam_position[0] -= cam_move_speed;
		cam_moved = true;
		break;
	case 'd':
		cam_position[0] += cam_move_speed;
		cam_moved = true;
		break;

		// camera di chuyển theo trục y
	case 'y':
		cam_position[1] -= cam_move_speed;
		cam_moved = true;
		break;
	case 'Y':
		cam_position[1] += cam_move_speed;
		cam_moved = true;
		break;

		// camera di chuyển theo trục z
	case 'w':
		cam_position[2] -= cam_move_speed;
		cam_moved = true;
		break;
	case 's':
		cam_position[2] += cam_move_speed;
		cam_moved = true;
		break;

		// Thay doi huong gio quat tuong
	case 'V':
		quat_tuong_quay_status = true - quat_tuong_quay_status;
		break;
		// Thay doi toc do quat tuong
	case 'v':
		quat_tuong_quay_canh_status += 1;
		quat_tuong_quay_canh_status %= 4;
		break;
		// Thay doi huong gio quat cay
	case 'B':
		quat_cay_quay_status = true - quat_cay_quay_status;
		break;
		// Thay doi toc do quat cay
	case 'b':
		quat_cay_quay_canh_status += 1;
		quat_cay_quay_canh_status %= 4;
		break;
		// Thay doi toc do quat tran
	case 'n':
		quat_tran_quay_canh_status += 1;
		quat_tran_quay_canh_status %= 4;
		break;
	}
}
// ------------------------------------------
void MouseFunc(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		rotateAll += 15.0;
		if (rotateAll > 360.0) { rotateAll -= 360.0; }
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		rotateAll -= 15.0;
		if (rotateAll < 0.0) { rotateAll += 360.0; }
	}

	glutPostRedisplay();
}
// ------------------------------------------
void SpecialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		cam_x_rotate += cam_x_rotate_speed;
		//cam_moved = true;
		break;
	case GLUT_KEY_DOWN:
		cam_x_rotate -= cam_x_rotate_speed;
		//cam_moved = true;
		break;

		// camera quay quanh trục y
	case GLUT_KEY_LEFT:
		cam_y_rotate += cam_y_rotate_speed;
		//cam_moved = true;
		break;
	case GLUT_KEY_RIGHT:
		cam_y_rotate -= cam_y_rotate_speed;
		//cam_moved = true;
		break;
	}
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Fan Shop");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutSpecialFunc(SpecialFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}
