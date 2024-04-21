#include "Game.h"
#include <stdio.h>

Game::Game(GameState* state, KeyStateManager* keyStateManager)
{
	this->isNeedInit = true;
	this->keyStateManager = keyStateManager;
	this->state = state;

	// �V���b�g�Ǘ��������i�K����ԍŏ��Bplayer��enemy�Ŏg�p���邽�߁B�j
	this->shotManager = new ShotManager();

	// �v���C���[������
	POINT playerPos = { (LONG)(WND_SIZE.x / 2), (LONG)WND_SIZE.y - 80 };
	this->player = new NormalPlayer(playerPos, this->keyStateManager, this->shotManager);

	// �G�l�~�[������
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

	
	// �v���C���[��update
	this->player->Update();
	// �e�}�l�[�W���[��update
	this->enemyManager->Update();
	this->shotManager->Update();
	// �����蔻��m�F

	// �Q�[���I�[�o�[ or �N���A��
	if (this->keyStateManager->getKeyState(VK_RETURN)->getIsDownStart()) {
		this->GameFinalize();
		*(this->state) = STATE_RESULT;
	}
}

void Game::DrawRequest(Renderer& renderer)
{
	// �w�i�摜�ݒ�
	renderer.SetBackground(IDB_BITMAP1);

	// �v���C���[�\��
	POINT playerPos = this->player->getPos();
	renderer.DrawRequestRect(playerPos, 20, 20, RGB(255, 255, 255), RGB(100, 100, 0), 1);

	// �G�l�~�[�\��
	for (int i = 0; i < this->enemyManager->getListLength(); i++)
	{
		POINT enemyPos = this->enemyManager->getActor(i)->getPos();
		renderer.DrawRequestRect(enemyPos, 20, 20, RGB(255, 0, 0), RGB(100, 100, 0), 1);
	}

	// �V���b�g�\��
	for (int i = 0; i < this->shotManager->getListLength(); i++)
	{
		POINT shotPos = this->shotManager->getActor(i)->getPos();
		renderer.DrawRequestRect(shotPos, 10, 30, RGB(255, 255, 0), RGB(100, 100, 0), 1);
	}
}

void Game::GameInitialize()
{
	// �v���C���[�̈ʒu�̏�����


	// �G�̏�����
	POINT enemyPos = { (LONG)(WND_SIZE.x / 2), 50 };
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos);
	enemyPos.x += 50;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos);
	enemyPos.y += 40;
	this->enemyManager->CreateEnemy<NormalEnemy>(enemyPos);
}

void Game::GameFinalize()
{
	// �G�̍폜
	this->enemyManager->clear();

	// �e�̍폜
	this->shotManager->clear();

	this->isNeedInit = true;
}
