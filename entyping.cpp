// 字體大小:28 將視窗的快速編輯模式關掉
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <fstream>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

#include "Page/NormalPage.h"
#include "Page/PageFront.h"
#include "Page/PageDirections.h"
#include "Page/PageMode.h"
#include "Page/PageDifficulty.h"
#include "Page/PageGameNormal.h"
#include "Page/PageGameCountdown.h"
#include "Page/PageGameFall.h"
#include "Page/Pagescoring.h"

int main()
{
	PageFront First;
	PageDirections Second;
	PageMode Third;
	PageDifficulty Fourth;
	Pagescoring Sixth;
	PageGameNormal FifthNormal;
	PageGameFall FifthFall;
	PageGameCountdown FifthCountdown;
	int game_end = 1;
	int mode = 0;
	int gmae_difficulty = 1;
	int Score = 0;
	bool score_mode = false;
	int game_stage = 0;
	srand(time(NULL));

	while (game_end)
	{
		system("CLS");
		switch (game_stage)
		{
		case 0:
			PlaySound(TEXT("musics/ghostfight.wav"), NULL, SND_ASYNC | SND_LOOP);
			game_stage = First.GameStage(game_stage);
			break;
		case 1:
			game_stage = Second.GameStage(game_stage);
			break;
		case 2:
			game_stage = Third.GameStage(game_stage);
			mode = Third.Mode();
			break;
		case 3:
			game_stage = Fourth.GameStage(game_stage, mode);
			gmae_difficulty = Fourth.Difficulty();
			break;
		case 4:
			score_mode = 1;
			if (mode == 0 || mode == 1 || mode == 2)
			{
				game_stage = FifthNormal.GameStage(game_stage, gmae_difficulty, mode);
				Score = FifthNormal.GameNormalScore();
			}
			if (mode == 3)
			{
				game_stage = FifthFall.GameStage(game_stage, gmae_difficulty);
				Score = FifthFall.GameFallScore();
			}
			if (mode == 4)
			{
				game_stage = FifthCountdown.GameStage();
				Score = FifthCountdown.GameCountdownScore();
			}
			break;
		case 5:
			game_stage = Sixth.GameStage(game_stage, Score, mode, gmae_difficulty, score_mode);
			score_mode = 0;
			break;
		default:
			game_end = 0;
			break;
		}
	}
	return 0;
}
