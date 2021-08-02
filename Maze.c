
#include<stdio.h>
#include<time.h>

#define ROWS 25	
#define COLUMNS 25

struct Zahyo {
	int x;
	int y;
};

//迷路を作成する関数
struct Zahyo create(int meiro[ROWS][COLUMNS], struct Zahyo dig) {
	int road = 0, wall = 1;
	int go = 0, stop = 1;
	//それぞれ下右上左に道を作れる場合はgo, 作れない場合はstop
	int isDir[4] = { go,go,go,go };
	while (1) {

		int dir = rand() % 4;

		switch (dir) {
		case 0:
			if (dig.y - 2 < 0) {
				isDir[0] = stop;
			}
			else if (meiro[dig.x][dig.y - 2] == road) {
				isDir[0] = stop;
			}
			else {
				meiro[dig.x][--dig.y] = road;
				meiro[dig.x][--dig.y] = road;
				int isDir[4] = { go,go,go,go };
			}
			break;
		case 1:
			if (dig.x + 2 > ROWS - 1) {
				isDir[1] = stop;
			}
			else if (meiro[dig.x + 2][dig.y] == road) {
				isDir[1] = stop;
			}
			else {
				meiro[++dig.x][dig.y] = road;
				meiro[++dig.x][dig.y] = road;
				int isDir[4] = { go,go,go,go };
			}
			break;
		case 2:
			if (dig.y + 2 > COLUMNS - 1) {
				isDir[2] = stop;
			}
			else if (meiro[dig.x][dig.y + 2] == road) {
				isDir[2] = stop;
			}
			else {
				meiro[dig.x][++dig.y] = road;
				meiro[dig.x][++dig.y] = road;
				int isDir[4] = { go,go,go,go };
			}
			break;
		case 3:
			if (dig.x - 2 < 0) {
				isDir[3] = stop;
			}
			else if (meiro[dig.x - 2][dig.y] == road) {
				isDir[3] = stop;
			}
			else {
				meiro[--dig.x][dig.y] = road;
				meiro[--dig.x][dig.y] = road;
				int isDir[4] = { go,go,go,go };
			}
			break;
		}
		if (isDir[0] == stop && isDir[1] == stop && isDir[2] == stop && isDir[3] == stop) {
			return(dig);
		}
	}
}

void sleep(int second) {
	int now = second * CLOCKS_PER_SEC + clock();

	while (now > clock());
}

