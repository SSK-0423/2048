#include "pch.h"

#include "Object.h"
#include "Camera.h"
#include "Window.h"
#include "Transform2D.h"

#include "DX12Wrapper/ConstantBuffer.h"

using namespace DirectX;
using namespace DX12Wrapper;

namespace Framework
{
	Camera::Camera(Object* owner) : IComponent(owner)
	{
		m_constantBuffer = std::make_unique<ConstantBuffer>();

		auto windowSize = Window::GetWindowSize();
		m_projection = XMMatrixOrthographicOffCenterLH(0.0f, windowSize.cx, windowSize.cy, 0.0f, m_near, m_far);

		auto transform = m_owner->GetComponent<Transform2D>();
		m_view = transform->GetTransformMatrix();
	}
	Camera::~Camera()
	{
	}
	void Camera::Update(float deltaTime)
	{
		auto transform = m_owner->GetComponent<Transform2D>();
		m_view = transform->GetTransformMatrix();
	}
	void Camera::Draw()
	{
	}
	ConstantBuffer& Framework::Camera::GetConstantBuffer() const
	{
		return *m_constantBuffer.get();
	}
	float Camera::GetFar() const
	{
		return m_far;
	}
	float Camera::GetNear() const
	{
		return m_near;
	}
	DirectX::XMMATRIX Camera::GetViewMatrix() const
	{
		return m_view;
	}
	DirectX::XMMATRIX Camera::GetProjectionMatrix() const
	{
		return m_projection;
	}
}

