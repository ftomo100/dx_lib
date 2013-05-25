#pragma once
//Player.h
//メソッドを実装
//Player・・・コンストラクタ
//update・・・毎フレームに更新する
//draw・・・描画
//setGraph・・グラフィックハンドルをセット

typedef int GraphHandle;

class Player {
public:
	int x;
	int y;
	GraphHandle graph;

	Player();
	void update();
	void draw();
	void setGraph(GraphHandle graph);
};
