#pragma once
//Enemy.h
//メソッドを実装
//Enemy・・・コンストラクタ
//update・・・毎フレームに更新する
//draw・・・描画
//setGraph・・グラフィックハンドルをセット
//speed・・・移動速度

typedef int GraphHandle;

class Enemy {
public:
	int x;
	int y;
	GraphHandle graph;
	int speed;

	Enemy();
	void update();
	void draw();
	void setGraph(GraphHandle graph);
};
