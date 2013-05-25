#include "Jitama.h"
#include "DxLib.h"

Jitama::Jitama(){
	//コンストラクタ
	//生成時に受け取った座標にセットする
	x = 0;
	y = 0;
}

void Jitama::update(){

	//右へ移動する。
	x += 10;
}

void Jitama::draw(){
	DrawGraph(x, y, graph, TRUE);
}

void Jitama::setGraph(GraphHandle graph){
	this->graph = graph;
}
