/*
選擇遊戲模式的頁面
GameStage()處理頁面流程
Print()處理頁面輸出
*/
#ifndef PAGEMODE_H
#define PAGEMODE_H
class PageMode : NormalPage
{
public:
	int Mode()
	{
		return mode;
	}
	int GameStage(int gamestage)
	{
		SetWindowsSize(35, 11);
		int tem_mousex = mousex;
		int tem_mousey = mousey;
		int button_control = 0;
		mousey_control = 0;
		vector<string> button;
		button.push_back("一般(小寫)");
		button.push_back("一般(大小寫)");
		button.push_back("一般(文本)");
		button.push_back("落下模式");
		button.push_back("倒數模式");
		button.push_back("回首頁");
		View(button, button_control);
		while (gamestage == 2)
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
					if (mousey - interface_cy > 145 + (27 * i) && mousey - interface_cy < 145 + (27 * (i + 1)) && button_control != i)
					{
						button_control = i;
						View(button, button_control);
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
					mode = 0;
					return 3;
				}
				if (button_control == 1)
				{
					mode = 1;
					return 3;
				}
				if (button_control == 2)
				{
					mode = 2;
					return 3;
				}
				if (button_control == 3)
				{
					mode = 3;
					return 3;
				}
				if (button_control == 4)
				{
					mode = 4;
					return 4;
				}
				if (button_control == 5)
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
					View(button, button_control);
				}
				else
				{
					if ((keyin == 83 || keyin == 115 || keyin == 80) && button.size() != NULL)
					{
						button_control++;
						button_control = button_control % button.size();
						View(button, button_control);
					}
					if ((keyin == 87 || keyin == 119 || keyin == 72) && button.size() != NULL)
					{
						button_control--;
						if (button_control < 0)
						{
							button_control = button.size() - 1;
						}
						View(button, button_control);
					}
				}

				if (keyin == 13)
				{
					if (button_control == 0)
					{
						mode = 0;
						return 3;
					}
					if (button_control == 1)
					{
						mode = 1;
						return 3;
					}
					if (button_control == 2)
					{
						mode = 2;
						return 3;
					}
					if (button_control == 3)
					{
						mode = 3;
						return 3;
					}
					if (button_control == 4)
					{
						mode = 4;
						return 4;
					}
					if (button_control == 5)
					{
						return 0;
					}
				}
			}
		}
		return -1;
	}

private:
	int mode = 0;
	void View(vector<string> button, int button_control)
	{
		gotoxy(0, 0);
		string output[11] = // 初始值
			{
				{"------------------------------------"},
				{"                                    "},
				{"               遊玩模式             "},
				{"                                    "},
				{"              ┌────────────────────┐"},
				{"              │               ▓    │"},
				{"              │  ▓ ▓   ▓▓   ▓▓▓ ▓▓▓│"},
				{"              │ ▓ ▓ ▓ ▓  ▓ ▓  ▓ ▓-┘│"},
				{"              │ ▓ ▓ ▓  ▓▓   ▓▓▓ ▓▓▓│"},
				{"              └────────────────────┘"},
				{"------------------------------------"},
			};
		for (int i = 0; i < button.size(); i++)
		{
			for (int j = 0; j < button[i].size(); j++)
				output[i + 4][2 + j] = button[i][j];
		}
		if (button.size() != 0 && button_control >= 0 && button_control < button.size())
			output[button_control + 4][1] = '-';
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < output[i].size(); j++)
			{
				if (j > 14 && i > 3 && i < 10)
				{
					if (button_control == 0)
					{
						SetColor(9);
					}
					if (button_control == 1)
					{
						SetColor(10);
					}
					if (button_control == 2)
					{
						SetColor(11);
					}
					if (button_control == 3)
					{
						SetColor(12);
					}
					if (button_control == 4)
					{
						SetColor(13);
					}
					if (button_control == 5)
					{
						SetColor(7);
					}
				}
				else if (i == 2)
				{
					SetColor(31);
				}
				else
				{
					SetColor(7);
				}
				cout << output[i][j];
			}
			cout << endl;
		}

		return;
	}
};
#endif