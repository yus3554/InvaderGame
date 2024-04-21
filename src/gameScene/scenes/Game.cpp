#include "Game.h"
#include <stdio.h>

Game::Game(GameState* state, KeyStateManager* keyStateManager)
{
	this->isNeedInit = true;
	this->keyStateManager = keyStateManager;
	this->state = state;

	// ショット管理初期化（必ず一番最初。playerとenemyで使用するため。）
	this->shotManager = new ShotManager();

	// プレイヤー初期化
	POINT playerPos = { (LONG)(WND_SIZE.x / 2), (LONG)WND_SIZE.y - 80 };
	this->player = new NormalPlayer(playerPos, this->keyStateManager, this->shotManager);

	// エネミー初期化
	this->enemyManager = new EnemyManager(this->shotManager);
}

Game::~Game()
{
	delete this->player;
	delete this->enemyManager;
	delete this->shotManager;
}

void Game::Update()
{
	if (this->isNeedInit)
	{
		this->GameInitialize();
		this->isNeedInit = false;
	}

	
	// プレイヤーのupdate
	this->player->Update();
	// 各マネージャーのupdate
	this->enemyManager->Update();
	this->shotManager->Update();
	// 当たり判定確認

	// ゲームオーバー or クリア時
	if (this->keyStateManager->getKeyState(VK_RETURN)->getIsDownStart()) {
		this->GameFinalize();
		*(this->state) = STATE_RESULT;
	}
}

void Game::DrawRequest(Renderer& renderer)
{
	// 背景画像設定
	renderer.SetBackground(IDB_BITMAP1);

	// プレイヤー表示
	POINT playerPos = this->player->getPos();
	renderer.DrawRequestRect(playerPos, 20, 20, RGB(255, 255, 255), RGB(100, 100, 0), 1);

	// エネミー表示
	for (int i = 0; i < this->enemyManager->getListLength(); i++)
	{
		POINT enemyPos = this->enemyManager->getActor(i)->getPos();
		renderer.DrawRequestRect(enemyPos, 20, 20, RGB(255, 0, 0), RGB(100, 100, 0), 1);
	}

	// ショット表示
	for (int i = 0; i < this->shotManager->getListLength(); i++)
	{
		POINT shotPos = this->shotManager->getActor(i)->getPos();
		renderer.DrawRequestRect(shotPos, 10, 30, RGB(255, 255, 0), RGB(100, 100, 0), 1);
	}
}

void Game::GameInitialize()
{
	// プレイヤーの位置の初期化


	// 敵の初期化
	POINT enemyPos = { (LONG)(WND_SIZE.x / 2), 50 };
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos);
	enemyPos.y += 40;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos);
}

void Game::GameFinalize()
{
	// 敵の削除
	this->enemyManager->clear();

	// 弾の削除
	this->shotManager->clear();

	this->isNeedInit = true;
}
