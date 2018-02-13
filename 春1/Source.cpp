#include <DxLib.h>
#include "Mino.h"

#define SCREEN_W 800
#define SCREEN_H 600
#define STAGE_X 10
#define STAGE_Y (20+4)
#define MASS_SIZE 20

int stage[STAGE_Y][STAGE_X];
int type = 0;
int rotate = 0;
int move = 0;
float pos = 0;
float speed = 6.f / 60.f;


int WINAPI WinMain(HINSTANCE, HINSTANCE , LPSTR, int)
{
	SetGraphMode(SCREEN_W, SCREEN_H, 32);   //ウィンドウサイズを設定
	ChangeWindowMode(TRUE);                 //ウィンドウモードに切り替え
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);


	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE)) {
		{
			static int prev_rotete_key = 0;
			const int rotete_key = CheckHitKey(KEY_INPUT_RIGHT) - CheckHitKey(KEY_INPUT_LEFT);
			if (prev_rotete_key != rotete_key) {
				prev_rotete_key = rotete_key;

				rotate += rotete_key;
				if (rotate >= 4) {
					rotate = 0;
				}
				else if (rotate < 0) {
					rotate = 3;
				}
			}
		}
		for (int i = 0; i < 7; ++i) {
			if (CheckHitKey(KEY_INPUT_1 + i)) {
				type = i;
			}
		}
		int movelimit = 0;
		int move_key = CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A);
		if (movelimit != move_key) {
			movelimit = move_key; 




		}

		DrawBox(
			0, 0,
			MASS_SIZE * STAGE_X, 
			MASS_SIZE * STAGE_Y,
			0x00ff00,
			FALSE
		);

		for (int y = 0; y < 4; ++y) {
			for (int x = 0; x < 4; ++x) {

				if (mino_template[type][rotate].block[y][x] != 0) {
					DrawBox(
						(move +x) * MASS_SIZE,
						((int)pos + y) * MASS_SIZE,
						(move + x + 1) * MASS_SIZE,
						((int)pos + y + 1) * MASS_SIZE,
						0x00ff00,
						TRUE
					);
				}
			}
		}

		if (pos < STAGE_Y) {
			pos += speed;
		}

		ScreenFlip();
		ClearDrawScreen();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}