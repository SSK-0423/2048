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
		// Canvas作成
		std::unique_ptr<GameSceneCanvas> gameCanvas = std::make_unique<GameSceneCanvas>();
		gameCanvas->Init();
		m_canvases.push_back(std::move(gameCanvas));

		auto windowSize = Window::GetWindowSize();

		// グリッド
		std::unique_ptr<GameObject> grid = std::make_unique<GameObject>();
		grid->AddComponent<Grid>(grid.get());
		m_gameObjects.push_back(std::move(grid));

		// 背景
		std::unique_ptr<GameObject> background = std::make_unique<GameObject>();
		Sprite* backgroundSprite = new Sprite(L"res/GameBackground.png");
		background->AddComponent<SpriteRenderer>(background.get());
		background->GetComponent<SpriteRenderer>()->SetSprite(backgroundSprite);
		background->GetComponent<SpriteRenderer>()->SetLayer(static_cast<UINT>(DRAW_LAYER::BACKGROUND));
		background->GetComponent<Transform2D>()->position = { windowSize.cx / 2.f, windowSize.cy / 2.f };
		background->GetComponent<Transform2D>()->scale = { windowSize.cx * 1.f, windowSize.cy * 1.f };
		m_gameObjects.push_back(std::move(background));

		// パネルの仕様
		// ・パネルのサイズはグリッドの1/4
		// ・パネルの位置はグリッドの中心
		// ・パネルの数は16個⇒オブジェクトプールで管理
		// ・パネルの数値は2の乗数で初期値は2or4
		// ・同じ数字と合体すると2倍の数字になる
		// ・パネルの数値は最大2048
		// ・パネルの数値は最小2
		// ・キー入力の方向にパネルが動く
		// ・ただし、動いた先に同じ数字のパネルがある場合は合体する
		// ・パネルが動くときにはアニメーションをつける
		// ・パネルが動くときには音を鳴らす
		//
	}
	void GameScene::Final()
	{
		m_gameObjects.clear();
		m_gameObjects.shrink_to_fit();
	}
}