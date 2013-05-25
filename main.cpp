#include "DxLib.h"
#include "Player.h"
#include "Jitama.h"
#include <list>

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
	
	//発射する弾の初期化
	//listを使って管理する
	std::list<Jitama> jitamas;
	int trigger = 0;

	//BGに書き込む
	SetDrawScreen(DX_SCREEN_BACK);
	
	while(ProcessMessage() != -1){
		//画面を消去する
		ClsDrawScreen();
		//四角形を描画する
		DrawBox(270, 190, 370, 290, GetColor(255, 255, 0), TRUE);

		player.update();
		player.draw();

		int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if(key & PAD_INPUT_A && trigger == 0){
			Jitama jitama;
			jitama.setGraph(LoadGraph("media/test_tama.bmp"));
			jitama.x = player.x;
			jitama.y = player.y;
			jitamas.push_back(jitama);
			//発射間隔(フレーム)を指定する
			trigger = 12;
		}
		if(trigger > 0) trigger--;

		for (auto i = jitamas.begin(); i != jitamas.end();){
			//自機の弾の更新処理
			//自機の弾の範囲チェック
			//画面外に出たらlistから削除する
			i->update();
			i->draw();
			if ( i->x > 320){
				i = jitamas.erase(i);
				continue;
			}
			++i;
		}

		//BGを表に出す(ダブルバッファリング)
		ScreenFlip();
	}

	//キー入力待ち
	WaitKey();
}
