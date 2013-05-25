#include "DxLib.h"
#include "Player.h"

void gameMain();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmsShow)
{
	//お約束として作るメイン。初期化と終了処理、ゲームメインを呼び出す。
	//ごちゃごちゃするのでメインとゲームメインは分けておく。
	//一度作ってしまえば、あとは変更する必要は少ない。

	//ウィンドウモードに設定
	ChangeWindowMode(true);
			
	//DXライブラリの初期化
	//初期化に失敗したら終了
	if(DxLib_Init() == -1)
	{
		return 1;
	}

	//ゲームメインの呼び出し
	gameMain();
	
	//DXライブラリの終了処理
	DxLib_End();				

	return 0;
}

void gameMain(void)
{
	//ゲームのメイン
	//こちらに色々な処理を記述する

	//playerの初期化
	Player player;
	player.setGraph( LoadGraph("media/test_jiki.bmp") );

	//BGに書き込む
	SetDrawScreen(DX_SCREEN_BACK);
	
	while(ProcessMessage() != -1){
		//画面を消去する
		ClsDrawScreen();
		//四角形を描画する
		DrawBox(270, 190, 370, 290, GetColor(255, 255, 0), TRUE);

		player.update();
		player.draw();

		//BGを表に出す(ダブルバッファリング)
		ScreenFlip();
	}

	//キー入力待ち
	WaitKey();
}
