#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

#include<bits/stdc++.h>

#define REP(i , l , r) for(int i = l ; i <= r ; i++)
#define REPD(i , l , r) for(int i = l ; i >= r ; i--)
#define REPS(i , l , r) for(int i = l ; i < r ; i++)

typedef long long int ll;

//dung cho ham random
#include <iostream>
#include <map>
using namespace std;

#define MAX_M 100
#define MAX_N 100

typedef struct {
	int m, n;
	int A[MAX_M][MAX_N];
	int r, c;
} State;
State random(){
	State S;
	srand(time(0));
	int r;
    map<int, bool> vis;
	S.m=3;
	S.n=3;
	
		for(int i=0;i<3;i++){
        	for(int j=0;j<3;j++){
        		// Random cho toi khi r chua co trong map vis
		        do{
		            r = 1+ rand() % 9;
		            S.A[i][j]=r;
		            
		        }while(vis.find(r) != vis.end());
				if(S.A[i][j]==9){
		            	S.r=i;
		            	S.c=j;
					}
				
				// Danh dau r da co.
        		vis[r] = true;	
			}
		}
		
		return S;
}
int  dieuKienRanDom(State S){
	int N=0;
	
	int B[10];
	int k=0;
	//chuyen mang 2 chieu thanh mang 1 chieu
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			B[k]=S.A[i][j];
			k++;
		}
	}
	
	for(int i=0;i<k-1;i++){
		if(B[i]==9){
			continue;
		}
		for(int j=i+1;j<k;j++){
			
			if(B[i]>B[j]){
				
				N++;
			}
		}
	}
	
	return N;
}
void block(int col, int row){
	setcolor(RED);
	rectangle(col-160 ,row-160 ,col ,row );
	
	setcolor(7);
	rectangle(col-160+5 ,row-160+5 ,col-5 ,row-5 );
	setfillstyle(SOLID_FILL, CYAN);
    floodfill(col-160+25 ,row-160+25, 7);
}

void initMap(int col,int row, State S){
	col=160,row=160;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			block(col,row);
			//------------
			//ve so
			setbkcolor(CYAN);
			settextstyle(0, 0, 7);
			if(S.A[i][j]==1){
				setcolor(RED);
				outtextxy(col-110, row -110, "1");
			}else if(S.A[i][j]==2){
				setcolor(RED);
				outtextxy(col-110, row -110, "2");
			}else if(S.A[i][j]==3){
				setcolor(RED);
				outtextxy(col-110, row -110, "3");
			}else if(S.A[i][j]==4){
				setcolor(RED);
				outtextxy(col-110, row -110, "4");
			}else if(S.A[i][j]==5){
				setcolor(RED);
				outtextxy(col-110, row -110, "5");
			}else if(S.A[i][j]==6){
				setcolor(RED);
				outtextxy(col-110, row -110, "6");
			}else if(S.A[i][j]==7){
				setcolor(RED);
				outtextxy(col-110, row -110, "7");
			}else if(S.A[i][j]==8){
				setcolor(RED);
				outtextxy(col-110, row -110, "8");
			}
			col+=160;
		}
		col=160;
		row+=160;
	}
	setbkcolor(BLACK);
}
//------------------------------------------------------------
//AUTOSOLVE
enum facing {
	LEFT , RIGHT , UP , DOWN , STAY
};

int puzzle[3][3] , posX , posY , checker , cost;

class node{
	public :
		int arr[3][3] , x , y , f;
		string way;
		facing canFace;
		
		node(int a[3][3] , string way , facing canFace , int x , int y , int f){
			this->f = f;
			this->way = way;
			this->canFace = canFace;
			this->x = x;
			this->y = y;
			REP(i,0,2){
				REP(j,0,2){
					arr[i][j] = a[i][j];
				}
			}
}
		
		bool canMoveLeft(){
			return canFace != LEFT && y > 0 && cost > herStic();
		}
		bool canMoveRight(){
			return canFace != RIGHT && y < 2 && cost > herStic();
		}
		bool canMoveUp(){
			return canFace != UP && x > 0 && cost > herStic();
		}
		bool canMoveDown(){
			return canFace != DOWN && x < 2 && cost > herStic();
		}
		
