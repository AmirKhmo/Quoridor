#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
//when player1 should enter sth , Board's color will be yellow
//when player2 should enter sth , Board's color will be blue
//when they should enter sth that related to both of them, Board's color will be white

#define edge '|'
#define space ' '
#define wall '#'
#define Player1 'A'
#define Player2 'B'

char board[100][100];


void clearScrean(){
	system("cls");
}


void setTextColor(int textColor, int backColor) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}


void sleep(unsigned int mseconds) {
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

int makeRandom() {
    return rand() % 2; // تصمیم تصادفی برای حرکت (0) یا قرار دادن دیوار (1)
}

int makeRandomMove() {
    return rand() % 4 + 1; // تصمیم تصادفی برای انتخاب یکی از 4 خانه مجاور
}

void Board(char walls[][100],int k,int x,int y,int a,int b){ // board preparation
	int i,j;
	for(i=0 ; i<k ; i++){
		for(j=0 ; j<k ; j++){
			if (i==x && j==y) board[i][j]=Player1;
			else if(i==a && j==b) board[i][j]=Player2;
			else if(walls[i][j]==wall) board[i][j]=wall;
			else if(walls[i][j]==edge) board[i][j]=edge;
			else if(i==0 || i==k-1 || j==0 || j==k-1) board[i][j]=edge;
			else if(i%2==0) board[i][j]=edge;
			else if(j%2==0) board[i][j]=edge;
			else board[i][j]=space;
		}
	}
}


char BoardPrint(int k){
	int i,j,r=1,t=1;
		for(i=0 ; i<=k ; i++){
			for(j=0 ; j<=k ; j++){
				if (j==k&&i%2==1&&i!=k) {
					printf("%d",r);
					r++;
				}
				else if(i==k&&j%2==0&&j<k-1&&j>18){
					printf("%d",t);
					t++;
				} 
				else if(i==k&&j%2==0&&j<k-1){
					printf(" %d",t);
					t++;
				}
				else printf("%c",board[i][j]);
			}
			printf("\n");
		}
}

int check[100][100];//this global array checkes every part of the board and use it in DFS

int DFS(int c,int d,char walls[][100],int k,int x,int y,int a,int b,int p){// this function tells us that we are allowed to build a wall in a certain location or not
	if(p==1){//It checkes whether we are allowed to construct a vertical wall that does not obstruct 'B' or not.
		int c1=0,c2=0,c3=0;
		if(walls[c][d]==wall)c1=1;
		if(walls[c+1][d]==wall)c2=1;
		if(walls[c+2][d]==wall)c3=1;
		walls[c][d]=wall;
		walls[c+1][d]=wall;
		walls[c+2][d]=wall;
		Board(walls,k,x,y,a,b);
 		int i,j,s=0;
		i=1;
		for(j=1;j<k;j+=2){
			if(a==i&&b==j) s=1;
		}
		check[a][b]=1;
		if(s==0&&a>2  &&board[a-1][b]!=wall&&check[a-2][b]!=1)  s=DFS(c,d,walls,k,x,y,a-2,b,1);
		if(s==0&&a<k-2&&board[a+1][b]!=wall&&check[a+2][b]!=1)  s=DFS(c,d,walls,k,x,y,a+2,b,1);
		if(s==0&&b<k-2&&board[a][b+1]!=wall&&check[a][b+2]!=1)  s=DFS(c,d,walls,k,x,y,a,b+2,1);
		if(s==0&&b>2  &&board[a][b-1]!=wall&&check[a][b-2]!=1)  s=DFS(c,d,walls,k,x,y,a,b-2,1);
		if(c1==0)walls[c][d]=edge;
		if(c2==0)walls[c+1][d]=edge;
		if(c3==0)walls[c+2][d]=edge;
		return s;
	}
	else if(p==2){//It checkes whether we are allowed to construct a horizontal wall that does not obstruct 'B' or not.
		int c1=0,c2=0,c3=0;
		if(walls[c][d]==wall)c1=1;
		if(walls[c][d+1]==wall)c2=1;
		if(walls[c][d+2]==wall)c3=1;
		walls[c][d]=wall;
		walls[c][d+1]=wall;
		walls[c][d+2]=wall;
		Board(walls,k,x,y,a,b);
		int i,j,s=0;
		i=1;
		for(j=1;j<k;j+=2){
			if(a==i&&b==j) s=1;
		}
		check[a][b]=1;
		if(s==0&&a>2  &&board[a-1][b]!=wall&&check[a-2][b]!=1)  s=DFS(c,d,walls,k,x,y,a-2,b,2);
		if(s==0&&a<k-2&&board[a+1][b]!=wall&&check[a+2][b]!=1)  s=DFS(c,d,walls,k,x,y,a+2,b,2);
		if(s==0&&b<k-2&&board[a][b+1]!=wall&&check[a][b+2]!=1)  s=DFS(c,d,walls,k,x,y,a,b+2,2);
		if(s==0&&b>2  &&board[a][b-1]!=wall&&check[a][b-2]!=1)  s=DFS(c,d,walls,k,x,y,a,b-2,2);
		if(c1==0)walls[c][d]=edge;
		if(c2==0)walls[c][d+1]=edge;
		if(c3==0)walls[c][d+2]=edge;
		return s;
	}
	else if(p==3){//It checkes whether we are allowed to construct a vertical wall that does not obstruct 'A' or not.
		int c1=0,c2=0,c3=0;
		if(walls[c][d]==wall)c1=1;
		if(walls[c+1][d]==wall)c2=1;
		if(walls[c+2][d]==wall)c3=1;
		walls[c][d]=wall;
		walls[c+1][d]=wall;
		walls[c+2][d]=wall;
		Board(walls,k,x,y,a,b);
		int i,j,s=0;
		i=k-2;
		for(j=1;j<k;j+=2){
			if(x==i&&y==j) s=1;
		}
		check[x][y]=1;
		if(s==0&&x>2  &&board[x-1][y]!=wall&&check[x-2][y]!=1)  s=DFS(c,d,walls,k,x-2,y,a,b,3);
		if(s==0&&x<k-2&&board[x+1][y]!=wall&&check[x+2][y]!=1)  s=DFS(c,d,walls,k,x+2,y,a,b,3);
		if(s==0&&y<k-2&&board[x][y+1]!=wall&&check[x][y+2]!=1)  s=DFS(c,d,walls,k,x,y+2,a,b,3);
		if(s==0&&y>2  &&board[x][y-1]!=wall&&check[x][y-2]!=1)  s=DFS(c,d,walls,k,x,y-2,a,b,3);
		if(c1==0)walls[c][d]=edge;
		if(c2==0)walls[c+1][d]=edge;
		if(c3==0)walls[c+2][d]=edge;
		return s;
	}
	else if(p==4){//It checkes whether we are allowed to construct a horizontal wall that does not obstruct 'A' or not.
		int c1=0,c2=0,c3=0;
		if(walls[c][d]==wall)c1=1;
		if(walls[c][d+1]==wall)c2=1;
		if(walls[c][d+2]==wall)c3=1;
		walls[c][d]=wall;
		walls[c][d+1]=wall;
		walls[c][d+2]=wall;
		Board(walls,k,x,y,a,b);
		int i,j,s=0;
		i=k-2;
		for(j=1;j<k;j+=2){
			if(x==i&&y==j) s=1;
		}
		check[x][y]=1;
		if(s==0&&x>2  &&board[x-1][y]!=wall&&check[x-2][y]!=1)  s=DFS(c,d,walls,k,x-2,y,a,b,4);
		if(s==0&&x<k-2&&board[x+1][y]!=wall&&check[x+2][y]!=1)  s=DFS(c,d,walls,k,x+2,y,a,b,4);
		if(s==0&&y<k-2&&board[x][y+1]!=wall&&check[x][y+2]!=1)  s=DFS(c,d,walls,k,x,y+2,a,b,4);
		if(s==0&&y>2  &&board[x][y-1]!=wall&&check[x][y-2]!=1)  s=DFS(c,d,walls,k,x,y-2,a,b,4);
		if(c1==0)walls[c][d]=edge;
		if(c2==0)walls[c][d+1]=edge;
		if(c3==0)walls[c][d+2]=edge;
		return s;
	}
}
typedef struct {
    char name[20];
    int position;
} Player;
typedef struct {
    char board[100][100];
} GameBoard;
typedef struct {
    Player players[2];
    GameBoard board;
} Game;
// Function to save the game state
void saveGame(Game game) {
    FILE *file;
    file = fopen("saved_game.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving game!\n");
        exit(1);
    }
    fprintf(file, "%s %d %s %d\n", game.players[0].name, game.players[0].position, game.players[1].name, game.players[1].position);
    // Save the game board
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            fprintf(file, "%c ", game.board.board[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Game saved successfully!\n");
}
// Function to load the game state
Game loadGame() {
    FILE *file;
    Game game;
    file = fopen("saved_game.txt", "r");
    if (file == NULL) {
        printf("No saved game found!\n");
        exit(1);
    }
    fscanf(file, "%s %d %s %d", game.players[0].name, &game.players[0].position, game.players[1].name, &game.players[1].position);
    // Load the game board
    for (int i = 0; i < 100 ;i++) {
        for (int j = 0; j < 100; j++) {
            fscanf(file, " %c", &game.board.board[i][j]);
            printf("%c ", game.board.board[i][j]);
        }
    }
    fclose(file);
    printf("Game loaded successfully!\n");
    return game;
}

int main () {
    int n, k;
    int i, j;
    int h, v;//h&v are two variavbles which scan every wall's coordinates
    int p, q;
    int ascii, sw = 0;//if player chose to build wall , sw will change to 1
    int x, y, a, b;// Variables that  show coordinates of player1 and player2's character
    int xx, yy, aa, bb;//copy of original variables
    int wallCount, wallCount1, wallCount2;//count of the walls for each player
    int e, t;
    char player1[30], player2[30], Bug[30];//each player's nickname
    char walls[100][100];// an array to put # as wall and match it with board
    char wallDirection;// vertical or horizontal
    char wallcount[20], nn[20], hh[20], vv[20];
    int playWithComputer;
    int continuegame;
    int continuegamec;
    FILE *file;
    Game game;
    Game currentGame;

    printf("Do you want to continue last game(1 for Yes,0 for No)");
    scanf("%d", &continuegame);
    if (continuegame) {
        Game loadedGame = loadGame();
        printf("Do you want continue with computer(1 for Yes,0 for No)");
        scanf("%d",&continuegamec);
        if(continuegamec) {
            do {//game started , Until someone reaches the other side, this loop will repeat
                do {//player1's next move...
                    xx = x, yy = y;
                    clearScrean();
                    sleep(400);
                    setTextColor(6, 0);
                    printf("<< %s >>\n", player1);// board's printing
                    printf("Remained walls: %d\n\n", wallCount1);
                    Board(walls, k, x, y, a, b);
                    BoardPrint(k);
                    printf("\nRemained walls: %d\n", wallCount2);
                    printf("<< %s >>\n", player2);// end of board's printing
                    printf("\n %s  if you want to build a wall enter any button\n else move 'A' character...! ",
                           player1);//asking the player1's next move...
                    printf("%c", getch());
                    ascii = getch();//scanning the player1's next move...
                    if (ascii == 80 && a == xx + 2 && yy == b && board[a + 1][b] != wall)
                        xx += 4;// ASCII code of up & down & left & right button
                    else if (ascii == 80) xx += 2;
                    else if (ascii == 75 && b == yy - 2 && xx == a && board[a][b - 1] != wall) yy -= 4;
                    else if (ascii == 75) yy -= 2;
                    else if (ascii == 77 && b == yy + 2 && xx == a && board[a][b + 1] != wall) yy += 4;
                    else if (ascii == 77) yy += 2;
                    else if (ascii == 72 && a == xx - 2 && yy == b && board[a - 1][b] != wall) xx -= 4;
                    else if (ascii == 72) xx -= 2;
                    else {//player chose to build a wall
                        if (wallCount1 > 0) {
                            do {
                                sw = 1;
                                clearScrean();
                                sleep(200);
                                setTextColor(6, 0);
                                printf("<< %s >>\n", player1);// board's printing
                                printf("Remained walls: %d\n\n", wallCount1);
                                Board(walls, k, x, y, a, b);
                                BoardPrint(k);
                                printf("\nRemained walls: %d\n", wallCount2);
                                printf("<< %s >>\n", player2);// end of board's printing
                                printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
                                scanf("%c", &wallDirection);
                                clearScrean();
                            } while (wallDirection != 'H' && wallDirection != 'V' && wallDirection != 'v' &&
                                     wallDirection !=
                                     'h');// we use do...while because wallDirection should be just one of these characters

                            if (wallDirection == 'v' || wallDirection == 'V') {
                                do {
                                    do {
                                        setTextColor(6, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        printf("\nEnter the wall's coordinates : ");
                                        scanf("%s", hh);
                                        scanf("%s", vv);
                                        h = 0, v = 0;
                                        for (i = 0; hh[i]; i++) {
                                            h = h * 10 + (hh[i] - 48);
                                        }
                                        for (i = 0; vv[i]; i++) {
                                            v = v * 10 + (vv[i] - 48);
                                        }
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 3);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 1) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h - 1;
                                v = 2 * v;
                                walls[h][v] = wall;
                                walls[h + 1][v] = wall;
                                walls[h + 2][v] = wall;
                                wallCount1--;
                            }

                            if (wallDirection == 'h' || wallDirection == 'H') {
                                do {
                                    do {
                                        setTextColor(6, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        printf("\nEnter the wall's coordinates : ");
                                        scanf("%s", hh);
                                        scanf("%s", vv);
                                        h = 0, v = 0;
                                        for (i = 0; hh[i]; i++) {
                                            h = h * 10 + (hh[i] - 48);
                                        }
                                        for (i = 0; vv[i]; i++) {
                                            v = v * 10 + (vv[i] - 48);
                                        }
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 4);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 2) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h;
                                v = 2 * v - 1;
                                walls[h][v] = wall;
                                walls[h][v + 1] = wall;
                                walls[h][v + 2] = wall;
                                wallCount1--;
                            }
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                        } else {
                            clearScrean();
                            sleep(400);
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                            printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
                            scanf("%d", &p);
                        }
                    }
                } while ((board[xx][yy] != space || board[(x + xx) / 2][(yy + y) / 2] == wall) && sw == 0);
                sw = 0;
                x = xx, y = yy;
                if (x == k - 2) break;
                saveGame(currentGame);

                int computer = makeRandom();
                do {//computer next move
                    aa = a, bb = b;
                    clearScrean();
                    sleep(400);
                    setTextColor(11, 0);
                    printf("<< %s >>\n", player1);// board's printing
                    printf("Remained walls: %d\n\n", wallCount1);
                    Board(walls, k, x, y, a, b);
                    BoardPrint(k);
                    printf("\nRemained walls: %d\n", wallCount2);
                    printf("<< %s >>\n", player2);// end of board's printing
                    if (computer == 0) {
                        srand(time(0)); // تنظیم seed تابع تصادفی بر اساس زمان فعلی
                        int move = makeRandomMove();
                        if (move == 1 && x == aa + 2 && bb == y)
                            aa += 4;// ASCII code of up & down & left & right button
                        else if (move == 1) aa += 2;
                        else if (move == 2 && bb == y - 2 && aa == x) bb -= 4;
                        else if (move == 2) bb -= 2;
                        else if (move == 3 && y == bb + 2 && x == aa) bb += 4;
                        else if (move == 3) bb += 2;
                        else if (move == 4 && x == aa - 2 && y == bb) aa -= 4;
                        else if (move == 4) aa -= 2;
                    } else {//player chose to build a wall
                        if (wallCount2 > 0) {
                            do {
                                sw = 1;
                                clearScrean();
                                setTextColor(11, 0);
                                sleep(200);
                                printf("<< %s >>\n", player1);// board's printing
                                printf("Remained walls: %d\n\n", wallCount1);
                                Board(walls, k, x, y, a, b);
                                BoardPrint(k);
                                printf("\nRemained walls: %d\n", wallCount2);
                                printf("<< %s >>\n", player2);// end of board's printing
                                int orientation = rand() % 2; // انتخاب تصادفی جهت افقی یا عمودی
                                if (orientation == 1) {
                                    wallDirection = 'H';
                                }
                                if (orientation == 0) {
                                    wallDirection = 'V';
                                }
                                clearScrean();
                            } while (wallDirection != 'H' && wallDirection != 'V' && wallDirection != 'v' &&
                                     wallDirection !=
                                     'h');// we use do...while because wallDirection should be just one of these characters

                            if (wallDirection == 'v' || wallDirection == 'V') {
                                do {
                                    do {
                                        setTextColor(11, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        int row = rand() % 9 + 1; // انتخاب تصادفی یک سطر
                                        int clown = rand() % 9 + 1;
                                        h = row;
                                        v = clown;
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 3);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 1) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h - 1;
                                v = 2 * v;
                                walls[h][v] = wall;
                                walls[h + 1][v] = wall;
                                walls[h + 2][v] = wall;
                                wallCount2--;
                            }

                            if (wallDirection == 'h' || wallDirection == 'H') {
                                do {
                                    do {
                                        setTextColor(11, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        int row = rand() % 9 + 1; // انتخاب تصادفی یک سطر
                                        int clown = rand() % 9 + 1;
                                        h = row;
                                        v = clown;
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 4);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 2) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h;
                                v = 2 * v - 1;
                                walls[h][v] = wall;
                                walls[h][v + 1] = wall;
                                walls[h][v + 2] = wall;
                                wallCount2--;
                            }
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                        } else {
                            clearScrean();
                            sleep(400);
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                            printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
                            scanf("%d", &p);
                        }
                    }
                } while ((board[aa][bb] != space || board[(a + aa) / 2][(bb + b) / 2] == wall) && sw == 0);
                sw = 0;
                a = aa, b = bb;
                saveGame(currentGame);
            }
            else{
            do {//game started , Until someone reaches the other side, this loop will repeat
                    do {//player1's next move...
                        xx = x, yy = y;
                        clearScrean();
                        sleep(400);
                        setTextColor(6, 0);
                        printf("<< %s >>\n", player1);// board's printing
                        printf("Remained walls: %d\n\n", wallCount1);
                        Board(walls, k, x, y, a, b);
                        BoardPrint(k);
                        printf("\nRemained walls: %d\n", wallCount2);
                        printf("<< %s >>\n", player2);// end of board's printing
                        printf("\n %s  if you want to build a wall enter any button\n else move 'A' character...! ",
                               player1);//asking the player1's next move...
                        printf("%c", getch());
                        ascii = getch();//scanning the player1's next move...
                        if (ascii == 80 && a == xx + 2 && yy == b && board[a + 1][b] != wall)
                            xx += 4;// ASCII code of up & down & left & right button
                        else if (ascii == 80) xx += 2;
                        else if (ascii == 75 && b == yy - 2 && xx == a && board[a][b - 1] != wall) yy -= 4;
                        else if (ascii == 75) yy -= 2;
                        else if (ascii == 77 && b == yy + 2 && xx == a && board[a][b + 1] != wall) yy += 4;
                        else if (ascii == 77) yy += 2;
                        else if (ascii == 72 && a == xx - 2 && yy == b && board[a - 1][b] != wall) xx -= 4;
                        else if (ascii == 72) xx -= 2;
                        else {//player chose to build a wall
                            if (wallCount1 > 0) {
                                do {
                                    sw = 1;
                                    clearScrean();
                                    sleep(200);
                                    setTextColor(6, 0);
                                    printf("<< %s >>\n", player1);// board's printing
                                    printf("Remained walls: %d\n\n", wallCount1);
                                    Board(walls, k, x, y, a, b);
                                    BoardPrint(k);
                                    printf("\nRemained walls: %d\n", wallCount2);
                                    printf("<< %s >>\n", player2);// end of board's printing
                                    printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
                                    scanf("%c", &wallDirection);
                                    clearScrean();
                                } while (wallDirection != 'H' && wallDirection != 'V' && wallDirection != 'v' &&
                                         wallDirection !=
                                         'h');// we use do...while because wallDirection should be just one of these characters

                                if (wallDirection == 'v' || wallDirection == 'V') {
                                    do {
                                        do {
                                            setTextColor(6, 0);
                                            printf("<< %s >>\n", player1);// board's printing
                                            printf("Remained walls: %d\n\n", wallCount1);
                                            Board(walls, k, x, y, a, b);
                                            BoardPrint(k);
                                            printf("\nRemained walls: %d\n", wallCount2);
                                            printf("<< %s >>\n", player2);// end of board's printing
                                            printf("\nEnter the wall's coordinates : ");
                                            scanf("%s", hh);
                                            scanf("%s", vv);
                                            h = 0, v = 0;
                                            for (i = 0; hh[i]; i++) {
                                                h = h * 10 + (hh[i] - 48);
                                            }
                                            for (i = 0; vv[i]; i++) {
                                                v = v * 10 + (vv[i] - 48);
                                            }
                                            clearScrean();
                                        } while (h < 1 || h >= n || v < 1 || v >= n);
                                        for (e = 0; e < 100; e++) {
                                            for (t = 0; t < 100; t++) {
                                                check[e][t] = 0;
                                            }
                                        }
                                        q = DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 3);
                                        Board(walls, k, x, y, a, b);
                                        clearScrean();
                                        for (e = 0; e < 100; e++) {
                                            for (t = 0; t < 100; t++) {
                                                check[e][t] = 0;
                                            }
                                        }
                                    } while (DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 1) != 1 || q !=
                                                                                                    1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                    h = 2 * h - 1;
                                    v = 2 * v;
                                    walls[h][v] = wall;
                                    walls[h + 1][v] = wall;
                                    walls[h + 2][v] = wall;
                                    wallCount1--;
                                }

                                if (wallDirection == 'h' || wallDirection == 'H') {
                                    do {
                                        do {
                                            setTextColor(6, 0);
                                            printf("<< %s >>\n", player1);// board's printing
                                            printf("Remained walls: %d\n\n", wallCount1);
                                            Board(walls, k, x, y, a, b);
                                            BoardPrint(k);
                                            printf("\nRemained walls: %d\n", wallCount2);
                                            printf("<< %s >>\n", player2);// end of board's printing
                                            printf("\nEnter the wall's coordinates : ");
                                            scanf("%s", hh);
                                            scanf("%s", vv);
                                            h = 0, v = 0;
                                            for (i = 0; hh[i]; i++) {
                                                h = h * 10 + (hh[i] - 48);
                                            }
                                            for (i = 0; vv[i]; i++) {
                                                v = v * 10 + (vv[i] - 48);
                                            }
                                            clearScrean();
                                        } while (h < 1 || h >= n || v < 1 || v >= n);
                                        for (e = 0; e < 100; e++) {
                                            for (t = 0; t < 100; t++) {
                                                check[e][t] = 0;
                                            }
                                        }
                                        q = DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 4);
                                        Board(walls, k, x, y, a, b);
                                        clearScrean();
                                        for (e = 0; e < 100; e++) {
                                            for (t = 0; t < 100; t++) {
                                                check[e][t] = 0;
                                            }
                                        }
                                    } while (DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 2) != 1 || q !=
                                                                                                    1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                    h = 2 * h;
                                    v = 2 * v - 1;
                                    walls[h][v] = wall;
                                    walls[h][v + 1] = wall;
                                    walls[h][v + 2] = wall;
                                    wallCount1--;
                                }
                                printf("<< %s >>\n", player1);// board's printing
                                printf("Remained walls: %d\n\n", wallCount1);
                                Board(walls, k, x, y, a, b);
                                BoardPrint(k);
                                printf("\nRemained walls: %d\n", wallCount2);
                                printf("<< %s >>\n", player2);// end of board's printing
                            } else {
                                clearScrean();
                                sleep(400);
                                printf("<< %s >>\n", player1);// board's printing
                                printf("Remained walls: %d\n\n", wallCount1);
                                Board(walls, k, x, y, a, b);
                                BoardPrint(k);
                                printf("\nRemained walls: %d\n", wallCount2);
                                printf("<< %s >>\n", player2);// end of board's printing
                                printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
                                scanf("%d", &p);
                            }
                        }
                    } while ((board[xx][yy] != space || board[(x + xx) / 2][(yy + y) / 2] == wall) && sw == 0);
                    sw = 0;
                    x = xx, y = yy;
                    if (x == k - 2) break;
                    saveGame(currentGame);

                    do {//player2's next move...
                        aa = a, bb = b;
                        clearScrean();
                        sleep(400);
                        setTextColor(11, 0);
                        printf("<< %s >>\n", player1);// board's printing
                        printf("Remained walls: %d\n\n", wallCount1);
                        Board(walls, k, x, y, a, b);
                        BoardPrint(k);
                        printf("\nRemained walls: %d\n", wallCount2);
                        printf("<< %s >>\n", player2);// end of board's printing
                        printf("\n %s if you want to build a wall enter any button\n else move 'B' character...! ",
                               player2);//asking the player1's next move...
                        printf("%c", getch());
                        ascii = getch();//scanning the player2's next move...
                        if (ascii == 80 && x == aa + 2 && bb == y) aa += 4;// ASCII code of up & down & left & right button
                        else if (ascii == 80) aa += 2;
                        else if (ascii == 75 && bb == y - 2 && aa == x) bb -= 4;
                        else if (ascii == 75) bb -= 2;
                        else if (ascii == 77 && y == bb + 2 && x == aa) bb += 4;
                        else if (ascii == 77) bb += 2;
                        else if (ascii == 72 && x == aa - 2 && y == bb) aa -= 4;
                        else if (ascii == 72) aa -= 2;
                        else {//player chose to build a wall
                            if (wallCount2 > 0) {
                                do {
                                    sw = 1;
                                    clearScrean();
                                    setTextColor(11, 0);
                                    sleep(200);
                                    printf("<< %s >>\n", player1);// board's printing
                                    printf("Remained walls: %d\n\n", wallCount1);
                                    Board(walls, k, x, y, a, b);
                                    BoardPrint(k);
                                    printf("\nRemained walls: %d\n", wallCount2);
                                    printf("<< %s >>\n", player2);// end of board's printing
                                    printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
                                    scanf("%c", &wallDirection);
                                    clearScrean();
                                } while (wallDirection != 'H' && wallDirection != 'V' && wallDirection != 'v' &&
                                         wallDirection !=
                                         'h');// we use do...while because wallDirection should be just one of these characters

                                if (wallDirection == 'v' || wallDirection == 'V') {
                                    do {
                                        do {
                                            setTextColor(11, 0);
                                            printf("<< %s >>\n", player1);// board's printing
                                            printf("Remained walls: %d\n\n", wallCount1);
                                            Board(walls, k, x, y, a, b);
                                            BoardPrint(k);
                                            printf("\nRemained walls: %d\n", wallCount2);
                                            printf("<< %s >>\n", player2);// end of board's printing
                                            printf("\nEnter the wall's coordinates : ");
                                            scanf("%s", hh);
                                            scanf("%s", vv);
                                            h = 0, v = 0;
                                            for (i = 0; hh[i]; i++) {
                                                h = h * 10 + (hh[i] - 48);
                                            }
                                            for (i = 0; vv[i]; i++) {
                                                v = v * 10 + (vv[i] - 48);
                                            }
                                            clearScrean();
                                        } while (h < 1 || h >= n || v < 1 || v >= n);
                                        for (e = 0; e < 100; e++) {
                                            for (t = 0; t < 100; t++) {
                                                check[e][t] = 0;
                                            }
                                        }
                                        q = DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 3);
                                        Board(walls, k, x, y, a, b);
                                        clearScrean();
                                        for (e = 0; e < 100; e++) {
                                            for (t = 0; t < 100; t++) {
                                                check[e][t] = 0;
                                            }
                                        }
                                    } while (DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 1) != 1 || q !=
                                                                                                    1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                    h = 2 * h - 1;
                                    v = 2 * v;
                                    walls[h][v] = wall;
                                    walls[h + 1][v] = wall;
                                    walls[h + 2][v] = wall;
                                    wallCount2--;
                                }

                                if (wallDirection == 'h' || wallDirection == 'H') {
                                    do {
                                        do {
                                            setTextColor(11, 0);
                                            printf("<< %s >>\n", player1);// board's printing
                                            printf("Remained walls: %d\n\n", wallCount1);
                                            Board(walls, k, x, y, a, b);
                                            BoardPrint(k);
                                            printf("\nRemained walls: %d\n", wallCount2);
                                            printf("<< %s >>\n", player2);// end of board's printing
                                            printf("\nEnter the wall's coordinates : ");
                                            scanf("%s", hh);
                                            scanf("%s", vv);
                                            h = 0, v = 0;
                                            for (i = 0; hh[i]; i++) {
                                                h = h * 10 + (hh[i] - 48);
                                            }
                                            for (i = 0; vv[i]; i++) {
                                                v = v * 10 + (vv[i] - 48);
                                            }
                                            clearScrean();
                                        } while (h < 1 || h >= n || v < 1 || v >= n);
                                        for (e = 0; e < 100; e++) {
                                            for (t = 0; t < 100; t++) {
                                                check[e][t] = 0;
                                            }
                                        }
                                        q = DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 4);
                                        Board(walls, k, x, y, a, b);
                                        clearScrean();
                                        for (e = 0; e < 100; e++) {
                                            for (t = 0; t < 100; t++) {
                                                check[e][t] = 0;
                                            }
                                        }
                                    } while (DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 2) != 1 || q !=
                                                                                                    1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                    h = 2 * h;
                                    v = 2 * v - 1;
                                    walls[h][v] = wall;
                                    walls[h][v + 1] = wall;
                                    walls[h][v + 2] = wall;
                                    wallCount2--;
                                }
                                printf("<< %s >>\n", player1);// board's printing
                                printf("Remained walls: %d\n\n", wallCount1);
                                Board(walls, k, x, y, a, b);
                                BoardPrint(k);
                                printf("\nRemained walls: %d\n", wallCount2);
                                printf("<< %s >>\n", player2);// end of board's printing
                            } else {
                                clearScrean();
                                sleep(400);
                                printf("<< %s >>\n", player1);// board's printing
                                printf("Remained walls: %d\n\n", wallCount1);
                                Board(walls, k, x, y, a, b);
                                BoardPrint(k);
                                printf("\nRemained walls: %d\n", wallCount2);
                                printf("<< %s >>\n", player2);// end of board's printing
                                printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
                                scanf("%d", &p);
                            }
                        }
                    } while ((board[aa][bb] != space || board[(a + aa) / 2][(bb + b) / 2] == wall) && sw == 0);
                    sw = 0;
                    a = aa, b = bb;
                } while (a != 1 && x != k - 2);
                saveGame(currentGame);
        }
        }else {
        printf("Do you want play with computer(1 for Yes,0 for No )");
        scanf("%d", &playWithComputer);
        if (playWithComputer) {
            // بازی با کامپیوتر
            do {//receive 'n' as dimention of the board which will be n*n
                sleep(500);
                printf("Please enter dimension of the board : ");
                scanf("%s", nn);
                n = 0;
                for (i = 0; nn[i]; i++) {
                    n = n * 10 + (nn[i] - 48);
                }
                clearScrean();
            } while (n < 4 || n > 25);
            k = 2 * n + 1;

            if (n % 2 == 0) { x = 1, y = n - 1; }// determining where should player 1&2's characters locate
            else { x = 1, y = n; }
            if (n % 2 == 0) { a = k - 2, b = n - 1; }
            else { a = k - 2, b = n; }

            //when player1 should enter sth , Board's color will be yellow
            //when player2 should enter sth , Board's color will be blue

            //scanning the nickname of player1
            sleep(400);
            setTextColor(6, 0);
            gets(Bug);
            printf("<< player1 >> \n");// board's printing
            printf("Remained walls: \n\n");
            Board(walls, k, x, y, a, b);
            BoardPrint(k);
            printf("\nRemained walls: \n");
            printf("<< player2 >> \n");// end of board's printing
            printf("\nPlayer1...! enter a nickname for yourself : ");
            gets(player1);
            clearScrean();


            do {//scanning the number of their walls
                wallCount = 0;
                clearScrean();
                sleep(400);
                setTextColor(15, 0);
                printf("<< %s >>\n", player1);// board's printing
                printf("Remained walls: \n\n");
                Board(walls, k, x, y, a, b);
                BoardPrint(k);
                printf("\nRemained walls: \n");
                printf("<< %s >>\n", player2);// end of board's printing
                printf("\nHow many walls would you like to have? ");
                scanf("%s", wallcount);
                wallCount = 0;
                for (i = 0; wallcount[i]; i++) {
                    wallCount = wallCount * 10 + (wallcount[i] - 48);
                }
                wallCount1 = wallCount;
                wallCount2 = wallCount;
                clearScrean();
            } while (wallCount >=n * n / 4);// we use do...while because wallCount for each player shouldn't be more than n*n/4


            do {//game started , Until someone reaches the other side, this loop will repeat
                do {//player1's next move...
                    xx = x, yy = y;
                    clearScrean();
                    sleep(400);
                    setTextColor(6, 0);
                    printf("<< %s >>\n", player1);// board's printing
                    printf("Remained walls: %d\n\n", wallCount1);
                    Board(walls, k, x, y, a, b);
                    BoardPrint(k);
                    printf("\nRemained walls: %d\n", wallCount2);
                    printf("<< %s >>\n", player2);// end of board's printing
                    printf("\n %s  if you want to build a wall enter any button\n else move 'A' character...! ",
                           player1);//asking the player1's next move...
                    printf("%c", getch());
                    ascii = getch();//scanning the player1's next move...
                    if (ascii == 80 && a == xx + 2 && yy == b && board[a + 1][b] != wall)
                        xx += 4;// ASCII code of up & down & left & right button
                    else if (ascii == 80) xx += 2;
                    else if (ascii == 75 && b == yy - 2 && xx == a && board[a][b - 1] != wall) yy -= 4;
                    else if (ascii == 75) yy -= 2;
                    else if (ascii == 77 && b == yy + 2 && xx == a && board[a][b + 1] != wall) yy += 4;
                    else if (ascii == 77) yy += 2;
                    else if (ascii == 72 && a == xx - 2 && yy == b && board[a - 1][b] != wall) xx -= 4;
                    else if (ascii == 72) xx -= 2;
                    else {//player chose to build a wall
                        if (wallCount1 > 0) {
                            do {
                                sw = 1;
                                clearScrean();
                                sleep(200);
                                setTextColor(6, 0);
                                printf("<< %s >>\n", player1);// board's printing
                                printf("Remained walls: %d\n\n", wallCount1);
                                Board(walls, k, x, y, a, b);
                                BoardPrint(k);
                                printf("\nRemained walls: %d\n", wallCount2);
                                printf("<< %s >>\n", player2);// end of board's printing
                                printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
                                scanf("%c", &wallDirection);
                                clearScrean();
                            } while (wallDirection != 'H' && wallDirection != 'V' && wallDirection != 'v' &&
                                     wallDirection !=
                                     'h');// we use do...while because wallDirection should be just one of these characters

                            if (wallDirection == 'v' || wallDirection == 'V') {
                                do {
                                    do {
                                        setTextColor(6, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        printf("\nEnter the wall's coordinates : ");
                                        scanf("%s", hh);
                                        scanf("%s", vv);
                                        h = 0, v = 0;
                                        for (i = 0; hh[i]; i++) {
                                            h = h * 10 + (hh[i] - 48);
                                        }
                                        for (i = 0; vv[i]; i++) {
                                            v = v * 10 + (vv[i] - 48);
                                        }
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 3);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 1) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h - 1;
                                v = 2 * v;
                                walls[h][v] = wall;
                                walls[h + 1][v] = wall;
                                walls[h + 2][v] = wall;
                                wallCount1--;
                            }

                            if (wallDirection == 'h' || wallDirection == 'H') {
                                do {
                                    do {
                                        setTextColor(6, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        printf("\nEnter the wall's coordinates : ");
                                        scanf("%s", hh);
                                        scanf("%s", vv);
                                        h = 0, v = 0;
                                        for (i = 0; hh[i]; i++) {
                                            h = h * 10 + (hh[i] - 48);
                                        }
                                        for (i = 0; vv[i]; i++) {
                                            v = v * 10 + (vv[i] - 48);
                                        }
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 4);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 2) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h;
                                v = 2 * v - 1;
                                walls[h][v] = wall;
                                walls[h][v + 1] = wall;
                                walls[h][v + 2] = wall;
                                wallCount1--;
                            }
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                        } else {
                            clearScrean();
                            sleep(400);
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                            printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
                            scanf("%d", &p);
                        }
                    }
                } while ((board[xx][yy] != space || board[(x + xx) / 2][(yy + y) / 2] == wall) && sw == 0);
                sw = 0;
                x = xx, y = yy;
                if (x == k - 2) break;
                saveGame(currentGame);

                int computer = makeRandom();
                do {//computer next move
                    aa = a, bb = b;
                    clearScrean();
                    sleep(400);
                    setTextColor(11, 0);
                    printf("<< %s >>\n", player1);// board's printing
                    printf("Remained walls: %d\n\n", wallCount1);
                    Board(walls, k, x, y, a, b);
                    BoardPrint(k);
                    printf("\nRemained walls: %d\n", wallCount2);
                    printf("<< %s >>\n", player2);// end of board's printing
                    if (computer == 0) {

                        srand(time(0)); // تنظیم seed تابع تصادفی بر اساس زمان فعلی

                        int move = makeRandomMove();

                        if (move == 1 && x == aa + 2 && bb == y)
                            aa += 4;// ASCII code of up & down & left & right button
                        else if (move == 1) aa += 2;
                        else if (move == 2 && bb == y - 2 && aa == x) bb -= 4;
                        else if (move == 2) bb -= 2;
                        else if (move == 3 && y == bb + 2 && x == aa) bb += 4;
                        else if (move == 3) bb += 2;
                        else if (move == 4 && x == aa - 2 && y == bb) aa -= 4;
                        else if (move == 4) aa -= 2;
                    } else {//player chose to build a wall
                        if (wallCount2 > 0) {
                            do {
                                sw = 1;
                                clearScrean();
                                setTextColor(11, 0);
                                sleep(200);
                                printf("<< %s >>\n", player1);// board's printing
                                printf("Remained walls: %d\n\n", wallCount1);
                                Board(walls, k, x, y, a, b);
                                BoardPrint(k);
                                printf("\nRemained walls: %d\n", wallCount2);
                                printf("<< %s >>\n", player2);// end of board's printing
                                int orientation = rand() % 2; // انتخاب تصادفی جهت افقی یا عمودی
                                if (orientation == 1) {
                                    wallDirection = 'H';
                                }
                                if (orientation == 0) {
                                    wallDirection = 'V';
                                }
                                clearScrean();
                            } while (wallDirection != 'H' && wallDirection != 'V' && wallDirection != 'v' &&
                                     wallDirection !=
                                     'h');// we use do...while because wallDirection should be just one of these characters

                            if (wallDirection == 'v' || wallDirection == 'V') {
                                do {
                                    do {
                                        setTextColor(11, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        int row = rand() % 9 + 1; // انتخاب تصادفی یک سطر
                                        int clown = rand() % 9 + 1;
                                        h = row;
                                        v = clown;
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 3);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 1) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h - 1;
                                v = 2 * v;
                                walls[h][v] = wall;
                                walls[h + 1][v] = wall;
                                walls[h + 2][v] = wall;
                                wallCount2--;
                            }

                            if (wallDirection == 'h' || wallDirection == 'H') {
                                do {
                                    do {
                                        setTextColor(11, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        int row = rand() % 9 + 1; // انتخاب تصادفی یک سطر
                                        int clown = rand() % 9 + 1;
                                        h = row;
                                        v = clown;
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 4);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 2) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h;
                                v = 2 * v - 1;
                                walls[h][v] = wall;
                                walls[h][v + 1] = wall;
                                walls[h][v + 2] = wall;
                                wallCount2--;
                            }
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                        } else {
                            clearScrean();
                            sleep(400);
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                            printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
                            scanf("%d", &p);
                        }
                    }
                } while ((board[aa][bb] != space || board[(a + aa) / 2][(bb + b) / 2] == wall) && sw == 0);
                sw = 0;
                a = aa, b = bb;
                saveGame(currentGame);

            } while (a != 1 && x != k - 2);
        } else {//co_op
            do {//receive 'n' as dimention of the board which will be n*n
                sleep(500);
                printf("Please enter dimension of the board : ");
                scanf("%s", nn);
                n = 0;
                for (i = 0; nn[i]; i++) {
                    n = n * 10 + (nn[i] - 48);
                }
                clearScrean();
            } while (n < 4 || n > 25);
            k = 2 * n + 1;

            if (n % 2 == 0) { x = 1, y = n - 1; }// determining where should player 1&2's characters locate
            else { x = 1, y = n; }
            if (n % 2 == 0) { a = k - 2, b = n - 1; }
            else { a = k - 2, b = n; }

//when player1 should enter sth , Board's color will be yellow
//when player2 should enter sth , Board's color will be blue

            //scanning the nickname of player1
            sleep(400);
            setTextColor(6, 0);
            gets(Bug);
            printf("<< player1 >> \n");// board's printing
            printf("Remained walls: \n\n");
            Board(walls, k, x, y, a, b);
            BoardPrint(k);
            printf("\nRemained walls: \n");
            printf("<< player2 >> \n");// end of board's printing
            printf("\nPlayer1...! enter a nickname for yourself : ");
            gets(player1);
            clearScrean();

            //scanning the nickname of player2
            sleep(400);
            setTextColor(11, 0);
            printf("<< %s >>\n", player1);// board's printing
            printf("Remained walls: \n\n");
            Board(walls, k, x, y, a, b);
            BoardPrint(k);
            printf("\nRemained walls: \n");
            printf("<< player2 >> \n");// end of board's printing
            printf("\nPlayer2...! enter a nickname for yourself : ");
            gets(player2);
            clearScrean();

            do {//scanning the number of their walls
                wallCount = 0;
                clearScrean();
                sleep(400);
                setTextColor(15, 0);
                printf("<< %s >>\n", player1);// board's printing
                printf("Remained walls: \n\n");
                Board(walls, k, x, y, a, b);
                BoardPrint(k);
                printf("\nRemained walls: \n");
                printf("<< %s >>\n", player2);// end of board's printing
                printf("\nHow many walls would you like to have? ");
                scanf("%s", wallcount);
                wallCount = 0;
                for (i = 0; wallcount[i]; i++) {
                    wallCount = wallCount * 10 + (wallcount[i] - 48);
                }
                wallCount1 = wallCount;
                wallCount2 = wallCount;
                clearScrean();
            } while (wallCount >=
                     n * n / 4);// we use do...while because wallCount for each player shouldn't be more than n*n/4


            do {//game started , Until someone reaches the other side, this loop will repeat
                do {//player1's next move...
                    xx = x, yy = y;
                    clearScrean();
                    sleep(400);
                    setTextColor(6, 0);
                    printf("<< %s >>\n", player1);// board's printing
                    printf("Remained walls: %d\n\n", wallCount1);
                    Board(walls, k, x, y, a, b);
                    BoardPrint(k);
                    printf("\nRemained walls: %d\n", wallCount2);
                    printf("<< %s >>\n", player2);// end of board's printing
                    printf("\n %s  if you want to build a wall enter any button\n else move 'A' character...! ",
                           player1);//asking the player1's next move...
                    printf("%c", getch());
                    ascii = getch();//scanning the player1's next move...
                    if (ascii == 80 && a == xx + 2 && yy == b && board[a + 1][b] != wall)
                        xx += 4;// ASCII code of up & down & left & right button
                    else if (ascii == 80) xx += 2;
                    else if (ascii == 75 && b == yy - 2 && xx == a && board[a][b - 1] != wall) yy -= 4;
                    else if (ascii == 75) yy -= 2;
                    else if (ascii == 77 && b == yy + 2 && xx == a && board[a][b + 1] != wall) yy += 4;
                    else if (ascii == 77) yy += 2;
                    else if (ascii == 72 && a == xx - 2 && yy == b && board[a - 1][b] != wall) xx -= 4;
                    else if (ascii == 72) xx -= 2;
                    else {//player chose to build a wall
                        if (wallCount1 > 0) {
                            do {
                                sw = 1;
                                clearScrean();
                                sleep(200);
                                setTextColor(6, 0);
                                printf("<< %s >>\n", player1);// board's printing
                                printf("Remained walls: %d\n\n", wallCount1);
                                Board(walls, k, x, y, a, b);
                                BoardPrint(k);
                                printf("\nRemained walls: %d\n", wallCount2);
                                printf("<< %s >>\n", player2);// end of board's printing
                                printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
                                scanf("%c", &wallDirection);
                                clearScrean();
                            } while (wallDirection != 'H' && wallDirection != 'V' && wallDirection != 'v' &&
                                     wallDirection !=
                                     'h');// we use do...while because wallDirection should be just one of these characters

                            if (wallDirection == 'v' || wallDirection == 'V') {
                                do {
                                    do {
                                        setTextColor(6, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        printf("\nEnter the wall's coordinates : ");
                                        scanf("%s", hh);
                                        scanf("%s", vv);
                                        h = 0, v = 0;
                                        for (i = 0; hh[i]; i++) {
                                            h = h * 10 + (hh[i] - 48);
                                        }
                                        for (i = 0; vv[i]; i++) {
                                            v = v * 10 + (vv[i] - 48);
                                        }
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 3);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 1) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h - 1;
                                v = 2 * v;
                                walls[h][v] = wall;
                                walls[h + 1][v] = wall;
                                walls[h + 2][v] = wall;
                                wallCount1--;
                            }

                            if (wallDirection == 'h' || wallDirection == 'H') {
                                do {
                                    do {
                                        setTextColor(6, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        printf("\nEnter the wall's coordinates : ");
                                        scanf("%s", hh);
                                        scanf("%s", vv);
                                        h = 0, v = 0;
                                        for (i = 0; hh[i]; i++) {
                                            h = h * 10 + (hh[i] - 48);
                                        }
                                        for (i = 0; vv[i]; i++) {
                                            v = v * 10 + (vv[i] - 48);
                                        }
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 4);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 2) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h;
                                v = 2 * v - 1;
                                walls[h][v] = wall;
                                walls[h][v + 1] = wall;
                                walls[h][v + 2] = wall;
                                wallCount1--;
                            }
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                        } else {
                            clearScrean();
                            sleep(400);
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                            printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
                            scanf("%d", &p);
                        }
                    }
                } while ((board[xx][yy] != space || board[(x + xx) / 2][(yy + y) / 2] == wall) && sw == 0);
                sw = 0;
                x = xx, y = yy;
                if (x == k - 2) break;
                saveGame(currentGame);

                do {//player2's next move...
                    aa = a, bb = b;
                    clearScrean();
                    sleep(400);
                    setTextColor(11, 0);
                    printf("<< %s >>\n", player1);// board's printing
                    printf("Remained walls: %d\n\n", wallCount1);
                    Board(walls, k, x, y, a, b);
                    BoardPrint(k);
                    printf("\nRemained walls: %d\n", wallCount2);
                    printf("<< %s >>\n", player2);// end of board's printing
                    printf("\n %s if you want to build a wall enter any button\n else move 'B' character...! ",
                           player2);//asking the player1's next move...
                    printf("%c", getch());
                    ascii = getch();//scanning the player2's next move...
                    if (ascii == 80 && x == aa + 2 && bb == y) aa += 4;// ASCII code of up & down & left & right button
                    else if (ascii == 80) aa += 2;
                    else if (ascii == 75 && bb == y - 2 && aa == x) bb -= 4;
                    else if (ascii == 75) bb -= 2;
                    else if (ascii == 77 && y == bb + 2 && x == aa) bb += 4;
                    else if (ascii == 77) bb += 2;
                    else if (ascii == 72 && x == aa - 2 && y == bb) aa -= 4;
                    else if (ascii == 72) aa -= 2;
                    else {//player chose to build a wall
                        if (wallCount2 > 0) {
                            do {
                                sw = 1;
                                clearScrean();
                                setTextColor(11, 0);
                                sleep(200);
                                printf("<< %s >>\n", player1);// board's printing
                                printf("Remained walls: %d\n\n", wallCount1);
                                Board(walls, k, x, y, a, b);
                                BoardPrint(k);
                                printf("\nRemained walls: %d\n", wallCount2);
                                printf("<< %s >>\n", player2);// end of board's printing
                                printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
                                scanf("%c", &wallDirection);
                                clearScrean();
                            } while (wallDirection != 'H' && wallDirection != 'V' && wallDirection != 'v' &&
                                     wallDirection !=
                                     'h');// we use do...while because wallDirection should be just one of these characters

                            if (wallDirection == 'v' || wallDirection == 'V') {
                                do {
                                    do {
                                        setTextColor(11, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        printf("\nEnter the wall's coordinates : ");
                                        scanf("%s", hh);
                                        scanf("%s", vv);
                                        h = 0, v = 0;
                                        for (i = 0; hh[i]; i++) {
                                            h = h * 10 + (hh[i] - 48);
                                        }
                                        for (i = 0; vv[i]; i++) {
                                            v = v * 10 + (vv[i] - 48);
                                        }
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 3);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h - 1, 2 * v, walls, k, x, y, a, b, 1) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h - 1;
                                v = 2 * v;
                                walls[h][v] = wall;
                                walls[h + 1][v] = wall;
                                walls[h + 2][v] = wall;
                                wallCount2--;
                            }

                            if (wallDirection == 'h' || wallDirection == 'H') {
                                do {
                                    do {
                                        setTextColor(11, 0);
                                        printf("<< %s >>\n", player1);// board's printing
                                        printf("Remained walls: %d\n\n", wallCount1);
                                        Board(walls, k, x, y, a, b);
                                        BoardPrint(k);
                                        printf("\nRemained walls: %d\n", wallCount2);
                                        printf("<< %s >>\n", player2);// end of board's printing
                                        printf("\nEnter the wall's coordinates : ");
                                        scanf("%s", hh);
                                        scanf("%s", vv);
                                        h = 0, v = 0;
                                        for (i = 0; hh[i]; i++) {
                                            h = h * 10 + (hh[i] - 48);
                                        }
                                        for (i = 0; vv[i]; i++) {
                                            v = v * 10 + (vv[i] - 48);
                                        }
                                        clearScrean();
                                    } while (h < 1 || h >= n || v < 1 || v >= n);
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                    q = DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 4);
                                    Board(walls, k, x, y, a, b);
                                    clearScrean();
                                    for (e = 0; e < 100; e++) {
                                        for (t = 0; t < 100; t++) {
                                            check[e][t] = 0;
                                        }
                                    }
                                } while (DFS(2 * h, 2 * v - 1, walls, k, x, y, a, b, 2) != 1 || q !=
                                                                                                1);// we use do...while because wall's coordinates should be in the board and should be in the free places
                                h = 2 * h;
                                v = 2 * v - 1;
                                walls[h][v] = wall;
                                walls[h][v + 1] = wall;
                                walls[h][v + 2] = wall;
                                wallCount2--;
                            }
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                        } else {
                            clearScrean();
                            sleep(400);
                            printf("<< %s >>\n", player1);// board's printing
                            printf("Remained walls: %d\n\n", wallCount1);
                            Board(walls, k, x, y, a, b);
                            BoardPrint(k);
                            printf("\nRemained walls: %d\n", wallCount2);
                            printf("<< %s >>\n", player2);// end of board's printing
                            printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
                            scanf("%d", &p);
                        }
                    }
                } while ((board[aa][bb] != space || board[(a + aa) / 2][(bb + b) / 2] == wall) && sw == 0);
                sw = 0;
                a = aa, b = bb;

            } while (a != 1 && x != k - 2);
            saveGame(currentGame);


            clearScrean();
            sleep(500);
            setTextColor(15, 0);
            printf("<< %s >>\n", player1);// board's printing
            printf("Remained walls: %d\n\n", wallCount1);
            Board(walls, k, x, y, a, b);
            BoardPrint(k);
            printf("\nRemained walls: %d\n", wallCount2);
            printf("<< %s >>\n", player2);// end of board's printing
            //determining winner
            if (x == k - 2) printf("\nThe winner is << %s >>...!", player1);
            else if (a == 1) printf("\nThe winner is << %s >>...!", player2);
        }
    }
}}

