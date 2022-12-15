#include "Matrix3x3.h"
#include <Novice.h>

Matrix3x3::Matrix3x3() {
	for (int y = 0; y < column; y++)
	{
		for (int x = 0; x < row; x++)
		{
			this->m[y][x] = 0.0f;
		}
	}
}

//	êœ
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mat) const {
	Matrix3x3 result;
	//	
	for (int y = 0; y < column; y++)
	{
		for (int x = 0; x < row; x++)
		{
			for (int i = 0; i < column; i++)
			{
				result.m[y][x] += this->m[y][i] * mat.m[i][x];
			}
		}
	}

	return result;
}

//	ë„ì¸
const Matrix3x3& Matrix3x3::operator=(const Matrix3x3& mat) {
	for (int y = 0; y < column; y++)
	{
		for (int x = 0; x < row; x++)
		{
			this->m[y][x] = mat.m[y][x];
		}
	}
	return *this;
}

//	ë„ì¸ä|ÇØéZ
const Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& mat) {
	*this = *this * mat;
	return *this;
}

Matrix3x3 Matrix3x3::MakeOrthographicMatrix(Vec2 lefttop, Vec2 rightbottom) {
	this->m[0][0] = 2.0f / (rightbottom.x - lefttop.x);
	this->m[1][1] = 2.0f / (lefttop.y - rightbottom.y);
	this->m[2][0] = (lefttop.x + rightbottom.x) / (lefttop.x - rightbottom.x);
	this->m[2][1] = (lefttop.y + rightbottom.y) / (rightbottom.y - lefttop.y);
	this->m[2][2] = 1.0f;
	
	return *this;
}


Matrix3x3 Matrix3x3::MakeViewportMatrix(Vec2 lefttop, float width, float height) {
	this->m[0][0] = width / 2.0f;
	this->m[1][1] = -(height / 2.0f);
	this->m[2][0] = lefttop.x + (width / 2.0f);
	this->m[2][1] = lefttop.y + (height / 2.0f);
	this->m[2][2] = 1.0f;

	return *this;
}


Matrix3x3 Matrix3x3::Inverse(Matrix3x3 matrix) {
	float num;
	num = 1 / ((matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2])
		+ (matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0])
		+ (matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1])
		- (matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0])
		- (matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2])
		- (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]));

	this->m[0][0] = num * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	this->m[0][1] = num * (-(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]));
	this->m[0][2] = num * (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);
	
	this->m[1][0] = num * (-(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]));
	this->m[1][1] = num * (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	this->m[1][2] = num * (-(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]));
	
	this->m[2][0] = num * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	this->m[2][1] = num * (-(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]));
	this->m[2][2] = num * (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	return *this;
}


/*	
Vec2 operator*(Vec2 vector, Matrix3x3 matrix) {
	Vec2 result = {0.0f,0.0f};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	result.x /= w;
	result.y /= w;
	return result;
}
*/

Matrix3x3 Matrix3x3::MakeTranslateMatrix(Vec2 translate) {
	//	ë„ì¸
	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;

	this->m[2][0] = translate.x;
	this->m[2][1] = translate.y;
	return *this;
}

Vec2 Transform(Vec2 vector, Matrix3x3 matrix) {
	Vec2 result = { 0.0f,0.0f };
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	result.x /= w;
	result.y /= w;
	return result;
}

