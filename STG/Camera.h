#pragma once
#include "Vector2.h"

class Camera {
private:
	Vector2 scale_;
	float rotation_;
	Vector2 translate_;

	Vector2 moveDir_;

	float scaleSpeed_;
	float rotationSpeed_;
	float translateSpeed_;

	int resetTimer_;

public:
	Camera();
	Camera(Vector2 cameraScale, float cameraRotation, Vector2 cameraTranslate);
	void CameraControls(char* pK, char* k);

	Vector2 GetCameraScale();
	float GetCameraRotation();
	Vector2 GetCameraTranslate();
};

