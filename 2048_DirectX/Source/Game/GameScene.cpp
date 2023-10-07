#include "pch.h"
#include "GameScene.h"
#include "GameSceneCanvas.h"
#include "Grid.h"

#include "Framework/Object.h"
#include "Framework/Button.h"
#include "Framework/SceneManager.h"
#include "Framework/Window.h"
#include "Framework/Sprite.h"
#include "Framework/Text.h"
#include "Framework/Transform2D.h"
#include "Framework/SpriteRenderer.h"
#include "Framework/Camera.h"

using namespace Framework;

namespace Game2048
{
	void GameScene::Init()
	{
		// Canvas�쐬
		std::unique_ptr<GameSceneCanvas> gameCanvas = std::make_unique<GameSceneCanvas>();
		gameCanvas->Init();
		m_canvases.push_back(std::move(gameCanvas));

		auto windowSize = Window::GetWindowSize();

		// �O���b�h
		std::unique_ptr<GameObject> grid = std::make_unique<GameObject>();
		grid->AddComponent<Grid>(grid.get());
		m_gameObjects.push_back(std::move(grid));

		// �w�i
		std::unique_ptr<GameObject> background = std::make_unique<GameObject>();
		Sprite* backgroundSprite = new Sprite(L"res/GameBackground.png");
		background->AddComponent<SpriteRenderer>(background.get());
		background->GetComponent<SpriteRenderer>()->SetSprite(backgroundSprite);
		background->GetComponent<SpriteRenderer>()->SetLayer(static_cast<UINT>(DRAW_LAYER::BACKGROUND));
		background->GetComponent<Transform2D>()->position = { windowSize.cx / 2.f, windowSize.cy / 2.f };
		background->GetComponent<Transform2D>()->scale = { windowSize.cx * 1.f, windowSize.cy * 1.f };
		m_gameObjects.push_back(std::move(background));

		// �p�l���̎d�l
		// �E�p�l���̃T�C�Y�̓O���b�h��1/4
		// �E�p�l���̈ʒu�̓O���b�h�̒��S
		// �E�p�l���̐���16�˃I�u�W�F�N�g�v�[���ŊǗ�
		// �E�p�l���̐��l��2�̏搔�ŏ����l��2or4
		// �E���������ƍ��̂����2�{�̐����ɂȂ�
		// �E�p�l���̐��l�͍ő�2048
		// �E�p�l���̐��l�͍ŏ�2
		// �E�L�[���͂̕����Ƀp�l��������
		// �E�������A��������ɓ��������̃p�l��������ꍇ�͍��̂���
		// �E�p�l���������Ƃ��ɂ̓A�j���[�V����������
		// �E�p�l���������Ƃ��ɂ͉���炷
		//
	}
	void GameScene::Final()
	{
		m_gameObjects.clear();
		m_gameObjects.shrink_to_fit();
	}
}