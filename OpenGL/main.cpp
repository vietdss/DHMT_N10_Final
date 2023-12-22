//Chương trình vẽ 1 hình lập phương đơn vị theo mô hình lập trình OpenGL hiện đại

#include "Angel.h"  /* Angel.h là file tự phát triển (tác giả Prof. Angel), có chứa cả khai báo includes glew và freeglut*/
#include <Windows.h>
#include<mmsystem.h>

// remember to prototype
void generateGeometry(void);
void initGPUBuffers(void);
void shaderSetup(void);
void display(void);
void keyboard(unsigned char key, int x, int y);


typedef vec4 point4;
typedef vec4 color4;
using namespace std;
GLfloat heSo = 1;
// Số các đỉnh của các tam giác
const int NumPoints = 36;

//point4 points[NumPoints]; /* Danh sách các đỉnh của các tam giác cần vẽ*/
//color4 colors[NumPoints]; /* Danh sách các màu tương ứng cho các đỉnh trên*/
//GLfloat l = -4.0, r = 4.0, bot = -4.0, top = 4.0, zNear = 2, zFar = 15;
GLfloat l = -0.02, r = 0.02;
GLfloat bot = -0.03, top = 0.03;
GLfloat zNear = 0.03, zFar = 10;

point4 vertices[8]; /* Danh sách 8 đỉnh của hình lập phương*/
color4 vertex_colors[8]; /*Danh sách các màu tương ứng cho 8 đỉnh hình lập phương*/
GLuint program, model_loc, view_loc, projection_loc, ambient_product_loc, diffuse_product_loc, specular_product_loc;

const int soDinhHLP = 36;
const int soDinhHinhTru = 144;
int Index = 0;
point4 points[soDinhHLP + soDinhHinhTru]; /* Danh sách các đỉnh của các tam giác cần vẽ*/
color4 colors[soDinhHLP + soDinhHinhTru]; /* Danh sách các màu tương ứng cho các đỉnh trên*/
vec3 normal[soDinhHLP + soDinhHinhTru];
point4 DinhHLP[8]; /* Danh sách 8 đỉnh của hình lập phương*/
color4 MauHLP[8]; /*Danh sách các màu tương ứng cho 8 đỉnh hình lập phương*/
point4 DinhHtru[26]; GLfloat dr = M_PI / 180;
color4 MauHtru[26];
//
//point4 light_position(-3, 5, 10,0);
point4 light_position(2, 3, 2, 0.0);;
color4 light_ambient(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light_specular(1.0, 1.0, 1.0, 1.0);
GLfloat material_shininess = 1000;
//Dieu khien mo hinh
bool shootRobot = false, shootXeTang_N = false, shoot_tenLua1 = false, shoot_tenLua2 = false, check_sung = false;
GLfloat tempDiChuyen = 0, tempQuayY = 0, xxRoBot = 0, yyRobot = 0, zzRobot = 0, xnRobot = 0, ynRobot = 0, znRobot = 0, xnTayTrenRobot1 = 0, xnTayTrenRobot2 = 0, xnTayDuoiRobot1 = 0, xnTayDuoiRobot2 = 0, xnChanRobot1 = 0, xnChanRobot2 = 0;
mat4 model = mat4(), model_xetang = mat4(), model_robot, model_canhTayRoBot, model_chanRobot, model_dauRobot, model_SungsRobot = mat4(), model_trungGian_robot1, model_trungGian_robot2, model_tenlua, model_xeTenLua, model_giaDotenLua;
GLfloat quayAllX = 0, quayAllY = 0, quayAllZ = 0, quayAllY1 = 0, quayAllY2 = 0, denXeTangR = 0, denXeTangG = 0, denXeTangB = 0;
GLfloat quayBangXeTang = 0, quayNongSung = 0, quayKhungSung = 0, diChuyenXeTang = 0, tesnXn = 0, testyn = 0, testZN = 0, xxSungRobot = 0;
GLfloat xnAK = 0, ynAK = 0, znAK = 0;
mat4 model_nongSung = mat4(); mat4 model_banhXe_Nghia;
float xEye = 0, yAt = 0, xAt = 0, gocQuayNgangCam = 0, quayBanhXeTenLua = 0, xXeTenLua = 0, gocQuayDocCam = 0, quayDauRobot = 0, ynXeTang = 0;
float ThetaXeTenLua[] = { 0,0,0,0 };
float QuayCamera[3] = { 90,0,0 };
bool PhamTrongNghia_control = false, NguyenThiBichNgoc_control = false, NguyenThiLinhNgan_control = false, HoangMinhNghia_control = false, NguyenHoangViet_control = false;
void initCube()
{
	// Gán giá trị tọa độ vị trí cho các đỉnh của hình lập phương
	vertices[0] = point4(-0.5, -0.5, 0.5, 1.0);
	vertices[1] = point4(-0.5, 0.5, 0.5, 1.0);
	vertices[2] = point4(0.5, 0.5, 0.5, 1.0);
	vertices[3] = point4(0.5, -0.5, 0.5, 1.0);
	vertices[4] = point4(-0.5, -0.5, -0.5, 1.0);
	vertices[5] = point4(-0.5, 0.5, -0.5, 1.0);
	vertices[6] = point4(0.5, 0.5, -0.5, 1.0);
	vertices[7] = point4(0.5, -0.5, -0.5, 1.0);

	// Gán giá trị màu sắc cho các đỉnh của hình lập phương	
	vertex_colors[0] = color4(0.0, 0.0, 0.0, 1.0); // black
	vertex_colors[1] = color4(1.0, 0.0, 0.0, 1.0); // red
	vertex_colors[2] = color4(1.0, 1.0, 0.0, 1.0); // yellow
	vertex_colors[3] = color4(0.0, 1.0, 0.0, 1.0); // green
	vertex_colors[4] = color4(0.0, 0.0, 1.0, 1.0); // blue
	vertex_colors[5] = color4(1.0, 0.0, 1.0, 1.0); // magenta
	vertex_colors[6] = color4(1.0, 1.0, 1.0, 1.0); // white
	vertex_colors[7] = color4(0.0, 1.0, 1.0, 1.0); // cyan



}
void quad(int a, int b, int c, int d)  /*Tạo một mặt hình lập phương = 2 tam giác, gán màu cho mỗi đỉnh tương ứng trong mảng colors*/\
{
	vec4 u = vertices[b] - vertices[a];
	vec4 v = vertices[c] - vertices[b];
	vec3 n = normalize(cross(u, v));

	colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; normal[Index] = n; Index++;
	colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; normal[Index] = n; Index++;
	colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; normal[Index] = n; Index++;
	colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; normal[Index] = n; Index++;
	colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; normal[Index] = n; Index++;
	colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; normal[Index] = n; Index++;
}
void makeColorCube(void)  /* Sinh ra 12 tam giác: 36 đỉnh, 36 màu*/

{
	quad(1, 0, 3, 2);
	quad(2, 3, 7, 6);
	quad(3, 0, 4, 7);
	quad(6, 5, 1, 2);
	quad(4, 5, 6, 7);
	quad(5, 4, 0, 1);
}
void TaoDinhSao() {

}
void TaoDinhHtru()
{
	//hình trụ mặt trên
	int j = 0;
	for (int i = 0; i <= 11; i++) {
		DinhHtru[i] = point4(cos(j * dr), 1, sin(j * dr), 1.0);
		j = j + 30;
	}
	DinhHtru[12] = point4(0, 1, 0, 1.0);
	//mặt dưới
	j = 0;
	for (int i = 13; i <= 24; i++) {
		DinhHtru[i] = point4(cos(j * dr), -1, sin(j * dr), 1.0);
		j = j + 30;
	}
	DinhHtru[25] = point4(0, -1, 0, 1.0);
}
void MBHTru(int a, int b, int c, int d) {
	vec4 u = DinhHtru[b] - DinhHtru[a];
	vec4 v = DinhHtru[c] - DinhHtru[b];
	vec3 n = normalize(cross(u, v));
	normal[Index] = n; points[Index] = DinhHtru[a]; Index++;
	normal[Index] = n; points[Index] = DinhHtru[b]; Index++;
	normal[Index] = n; points[Index] = DinhHtru[c]; Index++;

	normal[Index] = n; points[Index] = DinhHtru[a]; Index++;
	normal[Index] = n; points[Index] = DinhHtru[c]; Index++;
	normal[Index] = n; points[Index] = DinhHtru[d]; Index++;
}
void MTHTru1(int a[]) {
	vec4 u = DinhHtru[a[1]] - DinhHtru[a[7]];
	vec4 v = DinhHtru[a[4]] - DinhHtru[a[10]];
	vec3 n = normalize(cross(u, v));
	for (int i = 2; i <= 12; i++) {
		normal[Index] = n; points[Index] = DinhHtru[a[0]]; Index++;
		normal[Index] = n; points[Index] = DinhHtru[a[i - 1]]; Index++;
		normal[Index] = n; points[Index] = DinhHtru[a[i]]; Index++;
		if (i == 12) {
			normal[Index] = n; points[Index] = DinhHtru[a[0]]; Index++;
			normal[Index] = n; points[Index] = DinhHtru[a[12]]; Index++;
			normal[Index] = n; points[Index] = DinhHtru[a[1]]; Index++;
		}
	}
}
void MTHTru2(int a[]) {
	vec4 u = DinhHtru[a[1]] - DinhHtru[a[7]];
	vec4 v = DinhHtru[a[4]] - DinhHtru[a[10]];
	vec3 n = -1 * normalize(cross(u, v));
	for (int i = 2; i <= 12; i++) {
		normal[Index] = n; points[Index] = DinhHtru[a[0]]; Index++;
		normal[Index] = n; points[Index] = DinhHtru[a[i - 1]]; Index++;
		normal[Index] = n; points[Index] = DinhHtru[a[i]]; Index++;
		if (i == 12) {
			normal[Index] = n; points[Index] = DinhHtru[a[0]]; Index++;
			normal[Index] = n; points[Index] = DinhHtru[a[12]]; Index++;
			normal[Index] = n; points[Index] = DinhHtru[a[1]]; Index++;
		}
	}
}
void HinhTru() {
	int a[] = { 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	int b[] = { 25, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
	//mặt tròn
	MTHTru2(a);
	MTHTru1(b);
	//thân hình trụ
	for (int i = 1; i <= 11; i++) {
		MBHTru(a[i], a[i + 1], b[i + 1], b[i]);
	}
	MBHTru(a[12], a[1], b[1], b[12]);
}
void VeHinhTru(mat4 instance, mat4 matrix)
{
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * matrix * instance);
	glDrawArrays(GL_TRIANGLES, soDinhHLP, soDinhHinhTru);    /*Vẽ các tam giác*/
}

color4 ConvertRGBtoVec4(int a, int b, int c) {
	float x = (float)a / 255;
	float y = (float)b / 255;
	float z = (float)c / 255;
	float w = 1;
	return color4(x, y, z, w);
}



float DEGtoRAD(float DEG)
{
	return DEG / 360 * 2 * M_PI;
}
void setMau(int R, int G, int B, int material_shininess1) {
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess1);
	color4 ambient_product = light_ambient * ConvertRGBtoVec4(R, G, B);
	color4 diffuse_product = light_diffuse * ConvertRGBtoVec4(R, G, B);
	color4 specular_product = light_specular * ConvertRGBtoVec4(R, G, B);

	glUniform4fv(ambient_product_loc, 1, ambient_product);
	glUniform4fv(diffuse_product_loc, 1, diffuse_product);
	glUniform4fv(specular_product_loc, 1, specular_product);
}
void setMau(int R, int G, int B, int material_shininess1, vec4 lightpos) {
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, lightpos);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess1);
	color4 ambient_product = light_ambient * ConvertRGBtoVec4(R, G, B);
	color4 diffuse_product = light_diffuse * ConvertRGBtoVec4(R, G, B);
	color4 specular_product = light_specular * ConvertRGBtoVec4(R, G, B);

	glUniform4fv(ambient_product_loc, 1, ambient_product);
	glUniform4fv(diffuse_product_loc, 1, diffuse_product);
	glUniform4fv(specular_product_loc, 1, specular_product);
}
void VeHinhHop(mat4 instance, mat4 matrix) {
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * matrix * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);    /*Vẽ các tam giác*/
}
void generateGeometry(void)
{
	//hinh lap phuong
	initCube();
	makeColorCube();
	//hinh tru
	TaoDinhHtru();
	HinhTru();
	//hinh cau
}


