#pragma once

#include "App/GUI.h"
#include "ECS/Entity.h"

namespace golf {

class CameraControls {
public:
	CameraControls(agl::Camera& camera, float maxLeft, float maxRight, float maxUp, float maxDown);

	void update(float deltaT);
	void follow(float xPos, float yPos);

	void lock(float x, float y, float zoom);
	void unlock();

private:
	GUILayer m_gui;
	agl::Camera* m_camera;

	float m_camUpSpeed = 0;
	float m_camDownSpeed = 0;
	float m_camRightSpeed = 0;
	float m_camLeftSpeed = 0;
	Entity m_camLeft;
	Entity m_camRight;
	Entity m_camUp;
	Entity m_camDown;
	float m_camMinX;
	float m_camMaxX;
	float m_camMaxY;
	float m_camMinY;
	float m_zoom = 1.f;
	float m_targetZoom = 0.5f;
	float m_zoomTimer = 0.f;

	float xFollow = 0;
	float yFollow = 0;
	bool m_follow = false;

	float m_lockedX = 0.f;
	float m_lockedY = 0.f;
	float m_lockedZoom = 1.f;
	bool m_locked = false;

};



}
