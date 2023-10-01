#include "pch.h"
#include "Transform2D.h"
#include "DX12Wrapper/ConstantBuffer.h"
#include "DX12Wrapper/Dx12GraphicsEngine.h"

#include "Framework/Window.h"

using namespace DX12Wrapper;
using namespace Utility;
using namespace DirectX;

namespace Framework
{
	Transform2D::Transform2D(Object* owner)
		: IComponent(owner), m_buffer(std::make_unique<ConstantBuffer>()),
		position(0.f, 0.f), scale(100.f, 100.f), angle(0.f)
	{
		RESULT result = m_buffer->Create(Dx12GraphicsEngine::Instance().Device(), &m_bufferData, sizeof(m_bufferData));
		if (result == RESULT::FAILED)
		{
			MessageBoxA(NULL, "ContantBuffer�̐����Ɏ��s", "�G���[", MB_OK);
		}
	}
	void Transform2D::Update(float deltaTime)
	{
		m_bufferData.world = GetTransformMatrix();
		m_buffer->UpdateData(&m_bufferData);
	}
	DirectX::XMMATRIX Transform2D::GetTransformMatrix()
	{
		// �f�o�C�X���W�n�ɍ��킹��ۂ�+1����̂�y���W�̓}�C�i�X�l���g�� y=0��1 y=windowHeight��-1
		XMMATRIX translation = XMMatrixTranslation(position.x, -position.y, 0.f);
		XMMATRIX scaling = XMMatrixScaling(scale.x, scale.y, 1.f);
		XMMATRIX rotation = XMMatrixRotationZ(angle);

		// �s�N�Z���P�ʂ̍��W�n���琳�K���f�o�C�X���W�n�ɕύX����s��
		XMMATRIX convertToDeviceCoord = XMMatrixIdentity();
		auto windowSize = Window::GetWindowSize();
		convertToDeviceCoord.r[0].m128_f32[0] =  2.f / windowSize.cx;	// (0�`1)�ɐ��K��
		convertToDeviceCoord.r[1].m128_f32[1] =  2.f / windowSize.cy;	// (0�`1)�ɐ��K��
		convertToDeviceCoord.r[3].m128_f32[0] = -1.f;	//�f�o�C�X���W�n(-1�`1)�ɍ��킹��
		convertToDeviceCoord.r[3].m128_f32[1] =  1.f;	//�f�o�C�X���W�n(-1�`1)�ɍ��킹��

		XMMATRIX transformMatrix = scaling * rotation * translation * convertToDeviceCoord;

		return transformMatrix;
	}
	DX12Wrapper::ConstantBuffer& Transform2D::GetConstantBuffer()
	{
		return *m_buffer;
	}
}
