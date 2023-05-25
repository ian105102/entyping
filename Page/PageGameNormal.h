/*
一般模式遊戲的頁面
GameStage()處理頁面流程
Print()處理頁面輸出
Stop(int sleep) 處理暫停
ImportTopic() 將題目讀出來
GameScore() 用於計分
Cheack(char ch) 判斷打的是否正確
Print()處理輸出
*/
#ifndef PAGEGAMENORMAL_H
#define PAGEGAMENORMAL_H
class PageGameNormal : NormalPage
{
public:
	int GameNormalScore()
	{
		return gamenormal_score;
	}
	int GameStage(int game_stage, int gmae_difficultys, int game_mod)
	{
		int keyin = 0;
		difficultys = gmae_difficultys;
		gamenormal_score = 0;
		start_time = clock();
		if (!ImportTopic())
		{
			return 0;
		}
		int sleep = 0;
		int timeresit = 0;
		if (game_stage == 4)
		{
			for (frequency = 1; frequency <= 4 + difficultys; frequency++)
			{
				if (gamenormal_score < -950 || gamenormal_score > 950)
				{
					break;
				}
				system("cls");
				question = "\0";
				compare = "\0";
				player_keyin = "\0";
				for (int i = 0; i < 30; i++)
				{
					if (game_mod == 0)
						question += topic0[rand() % topic0.size()];
					if (game_mod == 1)
						question += topic1[rand() % topic1.size()];
					if (game_mod == 2)
						break;
				}
				if (game_mod == 2)
				{
					int randnum = rand() % topic2.size();
					question = topic2[randnum];
					topic2.erase(topic2.begin() + randnum);
				}
				Print();
				while (keyin != 13)
				{
					SetWindowsSize(37, 10);
					Print();
					int clocktime = clock();
					while (clock() - clocktime <= 500 && keyin != 13) // 0.5秒後刷新螢幕
					{
						if (_kbhit()) // 如果輸入
						{
							keyin = _getch();
							if (keyin == 27)
							{
								sleep = 1;
							}
							else if (keyin != 13)
							{
								Cheack(keyin);
							}
							if (sleep == 1)
							{
								if (Stop(sleep))
								{
									return 0;
								}
							}

							sleep = 0;
							clocktime = clock();
						}
					}
				}
				keyin = 0; // 完成一次輸入計分
				GameScore();
			}
		}
		gamenormal_score -= ((clock() - start_time) / 3000); // 扣出時間
		return 5;
	}

private:
	int gamenormal_score = 0;
	int frequency = 0;
	int start_time = 0;
	int difficultys = 0;
	int mouse_pointer = 0;
	vector<char> topic0 = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};
	vector<char> topic1 = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};
	vector<string> topic2 = {};
	string player_keyin = "\0";
	string question = "\0";
	string compare = "\0";
	int ImportTopic()
	{
		ifstream MyFile;
		MyFile.open("data/topic2.txt");
		if (!MyFile.is_open())
		{
			cout << "Failed to open file.\n";
			Sleep(3000);
			return 0;
		}
		string line;
		int n = 0;
		topic2.clear();
		while (getline(MyFile, line))
		{
			if (line.size() < 30)
			{
				topic2.push_back(line);
				n++;
			}
		}
		if (n <= 6)
		{
			cout << "Not enough text\n";
			Sleep(3000);
			return 0;
		}
		return 1;
		MyFile.close();
	}
	int Stop(int sleep)
	{
		int timeresit = clock();
		system("cls");
		SetColor(9);
		cout << "------------------------------------" << endl;
		cout << "                                    " << endl;
		cout << "                                    " << endl;
		cout << "                stop                " << endl;
		cout << "         再按一次ESC可以繼續!         " << endl;
		cout << "        按Backspace可以回首頁        " << endl;
		cout << "score: " << gamenormal_score - ((clock() - start_time) / 3000) << "  time: " << (clock() - start_time) / 1000 << endl;
		cout << "------------------------------------" << endl;
		SetColor(7);
		while (sleep == 1)
		{
			int ch = _getch();
			if (ch == 27)
			{
				sleep = 0;
				start_time += (clock() - timeresit);
				system("CLS");
				Print();
				return 0;
			}
			if (ch == 8)
			{
				sleep = 0;
				start_time += (clock() - timeresit);
				system("CLS");
				return 1;
			}
		}
	}
	void GameScore()
	{
		for (int i = 0; i < int(compare.size()); i++)
		{
			if (compare[i] == 'v')
			{
				gamenormal_score++;
			}
			if (compare[i] == 'x')
			{
				gamenormal_score--;
			}
		}
		gamenormal_score = gamenormal_score - (question.size() - compare.size());
	}
	void Cheack(char ch)
	{

		if (ch == 8 && player_keyin.size() >= 1)
		{

			player_keyin.pop_back();
		}
		if (ch != 8 && player_keyin.size() < int(question.size()))
		{
			player_keyin += ch;
		}
		compare = "\0";
		for (int i = 0; i < int(player_keyin.size()); i++)
		{
			if (question[i] == player_keyin[i])
			{
				compare += 'v';
			}
			else
			{
				compare += 'x';
			}
		}
		Print();
		if (player_keyin.size() >= 1 && question[player_keyin.size() - 1] != ch && player_keyin.size() != question.size() && ch != 8)
		{
			PageShake();
		}
	}
	void Print()
	{
		system("cls");
		gotoxy(0, 0);
		cout << "------------------------------------" << endl;
		cout << frequency << "/" << 4 + difficultys << endl;
		cout << "  ";
		for (int i = 0; i < compare.size(); i++)
		{
			if (compare[i] == 'v')
			{
				SetColor(2);
			}
			if (compare[i] == 'x')
			{
				SetColor(0xC);
			}
			cout << compare[i];
		}
		cout << "  " << endl;
		SetColor(7);

		cout << "=>";
		for (int i = 0; i < question.size(); i++)
		{
			if (i < compare.size() && compare[i] == 'v')
			{
				SetColor(2);
			}
			if (i < compare.size() && compare[i] == 'x')
			{
				SetColor(0xC);
			}
			if (i >= compare.size())
			{
				SetColor(7);
			}
			cout << question[i];
		}
		SetColor(7);
		cout << " \n"
			 << endl;
		cout << "=>";
		SetColor(240);

		if (mouse_pointer == 1)
		{
			cout << player_keyin << "|";
			mouse_pointer = 0;
		}

		else
		{
			cout << player_keyin << " ";
			mouse_pointer = 1;
		}
		for (int i = 0; i < question.size() - player_keyin.size(); i++)
			cout << ' ';
		cout << endl;
		SetColor(7);
		cout << "score: " << gamenormal_score - ((clock() - start_time) / 3000) << "  time: " << (clock() - start_time) / 1000 << endl;
		cout << "------------------------------------" << endl;
	}
};
#endif