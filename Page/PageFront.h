/*
開頭頁面
GameStage()處理頁面流程
View()處理頁面輸出
*/
#ifndef PAGEFRONT_H
#define PAGEFRONT_H
class PageFront : NormalPage
{
public:
	int GameStage(int gamestage)
	{
		SetWindowsSize(35, 11);
		vector<string> button;
		int button_control = 0;
		button.push_back("開始");
		button.push_back("介紹");
		button.push_back("排行榜");
		button.push_back("離開");
		View(button, button_control);
		int tem_mousex = mousex;
		int tem_mousey = mousey;
		mousey_control = 0;
		int i = 0;
		while (gamestage == 0)
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
					if (mousey - interface_cy > 200 + (27 * i) && mousey - interface_cy < 200 + (27 * (i + 1)) && button_control != i)
					{
						button_control = i;
						tem_mousey = mousey;
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
					return 2;
				}
				if (button_control == 1)
				{
					return 1;
				}
				if (button_control == 2)
				{
					return 5;
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
						return 2;
					}
					if (button_control == 1)
					{
						return 1;
					}
					if (button_control == 2)
					{
						return 5;
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
	void View(vector<string> button, int button_control)
	{
		gotoxy(0, 0);

		string output[11] =
			{
				{"------------------------------------"},
				{"                                   "},
				{"            英文打字練習            "},
				{"                                   "},
				{"               +-----+  click!     "},
				{"              /|  a  | +-----+     "},
				{"             + |     |/|  s  |     "},
				{"             | /-----/||     |     "},
				{"             |/     / |/-----/     "},
				{"             +-----+  +-----+      "},
				{"------------------------------------"},
			};
		for (int i = 0; i < button.size(); i++)
		{
			for (int j = 0; j < button[i].size(); j++)
				output[i + 6][2 + j] = button[i][j];
		}
		if (button.size() != 0 && button_control >= 0 && button_control < button.size())
			output[button_control + 6][1] = '-';
		for (int i = 0; i < 11; i++)
		{

			for (int j = 0; j < output[i].size(); j++)
			{
				if (j > 8 && i > 3 && i < 10)
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