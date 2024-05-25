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

	// �V���b�g�Ǘ��������i�K����ԍŏ��Bplayer��enemy�Ŏg�p���邽�߁B�j
	this->shotManager = new ShotManager(this->timer);

	// �v���C���[������
	POINTFLOAT playerPos = { (FLOAT)(WND_SIZE.x / 2.0), (FLOAT)(WND_SIZE.y - 100.0) };
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
		if (*(this->state) == STATE_LOADING)
			return;
	}
	
	// �v���C���[��update
	if (this->innerState == PLAY)
		this->player->Update();
	// �e�}�l�[�W���[��update
	this->enemyManager->Update();
	this->shotManager->Update();
	// �����蔻��m�F
	if (this->innerState == PLAY)
	{
		this->HitCheckPlayer();
		this->HitCheckEnemy();
	}

	// �v���Q�[���I�[�o�[��
	if (this->innerState == PRE_GAMEOVER)
	{
		// TODO: �{���ł���΁APlayer�Ƃ��ɂ��̕ӂ͎������������ǂ����A�ˊю����̂���Game.cpp�őS�������Ă���
		// TODO: �܂��A���b�ŉ����̃G�t�F�N�g�摜��؂�ւ��邩���A�萔�Ƃ�FPS�ɂ���Đ؂�ւ���ׂ������A�ЂƂ܂��n�[�h�R�[�f�B���O���Ă���
		this->playerExplosionResourceIndex = (this->timer->getNowFrame() - this->playerDeathFrame) / 2;
		if (this->playerExplosionResourceIndex >= 10)
			this->innerState = GAMEOVER;
	}

	// �Q�[���I�[�o�[ or �N���A��
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

	// �G�l�~�[�\��
	for (int i = 0; i < this->enemyManager->getListLength(); i++)
	{
		renderer.DrawRequestImage(
			this->enemyManager->getActor(i)->getPos(),
			this->resourceManager->GetResourceData(RESOURCE_ENEMY, 0), 0
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
			this->resourceManager->GetResourceData(RESOURCE_SHOT, shotIndex), 0
		);
	}


	// �v���C���[�\��
	if (this->innerState == PLAY)
		renderer.DrawRequestImage(
			this->player->getPos(),
			this->resourceManager->GetResourceData(RESOURCE_PLAYER, 0), 0
		);
	// �v���C���[�����G�t�F�N�g�\��
	if (this->innerState == PRE_GAMEOVER)
	{
		if (this->playerExplosionResourceIndex < 6)
		{
			// TODO: �G�t�F�N�g�摜�̃T�C�Y�ƃv���C���[�̉摜�T�C�Y���قȂ邽�߁A��������_�ɂ���ƈʒu������Ă��܂��B���̂���-16���Ă���
			// TODO: ���A������񂱂�ȃn�[�h�R�[�f�B���O�͗ǂ��Ȃ�
			ResourceData* data = this->resourceManager->GetResourceData(RESOURCE_EXPLOSION, this->playerExplosionResourceIndex);
			renderer.DrawRequestImage({this->player->getPos().x - 16, this->player->getPos().y - 16}, data, 0);
		}
			
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

	// Loading�i���[�h���������Ă��Ȃ���΁j
	if (!this->resourceManager->GetIsCompletedLoad())
	{
		*(this->preState) = STATE_GAME;
		*(this->state) = STATE_LOADING;
	}
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
	this->innerState = PLAY;

	// �X�e�[�g��ύX
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
