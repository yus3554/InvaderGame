#include "Game.h"

Game::Game(GameState* state, GameState* preState, KeyStateManager* keyStateManager, Timer* timer, ResourceManager* resourceManager)
{
	this->resourceManager = resourceManager;
	this->isNeedInit = true;
	this->keyStateManager = keyStateManager;
	this->state = state;
	this->preState = preState;
	this->timer = timer;
	this->innerState = PLAY;
	this->playerDeathFrame = 0;
	this->playerExplosionResourceIndex = 0;

	// ショット管理初期化（必ず一番最初。playerとenemyで使用するため。）
	this->shotManager = new ShotManager(this->timer);

	// プレイヤー初期化
	POINTFLOAT playerPos = { (FLOAT)(WND_SIZE.x / 2.0), (FLOAT)(WND_SIZE.y - 100.0) };
	this->player = new NormalPlayer(playerPos, this->keyStateManager, this->shotManager, this->timer);

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
		if (*(this->state) == STATE_LOADING)
			return;
	}
	
	// プレイヤーのupdate
	if (this->innerState == PLAY)
		this->player->Update();
	// 各マネージャーのupdate
	this->enemyManager->Update();
	this->shotManager->Update();
	// 当たり判定確認
	if (this->innerState == PLAY)
	{
		this->HitCheckPlayer();
		this->HitCheckEnemy();
	}

	// プリゲームオーバー時
	if (this->innerState == PRE_GAMEOVER)
	{
		// TODO: 本来であれば、Playerとかにこの辺は持たせた方が良いが、突貫実装のためGame.cppで全部書いている
		// TODO: また、何秒で何枚のエフェクト画像を切り替えるかも、定数とかFPSによって切り替えるべきだが、ひとまずハードコーディングしている
		this->playerExplosionResourceIndex = (this->timer->getNowFrame() - this->playerDeathFrame) / 2;
		if (this->playerExplosionResourceIndex >= 10)
			this->innerState = GAMEOVER;
	}

	// ゲームオーバー or クリア時
	if (this->innerState == GAMEOVER || this->innerState == CLEAR) {
		this->GameFinalize();
	}
}

void Game::DrawRequest(Renderer& renderer)
{
	ShotBase* shot;
	int shotIndex;

	if (*(this->state) != STATE_GAME) {
		return;
	}

	// エネミー表示
	for (int i = 0; i < this->enemyManager->getListLength(); i++)
	{
		renderer.DrawRequestImage(
			this->enemyManager->getActor(i)->getPos(),
			this->resourceManager->GetResourceData(RESOURCE_ENEMY, 0), 0
		);
	}

	// ショット表示
	for (int i = 0; i < this->shotManager->getListLength(); i++)
	{
		shot = dynamic_cast<ShotBase*>(this->shotManager->getActor(i));
		if (shot == NULL)
			throw "shotがNULLです。";

		if (shot->GetIsPlayerShot())
			shotIndex = 0;
		else
			shotIndex = 1;

		renderer.DrawRequestImage(
			shot->getPos(),
			this->resourceManager->GetResourceData(RESOURCE_SHOT, shotIndex), 0
		);
	}


	// プレイヤー表示
	if (this->innerState == PLAY)
		renderer.DrawRequestImage(
			this->player->getPos(),
			this->resourceManager->GetResourceData(RESOURCE_PLAYER, 0), 0
		);
	// プレイヤー爆発エフェクト表示
	if (this->innerState == PRE_GAMEOVER)
	{
		if (this->playerExplosionResourceIndex < 6)
		{
			// TODO: エフェクト画像のサイズとプレイヤーの画像サイズが異なるため、左上を原点にすると位置がずれてしまう。そのため-16している
			// TODO: が、もちろんこんなハードコーディングは良くない
			ResourceData* data = this->resourceManager->GetResourceData(RESOURCE_EXPLOSION, this->playerExplosionResourceIndex);
			renderer.DrawRequestImage({this->player->getPos().x - 16, this->player->getPos().y - 16}, data, 0);
		}
			
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


	this->resourceManager->LoadRequest(RESOURCE_PLAYER, 0);
	this->resourceManager->LoadRequest(RESOURCE_ENEMY, 0);
	this->resourceManager->LoadRequest(RESOURCE_SHOT, 0);
	this->resourceManager->LoadRequest(RESOURCE_SHOT, 1);
	this->resourceManager->LoadRequest(RESOURCE_EXPLOSION, 0);
	this->resourceManager->LoadRequest(RESOURCE_EXPLOSION, 1);
	this->resourceManager->LoadRequest(RESOURCE_EXPLOSION, 2);
	this->resourceManager->LoadRequest(RESOURCE_EXPLOSION, 3);
	this->resourceManager->LoadRequest(RESOURCE_EXPLOSION, 4);
	this->resourceManager->LoadRequest(RESOURCE_EXPLOSION, 5);

	// Loading（ロードが完了していなければ）
	if (!this->resourceManager->GetIsCompletedLoad())
	{
		*(this->preState) = STATE_GAME;
		*(this->state) = STATE_LOADING;
	}
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
	this->innerState = PLAY;

	// ステートを変更
	*(this->preState) = *(this->state);
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
			this->innerState = PRE_GAMEOVER;
			this->playerDeathFrame = timer->getNowFrame();
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
