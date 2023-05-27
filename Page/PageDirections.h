/*
處理遊戲說明的頁面
GameStage()處理頁面流程
View()處理頁面輸出
*/
#ifndef PAGEDIRECTIONS_H
#define PAGEDIRECTIONS_H
class PageDirections : NormalPage
{
public:
	int GameStage(int game_stage)
	{
		SetWindowsSize(35, 12);
		int tem_mousex = mousex;
		int tem_mousey = mousey;
		int button_control = 0;
		int page_num = 0;
		mousey_control = 0;
		vector<string> button;
		string output[12][20];
		button.push_back("下一頁");
		button.push_back("繼續");
		button.push_back("回首頁");
		int page = 0;

		ifstream MyFile;
		MyFile.open("data/description.txt");
		if (!MyFile.is_open())
		{
			cout << "Failed to open file.\n";
			game_stage = 0;
			Sleep(3000);
			return 7;
		}
		string line;
		int i = 0;
		int j = 0;
		while (getline(MyFile, line))
		{
			if (i < 12) // 一共有12行
			{
				output[i][j] = line;
				i++;
			}
			else
			{
				i = 0;
				j++;
				output[i][j] = line; // 看有幾頁
				i++;
			}
		}
		page_num = j;
		MyFile.close();

		View(button, button_control, page, game_stage, output);
		tem_mousex = mousex;
		tem_mousey = mousey;
		while (game_stage == 1)
		{
			SetWindowsSize(35, 12);
			if (mousey != tem_mousey && mousex != tem_mousex)
			{
				mousey_control = 1;
			}
			if (mousey_control == 1)
			{
				if (mousey > 440 && mousey < 475 && button_control != 0)
				{
					button_control = 0;
					tem_mousex = mousex;
					tem_mousey = mousey;
					View(button, button_control, page, game_stage, output);
				}
				else if (mousey > 475 && mousey < 510 && button_control != 1)
				{
					button_control = 1;
					tem_mousex = mousex;
					tem_mousey = mousey;
					View(button, button_control, page, game_stage, output);
				}
				else if (mousey > 510 && mousey < 545 && button_control != 2)
				{
					button_control = 2;
					tem_mousex = mousex;
					tem_mousey = mousey;
					View(button, button_control, page, game_stage, output);
				}
			}
			if (MOUSE_Click(VK_LBUTTON))
			{
				while (MOUSE_Click(VK_LBUTTON) == 1)
				{
				}
				if (button_control == 0)
				{
					page++;
					page = page % (page_num + 1);
					button_control = 0;
					system("cls");
					View(button, button_control, page, game_stage, output);
				}
				if (button_control == 1)
				{
					return 2;
				}
				if (button_control == 2)
				{
					return 0;
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
					View(button, button_control, page, game_stage, output);
				}
				else
				{
					if ((keyin == 83 || keyin == 115 || keyin == 80) && button.size() != NULL)
					{
						button_control++;
						button_control = button_control % button.size();
						View(button, button_control, page, game_stage, output);
					}
					if ((keyin == 87 || keyin == 119 || keyin == 72) && button.size() != NULL)
					{
						button_control--;
						if (button_control < 0)
						{
							button_control = button.size() - 1;
						}
						View(button, button_control, page, game_stage, output);
					}
				}

				if (keyin == 13)
				{
					if (button_control == 0)
					{
						button_control = 0;
						mousey_control = 0;
						page++;
						page = page % (page_num + 1);
						system("cls");
						View(button, button_control, page, game_stage, output);
					}
					if (button_control == 1)
					{
						return 2;
					}
					if (button_control == 2)
					{
						return 0;
					}
				}
			}
		}
		return -1;
	}

private:
	void View(vector<string> button, int button_control, int page, int game_stage, string output[15][20])
	{
		gotoxy(0, 0);
		for (int i = 0; i < button.size(); i++) // 將資料寫入陣列中
		{
			output[8 + i][page][3] = ' ';
			for (int j = 0; j < button[i].size(); j++)
				output[i + 8][page][4 + j] = button[i][j];
		}
		if (button.size() != 0 && button_control >= 0 && button_control < button.size())
			output[button_control + 8][page][3] = '-';

		for (int i = 0; i < 12; i++) // 總輸出
		{
			if (i == 1)
			{
				SetColor(14);
			}
			else
			{
				SetColor(7);
			}
			cout << output[i][page] << endl;
		}
	}
};
#endif