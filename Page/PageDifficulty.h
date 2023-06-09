/*
處理難度選擇的頁面
GameStage()處理頁面流程
View()處理頁面輸出
*/

#ifndef PAGEDIFFICULTY_H
#define PAGEDIFFICULTY_H
class PageDifficulty : NormalPage
{
public:
	int Difficulty()
	{
		return difficulty;
	}
	int GameStage(int game_stage, int mode)
	{
		SetWindowsSize(35, 11);
		int tem_mousex = mousex;
		int tem_mousey = mousey;
		int button_control = 0;
		mousey_control = 0;
		vector<string> button;
		button.push_back("0簡單");
		button.push_back("1一般");
		button.push_back("2困難");
		button.push_back("回上頁");
		View(button, button_control, mode);
		while (game_stage == 3)
		{
			SetWindowsSize(35, 11);
			if (mousey != tem_mousey && mousex != tem_mousex)
			{
				mousey_control = 1;
			}
			if (mousey_control == 1)
			{
				for (int i = 0; i < button.size(); i++)
				{
					if (mousey - interface_cy > 174 + (27 * i) && mousey - interface_cy < 174 + (27 * (i + 1)) && button_control != i)
					{
						button_control = i;
						View(button, button_control, mode);
					}
				}
			}
			if (MOUSE_Click(VK_LBUTTON) && mousey - interface_cy > 30 && mousex - interface_cx > 0 && mousex - interface_cx < 585 && mousey - interface_cy < 375)
			{
				while (MOUSE_Click(VK_LBUTTON) == 1)
				{
				}
				if (button_control == 0)
				{
					difficulty = 0;
					return 4;
				}
				if (button_control == 1)
				{
					difficulty = 1;
					return 4;
				}
				if (button_control == 2)
				{
					difficulty = 2;
					return 4;
				}
				if (button_control == 3)
				{
					return 2;
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
					View(button, button_control, mode);
				}
				else
				{
					if ((keyin == 83 || keyin == 115 || keyin == 80) && button.size() != NULL)
					{
						button_control++;
						button_control = button_control % button.size();
						View(button, button_control, mode);
					}
					if ((keyin == 87 || keyin == 119 || keyin == 72) && button.size() != NULL)
					{
						button_control--;
						if (button_control < 0)
						{
							button_control = button.size() - 1;
						}
						View(button, button_control, mode);
					}
				}

				if (keyin == 13)
				{
					if (button_control == 0)
					{
						difficulty = 0;
						return 4;
					}
					if (button_control == 1)
					{
						difficulty = 1;
						return 4;
					}
					if (button_control == 2)
					{
						difficulty = 2;
						return 4;
					}
					if (button_control == 3)
					{
						return 2;
					}
				}
			}
		}
		return -1;
	}

private:
	int difficulty = 0;
	void View(vector<string> button, int button_control, int mod)
	{
		string mode_string[] = {"一般(小寫)", "一般(大小寫)", "一般(文本)", "落下模式", "倒數模式"};
		gotoxy(0, 0);
		string output[11] =
			{
				{"------------------------------------"},
				{"                                    "},
				{"               難度選擇             "},
				{"                                    "},
				{"                                    "},
				{"                                    "},
				{"                                    "},
				{"                                    "},
				{"                                    "},
				{"                                    "},
				{"------------------------------------"},
			};
		for (int i = 0; i < button.size(); i++)
		{
			for (int j = 0; j < button[i].size(); j++)
				output[i + 5][16 + j] = button[i][j];
		}
		output[4] = {"         遊戲模式:"};
		output[4] += mode_string[mod];
		if (button.size() != 0 && button_control >= 0 && button_control < button.size())
			output[button_control + 5][15] = '-';
		for (int i = 0; i < 11; i++)
		{
			if (i == 2)
			{
				SetColor(31);
			}
			else if (i == 4)
			{
				SetColor(7);
			}
			else if (i == 5)
			{
				SetColor(10);
			}
			else if (i == 6)
			{
				SetColor(14);
			}
			else if (i == 7)
			{
				SetColor(12);
			}
			else if (i == 9)
			{
				SetColor(15);
			}
			else
			{
				SetColor(7);
			}
			cout << output[i] << "\n";
		}
		return;
	}
};
#endif