/*
最後分數選單的頁面
GameStage()處理頁面流程
View()處理頁面輸出
OutRankFile(vector<ranklist> rank)  處理寫檔
InputRankFile()   處理讀檔
*/
#ifndef PAGESCORING_H
#define PAGESCORING_H
class Pagescoring : NormalPage
{
public:
	int GameStage(int game_stage, int player_score, int player_mode, int gmae_difficulty, bool score_mode)
	{
		SetWindowsSize(35, 12);
		vector<ranklist> rank = InputRankFile();
		vector<string> button;
		button.push_back("上一項");
		button.push_back("下一項");
		button.push_back("回主頁");

		int tem_mousex = mousex;
		int tem_mousey = mousey;
		int button_control = 0;
		mousey_control = 0;
		int next = 0;
		int rank_sit = 0;
		string player_rank_name = "\0";
		ranklist temrank = {
			0,
			"\0",
			"\0",
		};
		temrank.score = player_score;
		if (score_mode) // 處理排名資料
		{
			button.push_back("離開");
			View(button, next, button_control, rank_sit, rank, temrank);
			PlaySound(TEXT("musics/ghostfight.wav"), NULL, SND_ASYNC | SND_LOOP);
			switch (player_mode)
			{
			case 0:
				temrank.mode = ("小寫" + to_string(gmae_difficulty));
				break;
			case 1:
				temrank.mode = ("大小寫" + to_string(gmae_difficulty));
				break;
			case 2:
				temrank.mode = ("文本" + to_string(gmae_difficulty));
				break;
			case 3:
				temrank.mode = ("落下" + to_string(gmae_difficulty));
				break;
			case 4:
				temrank.mode = ("倒數");
				break;
			default:
				temrank.mode = "???";
				break;
			}
			do
			{
				cout << "輸入名稱: ";
				getline(cin, temrank.name);
				if (temrank.name.size() > 9)
				{
					cout << "最多九個字" << endl;
					temrank.name = "\0";
					continue;
				}
				for (int i = 0; i < temrank.name.size(); i++)
				{
					if ((temrank.name[i] < 'a' || temrank.name[i] > 'z') && (temrank.name[i] < 'A' || temrank.name[i] > 'Z') && (temrank.name[i] < '0' || temrank.name[i] > '9') && temrank.name[i] != '?' && temrank.name[i] != '.')
					{
						temrank.name = "\0";
						cout << "只能英文數字，只開放?和.特殊符號" << endl;
						break;
					}
				}
				for (int i = 0; i < rank.size(); i++)
				{
					if (rank[i].name == temrank.name)
					{
						temrank.name = "\0";
						cout << "姓名重複" << endl;
					}
				}
			} while (temrank.name == "\0");
			int i = 0;
			while (i < rank.size() && player_score <= rank[i].score)
			{
				SetWindowsSize(35, 12);
				i++;
			}
			rank.insert(rank.begin() + i, temrank);
			rank_sit = i + 1;
			OutRankFile(rank);

			int music_time = clock();
			PlaySound(TEXT("musics/score.wav"), NULL, SND_ASYNC);
			while (clock() - music_time < 5000)
			{
				if ((clock() - music_time) % 30 == 0)
				{
					PageMove(450 + (rand() % (5 + (clock() - music_time) / 100)) - (5 + (clock() - music_time) / 100) / 2, 200 + (rand() % (5 + (clock() - music_time) / 100)) - (5 + (clock() - music_time) / 100) / 2);
				}
			}
			SetWindowsSize(35, 12);
			system("cls");
			if (rank_sit - 1 < 6)
			{
				next = 0;
			}
			else if (rank_sit + 5 > rank.size())
			{
				next = rank.size() - 6;
			}
			else
			{
				next = rank_sit - 1;
			}

			View(button, next, button_control, rank_sit, rank, temrank);
			music_time = clock();
			PlaySound(TEXT("musics/win.wav"), NULL, SND_ASYNC);
			while (clock() - music_time < 5000)
			{ // 修正停止時依然可以累計輸入的問題
				if (_kbhit())
				{
					_getch();
				}
			}
			PlaySound(TEXT("musics/ghostfight.wav"), NULL, SND_ASYNC | SND_LOOP);
		}
		View(button, next, button_control, rank_sit, rank, temrank);
		while (game_stage == 5)
		{
			SetWindowsSize(35, 12);
			if (mousey != tem_mousey && mousex != tem_mousex)
			{
				mousey_control = 1;
			}
			if (mousey_control == 1)
			{
				if (mousey > 430 && mousey < 455 && button_control != 0)
				{
					button_control = 0;
					View(button, next, button_control, rank_sit, rank, temrank);
				}
				if (mousey > 455 && mousey < 480 && button_control != 1)
				{
					button_control = 1;
					View(button, next, button_control, rank_sit, rank, temrank);
				}
				if (mousey > 480 && mousey < 505 && button_control != 2)
				{
					button_control = 2;
					View(button, next, button_control, rank_sit, rank, temrank);
				}
				if (mousey > 505 && mousey < 530 && button_control != 3)
				{
					button_control = 3;
					View(button, next, button_control, rank_sit, rank, temrank);
				}
			}
			if (MOUSE_Click(VK_LBUTTON))
			{
				while (MOUSE_Click(VK_LBUTTON) == 1)
				{
				}
				if (button_control == 0)
				{
					if (next >= 1)
					{
						next--;
						View(button, next, button_control, rank_sit, rank, temrank);
					}
				}
				if (button_control == 1)
				{
					if (next < int(rank.size()) - 6)
					{
						next++;
						View(button, next, button_control, rank_sit, rank, temrank);
					}
				}
				if (button_control == 2)
				{
					return 0;
				}
				if (button_control == 3)
				{
					return 6;
				}
			}

			if (_kbhit())
			{
				int keyin = _getch();
				if (keyin == 224)
				{
					keyin = _getch();
				}
				mousey_control = 0;
				tem_mousex = mousex;
				tem_mousey = mousey;
				if (button_control == -1 && keyin != 13)
				{
					button_control = 0;
					View(button, next, button_control, rank_sit, rank, temrank);
				}
				else
				{
					if ((keyin == 83 || keyin == 115 || keyin == 80) && button.size() != NULL)
					{
						button_control++;
						button_control = button_control % button.size();
						View(button, next, button_control, rank_sit, rank, temrank);
					}
					if ((keyin == 87 || keyin == 119 || keyin == 72) && button.size() != NULL)
					{
						button_control--;
						if (button_control < 0)
						{
							button_control = button.size() - 1;
						}
						View(button, next, button_control, rank_sit, rank, temrank);
					}
				}
				if (keyin == 13)
				{
					if (button_control == 0)
					{
						if (next >= 1)
						{
							next--;
							View(button, next, button_control, rank_sit, rank, temrank);
						}
					}
					if (button_control == 1)
					{
						if (next < int(rank.size()) - 6)
						{
							next++;
							View(button, next, button_control, rank_sit, rank, temrank);
						}
					}
					if (button_control == 2)
					{
						return 0;
					}
					if (button_control == 3)
					{
						return 6;
					}
				}
			}
		}
		return 0;
	}

private:
	struct ranklist
	{
		int score;
		string name;
		string mode;
	};
	vector<ranklist> InputRankFile()
	{
		vector<ranklist> rank;
		fstream RankFilein;
		RankFilein.open("sav/rank.sav", ios::in);
		int r1 = 0;
		string s1 = "\0", s2 = "\0";
		while (RankFilein >> r1 >> s1 >> s2)
		{
			rank.push_back({r1, s1, s2});
		}
		RankFilein.close();
		return rank;
	}
	void OutRankFile(vector<ranklist> rank)
	{
		fstream RankFileout;
		RankFileout.open("sav/rank.sav", ios::out | ios::ate);
		for (int i = 0; i < rank.size(); i++)
		{
			RankFileout << rank[i].score << " " << rank[i].name << " " << rank[i].mode << endl;
		}
		RankFileout.close();
	}

