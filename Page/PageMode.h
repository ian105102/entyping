/*
匡拒笴栏家Α
GameStage()矪瞶瑈祘
Print()矪瞶块
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
		int tem_mousex = mousex;
		int tem_mousey = mousey;
		int button_control = -1;
		vector<string> button;
		button.push_back("(糶)");
		button.push_back("(糶)");
		button.push_back("(ゅセ)");
		button.push_back("辅家Α");
		button.push_back("计家Α");
		button.push_back("");
		View(button, button_control);
		while (gamestage == 2)
		{
			SetWindowsSize(37, 11);

			if (mousey != tem_mousey && mousex != tem_mousex)
			{
				mousey_control = 1;
			}
			if (mousey_control == 1)
			{
				if (mousey > 345 && mousey < 370 && button_control != 0)
				{
					button_control = 0;
					View(button, button_control);
				}
				if (mousey > 370 && mousey < 395 && button_control != 1)
				{
					button_control = 1;
					View(button, button_control);
				}
				if (mousey > 395 && mousey < 420 && button_control != 2)
				{
					button_control = 2;
					View(button, button_control);
				}
				if (mousey > 420 && mousey < 445 && button_control != 3)
				{
					button_control = 3;
					View(button, button_control);
				}
				if (mousey > 445 && mousey < 475 && button_control != 4)
				{
					button_control = 4;
					View(button, button_control);
				}
				if (mousey > 475 && mousey < 500 && button_control != 5)
				{
					button_control = 5;
					View(button, button_control);
				}
			}

			if (MOUSE_Click(VK_LBUTTON))
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
				mousey_control = 0;
				tem_mousex = mousex;
				tem_mousey = mousey;
				int keyin = _getch();
				if (keyin == 83 || keyin == 115 && button.size() != NULL)
				{
					button_control++;
					button_control = button_control % button.size();
					View(button, button_control);
				}
				if (keyin == 87 || keyin == 119 && button.size() != NULL)
				{
					button_control--;
					if (button_control < 0)
					{
						button_control = button.size() - 1;
					}
					View(button, button_control);
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
		string output[11] =
		{
			{"------------------------------------"},
			{"                                    "},
			{"               笴家Α              "},
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
				output[i + 4][4 + j] = button[i][j];
		}
		if (button.size() != 0 && button_control >= 0 && button_control < button.size())
			output[button_control + 4][3] = '-';
		for (int i = 0; i < 11; i++)
		{
			cout << output[i] << "\n";
		}
		return;
	}
};
#endif 