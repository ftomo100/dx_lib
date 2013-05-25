#pragma once
//Jitama.h
//自機が発射する弾を実装
//メソッドを実装
//Jitama・・・コンストラクタ
//update・・・毎フレームに更新する
//draw・・・描画
//setGraph・・グラフィックハンドルをセット

typedef int GraphHandle;

class Jitama {
public:
	int x;
	int y;
	GraphHandle graph;
	int life;

	Jitama();
	void update();
	void draw();
	void setGraph(GraphHandle graph);
};
