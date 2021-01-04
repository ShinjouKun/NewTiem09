#pragma once
#include<string>
#include <Windows.h>
#include"Vector2.h"
#include"TexRenderer.h"
//Debug�p�e�L�X�g
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
	// �X�v���C�g�f�[�^�z��̓Y�����ԍ�
	int spriteIndex = 0;
	TexRenderer* debug;
	// �X�v���C�g�f�[�^�̔z��
	TexRenderer* spriteDatas[maxCharCount] = {};
};
