#pragma once

struct Vec2
{
	float x, y;
};

class Matrix3x3
{
public:
	//	コンストラクタ
	Matrix3x3();

private:
	static const int row = 3;
	static const int column = 3;

public:
	float m[column][row];
	
	//	積
	Matrix3x3 operator*(const Matrix3x3& mat) const;
	//	代入
	const Matrix3x3& operator=(const Matrix3x3& mat);
	//	代入掛け算
	const Matrix3x3& operator*=(const Matrix3x3& mat);

	//	正射影行列
	Matrix3x3 MakeOrthographicMatrix(Vec2 lefttop, Vec2 rightbottom);
	//	ビューポート行列
	Matrix3x3 MakeViewportMatrix(Vec2 lefttop, float width, float height);
	//	逆
	Matrix3x3 Inverse(Matrix3x3 matrix);
	//	二次元ベクトルを同次座標として変換する
	//	friend Vec2 operator*(Vec2 vector, Matrix3x3 matrix);
	
	//	平行移動行列の作成関数
	Matrix3x3 MakeTranslateMatrix(Vec2 translate);
};

//	二次元ベクトルを同次座標として変換する
Vec2 Transform(Vec2 vector, Matrix3x3 matrix);
