#pragma once
#include<string>
using namespace std;
class MatLoader
{
public:
	MatLoader();
	~MatLoader();
	void LoadMatrial(const std::string filename);//ロード
	void CreateMatrial(const std::string filename);//解析と作成
private:

};
