#include "pch.h"
#include "GameTimer.h"
#include "Framework/Object.h"
#include "Framework/Text.h"
#include "Framework/Transform2D.h"
#include "Framework/Window.h"

using namespace Framework;

namespace Game2048
{
	GameTimer::GameTimer(Framework::Object* owner) :
		Framework::IComponent(owner)
	{
		auto windowSize = Window::GetWindowSize();

		// テキスト追加
		auto text = m_owner->AddComponent<Text>(m_owner);
		text->SetScale(0.25f);
		text->SetColor(DirectX::Colors::Black);
		text->SetPosition({ windowSize.cx - 250.f, 0.f });
		text->SetText(L"00:00:00");
	}
	void GameTimer::Update(float deltaTime)
	{
		m_elapsedTime += deltaTime;

		// 時間表示
		int hour = static_cast<int>(m_elapsedTime / 3600.f);
		int minute = static_cast<int>((m_elapsedTime - hour * 3600.f) / 60.f);
		int second = static_cast<int>(m_elapsedTime - hour * 3600.f - minute * 60.f);

		std::wstring hourStr = hour < 10 ? L"0" + std::to_wstring(hour) : std::to_wstring(hour);
		std::wstring minuteStr = minute < 10 ? L"0"	+ std::to_wstring(minute) : std::to_wstring(minute);
		std::wstring secondStr = second < 10 ? L"0" + std::to_wstring(second) : std::to_wstring(second);
		
		std::wstring timeStr = L"Time " + hourStr + L":" + minuteStr + L":" + secondStr;
		
		m_owner->GetComponent<Text>()->SetText(timeStr);
	}

	void GameTimer::Draw()
	{
	}
}