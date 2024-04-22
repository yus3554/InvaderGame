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

	// �V���b�g�Ǘ��������i�K����ԍŏ��Bplayer��enemy�Ŏg�p���邽�߁B�j
	this->shotManager = new ShotManager(this->timer);

	// �v���C���[������
	POINTFLOAT playerPos = { WND_SIZE.x / 2.0, WND_SIZE.y - 80.0 };
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
	if (*(this->state) != STATE_GAME) {
		return;
	}

	// �w�i�摜�ݒ�
	renderer.SetBackground(IDB_BITMAP1);

	// �v���C���[�\��
	renderer.DrawRequestRect(
		this->player->getPos(),
		this->player->GetWidth(), this->player->GetHeight(),
		RGB(255, 255, 255), RGB(100, 100, 0), 1
	);

	// �G�l�~�[�\��
	for (int i = 0; i < this->enemyManager->getListLength(); i++)
	{
		renderer.DrawRequestRect(
			this->enemyManager->getActor(i)->getPos(),
			this->enemyManager->getActor(i)->GetWidth(), this->enemyManager->getActor(i)->GetHeight(),
			RGB(255, 0, 0), RGB(100, 100, 0), 1
		);
	}

	// �V���b�g�\��
	for (int i = 0; i < this->shotManager->getListLength(); i++)
	{
		renderer.DrawRequestRect(
			this->shotManager->getActor(i)->getPos(),
			this->shotManager->getActor(i)->GetWidth(), this->shotManager->getActor(i)->GetHeight(),
			RGB(255, 255, 0), RGB(100, 100, 0), 1
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