		int herStic(){
			int sum = 0;
			if(checker == 1){
//				if(arr[0][0] != 1) sum++;
//				if(arr[0][1] != 2) sum++;
//				if(arr[0][2] != 3) sum++;
//				if(arr[1][0] != 8) sum++;
//				if(arr[1][2] != 4) sum++;
//				if(arr[2][0] != 7) sum++;
//				if(arr[2][1] != 6) sum++;
//				if(arr[2][2] != 5) sum++;
			
			}else{
				if(arr[0][1] != 1) sum++;
				if(arr[0][2] != 2) sum++;
				if(arr[1][0] != 3) sum++;
				if(arr[1][1] != 4) sum++;
				if(arr[1][2] != 5) sum++;
				if(arr[2][0] != 6) sum++;
				if(arr[2][1] != 7) sum++;
				if(arr[2][2] != 8) sum++;
			}
			return sum + f;
		}
		
		void moveLeft(){
			swap(arr[x][y] , arr[x][y-1]);
			y--;
			canFace = RIGHT;
			way += "l";
			f++;
		}
		void moveRight(){
			swap(arr[x][y] , arr[x][y+1]);
			y++;
			canFace = LEFT;
			way += "r";
			f++;
		}
		void moveUp(){
			swap(arr[x][y] , arr[x-1][y]);
			x--;
			canFace = DOWN;
			way += "u";
			f++;
		}
		void moveDown(){
			swap(arr[x][y] , arr[x+1][y]);
			x++;
			canFace = UP;
			way += "d";
			f++;
		}
		
		bool checkFinish(){
			if(checker == 1){
				REP(i,0,2){
					if(arr[0][i] != i+1 || arr[2][i] != 7-i) return false;;
				}
				return arr[1][0] != 8 || arr[1][2] != 4 ? false : true;
			}else{
				REP(i,0,2){
					if(arr[0][i] != i || arr[1][i] != i+3 || arr[2][i] != i+6) return false;
				}
				return true;
			}
			
		}
};

void moveLeft(){
	swap(puzzle[posX][posY] , puzzle[posX][posY-1]);
	posY--;
}
void moveRight(){
	swap(puzzle[posX][posY] , puzzle[posX][posY+1]);
	posY++;
}
void moveUp(){
	swap(puzzle[posX][posY] , puzzle[posX-1][posY]);
	posX--;
}
void moveDown(){
	swap(puzzle[posX][posY] , puzzle[posX+1][posY]);
	posX++;
}

void initPuzzle(State S){
	
	
	
	 puzzle[0][0]=S.A[0][0];
	 puzzle[0][1]=S.A[0][1];
	 puzzle[0][2]=S.A[0][2];
	 puzzle[1][0]=S.A[1][0];
	 puzzle[1][1]=S.A[1][1];
	 puzzle[1][2]=S.A[1][2];
	 puzzle[2][0]=S.A[2][0];
	 puzzle[2][1]=S.A[2][1]; 
	 puzzle[2][2]=S.A[2][2];
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(S.A[i][j]==9){
				puzzle[i][j]=0;
			}
		}
	}//cout << "Nhap chi phi toi da cua thuat toan = ";
	
	cost =50;
	
	bool checked = true;
	int sum = 0;
	REP(i,0,2){
		REP(j,0,2){
			sum += puzzle[i][j];
			if(puzzle[i][j] > 8) {
				checked = false;
				break;
			}
		}
	}
	if(sum != 36 || checked == false){
		cout << "Nhap sai du lieu vui long nhap lai" << endl;
		return initPuzzle(S);
	}
	
	REP(i,0,2){
		REP(j,0,2){
			if(puzzle[i][j] == 0){
				posX = i;
				posY = j;
				return;
			}
		}
	}
}


void prin(){
	int col=160,row=160;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			block(col,row);
			//------------
			//ve so
			setbkcolor(CYAN);
			settextstyle(0, 0, 7);
if(puzzle[i][j]==1){
				setcolor(RED);
				outtextxy(col-110, row -110, "1");
			}else if(puzzle[i][j]==2){
				setcolor(RED);
				outtextxy(col-110, row -110, "2");
			}else if(puzzle[i][j]==3){
				setcolor(RED);
				outtextxy(col-110, row -110, "3");
			}else if(puzzle[i][j]==4){
				setcolor(RED);
				outtextxy(col-110, row -110, "4");
			}else if(puzzle[i][j]==5){
				setcolor(RED);
				outtextxy(col-110, row -110, "5");
			}else if(puzzle[i][j]==6){
				setcolor(RED);
				outtextxy(col-110, row -110, "6");
			}else if(puzzle[i][j]==7){
				setcolor(RED);
				outtextxy(col-110, row -110, "7");
			}else if(puzzle[i][j]==8){
				setcolor(RED);
				outtextxy(col-110, row -110, "8");
			}
			col+=160;
		}
		col=160;
		row+=160;
	}
	setbkcolor(BLACK);
}
		
