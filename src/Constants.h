#pragma once
#include <windows.h>


/// ####################################################
/// 
/// �}�N��
/// 
/// ####################################################

/// �w�肳�ꂽ�L�[��������Ă��邩�ǂ������擾
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/// �w�肳�ꂽ�L�[��������Ă��邩�ǂ������擾
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


/// ####################################################
///
/// �萔
/// 
/// ####################################################

/// <summary>
/// �E�B���h�E�N���X�̖��O
/// </summary>
constexpr PCTSTR WND_CLASS_NAME = TEXT("WindowClassName");

/// /// <summary>
/// �E�B���h�E�^�C�g��
/// </summary>
constexpr PCTSTR WND_TITLE = TEXT("Invader Game");

/// <summary>
/// �E�B���h�E�T�C�Y
/// </summary>
constexpr POINT WND_SIZE = { 720, 480 };

/// <summary>
/// UI �^�C�g��
/// </summary>
constexpr PCTSTR UI_TEXT_TITLE = TEXT("Invader Game");

/// <summary>
/// UI �Q�[���X�^�[�g
/// </summary>
constexpr PCTSTR UI_TEXT_START = TEXT("Start");

/// <summary>
/// UI �n�C�X�R�A
/// </summary>
constexpr PCTSTR UI_TEXT_HIGHSCORE = TEXT("High Score");

/// <summary>
/// UI �I��
/// </summary>
constexpr PCTSTR UI_TEXT_QUIT = TEXT("Quit");

/// <summary>
/// UI ���[�f�B���O
/// </summary>
constexpr PCTSTR UI_TEXT_LOADING = TEXT("Now Loading");

/// <summary>
/// Event�l�[�� �����_�[�X���b�h�p
/// </summary>
constexpr PCTSTR EVENT_NAME_RENDER_BEGIN = TEXT("RENDER_EVENT_BEGIN");
constexpr PCTSTR EVENT_NAME_RENDER_END = TEXT("RENDER_EVENT_END");

/// <summary>
/// Event�l�[�� ���\�[�X���[�h�X���b�h�p
/// </summary>
constexpr PCTSTR EVENT_NAME_RESOURCE_BEGIN = TEXT("RESOURCE_EVENT_BEGIN");
constexpr PCTSTR EVENT_NAME_RESOURCE_END = TEXT("RESOURCE_EVENT_END");

/// <summary>
/// �v���C���[�̏����ʒu
/// </summary>
constexpr POINT PLAYER_INIT_POS = {WND_SIZE.x / 2, WND_SIZE.y - 100};

/// <summary>
/// �`��t���[��
/// </summary>
constexpr int FPS = 60;

/// <summary>
/// �Ή��L�[�R�[�h�̐�
/// </summary>
constexpr int KEYCODE_LENGTH = 7;

/// <summary>
/// �Ή��L�[�R�[�h
/// </summary>
constexpr int KEYCODES[KEYCODE_LENGTH] = {
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE
};

/// <summary>
/// �Q�[���X�e�[�g
/// </summary>
enum GameState
{
	/// <summary>
	/// �^�C�g�����
	/// </summary>
	STATE_TITLE,

	/// <summary>
	/// �Q�[�����
	/// </summary>
	STATE_GAME,

	/// <summary>
	/// �n�C�X�R�A���
	/// </summary>
	STATE_HIGHSCORE,

	/// <summary>
	/// ���U���g���
	/// </summary>
	STATE_RESULT,

	/// <summary>
	/// �I��
	/// </summary>
	STATE_QUIT,

	/// <summary>
	/// ���[�f�B���O���
	/// </summary>
	STATE_LOADING,

	/// <summary>
	/// �X�e�[�g��
	/// </summary>
	STATE_NUM
};

/// <summary>
/// ���\�[�X���
/// </summary>
enum ResourceType
{
	/// <summary>
	/// �w�i
	/// </summary>
	RESOURCE_BACKGROUND,

	/// <summary>
	/// �v���C���[
	/// </summary>
	RESOURCE_PLAYER,

	/// <summary>
	/// �����G�t�F�N�g
	/// </summary>
	RESOURCE_EXPLOSION,

	/// <summary>
	/// �G
	/// </summary>
	RESOURCE_ENEMY,

	/// <summary>
	/// �V���b�g
	/// </summary>
	RESOURCE_SHOT
};


/// <summary>
/// �摜�̃��[�g�p�X
/// </summary>
constexpr char RESOURCE_ROOT_FOLDERPATH[100] = "C:/Users/Yusuke Ota/Development/github/InvaderGame/src/images/";

/// <summary>
/// ���[�g�p�X�ȉ��̔w�i�摜�p�X
/// </summary>
constexpr char BACKGROUND_FILEPATHS[2][20] =
{
	"background.bmp",
	"background2.bmp"
};

/// <summary>
/// ���[�g�p�X�ȉ��̃v���C���[�摜�p�X
/// </summary>
constexpr char PLAYER_FILEPATHS[1][20] = {
	"enemy1.bmp"
};

/// <summary>
/// ���[�g�p�X�ȉ��̔����G�t�F�N�g�摜�p�X
/// </summary>
constexpr char EXPLOSION_FILEPATHS[6][20] = {
	"explosion1.bmp",
	"explosion2.bmp",
	"explosion3.bmp",
	"explosion4.bmp",
	"explosion5.bmp",
	"explosion6.bmp"
};

/// <summary>
/// ���[�g�p�X�ȉ��̓G�摜�p�X
/// </summary>
constexpr char ENEMY_FILEPATHS[1][20] = {
	"player1.bmp"
};

/// <summary>
/// ���[�g�p�X�ȉ��̒e�摜�p�X
/// </summary>
constexpr char SHOT_FILEPATHS[2][20] = {
	"shot1.bmp",
	"shot2.bmp"
};
