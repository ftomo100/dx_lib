#include "DxLib.h"
#include "Player.h"
#include "Jitama.h"
#include "Enemy.h"
#include <list>

void gameMain();
bool isHit(int x1,int y1, int x2, int y2);

//�X�R�A
int gameScore;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmsShow)
{
	//���񑩂Ƃ��č�郁�C���B�������ƏI�������A�Q�[�����C�����Ăяo���B
	//�����Ⴒ���Ⴗ��̂Ń��C���ƃQ�[�����C���͕����Ă����B
	//��x����Ă��܂��΁A���Ƃ͕ύX����K�v�͏��Ȃ��B

	//�E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(true);
			
	//DX���C�u�����̏�����
	//�������Ɏ��s������I��
	if(DxLib_Init() == -1)
	{
		return 1;
	}

	//�Q�[�����C���̌Ăяo��
	gameMain();
	
	//DX���C�u�����̏I������
	DxLib_End();				

	return 0;
}

void gameMain(void)
{
	//�Q�[���̃��C��
	//������ɐF�X�ȏ������L�q����

	gameScore = 0;

	GraphHandle playerGraph = LoadGraph("media/test_jiki.bmp");
	GraphHandle jitamaGraph = LoadGraph("media/test_tama.bmp");
	GraphHandle enemyGraph = LoadGraph("media/test_teki.bmp");

	//player�̏�����
	Player player;
	player.setGraph(playerGraph);
	
	//enemy�̏�����
	std::list<Enemy> enemies;
	for ( int i = 0; i< 10 ; i++){
		Enemy enemy;
		enemy.setGraph(enemyGraph);
		enemies.push_back(enemy);
	}

	//���˂���e�̏�����
	//list���g���ĊǗ�����
	std::list<Jitama> jitamas;
	int trigger = 0;

	//BG�ɏ�������
	SetDrawScreen(DX_SCREEN_BACK);
	
	while(ProcessMessage() != -1){
		//��ʂ���������
		ClsDrawScreen();
		//�l�p�`��`�悷��
		DrawBox(270, 190, 370, 290, GetColor(255, 255, 0), TRUE);

		DrawFormatString(0, 0, GetColor(255,255,255), "SCORE:%6d", gameScore);

		player.update();
		player.draw();

		int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if(key & PAD_INPUT_A && trigger == 0){
			Jitama jitama;
			jitama.setGraph(jitamaGraph);
			jitama.x = player.x;
			jitama.y = player.y;
			jitamas.push_back(jitama);
			//���ˊԊu(�t���[��)���w�肷��
			trigger = 12;
		}
		if(trigger > 0) trigger--;

		for (auto i = jitamas.begin(); i != jitamas.end();){
			//���@�̒e�̍X�V����
			//���@�̒e�͈̔̓`�F�b�N
			//��ʊO�ɏo����list����폜����
			i->update();
			i->draw();
			if ( i->x > 640){
				i = jitamas.erase(i);
				continue;
			}
			++i;
		}

		for (auto i = enemies.begin(); i != enemies.end();){
			//�G�̍X�V����
			//���@�̒e�͈̔̓`�F�b�N
			//��ʊO�ɏo����list����폜����
			i->update();
			i->draw();
			if ( i->x < 0){
				Enemy enemy;
				enemy.setGraph(enemyGraph);
				enemies.push_back(enemy);

				i = enemies.erase(i);
				continue;
			}
			++i;
		}

		for (auto i = jitamas.begin(); i != jitamas.end();){
			//�����蔻��`�F�b�N
			//�e�ƓG���������Ă���ΓG����������
			for (auto j = enemies.begin(); j != enemies.end();){
				if ( isHit(i->x, i->y, j->x, j->y) ){
					Enemy enemy;
					enemy.setGraph(enemyGraph);
					enemies.push_back(enemy);
					//100�_�@���Z����
					gameScore += 100;

					j = enemies.erase(j);
					continue;
				}
				++j;
			}
			++i;
		}



		//BG��\�ɏo��(�_�u���o�b�t�@�����O)
		ScreenFlip();
	}

	//�L�[���͑҂�
	WaitKey();
}

bool isHit(int x1, int y1, int x2, int y2)
{
	//�����蔻��`�F�b�N
	//�e�̍��W�E�E�Ex1,y1 64x16
	//�G�̍��W�E�E�Ex2,y2 32x32
	int dist;

	//�e�͉E���Ŕ��肷�邽�߁A�e�̉�����ǉ�����B
	x1 += 64;

	dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	if ( dist < 200){
		return true;
	} else {
		return false;
	}
}