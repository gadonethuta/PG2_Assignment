#define _USE_MATH_DEFINES
#include "Camera.h"
#include "Basics.h"

#include <Novice.h>
#include <math.h>

Camera::Camera() {
	scale_ = { 1.0f, 1.0f };
	rotation_ = 0.0f;
	translate_ = { 640.0f, 360.0f };

	moveDir_ = { 0.0f, 0.0f };

	scaleSpeed_ = 0.025f;
	rotationSpeed_ = static_cast<float>(M_PI) / 180.0f;
	translateSpeed_ = 5.0f;

	resetTimer_ = 120;
}

Camera::Camera(Vector2 cameraScale, float cameraRotation, Vector2 cameraTranslate) {
	scale_ = cameraScale;
	rotation_ = cameraRotation;
	translate_ = cameraTranslate;

	moveDir_ = { 0.0f, 0.0f };

	scaleSpeed_ = 0.025f;
	rotationSpeed_ = static_cast<float>(M_PI) / 180.0f;
	translateSpeed_ = 5.0f;

	resetTimer_ = 120;
}

void Camera::CameraControls(char* pK, char* k) {
	if (k[DIK_R] && !pK[DIK_R]) {
		scale_ = { 1.0f, 1.0f };
		rotation_ = 0.0f;
		translate_ = { 640.0f, 360.0f };
	}
	resetTimer_--;
	moveDir_ = { 0.0f, 0.0f };
	if (k[DIK_W]) {
		resetTimer_ = 120;
		moveDir_.y = 1.0f;
	} else if (k[DIK_S]) {
		moveDir_.y = -1.0f;
		resetTimer_ = 120;
	}
	if (k[DIK_D]) {
		moveDir_.x = 1.0f;
		resetTimer_ = 120;
	} else if (k[DIK_A]) {
		moveDir_.x = -1.0f;
		resetTimer_ = 120;
	}
	moveDir_ = Basics::Normalize(moveDir_);
	translate_.x += moveDir_.x * translateSpeed_;
	translate_.y += moveDir_.y * translateSpeed_;


	if (k[DIK_Q]) {
		resetTimer_ = 120;
		rotation_ -= sinf(rotationSpeed_);
	} else if (k[DIK_E]) {
		rotation_ += sinf(rotationSpeed_);
		resetTimer_ = 120;
	}

	if (k[DIK_Z]) {
		scale_.x -= scaleSpeed_;
		scale_.y -= scaleSpeed_;
		resetTimer_ = 120;
	} else if (k[DIK_C]) {
		scale_.x += scaleSpeed_;
		scale_.y += scaleSpeed_;
		resetTimer_ = 120;
	}


	//何も押していないならカメラをリミットする
	if (resetTimer_ <= 0) {
		translate_.x = Basics::Lerp(translate_.x, 640.0f, 0.3f);
		translate_.y = Basics::Lerp(translate_.y, 360.0f, 0.3f);
		rotation_ = Basics::Lerp(rotation_, 0.0f, 0.3f);
		scale_.x = Basics::Lerp(scale_.x, 1.0f, 0.3f);
		scale_.y = Basics::Lerp(scale_.y, 1.0f, 0.3f);

	}
}

Vector2 Camera::GetCameraScale() {
	return scale_;
}

float Camera::GetCameraRotation() {
	return rotation_;
}

Vector2 Camera::GetCameraTranslate() {
	return translate_;
}
