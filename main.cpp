#include "DxLib.h"
#include "Player.h"
#include "Jitama.h"
#include <list>

void gameMain();

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

	//player�̏�����
	Player player;
	player.setGraph( LoadGraph("media/test_jiki.bmp") );
	
	//���˂���e�̏�����
	//list���g���ĊǗ�����
	std::list<Jitama> jitamas;

	//BG�ɏ�������
	SetDrawScreen(DX_SCREEN_BACK);
	
	while(ProcessMessage() != -1){
		//��ʂ���������
		ClsDrawScreen();
		//�l�p�`��`�悷��
		DrawBox(270, 190, 370, 290, GetColor(255, 255, 0), TRUE);

		player.update();
		player.draw();

		int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if(key & PAD_INPUT_A){
			Jitama jitama;
			jitama.setGraph(LoadGraph("media/test_tama.bmp"));
			jitama.x = player.x;
			jitama.y = player.y;
			jitamas.push_back(jitama);
		}

		for (auto i = jitamas.begin(); i != jitamas.end();){
			//���@�̒e�͈̔̓`�F�b�N
			//��ʊO�ɏo����list����폜����
			i->update();
			i->draw();
			if ( i->x > 320){
				i = jitamas.erase(i);
				continue;
			}
			++i;
		}

		//BG��\�ɏo��(�_�u���o�b�t�@�����O)
		ScreenFlip();
	}

	//�L�[���͑҂�
	WaitKey();
}
