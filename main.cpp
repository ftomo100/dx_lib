#include "DxLib.h"
#include "Player.h"
#include "Jitama.h"
#include "Enemy.h"
#include <list>

void gameMain();
bool isHit(int x1,int y1, int x2, int y2);

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

	GraphHandle playerGraph = LoadGraph("media/test_jiki.bmp");
	GraphHandle jitamaGraph = LoadGraph("media/test_tama.bmp");
	GraphHandle enemyGraph = LoadGraph("media/test_teki.bmp");

	//playerの初期化
	Player player;
	player.setGraph(playerGraph);
	
	//enemyの初期化
	std::list<Enemy> enemies;
	for ( int i = 0; i< 10 ; i++){
		Enemy enemy;
		enemy.setGraph(enemyGraph);
		enemies.push_back(enemy);
	}

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
			jitama.setGraph(jitamaGraph);
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
			if ( i->x > 640){
				i = jitamas.erase(i);
				continue;
			}
			++i;
		}

		for (auto i = enemies.begin(); i != enemies.end();){
			//敵の更新処理
			//自機の弾の範囲チェック
			//画面外に出たらlistから削除する
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
			//当たり判定チェック
			//弾と敵が当たっていれば敵を消去する
			for (auto j = enemies.begin(); j != enemies.end();){
				if ( isHit(i->x, i->y, j->x, j->y) ){
					Enemy enemy;
					enemy.setGraph(enemyGraph);
					enemies.push_back(enemy);

					j = enemies.erase(j);
					continue;
				}
				++j;
			}
			++i;
		}



		//BGを表に出す(ダブルバッファリング)
		ScreenFlip();
	}

	//キー入力待ち
	WaitKey();
}

bool isHit(int x1, int y1, int x2, int y2)
{
	//当たり判定チェック
	//弾の座標・・・x1,y1 64x16
	//敵の座標・・・x2,y2 32x32
	int dist;

	//弾は右側で判定するため、弾の横幅を追加する。
	x1 += 64;

	dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	if ( dist < 100){
		return true;
	} else {
		return false;
	}
}