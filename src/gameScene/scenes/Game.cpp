#include "Game.h"

Game::Game(GameState* state, KeyStateManager* keyStateManager, Timer* timer, ResourceManager* resourceManager)
{
	this->resourceManager = resourceManager;
	this->isNeedInit = true;
	this->keyStateManager = keyStateManager;
	this->state = state;
	this->timer = timer;
	this->isGameOver = false;
	this->isClear = false;

	// �V���b�g�Ǘ��������i�K����ԍŏ��Bplayer��enemy�Ŏg�p���邽�߁B�j
	this->shotManager = new ShotManager(this->timer);

	// �v���C���[������
	POINTFLOAT playerPos = { (FLOAT)(WND_SIZE.x / 2.0), (FLOAT)(WND_SIZE.y - 80.0) };
	this->player = new NormalPlayer(playerPos, this->keyStateManager, this->shotManager, this->timer);

	// �G�l�~�[������
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
	// ������
	if (this->isNeedInit)
	{
		this->GameInitialize();
		this->isNeedInit = false;
	}
	
	// �v���C���[��update
	this->player->Update();
	// �e�}�l�[�W���[��update
	this->enemyManager->Update();
	this->shotManager->Update();
	// �����蔻��m�F
	this->HitCheckPlayer();
	this->HitCheckEnemy();

	// �Q�[���I�[�o�[ or �N���A��
	if (this->isGameOver || this->isClear) {
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

	// �v���C���[�\��
	renderer.DrawRequestImage(
		this->player->getPos(),
		this->resourceManager->GetResourceData(RESOURCE_PLAYER, 0)
	);

	// �G�l�~�[�\��
	for (int i = 0; i < this->enemyManager->getListLength(); i++)
	{
		renderer.DrawRequestImage(
			this->enemyManager->getActor(i)->getPos(),
			this->resourceManager->GetResourceData(RESOURCE_ENEMY, 0)
		);
	}

	// �V���b�g�\��
	for (int i = 0; i < this->shotManager->getListLength(); i++)
	{
		shot = dynamic_cast<ShotBase*>(this->shotManager->getActor(i));
		if (shot == NULL)
			throw "shot��NULL�ł��B";

		if (shot->GetIsPlayerShot())
			shotIndex = 0;
		else
			shotIndex = 1;

		renderer.DrawRequestImage(
			shot->getPos(),
			this->resourceManager->GetResourceData(RESOURCE_SHOT, shotIndex)
		);
	}
}

void Game::GameInitialize()
{
	// �v���C���[�̈ʒu�̏�����
	this->player->InitPos();

	// �G�̏�����
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
	// �G�̍폜
	this->enemyManager->clear();

	// �e�̍폜
	this->shotManager->clear();

	// �������t���O��������
	this->isNeedInit = true;

	// isGameOver��isClear��������
	this->isClear = false;
	this->isGameOver = false;

	// �X�e�[�g��ύX
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