bool checkFinish(){
	int counter1 = 0, counter2 = 0;
	REP(i,0,2){
		if(puzzle[0][i] == i+1) counter1++;
	}
	
	REP(i,0,2){
		if(puzzle[2][i] == 7-i) counter1++;
	}
	if(puzzle[1][0] == 8){
		counter1++;
	} 
	if(puzzle[1][2] == 4) {
		counter1++;
	}
	if(counter1 == 8) return true;
		
	REP(i,0,2){
		if(puzzle[0][i] == i) counter2++;
		if(puzzle[1][i] == i+3) counter2++;
		if(puzzle[2][i] == i+6) counter2++;
	}
	if(counter2 == 8) return true;
	return false;
}

int countStart(){
	int sum = 0;
	REP(q,0,8){
		int row = q/3;
		int col = q%3;
		int counter = puzzle[row][col];
		REP(i,0,2){
			REP(j,0,2){
				if( (row < i && puzzle[i][j] < counter && puzzle[i][j] != 0 )  ){
					sum++;
				}else if(row == i && col < j && puzzle[i][j] < counter && puzzle[i][j] != 0){
					sum++;
				}
			}
		}
	}
	return sum;
}
void countStep(int cnt){
	char s[10];
	sprintf(s,"%d",cnt);
	settextstyle(8,0,2);
	setcolor(WHITE);
	
	outtextxy(480,430,"So lan di chuyen:");
	outtextxy(700,430,s);
	
}
void autosolve(State S){
	int step = 0 ;
	ll numOfNode = 0;
	bool check = checkFinish();
	initPuzzle(S);
	const clock_t begin_time = clock();
	string way = "";
	node nd(puzzle , "" , STAY , posX , posY , 0);
	vector<node> vt;
	vt.push_back(nd);
	checker = countStart() %2;
	cout << "Trang thai ban dau : " << endl;
	prin();
	cout << endl;
	while(!check && vt.size() != 0){
		vector<node> open;
			int i = vt.size()-1;
			if(vt.at(i).checkFinish()){
				way = vt.at(i).way;
				check = true;
				break;
			}else{
				if(vt.at(i).canMoveUp()){
					node nd = vt.at(i);
					nd.moveUp();
					open.push_back(nd);
				}
				if(vt.at(i).canMoveDown()){
					node nd = vt.at(i);
					nd.moveDown();
					open.push_back(nd);
				}
				if(vt.at(i).canMoveRight()){
					node nd = vt.at(i);
					nd.moveRight();
					open.push_back(nd);
				}
				if(vt.at(i).canMoveLeft()){
					node nd = vt.at(i);
					nd.moveLeft();
					open.push_back(nd);
				}
			}
			vt.pop_back();
			
		REPS(i,0,open.size()){
			REPS(j,i+1,open.size()){
				if(open.at(i).herStic() <= open.at(j).herStic()){
					swap(open.at(i) , open.at(j));
				}
			}
			
		}
		REPS(i,0,open.size()){
			if(open.at(i).herStic() == open.at(open.size()-1).herStic())
			vt.push_back(open.at(i));
}
		numOfNode++;
	}
	int cnt=0;
	REPS(i,0,way.length()){
		if(way[i] == 'l'){
			moveLeft();
			cnt++;
			prin();
			cout << "di chuyen sang trai" << endl << endl;
		}else if(way[i] == 'r'){
			moveRight();cnt++;
			prin();
			cout << "di chuyen sang phai" << endl << endl;
		}else if(way[i] == 'u'){
			moveUp();cnt++;
			prin();
			cout << "di chuyen len tren" << endl << endl;
		}else if(way[i] == 'd'){
			moveDown();cnt++;
			prin();
			cout << "di chuyen xuong duoi" << endl << endl;
		}
		countStep(cnt);
		delay(200);
	}
	cout << "Thuat toan AKT" << endl;
	cout << "So buoc di = " << way.length() << endl;
	cout << "So phep toan da thuc hien = " << numOfNode << endl;
	cout << "Thoi gian tinh toan = " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s";
}

//---------------------------------------------------------------
int is_finished(State S){
	//neu ma sap xep dung het cac vitri thi tra ve 1
	for(int i=0;i<S.m;i++){
		for(int j=0;j<S.n;j++){
			if(S.A[i][j]!=(i*S.n + j + 1))
				return 0;
		}
	}
	return 1;
}

