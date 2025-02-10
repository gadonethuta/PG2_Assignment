#pragma once
#include "Matrix3x3.h"
#include "Vector2.h"

#include "Camera.h"

class Matrix {
private:
	static Matrix* instance;
	
	Matrix3x3 cameraMatrix;
	Matrix3x3 viewMatrix;
	Matrix3x3 orthoMatrix;
	Matrix3x3 viewPortMatrix;
	Matrix3x3 vpVpMatrix;

	Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
	Matrix3x3 Inverse(Matrix3x3 matrix);
	Matrix3x3 MakeTranslateMatrix(Vector2 translate);
	Matrix3x3 MakeRotateMatrix(float theta);
	Matrix3x3 MakeScaleMatrix(Vector2 scale);
	Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);
	Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);
	Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

	Matrix();
public:
	static Matrix* GetInstance() {
		if (instance == nullptr) {
			instance = new Matrix();
		}
		return instance;
	}

	/// <summary>
	/// レンダリングパイプラインに入れる
	/// </summary>
	/// <param name="vector">入れたいベクター（カメラと反応しない）</param>
	/// <returns>入れたベクター（カメラと反応する）</returns>
	Vector2 Transform(Vector2 vector);
	/// <summary>
	/// 行列を計算する関数
	/// </summary>
	/// <param name="camera">カメラのインスタンス</param>
	void CalculateMatrix(Camera cam);
	//void CalculateMatrix(Vector2 cameraScale, float cameraRotation, Vector2 cameraPosition);

	//コピーを防ぐためにコピーコンストラクタと代入演算子を削除する
	Matrix(const Matrix&) = delete;
	Matrix& operator=(const Matrix&) = delete;
};

