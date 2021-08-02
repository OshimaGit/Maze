
#include<stdio.h>
#include<time.h>

#define ROWS 25	
#define COLUMNS 25

struct Zahyo {
	int x;
	int y;
};

//���H���쐬����֐�
struct Zahyo create(int meiro[ROWS][COLUMNS], struct Zahyo dig) {
	int road = 0, wall = 1;
	int go = 0, stop = 1;
	//���ꂼ�ꉺ�E�㍶�ɓ�������ꍇ��go, ���Ȃ��ꍇ��stop
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

//vidual studio �ł�scanf���g�p�ł��Ȃ��̂�scanf_s���g�p���Ă��܂�
int main(void) {
	while (1) {
		int choice = 1;
		int road = 0, wall = 1;
		char input;
		int meiro[ROWS][COLUMNS];
		int start_time;
		struct Zahyo start, goal, dig, player_zahyo, enemy_zahyo;

		//�X�^�[�g���
		while (1) {
			//chice=1�Feasy, 2�Fdifficult, 3�Fend
			printf("��:W, ��:S, E:����\n");
			choice == 1 ? printf("��1,easy\n") : printf("  1,easy\n");
			choice == 2 ? printf("��2,difficult\n") : printf("  2,difficult\n");
			choice == 3 ? printf("��3,end\n") : printf("  3,end\n");
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

		//���H�쐬
		srand((unsigned int)time(NULL));
		do {
			//meiro�z��̏�����
			for (int i = 0; i < COLUMNS; i++) {
				for (int j = 0; j < ROWS; j++) {
					meiro[j][i] = wall;
				}
			}
			//�X�^�[�g�ʒu�̌���
			start.x = 2 * (rand() % ((ROWS - 1) / 2)) + 1;
			start.y = 2 * (rand() % ((COLUMNS - 1) / 2)) + 1;
			meiro[start.x][start.y] = road;
			player_zahyo = start;

			goal = create(meiro, start);
			//�S�[���ƃX�^�[�g���߂����Ȃ��悤�ɂ���
		} while (abs(start.x - goal.x) < 2 * ROWS / 5 || abs(start.y - goal.y) < 2 * COLUMNS / 5);


		//���H�̕��G��
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

		//���ԑ���J�n
		start_time = clock() / CLOCKS_PER_SEC;

		enemy_zahyo.x = 2 * (rand() % ((ROWS - 1) / 2)) + 1;
		enemy_zahyo.y = 2 * (rand() % ((COLUMNS - 1) / 2)) + 1;
		while (1) {
			//���H�̕\��
			for (int i = 0; i < COLUMNS; i++) {
				for (int j = 0; j < ROWS; j++) {
					switch (choice) {
					case 1:
						if (meiro[j][i] == wall)printf("��");
						else {
							if (j == player_zahyo.x && i == player_zahyo.y)printf("�o");
							else if (j == enemy_zahyo.x && i == enemy_zahyo.y)printf("�G");
							else if (j == start.x && i == start.y)printf("�r");
							else if (j == goal.x && i == goal.y)printf("�f");
							else printf("  ");
						}break;
					case 2:
						if (meiro[j][i] == wall || (abs(player_zahyo.x - j) > 2 || abs(player_zahyo.y - i) > 2)
							&& (abs(goal.x - j) > 2 || abs(goal.y - i) > 2)
							&& (abs(enemy_zahyo.x - j) > 2 || abs(enemy_zahyo.y - i) > 2))printf("��");
						else {
							if (j == player_zahyo.x && i == player_zahyo.y)printf("�o");
							else if (j == enemy_zahyo.x && i == enemy_zahyo.y)printf("�G");
							else if (j == start.x && i == start.y)printf("�r");
							else if (j == goal.x && i == goal.y)printf("�f");
							else printf("  ");
						}break;
					}
				}
				puts("");
			}

			//�������
			printf("��:W, ��:S, ��:D, ��:A, R:��߂�\n");
			scanf_s("%c", &input);
			switch (input) {
			case 'w':if (meiro[player_zahyo.x][player_zahyo.y - 1] == road)player_zahyo.y--; break;
			case 's':if (meiro[player_zahyo.x][player_zahyo.y + 1] == road)player_zahyo.y++; break;
			case 'd':if (meiro[player_zahyo.x + 1][player_zahyo.y] == road)player_zahyo.x++; break;
			case 'a':if (meiro[player_zahyo.x - 1][player_zahyo.y] == road)player_zahyo.x--; break;
			}
			if (input == 'r')break;

			//�G�̈ړ�(�G�͕ǂ�ʂ蔲������)
			do {
				switch (rand() % 4) {
				case 0:if (enemy_zahyo.y - 1 > 0)enemy_zahyo.y--; break;
				case 1:if (enemy_zahyo.y + 1 < COLUMNS - 1)enemy_zahyo.y++; break;
				case 2:if (enemy_zahyo.x + 1 < ROWS - 1)enemy_zahyo.x++; break;
				case 3:if (enemy_zahyo.x - 1 > 0)enemy_zahyo.x--; break;
				}
			} while (meiro[enemy_zahyo.x][enemy_zahyo.y] == wall);

			system("cls");

			//�G�ɓ�����ƃQ�[���I�[�o�[
			if (enemy_zahyo.x == player_zahyo.x && enemy_zahyo.y == player_zahyo.y) {
				printf("�Q�[���I�[�o�[\n");
				sleep(3);
				break;
			}

			//�S�[���ɓ��B����ƃN���A
			if (player_zahyo.x == goal.x && player_zahyo.y == goal.y) {
				printf("�N���A\n");
				printf("�N���A���ԁF%ds", clock() / CLOCKS_PER_SEC - start_time);
				sleep(3);
				break;
			}
		}
	}
}