int up(State S, State *N){
		*N=S;
	
		N->A[S.r][S.c]=N->A[S.r-1][S.c];
		N->A[S.r-1][S.c]=N->m * N->n;
		(N->r) --;

}

int down(State S, State *N){
		*N=S;
	
		N->A[S.r][S.c]=N->A[S.r+1][S.c];
		N->A[S.r+1][S.c]= N->m * N->n;
		(N->r) ++;

}

int left(State S, State *N){
		*N=S;

		N->A[S.r][S.c]=N->A[S.r][S.c-1];
		N->A[S.r][S.c-1]= N->m * N->n;
		(N->c) --;

}

int right(State S, State *N){
		*N=S;

		N->A[S.r][S.c]=N->A[S.r][S.c+1];
		N->A[S.r][S.c+1]= N->m * N->n;
		(N->c) ++;

}

int click_pos(int x){
	int i = x /160;		
	x = 160*i;
	return x;
}
void text(){
	setcolor(RED);
	settextstyle(8,0,5);
	setbkcolor(BLACK);
	outtextxy(550,10,"GAME");
	outtextxy(510,50,"8-PUZZLE");
	
	//restart
	settextstyle(8,0,3);
	setcolor(WHITE);
	rectangle(540,130,690,180);
	outtextxy(560,140,"RESTART");
	
	//undo
	setcolor(YELLOW);
	rectangle(540,230,690,280);
	setcolor(WHITE);
	setbkcolor(BLACK);	
	outtextxy(550,240,"AUT0SOLVE");
	
	//exit
	setcolor(GREEN);
	rectangle(540,330,690,380);
	setcolor(WHITE);
	setbkcolor(BLACK);	
	outtextxy(580,340,"EXIT");
}

void win_theme(){
	cleardevice();
	setbkcolor(GREEN);
	setcolor(7);
	settextstyle(8,0,7);
	outtextxy(125,150,"YOU WIN!");
	text();
}



void click(int col, int row, State S,State N){
    int x, y;
	int cnt=0;
	countStep(cnt);		
		while (1){
		
		delay(0.0001);
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
				if ( x<=480 && y<=480){
				printf("left click %d %d\n ",x,y );
				col = click_pos(x) + 160;
				row = click_pos(y) + 160;
				printf("c = %d   r = %d\n",col,row);
				printf("\n");
					
					PlaySound(TEXT("menusound.wav"),NULL,SND_ASYNC);
					if(S.A[(row/160)-1+1][(col/160)-1]==S.A[S.r][S.c]){
						up(S,&N);
						S=N;
						cnt++;
					}else if(S.A[(row/160)-1-1][(col/160)-1]==S.A[S.r][S.c]){
						down(S, &N);
						S=N;
						cnt++;						
					}else if(S.A[(row/160)-1][(col/160)-1+1]==S.A[S.r][S.c]){
						left(S, &N);
						S=N;
						cnt++;
					}else if(S.A[(row/160)-1][(col/160)-1-1]==S.A[S.r][S.c]){
						right(S, &N);
						S=N;
						cnt++;
					}
					cleardevice();
					text();
					countStep(cnt);					
					initMap(col,row,S);
					
				}
				
			//-------------------------------------	
				//cac button
				if(x>=540&&x<=690&&y>=130&&y<=180){
					//restart
					PlaySound(TEXT("mediummodesound.wav"),NULL,SND_ASYNC);
					return ;
				}else if(x>=540&&x<=690&&y>=230&&y<=280){
					PlaySound(TEXT("mediummodesound.wav"),NULL,SND_ASYNC);
					cleardevice();
					text();					
					autosolve(S);
					
				}else if(x>=540&&x<=690&&y>=330&&y<=380){
					PlaySound(TEXT("mediummodesound.wav"),NULL,SND_ASYNC);
					delay(500);
					exit(1);
				}
			//--------------------------------------
				if(is_finished(S)){
					win_theme();
				}
				
				
			}
		}
	closegraph();	
}
//------------------------------------------------------------------------
int main(){
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	initwindow(750, 500);
	
	int col,row;
	State S,N;
	

START :
	
	S=random();
	while(dieuKienRanDom(S)%2!=0){
		S=random();
		if(dieuKienRanDom(S)%2==0){
			break;
		}
	}
	
	
	cleardevice();
	initMap(col,row, S);
	text();
	PlaySound(TEXT("HesAPiratePiratesOfTheCaribbean_368mu.wav"),NULL,SND_ASYNC);
	click(col, row,S, N);
	
goto START;
	getch();
	closegraph();
	return 0;
}
