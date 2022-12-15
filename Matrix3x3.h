#pragma once

struct Vec2
{
	float x, y;
};

class Matrix3x3
{
public:
	//	�R���X�g���N�^
	Matrix3x3();

private:
	static const int row = 3;
	static const int column = 3;

public:
	float m[column][row];
	
	//	��
	Matrix3x3 operator*(const Matrix3x3& mat) const;
	//	���
	const Matrix3x3& operator=(const Matrix3x3& mat);
	//	����|���Z
	const Matrix3x3& operator*=(const Matrix3x3& mat);

	//	���ˉe�s��
	Matrix3x3 MakeOrthographicMatrix(Vec2 lefttop, Vec2 rightbottom);
	//	�r���[�|�[�g�s��
	Matrix3x3 MakeViewportMatrix(Vec2 lefttop, float width, float height);
	//	�t
	Matrix3x3 Inverse(Matrix3x3 matrix);
	//	�񎟌��x�N�g���𓯎����W�Ƃ��ĕϊ�����
	//	friend Vec2 operator*(Vec2 vector, Matrix3x3 matrix);
	
	//	���s�ړ��s��̍쐬�֐�
	Matrix3x3 MakeTranslateMatrix(Vec2 translate);
};

//	�񎟌��x�N�g���𓯎����W�Ƃ��ĕϊ�����
Vec2 Transform(Vec2 vector, Matrix3x3 matrix);
