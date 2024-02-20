#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
#include<random>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<fstream>
using namespace std;

class SpeechManager
{
public:
	SpeechManager();
	~SpeechManager();
	void showMenu();
	void exitSystem();
	void initSpeechMember();
	void quickSpeaker();
	void startSpeech();
	void speechDraw();
	void speechContest();
	void showScore();
	void saveRecord();
	void loadRecord();
	void showRecord();
	void clearRecord();
	vector<int> v1;
	vector<int> v2;
	vector<int> Victory;
	map <int, speaker> m_speaker;
	int m_index;
	bool fileIsEmpty;
	map<int, vector<string>> m_Record;
private:

};

