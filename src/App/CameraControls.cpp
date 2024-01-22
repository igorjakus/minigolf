#include "CameraControls.h"

#include "Core/AppData.h"

#include "Util.hpp"

namespace golf {

CameraControls::CameraControls(agl::Camera& camera, float maxLeft, float maxRight, float maxUp, float maxDown)
	: m_camera(&camera), m_camMinX(maxLeft), m_camMaxX(maxRight), m_camMaxY(maxUp), m_camMinY(maxDown) {}

void CameraControls::update(float deltaT) {
	m_gui.render();

	const float winWidth = static_cast<float>(AppData::getWindow().getWindowSize().x);
	const float winHeight = static_cast<float>(AppData::getWindow().getWindowSize().y);

	const float mousePosX = AppData::getInput().getMouseX() / winWidth;
	const float mousePosY = AppData::getInput().getMouseY() / winHeight;

	bool cursorActive = !AppData::getInput().isMouseLocked();
	const float cameraSpeed = 10 * m_camera->getFocalLength();
	const float cameraResponse = 30;
	if (AppData::getInput().isKeyPressed("UP") || AppData::getInput().isKeyPressed("W") || ( mousePosY < 0.1f && cursorActive)) {
		m_camUpSpeed += 2 * deltaT * cameraResponse;
	}
	if (AppData::getInput().isKeyPressed("LEFT") || AppData::getInput().isKeyPressed("A") || (mousePosX < 0.1f && cursorActive)) {
		m_camLeftSpeed += 2 * deltaT * cameraResponse;
	}
	if (AppData::getInput().isKeyPressed("RIGHT") || AppData::getInput().isKeyPressed("D") || (mousePosX > 0.9f && cursorActive)) {
		m_camRightSpeed += 2 * deltaT * cameraResponse;
	}
	if (AppData::getInput().isKeyPressed("DOWN") || AppData::getInput().isKeyPressed("S") || (mousePosY > 0.9f && cursorActive)) {
		m_camDownSpeed += 2 * deltaT * cameraResponse;
	}

	m_camUpSpeed -= deltaT * cameraResponse;
	m_camLeftSpeed -= deltaT * cameraResponse;
	m_camRightSpeed -= deltaT * cameraResponse;
	m_camDownSpeed -= deltaT * cameraResponse;

	m_camUpSpeed = util::clamp(m_camUpSpeed, 0, cameraSpeed);
	m_camRightSpeed = util::clamp(m_camRightSpeed, 0, cameraSpeed);
	m_camLeftSpeed = util::clamp(m_camLeftSpeed, 0, cameraSpeed);
	m_camDownSpeed = util::clamp(m_camDownSpeed, 0, cameraSpeed);

	float cameraX = m_camera->getPosition().x;
	float cameraY = m_camera->getPosition().y;
	if(m_locked) {
		float c = 0.05f;
		c = 1.f - powf(c, deltaT);
		cameraX = util::lerp(cameraX, m_lockedX, c);
		cameraY = util::lerp(cameraY, m_lockedY, c);
		float targetZoom = m_lockedZoom;
		m_zoomTimer = 0.f;
		m_zoom = util::lerp(m_zoom, targetZoom, c);
		m_camera->setFocalLength(m_zoom);
	} else {
		cameraX += deltaT * (m_camRightSpeed - m_camLeftSpeed);
		cameraY += deltaT * (m_camUpSpeed - m_camDownSpeed);
		if(m_follow) {
			float c = 0.1f;
			c = 1.f - powf(c, deltaT);
			cameraX = util::lerp(cameraX, xFollow, c);
			cameraY = util::lerp(cameraY, yFollow, c);
			m_targetZoom = 0.5f;
			m_zoomTimer = 0.f;
		}
		if (AppData::getInput().getWheelOffset() >= 1) {
			m_targetZoom *= 0.8f;
			m_zoomTimer = 0;
		}
		if (AppData::getInput().getWheelOffset() <= -1) {
			m_targetZoom *= 1.25f;
			m_zoomTimer = 0;
		}
		m_targetZoom = util::clamp(m_targetZoom, 0.3f, 1.f);
		m_zoomTimer += deltaT * 3.f; if (m_zoomTimer > 1) { m_zoomTimer = 1; }
		m_zoom = util::lerp(m_zoom, m_targetZoom, m_zoomTimer);
		m_camera->setFocalLength(m_zoom);
	}
	cameraX = util::clamp(cameraX, m_camMinX, m_camMaxX);
	cameraY = util::clamp(cameraY, m_camMinY, m_camMaxY);
	m_camera->setPosition(cameraX, cameraY);

	m_follow = false; 
	unlock();
}

void CameraControls::follow(float xPos, float yPos) {
	xFollow = xPos;
	yFollow = yPos;
	m_follow = true;
}

void CameraControls::lock(float x, float y, float zoom) {
	m_locked = true;
	m_lockedX = x;
	m_lockedY = y;
	m_lockedZoom = zoom;
}

void CameraControls::unlock() {
	m_locked = false;
}

}
