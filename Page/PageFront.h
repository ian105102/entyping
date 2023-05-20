/*
�}�Y����
GameStage()�B�z�����y�{
View()�B�z������X
*/
#ifndef PAGEFRONT_H
#define PAGEFRONT_H
class PageFront : NormalPage
{
public:
	int GameStage(int gamestage)
	{
		vector<string> button;
		int button_control = -1;
		button.push_back("�}�l");
		button.push_back("����");
		button.push_back("�Ʀ�]");
		button.push_back("���}");
		View(button, button_control);
		int tem_mousex = mousex;
		int tem_mousey = mousey;
		mousey_control = 1;
		while (gamestage == 0)
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
					tem_mousex = mousex;
					tem_mousey = mousey;
					View(button, button_control);
				}
				if (mousey > 370 && mousey < 395 && button_control != 1)
				{
					button_control = 1;
					tem_mousex = mousex;
					tem_mousey = mousey;
					View(button, button_control);
				}
				if (mousey > 395 && mousey < 420 && button_control != 2)
				{
					button_control = 2;
					tem_mousex = mousex;
					tem_mousey = mousey;
					View(button, button_control);
				}
				if (mousey > 420 && mousey < 445 && button_control != 3)
				{
					button_control = 3;
					tem_mousex = mousex;
					tem_mousey = mousey;
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
		string output[10] =
			{
				{"------------------------------------"},
				{"                                   "},
				{"            �^�奴�r�m��             "},
				{"                                   "},
				{"               +-----+ +-----+     "},
				{"              /|  a  |/|  d  |     "},
				{"              ||     |||     |     "},
				{"              |/-----/|/-----/     "},
				{"              +-----+ +-----+      "},
				{"------------------------------------"},
			};
		for (int i = 0; i < button.size(); i++)
		{
			for (int j = 0; j < button[i].size(); j++)
				output[i + 4][4 + j] = button[i][j];
		}
		if (button.size() != 0 && button_control >= 0 && button_control < button.size())
			output[button_control + 4][3] = '-';
		for (int i = 0; i < 10; i++)
		{
			cout << output[i] << "\n";
		}
	}
};
#endif