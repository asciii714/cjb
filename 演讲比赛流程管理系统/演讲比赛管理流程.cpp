#include<iostream>
#include"speechManager.h"
#include<ctime>
using namespace std;


int main() 
{
	srand((unsigned int)time(NULL));
	SpeechManager spm;
	int choice = 0;
	while (true)
	{
		spm.showMenu();
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ" << endl;
		//for (map<int , speaker> ::iterator it = spm.m_speaker.begin();it!= spm.m_speaker.end();it++)
		//{
		//	cout << it->first << it->second.M_name << endl;
		//}
		cin >> choice;
		switch (choice)
		{
		case 1:
			spm.startSpeech();
			break;
		case 2:
			spm.showRecord();
			break;
		case 3:
			spm.clearRecord();
			break;
		case 0:
			spm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}


	}
	

	system("pause");
	return 0;
}