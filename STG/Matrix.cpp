#include "Matrix.h"

#include <Novice.h>
#include <math.h>
#include <assert.h>

Matrix::Matrix() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cameraMatrix.m[j][i] = 0.0f;
			viewMatrix.m[j][i] = 0.0f;
			orthoMatrix.m[j][i] = 0.0f;
			viewPortMatrix.m[j][i] = 0.0f;
			vpVpMatrix.m[j][i] = 0.0f;
		}
	}
}

Matrix3x3 Matrix::Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result = {};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return result;
}

Matrix3x3 Matrix::Inverse(Matrix3x3 matrix) {
	Matrix3x3 result = matrix;
	float determinant;
	determinant = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -

		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];
	if (determinant == 0) {
		return result;
	}
	float num = 1.0f / determinant;
	result.m[0][0] = num * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	result.m[0][1] = num * -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	result.m[0][2] = num * (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);

	result.m[1][0] = num * -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	result.m[1][1] = num * (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	result.m[1][2] = num * -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);

	result.m[2][0] = num * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	result.m[2][1] = num * -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	result.m[2][2] = num * (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);
	return result;
}

Matrix3x3 Matrix::MakeTranslateMatrix(Vector2 translate) {
	Matrix3x3 translateMatrix = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			translate.x, translate.y, 1.0f
	};
	return translateMatrix;
}

Matrix3x3 Matrix::MakeRotateMatrix(float theta) {
	Matrix3x3 rotateMatrix = {
		cosf(theta), sinf(theta), 0,
		-sinf(theta), cosf(theta), 0,
		0, 0, 1
	};
	return rotateMatrix;
}

Matrix3x3 Matrix::MakeScaleMatrix(Vector2 scale) {
	Matrix3x3 scaleMatrix = {
		scale.x, 0, 0,
		0, scale.y, 0,
		0, 0, 1
	};
	return scaleMatrix;
}

Matrix3x3 Matrix::MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	//Matrix3x3　に交換
	Matrix3x3 scaleMatrix = MakeScaleMatrix(scale);
	Matrix3x3 rotateMatrix = MakeRotateMatrix(rotate);
	Matrix3x3 translateMatrix = MakeTranslateMatrix(translate);

	//全部かける
	Matrix3x3 resultMatrix = Multiply(Multiply(scaleMatrix, rotateMatrix), translateMatrix);

	return resultMatrix;
}

Matrix3x3 Matrix::MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 result = {};
	result.m[0][0] = 2.0f / (right - left);				result.m[0][1] = 0.0f;								result.m[0][2] = 0.0f;
	result.m[1][0] = 0.0f;								result.m[1][1] = 2.0f / (top - bottom);				result.m[1][2] = 0.0f;
	result.m[2][0] = (left + right) / (left - right);	result.m[2][1] = (top + bottom) / (bottom - top);	result.m[2][2] = 1.0f;
	return result;
}

Matrix3x3 Matrix::MakeViewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 result = {};
	result.m[0][0] = width / 2.0f; result.m[0][1] = 0.0f; result.m[0][2] = 0.0f;
	result.m[1][0] = 0.0f; result.m[1][1] = -height / 2.0f; result.m[1][2] = 0.0f;
	result.m[2][0] = left + (width / 2.0f); result.m[2][1] = top + (height / 2.0f); result.m[2][2] = 1.0f;

	return result;
}

Vector2 Matrix::Transform(Vector2 vector) {
	Vector2 result;
	result.x = vector.x * vpVpMatrix.m[0][0] + vector.y * vpVpMatrix.m[1][0] + 1.0f * vpVpMatrix.m[2][0];
	result.y = vector.x * vpVpMatrix.m[0][1] + vector.y * vpVpMatrix.m[1][1] + 1.0f * vpVpMatrix.m[2][1];
	float w = vector.x * vpVpMatrix.m[0][2] + vector.y * vpVpMatrix.m[1][2] + 1.0f * vpVpMatrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

void Matrix::CalculateMatrix(Camera cam) {
	cameraMatrix = MakeAffineMatrix(cam.GetCameraScale(), cam.GetCameraRotation(), cam.GetCameraTranslate());
	viewMatrix = Inverse(cameraMatrix);
	orthoMatrix = MakeOrthographicMatrix(-640.0f, 360.0f, 640.0f, -360.0f);
	viewPortMatrix = MakeViewportMatrix(0.0f, 0.0f, 1280.0f, 720.0f);
	vpVpMatrix = Multiply(viewMatrix, orthoMatrix);
	vpVpMatrix = Matrix::Multiply(vpVpMatrix, viewPortMatrix);
}

