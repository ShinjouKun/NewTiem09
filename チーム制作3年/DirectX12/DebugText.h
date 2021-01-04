#pragma once
#include<string>
#include <Windows.h>
#include"Vector2.h"
#include"TexRenderer.h"
//Debug用テキスト
class DebugText
{
public:
	DebugText();
	~DebugText();
	void Init(UINT texNum);
	void Print(const std::string& text, Vector2 pos, float size);
	void DrawALL();
private:
	static const int maxCharCount = 256;
	static const int fontWidth = 32;
	static const int fontHeight = 32;
	static const int fontLineCount = 14;
	// スプライトデータ配列の添え字番号
	int spriteIndex = 0;
	TexRenderer* debug;
	// スプライトデータの配列
	TexRenderer* spriteDatas[maxCharCount] = {};
};
