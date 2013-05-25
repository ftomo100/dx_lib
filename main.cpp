#include "DxLib.h"
#include "Player.h"

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

	//BG�ɏ�������
	SetDrawScreen(DX_SCREEN_BACK);
	
	while(ProcessMessage() != -1){
		//��ʂ���������
		ClsDrawScreen();
		//�l�p�`��`�悷��
		DrawBox(270, 190, 370, 290, GetColor(255, 255, 0), TRUE);

		player.update();
		player.draw();

		//BG��\�ɏo��(�_�u���o�b�t�@�����O)
		ScreenFlip();
	}

	//�L�[���͑҂�
	WaitKey();
}