//vidual studio ではscanfが使用できないのでscanf_sを使用しています
int main(void) {
	while (1) {
		int choice = 1;
		int road = 0, wall = 1;
		char input;
		int meiro[ROWS][COLUMNS];
		int start_time;
		struct Zahyo start, goal, dig, player_zahyo, enemy_zahyo;

		//スタート画面
		while (1) {
			//chice=1：easy, 2：difficult, 3：end
			printf("↑:W, ↓:S, E:決定\n");
			choice == 1 ? printf("○1,easy\n") : printf("  1,easy\n");
			choice == 2 ? printf("○2,difficult\n") : printf("  2,difficult\n");
			choice == 3 ? printf("○3,end\n") : printf("  3,end\n");
			scanf_s("%c", &input);
			if (input == 'w') {
				if (choice > 1)choice--;
			}
			else if (input == 's') {
				if (choice < 3)choice++;
			}
			else if (input == 'e') {
				system("cls");
				break;
			}
			system("cls");
		}

		if (choice == 3)return(0);

		//迷路作成
		srand((unsigned int)time(NULL));
		do {
			//meiro配列の初期化
			for (int i = 0; i < COLUMNS; i++) {
				for (int j = 0; j < ROWS; j++) {
					meiro[j][i] = wall;
				}
			}
			//スタート位置の決定
			start.x = 2 * (rand() % ((ROWS - 1) / 2)) + 1;
			start.y = 2 * (rand() % ((COLUMNS - 1) / 2)) + 1;
			meiro[start.x][start.y] = road;
			player_zahyo = start;

			goal = create(meiro, start);
			//ゴールとスタートが近すぎないようにする
		} while (abs(start.x - goal.x) < 2 * ROWS / 5 || abs(start.y - goal.y) < 2 * COLUMNS / 5);


		//迷路の複雑化
		for (int k = 0; k < 3; k++) {
			for (int i = 0; i < COLUMNS; i++) {
				for (int j = 0; j < ROWS; j++) {
					if (meiro[j][i] == road && j % 2 == 1 && i % 2 == 1) {
						dig.x = j;
						dig.y = i;
						create(meiro, dig);
					}
				}
			}
		}

		//時間測定開始
		start_time = clock() / CLOCKS_PER_SEC;

		enemy_zahyo.x = 2 * (rand() % ((ROWS - 1) / 2)) + 1;
		enemy_zahyo.y = 2 * (rand() % ((COLUMNS - 1) / 2)) + 1;
		while (1) {
			//迷路の表示
			for (int i = 0; i < COLUMNS; i++) {
				for (int j = 0; j < ROWS; j++) {
					switch (choice) {
					case 1:
						if (meiro[j][i] == wall)printf("■");
						else {
							if (j == player_zahyo.x && i == player_zahyo.y)printf("Ｐ");
							else if (j == enemy_zahyo.x && i == enemy_zahyo.y)printf("敵");
							else if (j == start.x && i == start.y)printf("Ｓ");
							else if (j == goal.x && i == goal.y)printf("Ｇ");
							else printf("  ");
						}break;
					case 2:
						if (meiro[j][i] == wall || (abs(player_zahyo.x - j) > 2 || abs(player_zahyo.y - i) > 2)
							&& (abs(goal.x - j) > 2 || abs(goal.y - i) > 2)
							&& (abs(enemy_zahyo.x - j) > 2 || abs(enemy_zahyo.y - i) > 2))printf("■");
						else {
							if (j == player_zahyo.x && i == player_zahyo.y)printf("Ｐ");
							else if (j == enemy_zahyo.x && i == enemy_zahyo.y)printf("敵");
							else if (j == start.x && i == start.y)printf("Ｓ");
							else if (j == goal.x && i == goal.y)printf("Ｇ");
							else printf("  ");
						}break;
					}
				}
				puts("");
			}

			//操作入力
			printf("↑:W, ↓:S, →:D, ←:A, R:やめる\n");
			scanf_s("%c", &input);
			switch (input) {
			case 'w':if (meiro[player_zahyo.x][player_zahyo.y - 1] == road)player_zahyo.y--; break;
			case 's':if (meiro[player_zahyo.x][player_zahyo.y + 1] == road)player_zahyo.y++; break;
			case 'd':if (meiro[player_zahyo.x + 1][player_zahyo.y] == road)player_zahyo.x++; break;
			case 'a':if (meiro[player_zahyo.x - 1][player_zahyo.y] == road)player_zahyo.x--; break;
			}
			if (input == 'r')break;

			//敵の移動(敵は壁を通り抜けられる)
			do {
				switch (rand() % 4) {
				case 0:if (enemy_zahyo.y - 1 > 0)enemy_zahyo.y--; break;
				case 1:if (enemy_zahyo.y + 1 < COLUMNS - 1)enemy_zahyo.y++; break;
				case 2:if (enemy_zahyo.x + 1 < ROWS - 1)enemy_zahyo.x++; break;
				case 3:if (enemy_zahyo.x - 1 > 0)enemy_zahyo.x--; break;
				}
			} while (meiro[enemy_zahyo.x][enemy_zahyo.y] == wall);

			system("cls");

			//敵に当たるとゲームオーバー
			if (enemy_zahyo.x == player_zahyo.x && enemy_zahyo.y == player_zahyo.y) {
				printf("ゲームオーバー\n");
				sleep(3);
				break;
			}

			//ゴールに到達するとクリア
			if (player_zahyo.x == goal.x && player_zahyo.y == goal.y) {
				printf("クリア\n");
				printf("クリア時間：%ds", clock() / CLOCKS_PER_SEC - start_time);
				sleep(3);
				break;
			}
		}
	}
}

