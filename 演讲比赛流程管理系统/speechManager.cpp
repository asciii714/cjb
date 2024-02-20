#include"speechManager.h"
#include<string>
SpeechManager::SpeechManager()
{
	this->initSpeechMember();
	this->quickSpeaker();
	this->loadRecord();
}

SpeechManager::~SpeechManager()
{
}

void SpeechManager::showMenu()
{
	cout << "*********************************" << endl;
	cout << "******欢迎参加演讲比赛***********" << endl;
	cout << "****** 1.开始演讲比赛************" << endl;
	cout << "****** 2.查看往局记录************" << endl;
	cout << "****** 3.清空比赛记录************" << endl;
	cout << "****** 0.退出比赛程序************" << endl;
	cout << "*********************************" << endl;
	cout << endl;

}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeechMember()
{
	this->v1.clear();
	this->v2.clear();
	this->Victory.clear();
	this->m_speaker.clear();
	this->m_index = 1;
	this->m_Record.clear();
	this->fileIsEmpty = true;
}

void SpeechManager::quickSpeaker()
{
	string nameseed = "ABCDEFGHIJKL";
	
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name = "选手";
		name += nameseed[i];
		speaker sp;
		sp.M_name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.M_score[j] = 0;
		}
		this->v1.push_back(i + 1001);
		this->m_speaker.insert(make_pair(i + 1001, sp));
	}

	
}

void SpeechManager::startSpeech()
{
	//抽签 比赛 显示结果
	this->speechDraw();
	this->speechContest();
	this->showScore();
	this->m_index++;
	this->speechDraw();
	this->speechContest();
	this->showScore();
	this->saveRecord();
	this->initSpeechMember();
	this->quickSpeaker();
	this->loadRecord();
	cout << "比赛完美结束" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "第" << this->m_index << "轮的选手正在抽签" << endl;
	cout << "------------------------------------------------" << endl;
	cout << "抽签顺序如下" << endl;
	if (this->m_index == 1) 
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it  = v1.begin();it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "--------------------------------------" << endl;
	system("pause");
	cout << endl;

}

void SpeechManager::speechContest()
{
	cout << "第" << this->m_index << "轮比赛正式开始" << endl;
	multimap<double, int, greater<double>> GroupScores;
	int num = 0;
	vector<int> v_src;
	if (this->m_index == 1) {
		v_src = v1;
	}
	else
	{
		v_src = v2;
	}
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		deque<double> d;//评委打分
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
			/*cout << score << " ";*/

		}
		/*	cout << endl;*/
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		this->m_speaker[*it].M_score[this->m_index - 1] = avg;
		GroupScores.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次： " << endl;
			for (multimap<double, int, greater<double>>::iterator it = GroupScores.begin(); it != GroupScores.end(); it++)
			{
				cout << "编号" << it->second << "\t" << "姓名" << this->m_speaker[it->second].M_name << "\t" << "成绩" << this->m_speaker[it->second].M_score[this->m_index - 1] << endl;
			}
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = GroupScores.begin(); it != GroupScores.end() && count < 3; it++, count++)
			{
				if (this->m_index == 1)
				{
					this->v2.push_back((*it).second);
				}
				else
				{
					this->Victory.push_back((*it).second);
				}
			}
			cout << endl;
			GroupScores.clear();
		}
	}
	cout << "-------------------" << "第" << this->m_index << "轮比赛完毕----------------" << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "----------第" << this->m_index << "轮晋级选手信息如下" << endl;
	vector<int> v;
	if (this->m_index == 1) 
	{
		v = v2;
	}
	else
	{
		v = Victory;
	}
	for (vector<int>::iterator it = v.begin();it != v.end();it++)
	{
		cout << "编号： " << *it << "\t" << "姓名： " << this->m_speaker[*it].M_name << "\t"<<"得分: "<<this->m_speaker[*it].M_score[this->m_index - 1]<<endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = this->Victory.begin();it!=this->Victory.end(); it++)
	{
		ofs << *it << "," << this->m_speaker[*it].M_score[1] << ",";
	}
	ofs << endl;
	cout << "记录已保存" << endl;
	this->fileIsEmpty = false;
	ofs.close();
}

void SpeechManager::loadRecord()
{
	ifstream ifs;
	ifs.open("speech.csv", ios::in );
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	vector<string> v;
	int index = 0;
	while (ifs >> data) {
		/*cout << data << endl;*/
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty == true) 
	{
		cout << "文件为不存在或者文件不存在" << endl;

	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届"
				<< "冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
				<< "亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
				<< "季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;

		}
	}
	
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "是否清空文件" << endl;
	cout << "1,是" << endl;
	cout << "2,否" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initSpeechMember();
		this->quickSpeaker();
		this->loadRecord();
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");

}