	void View(vector<string> button, int next, int button_control, int rank_sit, vector<ranklist> rank, ranklist temrank)
	{
		gotoxy(0, 0);
		string output[12]{
			{"------------------------------------"},
			{"                                    "},
			{"               排行榜                "},
			{"                                    "},
			{"        排名 分數 模式難度 名稱       "},
			{"                                    "},
			{"                                    "},
			{"                                    "},
			{"                                    "},
			{"                                    "},
			{"                                    "},
			{"------------------------------------"},
		};
		for (int i = 0; i < button.size(); i++) // 按鈕寫入string
		{
			for (int j = 0; j < button[i].size(); j++)
				output[i + 7][1 + j] = button[i][j];
		}
		if (button.size() != 0 && button_control >= 0 && button_control < button.size())
			output[button_control + 7][0] = '-';
		if (temrank.name != "\0") // 玩家排名寫入string
		{
			string s = "你的分數:";
			s += to_string(temrank.score);
			s += "排名:";
			s += to_string(rank_sit);
			for (int i = 0; i < s.size(); i++)
			{
				output[3][8 + i] = s[i];
			}
		}
		for (int i = 1; i <= min(int(rank.size()), 6); i++) // 排名資料寫入string
		{

			for (int j = 0; j < to_string(i + next).size(); j++)
			{
				output[i + 4][8 + j] = to_string(i + next)[j];
				output[i + 4][9 + j] = ',';
			}
			for (int j = 0; j < to_string(rank[i - 1 + next].score).size(); j++)
			{
				output[i + 4][13 + j] = to_string(rank[i - 1 + next].score)[j];
			}
			for (int j = 0; j < rank[i - 1 + next].mode.size(); j++)
			{
				output[i + 4][18 + j] = rank[i - 1 + next].mode[j];
			}
			for (int j = 0; j < rank[i - 1 + next].name.size(); j++)
			{
				output[i + 4][27 + j] = rank[i - 1 + next].name[j];
			}
		}

		for (int i = 0; i < 12; i++) // 輸出
		{
			for (int j = 0; j < output[i].size(); j++)
			{
				if (i == 4 && j > 7 && j < 36)
				{
					SetColor(112);
				}
				else if (i == 2)
				{
					SetColor(31);
				}
				else if (i == 3 && temrank.name != "\0")
				{
					SetColor(9);
				}
				else if (5 == i + next && j > 7 && i > 4 && i < 11 && rank.size() > 0)
				{
					SetColor(236);
				}
				else if (6 == i + next && j > 7 && i > 4 && i < 11 && rank.size() > 1)
				{
					SetColor(156);
				}
				else if (7 == i + next && j > 7 && i > 4 && i < 11 && rank.size() > 2)
				{
					SetColor(172);
				}
				else if (rank_sit + 4 == i + next && j > 7 && i > 4 && i < 11)
				{
					SetColor(9);
				}
				else
				{
					SetColor(7);
				}
				cout << output[i][j];
			}
			cout << endl;
		}
	}
};
#endif