void initGPUBuffers(void)
{
	// Tạo một VAO - vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Tạo và khởi tạo một buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(normal), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), sizeof(normal), normal);

}


void shaderSetup(void)
{
	// Nạp các shader và sử dụng chương trình shader
	program = InitShader("vshader1.glsl", "fshader1.glsl");   // hàm InitShader khai báo trong Angel.h
	glUseProgram(program);

	// Khởi tạo thuộc tính vị trí đỉnh từ vertex shader
	GLuint loc_vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc_vPosition);
	glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint loc_vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc_vColor);
	glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

	GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(loc_vNormal);
	glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points) + sizeof(colors)));

	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);

	model_loc = glGetUniformLocation(program, "model");
	projection_loc = glGetUniformLocation(program, "projection");
	view_loc = glGetUniformLocation(program, "view");

	ambient_product_loc = glGetUniformLocation(program, "AmbientProduct");
	diffuse_product_loc = glGetUniformLocation(program, "DiffuseProduct");
	specular_product_loc = glGetUniformLocation(program, "SpecularProduct");
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);        /* Thiết lập màu trắng là màu xóa màn hình*/
}


void nen() {
	mat4 instance = Translate(0, -0.02, 0) * Scale(4, 0.04, 4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void vanhChanBun(GLfloat x, GLfloat y, GLfloat z) {
	//chan trc mặt người nhìn
	/*mat4 model_chanbun = Translate(x, y, z);
	 mat4 m =model_chanbun* Scale(1.2, 0.04, 0.2);
	VeHinhHop(m, model_xetang);

	 m = model_chanbun * Translate(-1.2 / 2, 0, 0) * RotateZ(45)* Translate(-0.1, 0, 0) *Scale(0.2, 0.04,0.2 );
	VeHinhHop(m, model_xetang);

	m = model_chanbun * Translate(1.2 / 2, 0, 0) * RotateZ(-45) * Translate(0.1, 0, 0) * Scale(0.2, 0.04, 0.2);
	VeHinhHop(m, model_xetang);*/

	mat4 model_chanbun = Translate(x, y, z);
	mat4 m = model_chanbun * Scale(1.38, 0.04, 0.24);
	VeHinhHop(m, model_xetang);

	m = model_chanbun * Translate(-1.38 / 2, 0, 0) * RotateZ(90) * Translate(-0.1, 0, 0) * Scale(0.2, 0.04, 0.2);
	VeHinhHop(m, model_xetang);

	m = model_chanbun * Translate(1.38 / 2 - 0.02, 0, 0) * RotateZ(-90) * Translate(0.1, 0, 0) * Scale(0.2, 0.04, 0.2);
	VeHinhHop(m, model_xetang);
	m = model_chanbun * Translate(0, -0.1, 0.1 + 0.02) * RotateX(90) * Translate(0, -0.02, 0) * Scale(1.38, 0.04, 0.2);
	VeHinhHop(m, model_xetang);
	m = model_chanbun * Translate(0, -0.1, -(0.1 - 0.02)) * RotateX(90) * Translate(0, -0.02, 0) * Scale(1.34, 0.04, 0.2);
	VeHinhHop(m, model_xetang);


	setMau(denXeTangR, denXeTangG, denXeTangB, 270);

	m = model_chanbun * Translate(1.38 / 2 + 0.02, 0, 0) * RotateZ(-90) * Translate(0.1, 0, 0) * Scale(0.1, 0.04, 0.1);
	VeHinhHop(m, model_xetang);
}
// mảnh xích xe
void manhXichXe(GLfloat x, GLfloat y, GLfloat z) {
	mat4 instance = Translate(x, y, z) * Scale(0.2, 0.02, 0.4);
	VeHinhHop(instance, model_xetang);
}
void manhXichXeBen(GLfloat x, GLfloat y, GLfloat z, GLfloat rZ) {
	mat4 instance = Translate(x, y, z) * RotateZ(rZ) * Translate(0, -0.1, 0) * Scale(0.02, 0.2, 0.4);
	VeHinhHop(instance, model_xetang);
}
void banhXe_Nghia() {
	setMau(192, 192, 192, 270);
	setMau(183, 183, 183, 270);
	//Translate(x, y, z)* RotateZ(quayBangXeTang)
	mat4 instance = RotateX(90) * Scale(0.15, 0.05, 0.15);
	VeHinhTru(instance, model_banhXe_Nghia);
	setMau(255, 255, 0, 270);
	mat4 thanhBanhXe = Translate(0, 0, (0.01 / 2 + 0.05)) * RotateZ(+45) * Scale(0.01, 0.15 * 1.8, 0.01);
	VeHinhHop(thanhBanhXe, model_banhXe_Nghia);
	thanhBanhXe = Translate(0, 0, (0.01 / 2 + 0.05)) * RotateZ(-45) * Scale(0.01, 0.15 * 1.8, 0.01);
	VeHinhHop(thanhBanhXe, model_banhXe_Nghia);
	thanhBanhXe = Translate(0, 0, -(0.01 / 2 + 0.05)) * RotateZ(+45) * Scale(0.01, 0.15 * 1.8, 0.01);
	VeHinhHop(thanhBanhXe, model_banhXe_Nghia);
	thanhBanhXe = Translate(0, 0, -(0.01 / 2 + 0.05)) * RotateZ(-45) * Scale(0.01, 0.15 * 1.8, 0.01);
	VeHinhHop(thanhBanhXe, model_banhXe_Nghia);
}
void thanGiuaXeTang() {

	mat4 instance = Scale(0.8, 0.2, 0.4);
	VeHinhHop(instance, model_xetang);
}
void thanXeTang() {
	setMau(54, 54, 54, 270);
	mat4 instance = Translate(0, 0.15 + 0.01, 0.6 / 2 - 0.05 / 2) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	instance = Translate(0, -(0.15 + 0.01), 0.6 / 2 - 0.05 / 2) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	//setMau(105, 105 ,105);
	//trên
	for (int i = 1; i <= 3; i++) {
		instance = Translate((0.15) * i, 0.15 + 0.01, 0.6 / 2 - 0.05 / 2) * Scale(0.15, 0.02, 0.2);
		VeHinhHop(instance, model_xetang);
	}
	for (int i = 1; i <= 3; i++) {
		instance = Translate(-(0.15) * i, 0.15 + 0.01, 0.6 / 2 - 0.05 / 2) * Scale(0.15, 0.02, 0.2);
		VeHinhHop(instance, model_xetang);
	}
	//phai
	instance = Translate((0.15) * 3 + 0.15 / 2, 0.15, 0.6 / 2 - 0.05 / 2) * RotateZ(-45) * Translate(0.15 / 2, 0, 0) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	instance = Translate((0.15) * 3 + 0.15 + 0.02, 0.15 * sin(45) - 0.15 / 2, 0.6 / 2 - 0.05 / 2) * RotateZ(-90) * Translate(0.15 / 2, 0, 0) * Scale(0.10, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	instance = Translate((0.15) * 3 + 0.15 / 2, -0.15 - 0.01, 0.6 / 2 - 0.05 / 2) * RotateZ(45) * Translate(0.15 / 2, 0, 0) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	//duoi
	for (int i = 1; i <= 3; i++) {
		instance = Translate((0.16) * i, -(0.15 + 0.01), 0.6 / 2 - 0.05 / 2) * Scale(0.15, 0.02, 0.2);
		VeHinhHop(instance, model_xetang);
	}
	for (int i = 1; i <= 3; i++) {
		instance = Translate(-(0.16) * i, -(0.15 + 0.01), 0.6 / 2 - 0.05 / 2) * Scale(0.15, 0.02, 0.2);
		VeHinhHop(instance, model_xetang);
	}

	//trai
	instance = Translate(-((0.16) * 3 + 0.16 / 2), 0.15, 0.6 / 2 - 0.05 / 2) * RotateZ(45) * Translate(-0.15 / 2, 0, 0) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	instance = Translate(-((0.16) * 3 + 0.16 + 0.04), 0.15 * sin(45) - 0.15 / 2, 0.6 / 2 - 0.05 / 2) * RotateZ(-90) * Translate(0.15 / 2, 0, 0) * Scale(0.10, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	instance = Translate(-((0.16) * 3 + 0.16 / 2), -0.15 - 0.01, 0.6 / 2 - 0.05 / 2) * RotateZ(-45) * Translate(-0.15 / 2, 0, 0) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);

	//
	setMau(54, 54, 54, 270);
	instance = Translate(0, 0.15 + 0.01, -(0.6 / 2 - 0.05 / 2)) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	for (int i = 1; i <= 3; i++) {
		instance = Translate((0.15) * i, 0.15 + 0.01, -(0.6 / 2 - 0.05 / 2)) * Scale(0.15, 0.02, 0.2);
		VeHinhHop(instance, model_xetang);
	}
	for (int i = 1; i <= 3; i++) {
		instance = Translate(-(0.15) * i, 0.15 + 0.01, -(0.6 / 2 - 0.05 / 2)) * Scale(0.15, 0.02, 0.2);
		VeHinhHop(instance, model_xetang);
	}
	//phai
	instance = Translate((0.16) * 3 + 0.15 / 2, 0.15, -(0.6 / 2 - 0.05 / 2)) * RotateZ(-45) * Translate(0.15 / 2, 0, 0) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	instance = Translate((0.16) * 3 + 0.15 + 0.02, 0.15 * sin(45) - 0.15 / 2, -(0.6 / 2 - 0.05 / 2)) * RotateZ(-90) * Translate(0.15 / 2, 0, 0) * Scale(0.10, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	instance = Translate((0.16) * 3 + 0.15 / 2, -0.15 - 0.01, -(0.6 / 2 - 0.05 / 2)) * RotateZ(45) * Translate(0.15 / 2, 0, 0) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	//duoi
	for (int i = 1; i <= 3; i++) {
		instance = Translate((0.16) * i, -(0.15 + 0.01), -(0.6 / 2 - 0.05 / 2)) * Scale(0.15, 0.02, 0.2);
		VeHinhHop(instance, model_xetang);
	}
	for (int i = 1; i <= 3; i++) {
		instance = Translate(-(0.16) * i, -(0.15 + 0.01), -(0.6 / 2 - 0.05 / 2)) * Scale(0.15, 0.02, 0.2);
		VeHinhHop(instance, model_xetang);
	}
	instance = Translate(0, -(0.16), -(0.6 / 2 - 0.05 / 2)) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);

	//trai
	instance = Translate(-((0.15) * 3 + 0.15 / 2), 0.15, -(0.6 / 2 - 0.05 / 2)) * RotateZ(45) * Translate(-0.15 / 2, 0, 0) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	instance = Translate(-((0.15) * 3 + 0.15 + 0.02), 0.15 * sin(45) - 0.15 / 2, -(0.6 / 2 - 0.05 / 2)) * RotateZ(-90) * Translate(0.15 / 2, 0, 0) * Scale(0.10, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	instance = Translate(-((0.15) * 3 + 0.15 / 2), -0.15 - 0.01, -(0.6 / 2 - 0.05 / 2)) * RotateZ(-45) * Translate(-0.15 / 2, 0, 0) * Scale(0.15, 0.02, 0.2);
	VeHinhHop(instance, model_xetang);
	/*banhXeTang(1.2 / 2 - 0.15 , 0, -(0.6 / 2 - 0.05 / 2));
	banhXeTang(1.2 / 2 - 0.15-0.3, 0, -(0.6 / 2 - 0.05 / 2));
	banhXeTang(1.2 / 2 - 0.15-0.6, 0, -(0.6 / 2 - 0.05 / 2));
	banhXeTang(-(1.2 / 2 - 0.15 ), 0, -(0.6 / 2 - 0.05 / 2));*/
	setMau(34, 139, 34, 270);
	//thanxe
	setMau(34, 139, 34, 270);
	vanhChanBun(0, 0.15 + 0.03, 0.6 / 2 - 0.05 / 2);
	setMau(34, 139, 34, 170);
	vanhChanBun(0, 0.15 + 0.03, -(0.6 / 2 - 0.05 / 2));

	setMau(34, 139, 34, 270, vec4(1, 4, -2, 1));
	//setMau(255, 165, 0, 270, vec4(1,4,-2,1));
	instance = Translate(0, 0.11 + 0.1 + 0.04, 0) * Scale(0.8, 0.2, 0.4);
	VeHinhHop(instance, model_xetang);
	//thanh chan thân
	instance = Translate(0, 0.11 + 0.1 + 0.04 + 0.1, 0.4 / 2 + 0.1) * RotateX(-0) * Translate(0, -0.1, 0) * Scale(0.8, 0.2, 0.1);
	VeHinhHop(instance, model_xetang);
	instance = Translate(0, 0.11 + 0.1 + 0.04 + 0.1, -(0.4 / 2 + 0.1)) * RotateX(0) * Translate(0, -0.1, 0) * Scale(0.8, 0.2, 0.1);
	VeHinhHop(instance, model_xetang);

	instance = Translate(-0.8 / 2 + 0.08, 0.11 + 0.1 + 0.04 + 0.1 - 0.07, 0) * RotateZ(-45) * Translate(0, -0.1, 0) * Scale(0.04 + 0.16, 0.22, 0.4 + 0.3);
	VeHinhHop(instance, model_xetang);
	instance = Translate(0.8 / 2 - 0.08, 0.11 + 0.1 + 0.04 + 0.1 - 0.07, 0) * RotateZ(45) * Translate(0, -0.1, 0) * Scale(0.04 + 0.16, 0.22, 0.4 + 0.3);
	VeHinhHop(instance, model_xetang);
	/*instance = Translate(0, 0.11 + 0.1 + 0.04 + 0.1, 0.4 / 2) * RotateX(-45) * Translate(0, -0.1, 0) * Scale(0.8, 0.2, 0.04);
	VeHinhHop(instance, model_xetang);
	instance = Translate(0, 0.11 + 0.1 + 0.04 + 0.1, -(0.4 / 2)) * RotateX(45) * Translate(0, -0.1, 0) * Scale(0.8, 0.2, 0.04);
	VeHinhHop(instance, model_xetang);

	instance = Translate(-0.8 / 2, 0.11 + 0.1 + 0.04 + 0.1, 0) * RotateZ(-45) * Translate(0, -0.1, 0) * Scale(0.04, 0.2, 0.4);
	VeHinhHop(instance, model_xetang);
	instance = Translate(0.8 / 2, 0.11 + 0.1 + 0.04 + 0.1, 0) * RotateZ(45) * Translate(0, -0.1, 0) * Scale(0.04, 0.2, 0.4);
	VeHinhHop(instance, model_xetang);*/
	setMau(34, 139, 34, 270);
	/*mat4 m = Translate(0,0.23,-0.32)*Scale(0.06, 0.05, 0.09);
	VeHinhHop(m, model_xetang);*/
	/*for (int i = 0; i < 5; i++) {
		mat4 m = Translate(i*0.1, 0.335, -0.32) * Scale(0.15, 0.2, 0.09);
		VeHinhHop(m, model_xetang);
	 }
	for (int i = 0; i < 5; i++) {
		mat4 m = Translate(i * 0.1, 0.335, -0.32) * Scale(0.15, 0.2, 0.09);
		VeHinhHop(m, model_xetang);
	}*/
	//for (int i = 0; i < 5; i++) {
	//	mat4 m = Translate(i * 0.078, 0.3, -0.32) * Scale(0.06, 0.05, 0.09);
	//	VeHinhHop(m, model_xetang);
	//}
	//for (int i = 0; i < 5; i++) {
	//	mat4 m = Translate(-i * 0.078, 0.3, -0.32) * Scale(0.06, 0.05, 0.09);
	//	VeHinhHop(m, model_xetang);
	//}


}
void khungQuayXeTang() {
	setMau(34, 139, 34, 270);
	mat4 instance = Translate(0, 0, 0.2 - 0.01) * Scale(0.4, 0.2, 0.04);
	VeHinhHop(instance, model_xetang);
	instance = Translate(0, 0, -(0.2 - 0.01)) * Scale(0.4, 0.2, 0.04);
	VeHinhHop(instance, model_xetang);

	instance = Translate(-0.15 - 0.02, 0, 0) * Scale(0.04, 0.2, 0.4 - 0.02);
	VeHinhHop(instance, model_xetang);

	instance = Translate(0, 0.15 / 2 + 0.02, 0) * Scale(0.4, 0.04, 0.4 - 0.02);
	VeHinhHop(instance, model_xetang);
}
void nongSung_xeTang() {
	setMau(160, 82, 45, 270);
	setMau(255, 165, 0, 270);
	mat4 instance = Scale(0.04, 0.15, 0.4 - 0.02);
	VeHinhHop(instance, model_xetang);
	instance = Translate(0.3, 0, 0) * RotateZ(90) * Scale(0.05, 0.3, 0.05);
	VeHinhTru(instance, model_xetang);
	setMau(0, 0, 0, 270);
	instance = Translate(0.3 + 0.25, 0, 0) * RotateZ(90) * Scale(0.07, 0.09, 0.07);
	VeHinhTru(instance, model_xetang);
}
GLfloat danBanSung_robot = 0, danBanXeTang_Nghia = 0, danBantenLua1 = 0, danBantenLua2 = 0;
void dan() {
	mat4 instance = Translate(0.4, 0, 0) * RotateZ(90) * Scale(0.02, 0.1, 0.02);
	VeHinhTru(instance, model_xetang);
}

void XeTang() {

	model_xetang = RotateY(ynXeTang) * Translate(diChuyenXeTang, 0, 0) * Translate(0, 0.15 + 0.04, 0);
	thanXeTang();
	model_banhXe_Nghia = model_xetang * Translate(1.2 / 2 - 0.15, 0, 0.6 / 2 - 0.05 / 2) * RotateZ(quayBangXeTang);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xetang * Translate(1.2 / 2 - 0.15 - 0.3, 0, 0.6 / 2 - 0.05 / 22) * RotateZ(quayBangXeTang);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xetang * Translate(1.2 / 2 - 0.15 - 0.6, 0, 0.6 / 2 - 0.05 / 22) * RotateZ(quayBangXeTang);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xetang * Translate(-(1.2 / 2 - 0.15), 0, 0.6 / 2 - 0.05 / 2) * RotateZ(quayBangXeTang);
	banhXe_Nghia();
	//
	//
	model_banhXe_Nghia = model_xetang * Translate(1.2 / 2 - 0.15, 0, -(0.6 / 2 - 0.05 / 22)) * RotateZ(quayBangXeTang);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xetang * Translate(1.2 / 2 - 0.15 - 0.3, 0, -(0.6 / 2 - 0.05 / 2)) * RotateZ(quayBangXeTang);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xetang * Translate(1.2 / 2 - 0.15 - 0.6, 0, -(0.6 / 2 - 0.05 / 2)) * RotateZ(quayBangXeTang);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xetang * Translate(-(1.2 / 2 - 0.15), 0, -(0.6 / 2 - 0.05 / 2)) * RotateZ(quayBangXeTang);
	banhXe_Nghia();

	model_xetang = model_xetang * RotateY(quayKhungSung) * Translate(0, 0.2 + 0.1 + 0.15, 0);
	khungQuayXeTang();
	model_xetang = model_xetang * Translate(0.2, 0.15 / 2, 0) * RotateZ(quayNongSung) * Translate(0.04 / 2, -0.15 / 2, 0);
	nongSung_xeTang();
	setMau(255, 0, 0, 270);
	model_xetang = model_xetang * Translate(danBanXeTang_Nghia, 0, 0);
	dan();

}
void hinh1() {
	setMau(35, 139, 34, 270);
	mat4 instance = Scale(1, 1, 1);
	VeHinhTru(instance, mat4());
}
void reshape(int width, int height)
{
	vec4 eye(2, 2, 2, 1);
	//vec4 eye = vec4(−1.5f, −2.0f, −4.1f, 1);
	vec4 at(0, 0, 0, 1);
	vec4 up(0, 1, 0, 1);

	mat4 view = LookAt(eye, at, up);
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, view);

	mat4 projection = Ortho(-2, 2, -2, 2, 2, 10);
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);

	glViewport(0, 0, width, height);
}clock_t lastShootTime = 0;

float xx = 0, yy = 0, zz = 0;
void dauRoBot() {

	setMau(255, 250, 179, 100);
	mat4 m = Scale(0.2, 0.2, 0.2);
	VeHinhHop(m, model_dauRobot);
	setMau(255, 0, 0, 100);
	m = Translate(0, -0.05, 0.1) * Scale(0.08, 0.03, 0.03);
	VeHinhHop(m, model_dauRobot);
	m = Translate(0.05, 0.05, 0.1 + 0.01) * RotateX(-90) * Scale(0.025, 0.005, 0.025);
	VeHinhTru(m, model_dauRobot);
	m = Translate(-0.05, 0.05, 0.1 + 0.01) * RotateX(-90) * Scale(0.025, 0.005, 0.025);
	VeHinhTru(m, model_dauRobot);

	setMau(54, 117, 23, 100);
	m = Translate(0, 0.1 + 0.07 / 2, 0.03 / 2) * Scale(0.25, 0.07, 0.23);
	VeHinhHop(m, model_dauRobot);
	m = Translate(0, 0.1, -0.08) * Scale(0.2, 0.12, 0.07);
	VeHinhHop(m, model_dauRobot);
	m = Translate(0.1, 0.1, 0) * Scale(0.07, 0.12, 0.2);
	VeHinhHop(m, model_dauRobot);
	m = Translate(-0.1, 0.1, 0) * Scale(0.07, 0.12, 0.2);
	VeHinhHop(m, model_dauRobot);
}
void Sung_Nghia(float x, float y, float z) {
	//model_SungsRobot =  RotateY(90)*Translate(0.33, 0.25, 0);// *RotateY(90);
	setMau(189, 107, 9, 270);
	mat4 m = Scale(0.8, 0.2, 0.14);
	VeHinhHop(m, model_SungsRobot);
	m = Translate(-0.4 - 0.15 - 0.1, -0.1, 0) * Scale(0.1, 0.3, 0.1);
	VeHinhHop(m, model_SungsRobot);
	setMau(0, 0, 255, 270);
	m = Translate(-0.4 - 0.1, -0.1, 0) * RotateZ(-45) * Scale(0.06, 0.3, 0.1);
	VeHinhHop(m, model_SungsRobot);
	m = Translate(-0.4 - 0.15, 0, 0) * Scale(0.3, 0.12, 0.12);
	VeHinhHop(m, model_SungsRobot);
	m = Translate(0.15, -0.1 - 0.15, 0) * Scale(0.12, 0.3, 0.12);
	VeHinhHop(m, model_SungsRobot);
	m = Translate(-0.3, -0.1 - 0.05, 0) * RotateZ(-40) * Scale(0.12, 0.3, 0.12);
	VeHinhHop(m, model_SungsRobot);
	m = Translate(+0.4 + 0.15, 0, 0) * RotateZ(90) * Scale(0.06, 0.3, 0.06);
	VeHinhTru(m, model_SungsRobot);
	setMau(54, 54, 54, 270);
	m = Translate(0.3, 0.1, 0) * RotateZ(45) * Scale(0.1, 0.1, 0.06);
	VeHinhHop(m, model_SungsRobot);
	setMau(54 + heSo, 54, 54, 270);
	m = Translate(+0.4 + 0.15 + 0.28, 0, 0) * RotateZ(90) * Scale(0.07, 0.1, 0.07);
	VeHinhTru(m, model_SungsRobot);
	setMau(1, 0, 0, 270);

	//model_SungsRobot = ;
	/*m = Translate(danBan, 0, 0) * Translate(0.4, 0, 0)*RotateZ(90) * Scale(0.03, 0.1, 0.03);
	VeHinhTru(m, model_SungsRobot);*/
}
void dan_sung_robot() {
	setMau(249, 244, 0, 100);
	mat4 m = RotateZ(90) * Scale(0.03, 0.1, 0.03);
	VeHinhTru(m, model_SungsRobot);
}
void thanRobot() {

	setMau(255, 250, 179, 500);
	//thân
	mat4 m = Scale(0.5, 0.8, 0.3);
	VeHinhHop(m, model_robot);
	m = Scale(0.5, 0.8, 0.3);
	//khớp vai
	VeHinhHop(m, model_robot);
	m = Translate(0.3, 0.4 - 0.11, 0) * RotateZ(90) * Scale(0.08, 0.05, 0.06);
	VeHinhTru(m, model_robot);
	m = Translate(-0.3, 0.4 - 0.11, 0) * RotateZ(90) * Scale(0.08, 0.05, 0.06);
	VeHinhTru(m, model_robot);
	setMau(0, 0, 0, 0);
	m = Translate(-0.15, -0.4, 0) * RotateZ(90) * Scale(0.08, 0.05, 0.08);
	VeHinhTru(m, model_robot);
	m = Translate(0.15, -0.4, 0) * RotateZ(90) * Scale(0.08, 0.05, 0.08);
	VeHinhTru(m, model_robot);
	m = Translate(0, 0.44, 0) * Scale(0.08, 0.05, 0.08);
	VeHinhTru(m, model_robot);
}
void xyz() {
	mat4 m = Translate(0, 2, 1) * RotateX(90) * Scale(0.01, 2, 0.01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, m);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	setMau(1, 0, 0, 100);
	m = Translate(1, 2, 0) * RotateZ(90) * Scale(0.01, 2, 0.01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, m);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	// xanh y
	setMau(0, 1, 0, 100);
	m = Translate(0, 1 + 2, 0) * Scale(0.01, 2, 0.01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, m);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tayTren() {
	setMau(24, 139, 34, 0);
	//Translate(-0.36,0.15,0)*
	mat4 m = Scale(0.16, 0.4, 0.16);
	VeHinhHop(m, model_canhTayRoBot);
	setMau(0, 0, 0, 30);
	/*m =Translate(0.08+0.05/2,0.4/2/2,0)* Scale(0.05, 0.4/3, 0.16);
	VeHinhHop(m, model_canhTayRoBot);*/
	setMau(0, 0, 0, 30);
	//Translate(-0.36, 0.15 - 0.22, 0)*
	m = Translate(0, -0.2, 0) * RotateZ(90) * Scale(0.04, 0.06, 0.04);
	VeHinhTru(m, model_canhTayRoBot);
	setMau(205, 85, 85, 30);
	/* m = Translate(-0.36, 0.15 -0.22-0.2-0.015, 0) * Scale(0.12, 0.36, 0.12);
	VeHinhHop(m, model_robot);*/
}
void tayDuoi() {
	//Translate(-0.36, 0.15 - 0.22 - 0.2 - 0.015, 0)*
	setMau(178, 34, 34, 100);
	mat4 m = Scale(0.12, 0.36, 0.12);
	VeHinhHop(m, model_canhTayRoBot);
}
void chanRobot() {
	setMau(178, 34, 34, 100);
	mat4 m = Scale(0.17, 0.7, 0.17);
	VeHinhHop(m, model_chanRobot);
}
float ynTayDuoiRobot = 0, znTayDuoiRobot = 0;
void RoBot_Nghia() {
	model_robot = RotateY(ynRobot + 90) * Translate(xxRoBot, 0.6, 0) * RotateY(90) * Scale(0.5, 0.5, 0.5);
	thanRobot();
	model_dauRobot = model_robot * Translate(0, 0.54, 0) * RotateY(quayDauRobot);
	dauRoBot();
	//model_trungGian_robot1 =model_robot*Translate(0+ xxSungRobot,0.1,-0.23)*RotateZ(45)*Scale(0.7,0.7,0.7);
	//model_SungsRobot =model_robot*Translate(0,0.1,-0.23)*RotateZ(45)*Scale(0.7,0.7,0.7);
	//Sung_Nghia(0, 0, 0);
	model_canhTayRoBot = model_robot * Translate(-0.36, 0.17, 0) * Translate(0, 0.14, 0) * RotateX(xnTayTrenRobot1) * Translate(0, -0.14, 0);
	tayTren();
	model_canhTayRoBot = model_canhTayRoBot * Translate(0, -0.22 - 0.14, 0) * Translate(0, 0.16, 0) * RotateY(25) * RotateX(xnTayDuoiRobot1) * RotateX(-60) * Translate(0, -0.16, 0);
	tayDuoi();
	//model_trungGian_robot2 = model_canhTayRoBot *Translate(0.22,-0.2,0.2)*RotateZ(-10)*RotateX(60) *  Translate(-0.33, -0.25, 0) * RotateY(ynAK) * Translate(0.33 + xxSungRobot, 0.25, 0) * Scale(0.7, 0.7, 0.7);

	//model_trungGian_robot2 = model_canhTayRoBot  * Translate(-0.3 + 0.32,-0.25 + 0.1 , 0 )*RotateX(55)*RotateZ(10)* RotateY(ynAK -25)*Translate(0.3+ xxSungRobot, 0.25, 0) * Scale(0.68, 0.68, 0.68);
	model_SungsRobot = model_canhTayRoBot * Translate(0.3, -0.1, 0.28) * Translate(+xxSungRobot, 0, 0) * RotateZ(12) * RotateX(60) * RotateY(-30) * Translate(-0.33, -0.25, 0) * RotateY(ynAK) * Translate(0.33, 0.25, 0) * Scale(0.7, 0.7, 0.7);
	//Sung_Nghia(0, 0, 0);
	Sung_Nghia(0, 0, 0);
	model_SungsRobot *= Translate(danBanSung_robot, 0, 0) * Translate(0.4, 0, 0);
	dan_sung_robot();
	model_canhTayRoBot = model_robot * Translate(0.36, 0.17, 0) * Translate(0, 0.14, 0) * RotateX(xnTayTrenRobot2) * Translate(0, -0.14, 0);
	tayTren();
	model_canhTayRoBot = model_canhTayRoBot * Translate(0, -0.22 - 0.14, 0) * Translate(0, 0.16, 0) * RotateY(-30) * RotateX(xnTayDuoiRobot2 - 70) * Translate(0, -0.16, 0);
	tayDuoi();
	//chân
	model_chanRobot = model_robot * Translate(-0.15, -0.415, 0) * RotateX(xnChanRobot1) * Translate(0, -0.35, 0);
	chanRobot();
	model_chanRobot = model_robot * Translate(0.15, -0.415, 0) * RotateX(xnChanRobot2) * Translate(0, -0.35, 0);
	chanRobot();
}
void view_projection() {
	/*vec4 eye = vec4(3, 5, 10, 1);
	vec4 at = vec4(0, 0, 0, 1);*/
	//vec4 up = vec4(0, 1, 0, 1);

	//mat4 v = LookAt(eye, at, up);
	//glUniformMatrix4fv(view_loc, 1, GL_TRUE, v);

	//mat4 p = Frustum(l, r, bot, top, zNear, zFar);
	//glUniformMatrix4fv(projection_loc, 1, GL_TRUE, p);
	//at = vec4(0, 0, 0, 1);
	//at = vec4(cosf(DEGtoRAD(QuayCamera[0])), QuayCamera[1], cosf(DEGtoRAD(QuayCamera[2])), 1) + eye;
	//RotateX(QuayCamera[1])*
	//RotateY(gocQuayNgangCam)*

	//camera
	vec4 eye = Translate(xEye, 0, 0 * xEye * tan(gocQuayNgangCam)) * vec4(0, 0.2, -6, 1);
	float eye_trucY = abs(eye.z);
	///cout << "eye_Y"<<eye_trucY;
	//RotateY(-gocQuayNgangCam)*
	vec4 at = Translate(xEye + sin(gocQuayNgangCam) * eye_trucY, 0 + tanf(gocQuayDocCam) * eye_trucY, cos(gocQuayNgangCam) * eye_trucY) * vec4(0, 0.2, -1, 1);

	//camera
	//vec4 at = Translate(xEye + tanf(gocQuayNgangCam) * eye_trucY, 0 + tanf(gocQuayDocCam) * eye_trucY, 0) * vec4(0, 0.2, -1, 1);
	//vec4 at = Translate(0, 0, -eye_trucY)*RotateY(gocQuayNgangCam)*Translate(0,0,eye_trucY)*vec4(0, 0.2, -1, 1);
	/*vec4 at = Translate(xEye,0,0)*vec4(0, 0.2, -1, 1);
	if (gocQuayNgangCam < 180) {
		at =  Translate(0, 0, -eye_trucY) * RotateY(gocQuayNgangCam) * Translate(0, 0, eye_trucY)*at;
	}
	else {
		at = Translate(0, 0, +eye_trucY) * RotateY(gocQuayNgangCam) * Translate(0, 0, eye_trucY) * at;
	}*/
	vec4 up(0, 1, 0, 1);

	//at = Translate(tan(gocQuayNgangCam) * eye_trucY, 0, 0) * at;
	mat4 view = LookAt(eye, at, up);
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, view);
	mat4 p = Frustum(l, r, bot, top, zNear, zFar);
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, p);
}
void TenLua_Nghia() {
	setMau(54, 117, 23, 100);

	mat4 m = RotateZ(90) * Scale(0.12, 0.3, 0.12);
	VeHinhTru(m, model_tenlua);
	m = Translate(-0.18, 0.17, 0) * Scale(0.15, 0.15, 0.05);
	VeHinhHop(m, model_tenlua);
	m = Translate(-0.18, -0.17, 0) * Scale(0.15, 0.15, 0.05);
	VeHinhHop(m, model_tenlua);
	m = Translate(-0.18, 0, -0.17) * Scale(0.15, 0.05, 0.15);
	VeHinhHop(m, model_tenlua);
	m = Translate(-0.18, 0, 0.17) * Scale(0.15, 0.05, 0.15);
	VeHinhHop(m, model_tenlua);
	setMau(160, 82, 45, 100);
	m = Translate(0.3, 0, 0) * RotateY(45) * Scale(0.12, 0.12, 0.12);
	VeHinhHop(m, model_tenlua);
	/*m = Translate(0.3, 0, 0) *RotateX(90)* RotateY(45) * Scale(0.12, 0.12, 0.12);
	VeHinhHop(m, model_tenlua);*/
}

void GiaDoTenLua() {

	mat4 m = Scale(0.8, 0.15, 0.8);
	VeHinhHop(m, model_giaDotenLua);
	m = Translate(0, -0.15 / 2 - 0.1, 0) * Scale(0.3, 0.08, 0.3);
	VeHinhTru(m, model_giaDotenLua);

}
void GiaDoXoayDocTenLua() {
	setMau(123, 45, 255, 100);
	/*mat4 m = Translate(0, 1.3-1.3, 0) * RotateX(90) * Scale(0.2, 0.05, 0.2);
	VeHinhTru(m, model_giaDotenLua);*/
	mat4 m = Translate(0, 0, 0.2 + 0.1) * Scale(0.8, 0.1, 0.1);
	VeHinhHop(m, model_giaDotenLua);
	m = Translate(0, 0, -0.2 - 0.1) * Scale(0.8, 0.1, 0.1);
	VeHinhHop(m, model_giaDotenLua);
}
void XeTenLua() {
	setMau(34, 139, 34, 270);
	mat4 m = Translate(1 - 0.4, 0.2, 0) * Scale(0.4, 0.4, 0.8);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(1 - 0.3, 0.115, 0) * RotateZ(-70) * Scale(0.48, 0.4, 0.8);
	VeHinhHop(m, model_xeTenLua);

	setMau(1, 1, 1, 270);
	m = Translate(1 - 0.13, 0.2, 0) * RotateZ(20) * Scale(0.1, 0.25, 0.5);
	VeHinhHop(m, model_xeTenLua);
	/*m = Translate(1 - 0.3, 0.2,0.37) * Scale(0.25, 0.2, 0.1);
	VeHinhHop(m, model_xeTenLua);*/
	setMau(255, 165, 0, 270);
	m = Translate(0, -0.05, 0) * Scale(2, 0.1, 0.81);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(0.1, -0.15, 0) * Scale(0.65, 0.15, 0.8);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(1 - 0.1, -0.15, 0) * Scale(0.2, 0.15, 0.8);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(-0.85, -0.1, -0.29) * RotateZ(-45) * Translate(0, -0.1, 0) * Scale(0.05, 0.2, 0.25);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(-0.85, -0.1, 0.29) * RotateZ(-45) * Translate(0, -0.1, 0) * Scale(0.05, 0.2, 0.25);
	VeHinhHop(m, model_xeTenLua);


	setMau(182, 41, 43, 270);

	m = Translate(1 + 0.01, 0, -0.2) * RotateZ(-90) * Translate(0.1, 0, 0) * Scale(0.1, 0.04, 0.1);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(1 + 0.01, 0, 0.2) * RotateZ(-90) * Translate(0.1, 0, 0) * Scale(0.1, 0.04, 0.1);
	VeHinhHop(m, model_xeTenLua);

	setMau(255, 165, 0, 270);
	m = Translate(0.8, 0.22, -0.45) * Scale(0.03, 0.15, 0.06);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(0.8, 0.22, 0.45) * Scale(0.03, 0.15, 0.06);
	VeHinhHop(m, model_xeTenLua);

	m = Translate(0.8, 0.1, -0.42) * Scale(0.03, 0.03, 0.1);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(0.8, 0.1, 0.42) * Scale(0.03, 0.03, 0.1);
	VeHinhHop(m, model_xeTenLua);

	m = Translate(0.8, 0.125, -0.45) * Scale(0.03, 0.08, 0.03);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(0.8, 0.125, 0.45) * Scale(0.03, 0.08, 0.03);
	VeHinhHop(m, model_xeTenLua);
	setMau(188, 143, 143, 100);
	m = Translate(0.38, 0.2, -0.37) * Scale(0.025, 0.3, 0.025);
	VeHinhTru(m, model_xeTenLua);
	m = Translate(0.41, 0.55, -0.37) * Translate(0, -0.1, 0) * RotateZ(40) * Translate(0, 0.1, 0) * Scale(0.025, 0.05, 0.025);
	VeHinhTru(m, model_xeTenLua);
	m = Translate(0.38, 0.2, 0.37) * Scale(0.025, 0.3, 0.025);
	VeHinhTru(m, model_xeTenLua);
	m = Translate(0.41, 0.55, 0.37) * Translate(0, -0.1, 0) * RotateZ(40) * Translate(0, 0.1, 0) * Scale(0.025, 0.05, 0.025);
	VeHinhTru(m, model_xeTenLua);
	/*m = Translate(1 - 0.3, 0.115, 0) * RotateZ(-70) * Scale(0.48, 0.4, 0.8);
	VeHinhHop(m, model_xeTenLua);*/

	/*setMau(182, 41, 43,270);
	for (int i = 0; i < 5; i++)
	{
		m = Translate(1 - 0.25, 0.45, i*0.08) * Scale(0.03, 0.1, 0.03);
		VeHinhHop(m, model_xeTenLua);
		m = Translate(1 - 0.25, 0.45, -i * 0.08) * Scale(0.03, 0.1, 0.03);
		VeHinhHop(m, model_xeTenLua);
		m = Translate(1 - 0.55, 0.45, i * 0.08) * Scale(0.03, 0.1, 0.03);
		VeHinhHop(m, model_xeTenLua);
		m = Translate(1 - 0.55, 0.45, -i * 0.08) * Scale(0.03, 0.1, 0.03);
		VeHinhHop(m, model_xeTenLua);
	}
	m = Translate(1 - 0.55+0.08, 0.45, 4 * 0.08) * Scale(0.03, 0.1, 0.03);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(1 - 0.55 + 0.08*2, 0.45, 4 * 0.08) * Scale(0.03, 0.1, 0.03);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(1 - 0.55 + 0.08 * 3, 0.45, 4 * 0.08) * Scale(0.03, 0.1, 0.03);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(1 - 0.55 + 0.08, 0.45, -4 * 0.08) * Scale(0.03, 0.1, 0.03);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(1 - 0.55 + 0.08 * 2, 0.45, -4 * 0.08) * Scale(0.03, 0.1, 0.03);
	VeHinhHop(m, model_xeTenLua);
	m = Translate(1 - 0.55 + 0.08 * 3, 0.45, -4 * 0.08) * Scale(0.03, 0.1, 0.03);
	VeHinhHop(m, model_xeTenLua);*/
}
void XeTenLuaSieuVip() {
	model_xeTenLua = RotateY(ThetaXeTenLua[0]) * Translate(xXeTenLua, 0.5, 0);
	XeTenLua();

	model_banhXe_Nghia = model_xeTenLua * Translate(0.6, -0.15 - 0.1, 0.36) * RotateZ(quayBanhXeTenLua);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xeTenLua * Translate(0.6, -0.15 - 0.1, -0.36) * RotateZ(quayBanhXeTenLua);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xeTenLua * Translate(-0.37, -0.15 - 0.1, 0.36) * RotateZ(quayBanhXeTenLua);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xeTenLua * Translate(-0.37, -0.15 - 0.1, -0.36) * RotateZ(quayBanhXeTenLua);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xeTenLua * Translate(-0.7, -0.15 - 0.1, 0.36) * RotateZ(quayBanhXeTenLua);
	banhXe_Nghia();
	model_banhXe_Nghia = model_xeTenLua * Translate(-0.7, -0.15 - 0.1, -0.36) * RotateZ(quayBanhXeTenLua);
	banhXe_Nghia();

	model_giaDotenLua = model_xeTenLua * Translate(-0.3, 0.15, 0) * RotateY(ThetaXeTenLua[1]);
	GiaDoTenLua();
	model_giaDotenLua = model_giaDotenLua * Translate(0, 0.1, 0) * Translate(-0.4, 0, 0) * RotateZ(ThetaXeTenLua[2]) * RotateZ(20) * Translate(0.4, 0, 0);
	GiaDoXoayDocTenLua();
	model_tenlua = model_giaDotenLua * Translate(danBantenLua1, 0, 0) * Translate(0, 0.12, 0.2 + 0.1) * RotateX(30) * Scale(2, 1, 1);
	TenLua_Nghia();
	model_tenlua = model_giaDotenLua * Translate(danBantenLua2, 0, 0) * Translate(0, 0.15, -0.2 - 0.1) * RotateX(30) * Scale(2, 1, 1);
	TenLua_Nghia();
}
void sanNha() {
	setMau(230, 241, 216, 30, vec4(0, 10, 0, 1));
	mat4 m = Translate(0, -00.03 / 2, 0) * Scale(20, 0.03, 20);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, m);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

//Xe phao (Minh Nghia)
mat4 model_nong, model_banh, model_nong1, model_ban;
GLfloat theta[10] = { 0,0,0,0,0,0,0,0,0,0 };

mat4 model_xe_phao;
void setMau(vec4 color) {

	color4 ambient_product = light_ambient * color;
	color4 diffuse_product = light_diffuse * color;
	color4 specular_product = light_specular * color;

	glUniform4fv(ambient_product_loc, 1, ambient_product);
	glUniform4fv(diffuse_product_loc, 1, diffuse_product);
	glUniform4fv(specular_product_loc, 1, specular_product);
}
void than()
{
	mat4 instance = Scale(0.8, 0.2, 0.3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tamchan(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
	mat4 instance = Translate(x, y, z) * RotateX(a) * Scale(0.2, 0.203, 0.005);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void tamchanthan()
{
	tamchan(0.1, 0, 0.167, -10);
	tamchan(-0.1, 0, 0.167, -10);
	tamchan(0.3, 0, 0.167, -10);
	tamchan(-0.3, 0, 0.167, -10);
	tamchan(0.1, 0, -0.167, 10);
	tamchan(-0.1, 0, -0.167, 10);
	tamchan(0.3, 0, -0.167, 10);
	tamchan(-0.3, 0, -0.167, 10);
}
void day()
{
	mat4 instance = Translate(0.1, -0.15, 0) * Scale(1, 0.1, 0.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void vanhxe(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 instance = Translate(x, y, z) * Scale(0.2, 0.01, 0.1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void vanhxe1(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
	mat4 instance = Translate(x, y, z) * RotateZ(a) * Scale(0.1, 0.01, 0.1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void vanhngang()
{
	vanhxe(-0.4, -0.12, -0.15);
	vanhxe(0.4, -0.12, -0.15);
	vanhxe(0, -0.12, -0.15);
	vanhxe(-0.4, -0.12, 0.15);
	vanhxe(0.4, -0.12, 0.15);
	vanhxe(0, -0.12, 0.15);
}
void vanhdoc()
{
	vanhxe1(-0.53, -0.143, -0.15, 40);
	vanhxe1(-0.13, -0.143, -0.15, 40);
	vanhxe1(0.27, -0.143, -0.15, 40);
	vanhxe1(-0.27, -0.143, -0.15, -40);
	vanhxe1(0.13, -0.143, -0.15, -40);
	vanhxe1(0.53, -0.143, -0.15, -40);
	vanhxe1(-0.53, -0.143, 0.15, 40);
	vanhxe1(-0.13, -0.143, 0.15, 40);
	vanhxe1(0.27, -0.143, 0.15, 40);
	vanhxe1(-0.27, -0.143, 0.15, -40);
	vanhxe1(0.13, -0.143, 0.15, -40);
	vanhxe1(0.53, -0.143, 0.15, -40);
}
void thannong1()
{
	mat4 instance = Translate(0, 0.18, 0) * Scale(0.3, 0.1, 0.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_nong * model_nong1 * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nong1()
{
	mat4 instance = Translate(-0.19, 0.18, 0) * Scale(0.08, 0.08, 0.08);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_nong * model_nong1 * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nong2()
{
	mat4 instance = Translate(-0.08, 0.18, 0.13) * Scale(0.06, 0.06, 0.06);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_nong * model_nong1 * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nong3()
{
	mat4 instance = Translate(-0.08, 0.18, -0.13) * Scale(0.06, 0.06, 0.06);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_nong * model_nong1 * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void tron1(GLfloat x) {
	mat4 instance = Translate(-0.53, 0.18, 0) * RotateY(90) * RotateZ(x) * Scale(0.05, 0.05, 0.6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_nong * model_nong1 * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nongtron1() {
	for (int i = 1; i <= 180; i++) {
		tron1(i);
	}
}

void tron2(GLfloat x) {
	mat4 instance = Translate(-0.35, 0.18, -0.08) * RotateY(90) * RotateZ(x) * Scale(0.03, 0.03, 0.4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_nong * model_nong1 * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nongtron2() {
	for (int i = 1; i <= 180; i++) {
		tron2(i);
	}
}
void tron3(GLfloat x) {
	mat4 instance = Translate(-0.35, 0.18, 0.08) * RotateY(90) * RotateZ(x) * Scale(0.03, 0.03, 0.4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_nong * model_nong1 * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nongtron3() {
	for (int i = 1; i <= 180; i++) {
		tron3(i);
	}
}
void tron4(GLfloat x) {
	mat4 instance = Translate(-0.31, 0.18, 0.13) * RotateY(90) * RotateZ(x) * Scale(0.03, 0.03, 0.4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_nong * model_nong1 * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nongtron4() {
	for (int i = 1; i <= 180; i++) {
		tron4(i);
	}
}
void tron5(GLfloat x) {
	mat4 instance = Translate(-0.31, 0.18, -0.13) * RotateY(90) * RotateZ(x) * Scale(0.03, 0.03, 0.4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_nong * model_nong1 * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nongtron5() {
	for (int i = 1; i <= 180; i++) {
		tron5(i);
	}
}
void tronquay(GLfloat x) {
	mat4 instance = Translate(0, 0.11, 0) * RotateX(90) * RotateZ(x) * Scale(0.1, 0.1, 0.05);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_nong * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nongquay() {
	for (int i = 1; i <= 180; i++) {
		tronquay(i);
	}
}


void dauxe1()
{
	mat4 instance = Translate(-0.45, 0.01, 0) * RotateZ(30) * Scale(0.2, 0.1, 0.3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void dauxe2()
{
	mat4 instance = Translate(-0.55, -0.105, 0) * RotateZ(30) * Scale(0.1, 0.2, 0.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void dauxe3()
{
	mat4 instance = Translate(-0.42, -0.08, 0) * RotateZ(30) * Scale(0.2, 0.1, 0.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void ditxe1()
{
	mat4 instance = Translate(0.5, 0, 0) * RotateZ(45) * Scale(0.005, 0.283, 0.3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void ditxe2()
{
	mat4 instance = Translate(0.45, -0.03, 0) * RotateZ(45) * Scale(0.005, 0.2, 0.3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void ditxe3()
{
	mat4 instance = Translate(0.42, -0.06, 0) * RotateZ(45) * Scale(0.005, 0.1, 0.3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void duongtron1(GLfloat x) {
	mat4 instance = Translate(0, -0.25, -0.19) * RotateZ(x) * Scale(0.22, 0.01, 0.08);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_banh * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void banhxee1() {
	for (int i = 1; i <= 180; i++) {
		duongtron1(i);
	}
}
void duongtron2(GLfloat x) {
	mat4 instance = Translate(0, -0.25, 0.19) * RotateZ(x) * Scale(0.22, 0.01, 0.08);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_banh * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void banhxee2() {
	for (int i = 1; i <= 180; i++) {
		duongtron2(i);
	}
}
void duongtron3(GLfloat x) {
	mat4 instance = Translate(-0.4, -0.25, -0.19) * RotateZ(x) * Scale(0.22, 0.01, 0.08);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_banh * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void banhxee3() {
	for (int i = 1; i <= 180; i++) {
		duongtron3(i);
	}
}
void duongtron4(GLfloat x) {
	mat4 instance = Translate(-0.4, -0.25, 0.19) * RotateZ(x) * Scale(0.22, 0.01, 0.08);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_banh * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void banhxee4() {
	for (int i = 1; i <= 180; i++) {
		duongtron4(i);
	}
}
void duongtron5(GLfloat x) {
	mat4 instance = Translate(0.4, -0.25, -0.19) * RotateZ(x) * Scale(0.22, 0.01, 0.08);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_banh * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void banhxee5() {
	for (int i = 1; i <= 180; i++) {
		duongtron5(i);
	}
}
void duongtron6(GLfloat x) {
	mat4 instance = Translate(0.4, -0.25, 0.19) * RotateZ(x) * Scale(0.22, 0.01, 0.08);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_xe_phao * model_banh * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void banhxee6() {
	for (int i = 1; i <= 180; i++) {
		duongtron6(i);
	}
}
void nong()
{
	thannong1();
	model_nong1 = Translate(0, 0.18, 0) * RotateZ(theta[5]) * Translate(0, -0.18, 0);
	nongtron1();
	vec4 e = vec4(0.0, 0.0, 0.0, 0.9);
	setMau(e);
	nong1();
	nong2();
	nong3();
	vec4 a = vec4(0.1, 0.2, 0.1, 0.8);
	setMau(a);
	nongtron2();
	nongtron3();
	nongtron4();
	nongtron5();
	nongquay();
}

void banhxe()
{
	banhxee1();
	banhxee2();
	banhxee3();
	banhxee4();
	banhxee5();
	banhxee6();
}
void ditxe()
{
	ditxe1();
	ditxe2();
	ditxe3();
}
void dauxe()
{
	dauxe1();
	dauxe2();
	dauxe3();
}

void thanxe()
{
	than();
	tamchanthan();
	dauxe();
	day();
	vec4 e = vec4(0.0, 0.0, 0.0, 0.9);
	setMau(e);
	vanhngang();
	vanhdoc();
	ditxe();
}
void xephao_MNghia()
{
	vec4 b = vec4(0.1, 0.6, 0.1, 0.8);
	setMau(b);
	thanxe();
	vec4 d = vec4(0.1, 0.4, 0.1, 0.8);
	setMau(d);
	model_nong = RotateY(theta[4]);
	nong();
	vec4 c = vec4(0.1, 0.1, 0.1, 0.8);
	setMau(c);
	banhxe();
}
//Viet dep trai
mat4 instance;
mat4 model_maybay, model_canhQuatMayBay, model_boom;
bool rotateFan = false;
bool boom = false;
bool bay = false;
bool danVV = false;
float thetaV[20];
void thanMayBay() {
	vec4 a = vec4(0.2, 0.4, 0.0, 1.0);
	setMau(a);
	instance = Translate(0.5, 0, 0) * Scale(0.1, 0.25, 0.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(0.575, 0, 0) * Scale(0.05, 0.2, 0.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(0.15, 0, 0) * Scale(0.6, 0.2, 0.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.21, 0.025, 0) * Scale(0.12, 0.15, 0.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.36, 0.05, 0) * Scale(0.18, 0.1, 0.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void canhMayBay() {
	vec4 a = vec4(0.5, 0.4, 0.2, 1.0);
	setMau(a);
	instance = Translate(0.0 + 0.2, 0.0, 0.215) * Scale(0.2, 0.05, 0.6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.05 + 0.2, 0.0, 0.25) * RotateY(10) * Scale(0.2, 0.05, 0.5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(0.0 + 0.2, 0.0, -0.215) * Scale(0.2, 0.05, 0.6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.05 + 0.2, 0.0, -0.25) * RotateY(-10) * Scale(0.2, 0.05, 0.5);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void duoiMayBay() {
	vec4 a = vec4(0.2, 0.4, 0.0, 1.0);
	setMau(a);
	instance = Translate(-0.395, 0.05, -0.11) * Scale(0.1, 0.03, 0.3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.37, 0.05, -0.12) * RotateY(10) * Scale(0.1, 0.03, 0.25);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.395, 0.05, 0.11) * Scale(0.1, 0.03, 0.3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay* instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.37, 0.05, 0.12) * RotateY(-10) * Scale(0.1, 0.03, 0.25);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay* instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	instance = Translate(-0.41, 0.105, 0) * Scale(0.07, 0.15, 0.03);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model* model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.34, 0.10, 0) * RotateZ(60) * Scale(0.1, 0.15, 0.03);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay* instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void canhQuatMayBay() {
	vec4 a = vec4(0.8, 0.4, 0.0, 1.0);
	setMau(a);
	instance = Translate(0.62, 0, 0) * Scale(0.05, 0.05, 0.05);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay* instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	instance = Translate(0.625, 0.08, 0) * Scale(0.02, 0.15, 0.02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay* model_canhQuatMayBay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(0.625, -0.08, 0) * Scale(0.02, 0.15, 0.02);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay* model_canhQuatMayBay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void choNgoiMayBay() {
	vec4 a = vec4(0.2, 0.4, 0.0, 1.0);
	setMau(a);
	instance = Translate(0.1, 0.1, 0.04) * RotateZ(45) * Scale(0.1, 0.1, 0.01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay* instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(0.1, 0.1, -0.04) * RotateZ(45) * Scale(0.1, 0.1, 0.01);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay* instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(0.135, 0.135, 0) * RotateZ(45) * Scale(0.01, 0.1, 0.08);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay* instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(0.07, 0.135, 0) * RotateZ(-45) * Scale(0.01, 0.1, 0.08);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void bom() {
	instance = Scale(0.15, 0.15, 0.15);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_maybay*  model_boom * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void maybay() {


	model_maybay = RotateX(thetaV[0]) * RotateY(thetaV[1]) * Translate(thetaV[3], thetaV[4], 0);
	thanMayBay();
	canhMayBay();
	duoiMayBay();
	choNgoiMayBay();
	model_canhQuatMayBay = RotateX(thetaV[2]);
	canhQuatMayBay();
	model_boom = Translate(0, thetaV[5], 0);
	bom();
}
void idleViet()
{
	if (rotateFan) {
		thetaV[2] -= 50;
		
	}
	if (bay) {
		thetaV[4] += 0.01;
		if (thetaV[4] >0.6) {
			thetaV[4] += 0.0; // Reset to original position
			bay = false;  // Stop the boom movement
		}
	}

	if (boom) {
		thetaV[5] -= 0.1;
		if (thetaV[5] < -1.2) {
			thetaV[5] = 0.0; // Reset to original position
			boom = false;  // Stop the boom movement
		}
	}
	if (danVV) {
		thetaV[8] -= 0.1;
		if (thetaV[8] < -1.2) {
			thetaV[8] = 0.0; // Reset to original position
			danVV = false;  // Stop the boom movement
		}
	}
	glutPostRedisplay();
	glutPostRedisplay();
}

mat4 model_danV;
mat4 model_xeV, model_phao;
void thanXe() {


	vec4 a = vec4(0.2, 0.4, 0, 1);
	setMau(a);
	instance = Scale(1, 0.1, 0.4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(0, 0.15, 0) * Scale(0.1, 0.1, 0.1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);
	instance = Translate(0, 0.25, 0) * Scale(0.1, 0.05, 0.1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);



}
void banhXe() {
	vec4 a = vec4(0, 0, 0, 0);
	setMau(a);
	instance = Translate(-0.3, -0.075, 0.15) * RotateZ(90) * RotateX(90) * Scale(0.1, 0.025, 0.1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);
	instance = Translate(-0.3, -0.075, -0.15) * RotateZ(90) * RotateX(90) * Scale(0.1, 0.025, 0.1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);
	instance = Translate(0.3, -0.075, 0.15) * RotateZ(90) * RotateX(90) * Scale(0.1, 0.025, 0.1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);
	instance = Translate(0.3, -0.075, -0.15) * RotateZ(90) * RotateX(90) * Scale(0.1, 0.025, 0.1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);



}
void phao() {
	vec4 a = vec4(0.2, 0.4, 0, 1);
	setMau(a);
	instance = Translate(-0.05, 0.3, 0) * RotateX(90) * Scale(0.025, 0.1, 0.025);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * model_phao * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);
	instance = Translate(-0.05, 0.3, 0.05) * RotateZ(-60) * Scale(0.45, 0.025, 0.025);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * model_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.05, 0.3, -0.05) * RotateZ(-60) * Scale(0.45, 0.025, 0.025);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * model_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.175, 0.5, 0) * RotateZ(-60) * Scale(0.025, 0.025, 0.2);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * model_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);


	instance = Translate(-0.25, 0.325, 0) * RotateZ(-60) * Scale(0.2, 0.025, 0.1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * model_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.13, 0.45, 0) * RotateZ(-60) * Scale(0.05, 0.15, 0.05);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * model_phao * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);
	instance = Translate(-0.05, 0.4, 0) * RotateZ(-60) * Scale(0.05, 0.2, 0.05);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * model_phao * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);
	instance = Translate(0.3, 0.6, 0) * RotateZ(-60) * Scale(0.025, 0.2, 0.025);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * model_phao * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);


	instance = Translate(-0.25, 0.325, 0) * RotateX(90) * Scale(0.025, 0.2, 0.025);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * model_phao * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);
	vec4 b = vec4(0, 0, 0, 0);
	setMau(b);
	instance = Translate(0.5, 0.715, 0) * RotateZ(-60) * RotateY(45) * Scale(0.05, 0.1, 0.05);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * model_phao * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void nguoiV() {
	vec4 a = vec4(0.6, 0.4, 0.2, 1.0);
	setMau(a);

	instance = Translate(-0.36, 0.125, 0.04) * RotateZ(10) * Scale(0.05, 0.15, 0.05);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.37, 0.125, -0.04) * Scale(0.05, 0.15, 0.05);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.37, 0.225, 0) * Scale(0.05, 0.15, 0.125);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.32, 0.275, 0.08) * RotateZ(130) * Scale(0.05, 0.15, 0.05);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.32, 0.275, -0.08) * RotateZ(130) * Scale(0.05, 0.15, 0.05);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	instance = Translate(-0.37, 0.335, 0) * Scale(0.035, 0.035, 0.035);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV * instance);
	glDrawArrays(GL_TRIANGLES, NumPoints, soDinhHinhTru);
}

void danV() {
	vec4 b = vec4(0, 0, 0, 0);
	setMau(b);
	instance = Scale(0.035, 0.035, 0.035);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * model_xeV* model_phao * model_danV * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void xeV() {
	model_xeV = Translate(thetaV[9], 0.2, 0);
	thanXe();
	nguoiV();
	banhXe();
	
	phao();
	model_danV = Translate(0.525, 0.725, 0) * RotateZ(30) * Translate(-thetaV[8], 0, 0);
	danV();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	view_projection();
	//nen();
	//comment
	xyz();
	mat4 temp_model = RotateY(quayAllY);
	model = temp_model * Translate(-1.9, 0, -0.5)*RotateY(55) * Scale(1.1, 1.1, 1.1);
	XeTang();
	model = temp_model * RotateY(55) * Translate(1, 0, -1);
	XeTenLuaSieuVip();
	model = temp_model * Translate(0, 0, -5) * Scale(0.3, 0.3, 0.3);
	RoBot_Nghia();
	sanNha();
	model_xe_phao = Translate(1.3, 0.47, 0) * RotateX(theta[0]) * RotateY(theta[1] - 105) * RotateZ(theta[2]) * Translate(theta[3], 0, 0) * Scale(1.3, 1.3, 1.3);
	xephao_MNghia();
	model = Translate(0, 3, 0)*  RotateY(18 * 5)   *Scale(2, 2, 2);
	maybay();
	model = temp_model * Translate(2.2, 0, 0) * Scale(0.7, 0.7, 0.7);
	xeV();
	glutSwapBuffers();
}
void Idle_Nghia() {
	if (shootRobot == true) {
		xxSungRobot -= 0.003;
		heSo += 0.2f;
		danBanSung_robot += 0.3f;
		quayAllY1 += 5;
		if (danBanSung_robot >= 5) {
			danBanSung_robot = 0;
			xxSungRobot = 0;
			quayAllY1 = 0;
			shootRobot = false;
		}
	}
	else {
		// Kiểm tra thời gian kể từ lần bắn cuối cùng
		clock_t currentTime = clock();
		double elapsedTime = static_cast<double>(currentTime - lastShootTime) / CLOCKS_PER_SEC;

		// Nếu đã ngừng bắn 2 giây, giảm hệ số về 1
		if (elapsedTime >= 2.0 && heSo > 1.0f) {
			heSo -= 0.02f;
		}

	}
	if (shootXeTang_N == true) {
		danBanXeTang_Nghia += 0.4f;
		if (danBanXeTang_Nghia >= 6) {
			danBanXeTang_Nghia = 0;
			shootXeTang_N = false;
		}
	}
	if (shoot_tenLua1 == true) {
		danBantenLua1 += 0.5f;
		if (danBantenLua1 >= 9) {
			danBantenLua1 = 0;
			shoot_tenLua1 = false;
		}
	}
	if (shoot_tenLua2 == true) {
		danBantenLua2 += 0.5f;
		if (danBantenLua2 >= 9) {
			danBantenLua2 = 0;
			shoot_tenLua2 = false;
		}
	}
	//if (check_sung == false) {
	//	model_SungsRobot = model_trungGian_robot2;
	//}
	//else
	//{
	//	model_SungsRobot = model_trungGian_robot1;
	//}
	glutPostRedisplay();
}
bool isKeyPressed(int key) {
	return GetAsyncKeyState(key) & 0x8000;
}
//
//LPCTSTR soundFilePath = TEXT("C:\\Users\\HP\\Downloads\\sung2.wav");

float k = 5;
float k2 = 1.5;
//
void keyboard(unsigned char key, int x, int y)
{

	if (PhamTrongNghia_control == true) {
		switch (key) {
		case '1':
			shootXeTang_N = true;
			glutPostRedisplay();
			break;
		case '2':
			shoot_tenLua1 = true;
			glutPostRedisplay();
			break;
		case '3':
			shoot_tenLua2 = true;
			glutPostRedisplay();
			break;
		case 'j':
			ThetaXeTenLua[0] += 5;
			glutPostRedisplay();
			break;
		case 'k':
			xXeTenLua += 0.02;
			quayBanhXeTenLua -= 5;
			glutPostRedisplay();
			break;
		case 'K':
			xXeTenLua -= 0.02;
			quayBanhXeTenLua += 5;
			glutPostRedisplay();
			break;
		case 'l':
			ThetaXeTenLua[1] += 5;
			glutPostRedisplay();
			break;
		case ';':
			ThetaXeTenLua[2] += 5;
			if (ThetaXeTenLua[2] >= 60)
				ThetaXeTenLua[2] = 60;
			glutPostRedisplay();
			break;
			//Robot
		case 'b':
			xxRoBot += 0.05f;
			xnChanRobot1 += k;
			xnChanRobot2 -= k;
			xnTayTrenRobot1 += k2;
			xnTayTrenRobot2 += k2;// Tăng góc xoay
			if (xnChanRobot1 > 45.0f || xnChanRobot1 < -45.0f) {
				k = -k; // Đảo ngược hướng nếu đạt đến giới hạn
				k2 = -k2;
			}

			glutPostRedisplay();
			break;
		case 'B':
			xxRoBot -= 0.05f;
			xnChanRobot1 += k;
			xnChanRobot2 -= k;
			xnTayTrenRobot1 += k2;
			xnTayTrenRobot2 += k2;// Tăng góc xoay
			if (xnChanRobot1 > 45.0f || xnChanRobot1 < -45.0f) {
				k = -k; // Đảo ngược hướng nếu đạt đến giới hạn
				k2 = -k2;
			}

			glutPostRedisplay();
			break;
		case 'n':
			xnTayTrenRobot1 -= 5;
			glutPostRedisplay();
			if (xnTayTrenRobot1 <= -150)
				xnTayTrenRobot1 = -150;
			break;
		case 'N':
			xnTayTrenRobot1 += 5;
			glutPostRedisplay();
			/*if (xnTayTrenRobot <= -150)
				xnTayTrenRobot = -150;*/
			break;
		case 'm':  xnTayDuoiRobot1 += 5;
			if (xnTayDuoiRobot1 >= 16 * 5)
				xnTayDuoiRobot1 = 16 * 5;
			glutPostRedisplay();
			break;
		case 'M':  xnTayDuoiRobot1 -= 5;
			if (xnTayDuoiRobot1 <= -5 * 14)
				xnTayDuoiRobot1 = -5 * 14;
			glutPostRedisplay();
			break;
		case ',': ynAK -= 5;
			glutPostRedisplay();
			break;
		case '<': ynAK += 5;
			glutPostRedisplay();
			break;
		case 'o': quayDauRobot -= 5;
			glutPostRedisplay();
			break;
		case 'O': quayDauRobot -= 5;
			glutPostRedisplay();
			break;
			/*case 'i': xnChanRobot1 += 5;
				glutPostRedisplay();
				break;
			case 'I': xnChanRobot1 -= 5;
				if (xnChanRobot1 <= -90)
					xnChanRobot1 = -90;
				glutPostRedisplay();
				break;*/
		case '/':
			xnTayDuoiRobot2 += 5;
			if (xnTayDuoiRobot2 >= 16 * 5)
				xnTayDuoiRobot2 = 16 * 5;
			glutPostRedisplay();
			break;
		case '?':  xnTayDuoiRobot2 -= 5;
			if (xnTayDuoiRobot2 <= -5 * 14)
				xnTayDuoiRobot2 = -5 * 14;
			glutPostRedisplay();
			break;
		case '.':
			xnTayTrenRobot2 -= 5;
			glutPostRedisplay();
			if (xnTayTrenRobot2 <= -150)
				xnTayTrenRobot2 = -150;
			break;
		case '>':
			xnTayTrenRobot2 += 5;
			glutPostRedisplay();
			/*if (xnTayTrenRobot <= -150)
				xnTayTrenRobot = -150;*/
			break;
		case 'i': ynRobot += 5;
			xnChanRobot1 += k;
			xnChanRobot2 -= k;
			xnTayTrenRobot1 += k2;// Tăng góc xoay
			if (xnChanRobot1 > 45.0f || xnChanRobot1 < -45.0f) {
				k = -k; // Đảo ngược hướng nếu đạt đến giới hạn
				k2 = -k2;
			}
			glutPostRedisplay();
			break;
			//robot<-
		case ' ':
			xnChanRobot1 = 0;
			xnChanRobot2 = 0;
			glutPostRedisplay();
			break;
			//XeTang
		case 'z':
			quayBangXeTang -= 5;
			diChuyenXeTang += 0.01f;
			glutPostRedisplay();
			break;
		case 'Z':
			quayBangXeTang += 5;
			diChuyenXeTang -= 0.01f;
			glutPostRedisplay();
			break;
		case'x': quayKhungSung += 5;
			glutPostRedisplay();
			break;
		case'X':
			quayKhungSung -= 5;
			glutPostRedisplay();
			break;
		case'c': quayNongSung += 5;
			if (quayNongSung >= 45) quayNongSung = 45;
			glutPostRedisplay();
			break;
		case'C': quayNongSung -= 5;
			if (quayNongSung <= 0) quayNongSung = 0;
			glutPostRedisplay();
			break;
		case 'v':
			ynXeTang += 5;
			glutPostRedisplay();
			break;
			//Xetang
		case 'p':
			shootRobot = true;
			//PlaySound(soundFilePath, NULL, SND_ASYNC);
			//glutPostRedisplay();
			break;

		case'T':
			check_sung = !check_sung;

			glutPostRedisplay();
			break;

		}
	}
	if (NguyenThiBichNgoc_control == true) {
		switch (key) {

		}
	}
	if (HoangMinhNghia_control == true) {
		switch (key) {
		case 'X':
			theta[0] += 5;
			glutPostRedisplay();
			break;
		case 'Y':
			theta[1] += 5;
			glutPostRedisplay();
			break;
		case 'Z':
			theta[2] += 5;
			glutPostRedisplay();
			break;
		case 'T':
			theta[3] -= 0.01f;
			glutPostRedisplay();
			break;
		case 'L':
			theta[3] += 0.01f;
			glutPostRedisplay();
			break;
		case 'A':
			theta[4] += 5;
			glutPostRedisplay();
			break;
		case 'D':
			theta[4] -= 5;
			glutPostRedisplay();
			break;
		case 'W':
			if (theta[5] > -25)
				theta[5] -= 1;
			glutPostRedisplay();
			break;
		case 'S':
			if (theta[5] < 5)
				theta[5] += 1;
			glutPostRedisplay();
			break;
		case 'B':
			theta[6] += 5;
			glutPostRedisplay();
			break;
			break;
		}
	}
	if (NguyenHoangViet_control == true) {
		switch (key) {
			
		case 'c':
			thetaV[0] += 5;
			break;
		case 'v':
			thetaV[1] += 5;
			break;
		case 'j':
			
			thetaV[3] -= 0.01;
			break;
		case 'l':
			
			thetaV[3] += 0.01;
			break;
		case 'i':
			
			thetaV[4] += 0.01;
			break;
		case 'k':
			
			thetaV[4] -= 0.01;
			break;
		case 'p':
			rotateFan = !rotateFan;
			bay = true;
			break;
		case 'b':
			boom = true;
			break;
		case 'm':

			thetaV[9] += 0.01;
			break;
		case 'n':
			thetaV[9] -= 0.01;
			break;
		case 'u':
			danVV = true;
			break;
		}
		glutPostRedisplay();
	}
	if (NguyenThiLinhNgan_control == true) {
		switch (key) {

		}
	}
	if (PhamTrongNghia_control == false || NguyenThiBichNgoc_control == false || HoangMinhNghia_control == false || NguyenThiLinhNgan_control == false || NguyenHoangViet_control == false) {
		switch (key) {
			{
		case '!': PhamTrongNghia_control = true; NguyenThiBichNgoc_control = false; HoangMinhNghia_control = false; NguyenThiLinhNgan_control = false; NguyenHoangViet_control = false;
			break;
		case '@': PhamTrongNghia_control = false; NguyenThiBichNgoc_control = true; HoangMinhNghia_control = false; NguyenThiLinhNgan_control = false; NguyenHoangViet_control = false;
			break;
		case '#': PhamTrongNghia_control = false; NguyenThiBichNgoc_control = false; HoangMinhNghia_control = true; NguyenThiLinhNgan_control = false; NguyenHoangViet_control = false;
			break;
		case '$': PhamTrongNghia_control = false; NguyenThiBichNgoc_control = false; HoangMinhNghia_control = false; NguyenThiLinhNgan_control = false; NguyenHoangViet_control = true;
			break;
		case '%': PhamTrongNghia_control = false; NguyenThiBichNgoc_control = false; HoangMinhNghia_control = false; NguyenThiLinhNgan_control = true; NguyenHoangViet_control = false;
			break;
		case 'w': zNear *= 1.1; zFar *= 1.1; glutPostRedisplay(); break;
		case 's': zNear *= 0.9; zFar *= 1.6; glutPostRedisplay(); break;
		case 'f':
			gocQuayNgangCam += 0.1;
			glutPostRedisplay();
			break;
		case 'h':
			gocQuayNgangCam -= 0.1;
			glutPostRedisplay();
			break;
		case 't':
			gocQuayDocCam += 0.01;
			break;
		case 'g':
			gocQuayDocCam -= 0.01;
			break;
		case 'a':
			xEye += 0.1;
			break;
		case 'd':
			xEye -= 0.1;
			glutPostRedisplay();
			break;
		case 033:			// 033 is Escape key octal value
			exit(1);		// quit program
			break;
			}


		}
	}
}

void idle() {
	Idle_Nghia();
	idleViet();
 }

int main(int argc, char** argv)
{
	// main function: program starts here

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Drawing a Cube");


	glewInit();

	generateGeometry();
	initGPUBuffers();
	shaderSetup();
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	//glutReshapeFunc(reshape);
	
	
	glutMainLoop();
	return 0;
}


