#include "Game.h"
#include <stdio.h>

Game::Game(GameState* state, KeyStateManager* keyStateManager, Timer* timer)
{
	this->isNeedInit = true;
	this->keyStateManager = keyStateManager;
	this->state = state;
	this->timer = timer;
	this->isGameOver = false;
	this->isClear = false;

	// ショット管理初期化（必ず一番最初。playerとenemyで使用するため。）
	this->shotManager = new ShotManager(this->timer);

	// プレイヤー初期化
	POINTFLOAT playerPos = { (FLOAT)(WND_SIZE.x / 2.0), (FLOAT)(WND_SIZE.y - 80.0) };
	this->player = new HyperPlayer(playerPos, this->keyStateManager, this->shotManager, this->timer);

	// エネミー初期化
	this->enemyManager = new EnemyManager(this->shotManager, this->timer);
}

Game::~Game()
{
	delete this->player;
	delete this->enemyManager;
	delete this->shotManager;
}

void Game::Update()
{
	// 初期化
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
	this->HitCheckPlayer();
	this->HitCheckEnemy();

	// ゲームオーバー or クリア時
	if (this->isGameOver || this->isClear) {
		this->GameFinalize();
	}
}

void Game::DrawRequest(Renderer& renderer)
{
	ShotBase* shot;
	COLORREF shotColor;

	if (*(this->state) != STATE_GAME) {
		return;
	}

	// プレイヤー表示
	renderer.DrawRequestRect(
		this->player->getPos(),
		this->player->GetWidth(), this->player->GetHeight(),
		RGB(255, 255, 255), RGB(100, 100, 0), 1
	);

	// エネミー表示
	for (int i = 0; i < this->enemyManager->getListLength(); i++)
	{
		renderer.DrawRequestRect(
			this->enemyManager->getActor(i)->getPos(),
			this->enemyManager->getActor(i)->GetWidth(), this->enemyManager->getActor(i)->GetHeight(),
			RGB(255, 0, 0), RGB(100, 100, 0), 1
		);
	}

	// ショット表示
	for (int i = 0; i < this->shotManager->getListLength(); i++)
	{
		shot = dynamic_cast<ShotBase*>(this->shotManager->getActor(i));
		if (shot == NULL)
			throw "shotがNULLです。";

		if (shot->GetIsPlayerShot())
			shotColor = RGB(255, 255, 0);
		else
			shotColor = RGB(0, 255, 0);

		renderer.DrawRequestRect(
			shot->getPos(),	shot->GetWidth(), shot->GetHeight(),
			shotColor, RGB(100, 100, 0), 1
		);
	}
}

void Game::GameInitialize()
{
	// プレイヤーの位置の初期化
	this->player->InitPos();

	// 敵の初期化
	POINTFLOAT enemyPos = { 20.0, 50.0 };
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.y += 40;
	enemyPos.x = 20.0;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos, 200);
}

void Game::GameFinalize()
{
	// 敵の削除
	this->enemyManager->clear();

	// 弾の削除
	this->shotManager->clear();

	// 初期化フラグを初期化
	this->isNeedInit = true;

	// isGameOverとisClearを初期化
	this->isClear = false;
	this->isGameOver = false;

	// ステートを変更
	*(this->state) = STATE_RESULT;
}

void Game::HitCheckPlayer()
{
	RECT playerRect = this->player->GetRect();
	RECT shotRect;
	RECT intersectRect;
	for (int i = 0; i < this->shotManager->getListLength(); i++)
	{
		ShotBase* shot = dynamic_cast<ShotBase*>(this->shotManager->getActor(i));
		if (shot == nullptr || shot->GetIsPlayerShot())
			continue;

		shotRect = shot->GetRect();
		bool isHit = IntersectRect(&intersectRect, &playerRect, &shotRect);
		if (isHit)
		{
			this->isGameOver = true;
			return;
		}
	}
}

void Game::HitCheckEnemy()
{
	RECT shotRect;
	RECT enemyRect;
	RECT intersectRect;
	for (int i = 0; i < this->shotManager->getListLength(); i++)
	{
		ShotBase* shot = dynamic_cast<ShotBase*>(this->shotManager->getActor(i));
		if (shot == nullptr || !shot->GetIsPlayerShot())
			continue;

		shotRect = shot->GetRect();

		for (int j = 0; j < this->enemyManager->getListLength(); j++)
		{
			enemyRect = this->enemyManager->getActor(j)->GetRect();
			bool isHit = IntersectRect(&intersectRect, &enemyRect, &shotRect);
			if (isHit)
			{
				this->enemyManager->removeActor(j);
				this->shotManager->removeActor(i);
				i--;
				j--;
				break;
			}
		}
	}
}
