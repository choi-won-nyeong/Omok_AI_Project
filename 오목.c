//KILL
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <direct.h>
#include <limits.h>

INPUT_RECORD rec;
DWORD        dwNOER;

typedef struct _su
{
	int x, y;
	struct _su *prev;
	struct _su *next;
} su;

typedef struct _net	//network의 값을 저장
{
	int i, j, k, l;
	int n;	// 몇 번째 수인지를 저장
} net;

int sw=0;
int omok[15][15];
int omok_su[225][2];	// 둔 수를 저장 
int jik[15][15];	// 이기면 해당자리 +1 지면 -1(숫자가 큰 자리에 두게 함) 
int jik3[15][15];
int network[15][15][15][15];
int result[2][225];	// 이긴 횟수 
int a=1, b=5;
int cnt=0;
int x, y;
char s[32];	// 파일의 경로를 가르키는 변수
char logs_name[9]="\\logs_04";	// 디렉토리 이름
int que_cnt=0;
net que[11390625];
su *head;
su *tail;
//head->prev=head;
//head->next=tail;
//tail->prev=head;
//tail->next=tail;


void cls(){system("cls");}
void pause(){system("pause>nul");}

int _Sleep(int tick);	// tick/1000초 만큼 기다림 
int _Print();	// 오목판의 상태를 출력함 
int _Input();	// 입력을 받아들임
int _Judgment();	// 승패를 판정함
int _Computer();	// 컴퓨터
int _Reset();	// 초기화
//int _Insert_Su();	// 연결리스트 삽입
int _File_Open();	// 로그를 저장할 파일을 연다. 
int _End_Game(int draw, int select);	// 게임이 종료되면 데이터를 반영함 (비기면 1, 선택한 모드) 
int _FolkmUsic();	// (적)컴퓨터(함수 이름은 우리 형이 지음)

int main()
{
	int sw_draw=0;// 비기면 0
	int temp;
	char select=0;
	FILE *save;

    while(1)
    {
    	select=-1;
    	_Reset();
    	
    	while( !('0'<=select && select<='5') )
    		select=_getch();
    		
    	//select -= '0';
    	
	    switch(select)
	    {
	    	case '0':
	    		{
	    			return 0;
				}
	    	case '1':
	    		{
					while(1)
					{
						cls();
						_Print();
						if(5<=_Judgment()) break;
						
						_Input();
					}
				}
				break;
			case '2':
				{
					//while(1)
					{
						_Reset();
						if(_File_Open()==-1) return 0;
						
						//save = fopen(s, "a+");
						//fprintf(save, "%d\n", select);
						while(1)
						{
							cls();
							_Print();

							temp=_Judgment();
							if(5<=temp)
							{
								if(temp==10) sw_draw=1;
								_End_Game(sw_draw, select);
								break;
							}
							
							_Computer();
							//fprintf(save, "%c%c\n", x+'a', y+'A');
							omok_su[cnt-1][0]=x;
							omok_su[cnt-1][1]=y;
							pause();
							//_sleep(200);
						}
						//fclose(save);
						pause();
						//_sleep(10000);
					}
				}
				break;
			case '3':
			case '4':
				{
					_Reset();
					if(_File_Open()==-1) return 0;
						
					save = fopen(s, "a+");
					fprintf(save, "%d\n", select);
					
					while(1)
					{
						cls();
						_Print();
						temp=_Judgment();
						if(5<=temp)
						{
							if(temp==10) sw_draw=1;
							_End_Game(sw_draw, select);
							break;
						}
							
						
						if(select=='3') _Computer();
						else _Input();
						fprintf(save, "%c%c\n", x+'a', y+'A');
						omok_su[cnt-1][0]=x;
						omok_su[cnt-1][1]=y;
						cls();
						_Print();
						temp=_Judgment();
						if(5<=temp)
						{
							if(temp==10) sw_draw=1;
							_End_Game(sw_draw, select);
							break;
						}	
						
						if(select=='3') _Input();
						else _Computer();
						fprintf(save, "%c%c\n", x+'a', y+'A');
						omok_su[cnt-1][0]=x;
						omok_su[cnt-1][1]=y;
					}
					fclose(save);
				}
				break;
			case '5':
				//while(1)
				{
					{
						_Reset();
						if(_File_Open()==-1) return 0;
						
						save = fopen(s, "a+");
						fprintf(save, "%d\n", select);
						
						while(1)
						{
							cls();
							_Print();
							temp=_Judgment();
							if(5<=temp)
							{
								if(temp==10) sw_draw=1;
								//_Print();
								_End_Game(sw_draw, select);
								break;
							}
							
							if(sw==1) _Computer();
							else _FolkmUsic();
							fprintf(save, "%c%c\n", x+'a', y+'A');
							omok_su[cnt-1][0]=x;
							omok_su[cnt-1][1]=y;
							cls();
							_Print();
							temp=_Judgment();
							if(5<=temp)
							{
								if(temp==10) sw_draw=1;
								//_Print();
								_End_Game(sw_draw, select);
								break;
							}
							
							if(sw==1) _FolkmUsic();
							else _Computer();
							fprintf(save, "%c%c\n", x+'a', y+'A');
							omok_su[cnt-1][0]=x;
							omok_su[cnt-1][1]=y;
							
							pause();
							//_sleep(1000);
						}
						fclose(save);
						
						if(sw==1) sw=0;
						else sw=1;	
					}
				}
				break;
		}
	}
	return 0; 
}

int _FolkmUsic()	// 컴퓨터(함수 이름은 우리 형이 지음)
{
	int i, j;
	int max=INT_MIN;
	int ran1, ran2;
	
	for(i=0; i<15; i++)	// jik의 최댓값 구하기 
	{
		for(j=0; j<15; j++)
		{
			if(max<jik3[i][j] && omok[i][j]==0) max = jik3[i][j];
		}
	}
	
	srand( clock() );
	
	while(1)
	{
		ran1=rand()%15;
		ran2=rand()%15;
		if(omok[ran1][ran2]!=0 || jik3[ran1][ran2]<max) continue;	// 해당 좌표에 돌이 놓여져 있거나 가치망(?) 최댓값 보다 작다면 좌표를 다시 구함. 
		else
		{
			cnt++;
			omok[ran1][ran2]=cnt%2+1;
			x = ran2;
			y = ran1;
			break;
		}
	}
	return 0;
}

int _End_Game(int draw, int select)	// 게임이 종료되면 데이터를 반영함 
{
	int i, j, k, l;
	int sum1=0, sum2=0; 
	FILE *data, *data3;
	FILE *win, *win2;
	
	for(i=0; i<=cnt; i++)
	{
		if((cnt-1)%2==i%2) jik3[omok_su[i][1]][omok_su[i][0]] += (224/8-i/8);
		else jik3[omok_su[i][1]][omok_su[i][0]] -= (224/8-i/8);
	}

	for(i=0; i<32; i++) s[i]=0;
	strcat(s, logs_name);
	strcat(s, "\\dt_01.txt");
	
	if(select=='2')
	{
		for(i=0; i<que_cnt; i++)
		{
			if(que[i].n%2!=cnt%2) network[que[i].i][que[i].j][que[i].k][que[i].l] -= 2;
			else if(que[i].n<=cnt-12) network[que[i].i][que[i].j][que[i].k][que[i].l] += 100;
		}
	}
	else if(select=='5')
	{
		for(i=0; i<que_cnt; i++)
		{
			if(cnt%2!=sw%2) network[que[i].i][que[i].j][que[i].k][que[i].l] -= 2;
		}
	}

	data=fopen(s, "w");
	for(i=0; i<15; i++)
	{
		for(j=0; j<15; j++)
		{
			for(k=0; k<15; k++)
			{
				for(l=0; l<15; l++)
				{
					//printf("%5d", network[i][j][k][l]);
					fprintf(data, "%10d", network[i][j][k][l]);
				}
				//printf("\n");
				fprintf(data, "\n");
			}
			//printf("\n");
			fprintf(data, "\n");
		}
	}

	for(i=0; i<32; i++) s[i]=0;
	strcat(s, logs_name);
	strcat(s, "\\data3.txt");

	data3=fopen(s, "w");
	
	for(i=0; i<15; i++)
	{
		for(j=0; j<15; j++)
		{
			fprintf(data3, "%10d", jik3[i][j]);
		}
		fprintf(data3, "\n");
	}
	
	fclose(data);
	fclose(data3);
	
	for(i=0; i<32; i++) s[i]=0;
	strcat(s, logs_name);
	strcat(s, "\\result1.txt");
	
	win = fopen(s, "a+");
	s[15]++;
	win2 = fopen(s, "a+");
	for(i=0; i<225; i++)
	{
		fscanf(win, "%d", &i);
		fscanf(win, "%d", &result[0][i]);
		fscanf(win2, "%d", &i);
		fscanf(win2, "%d", &result[1][i]);
	}
	fclose(win);
	fclose(win2);
	
	s[15]--;
	win = fopen(s, "w");
	s[15]++;
	win2 = fopen(s, "w");
	
	if(draw==1)
	{
		result[0][0]++;
		result[1][0]++;
	}
	
	for(i=0; i<225; i++)
	{
		if(cnt==i+1 && cnt%2==sw%2) result[0][i]++;
		else if(cnt==i+1 && cnt%2!=sw%2) result[1][i]++;
		fprintf(win, "%d %d\n", i, result[0][i]);
		fprintf(win2, "%d %d\n", i, result[1][i]); 
		sum1 += result[0][i];
		sum2 += result[1][i];
	}
	fclose(win);
	fclose(win2);
	cls();
	printf("%5d %5d %5s\n", 1, 2, "draw");
	printf("%5d %5d %5d %5d %5d", sum1, sum2, result[0][0], result[1][0], sw);
	//pause();
	return 0;
}

int _File_Open()	// 로그를 저장할 파일을 연다. 
{
	int i, j, k, l;
	int number=0;
	char s2[11];
	FILE *logs;
	FILE *data, *data3;
	
	mkdir(logs_name);
	
	for(i=0; i<32; i++) s[i]=0;
	strcat(s, logs_name);
	strcat(s, "\\th.txt");
	
	logs=fopen(s, "a+");
	fscanf(logs, "%d", &number);
	fclose(logs);
	
	logs=fopen(s, "w");
	fprintf(logs, "%d", number+1);
	fclose(logs);
	
	///*
	if(number>=10000000)
	{
		printf("\n종료\n");
		pause();
		pause();
		pause();
		pause();
		pause();
		return -1;
	}
	//*/
	
	for(i=0; i<32; i++) s[i]=0;
	strcat(s, logs_name);
	strcat(s, "\\dt_01.txt");

	if( (data = fopen(s, "r+"))==0 )
	{
		data = fopen(s, "a+");
		fclose(data);
		for(i=0; i<15; i++) for(j=0; j<15; j++) for(k=0; k<15; k++) for(l=0; l<15; l++) network[i][j][k][l]=0;
	}
	else for(i=0; i<15; i++) for(j=0; j<15; j++) for(k=0; k<15; k++) for(l=0; l<15; l++) fscanf(data, "%d", &network[i][j][k][l]);
	
	for(i=0; i<32; i++) s[i]=0;
	strcat(s, logs_name);
	strcat(s, "\\data3.txt");

	if( (data3 = fopen(s, "r+"))==0 )
	{
		data3 = fopen(s, "a+");
		fclose(data3);
		for(i=0; i<15; i++) for(j=0; j<15; j++) jik3[i][j]=0;
	}
	else for(i=0; i<15; i++) for(j=0; j<15; j++) fscanf(data3, "%d", &jik3[i][j]);

	if(data!=0) fclose(data);
	if(data3!=0) fclose(data3);
	
	for(i=0; i<32; i++) s[i]=0;
	
	strcat(s, logs_name);
	strcat(s, "\\");
	
	for(i=9; i>=0; i--)
	{
		s2[i] = number % 10 + '0';
		number = number / 10;
	}
	s2[10]=0;
	strcat(s, s2);
	
	strcat(s, ".txt");
	
	return 0;
}

int _Reset()	// 초기화
{
	int i, j, k, l;

	for(i=0; i<15; i++)
	{
		for(j=0; j<15; j++)
		{
			omok[i][j]=0;
			jik[i][j]=0;
			jik3[i][j]=0;
			for(k=0; k<15; k++) for(l=0; l<15; l++) network[i][j][k][l]=0;
		}
	}
	
	for(i=0; i<225; i++)
	{
		omok_su[i][0]=0;
		omok_su[i][1]=0;
		result[0][i]=0;
		result[1][i]=0;
	}
	
	cnt = 0;
	que_cnt = 0;
	
	return 0;	
}

int _Computer()	// 컴퓨터
{
	int i, j, k, l;
	int max=INT_MIN;
	int ran1, ran2;
	int sw=0;

	srand( clock() );

	for(i=0; i<15; i++)
		for(j=0; j<15; j++)
			jik[i][j]=0;

	for(i=0; i<15; i++)
	{
		for(j=0; j<15; j++)
		{
			for(k=0; k<15; k++)
			{
				for(l=0; l<15; l++)
				{
					if(rand()%100==1)
					{
						network[i][j][k][l]++;
						que[que_cnt].i=i;
						que[que_cnt].j=j;
						que[que_cnt].k=k;
						que[que_cnt].l=l;
						que[que_cnt].n=cnt+1;
						que_cnt++;
					}
				}
			}
		}
	}

	for(i=0; i<15; i++)	// jik[k][l]의 가중합계 구하기
	{
		for(j=0; j<15; j++)
		{
			if(omok[i][j]==0) continue;	//돌이 놓여져 있는 곳의 합계만 구함.
			for(k=0; k<15; k++)
			{
				for(l=0; l<15; l++)
				{
					jik[k][l] += network[i][j][k][l];
				}
			}
		}
	}

	for(i=0; i<15; i++)	// jik의 최댓값 구하기 
	{
		for(j=0; j<15; j++)
		{
			if(max==jik[i][j] && omok[i][j]==0) sw=0;
			if(max<jik[i][j] && omok[i][j]==0)
			{
				max = jik[i][j];
				sw=1;
				ran1 = i;
				ran2 = j;
			}
		}
	}
	
	while(1)
	{
		if(sw==0)
		{
			ran1=rand()%15;
			ran2=rand()%15;
		}
		
		if(sw==0 && (omok[ran1][ran2]!=0 || jik[ran1][ran2]<max) ) continue;	// 해당 좌표에 돌이 놓여져 있거나 가치망(?) 최댓값 보다 작다면 좌표를 다시 구함. 
		else
		{
			cnt++;
			omok[ran1][ran2]=cnt%2+1;
			x = ran2;
			y = ran1;
			break;
		}
	}
	return 0;
}

int _Judgment()	// 승패를 판정함
{
	int i, j;
	int count=0;
	
	for(i=y-4; i<=y+4; i++)	// 세로 확인 
	{
		if( !(0<=i && i<=14) ) continue;
		else if(omok[i][x]==cnt%2+1) count++;
		else count=0;
		if(5<=count) return count;
	}
	
	count=0;
	for(i=x-4; i<=x+4; i++)	//가로 확인 
	{
		if( !(0<=i && i<=14) ) continue;
		else if(omok[y][i]==cnt%2+1) count++;
		else count=0;
		if(5<=count) return count;
	}
	
	count=0;
	for(i=-4; i<=4; i++)	// 대각선(왼쪽위에서 오른쪽아래) 확인 
	{
		if( !(0<=x+i && x+i<=14) || !(0<=y+i && y+i<=14) ) continue;
		else if(omok[y+i][x+i]==cnt%2+1) count++;
		else count=0;
		if(5<=count) return count;
	}
	
	count=0;
	for(i=-4; i<=4; i++)	// 대각선(오른쪽위에서 왼쪽아래) 확인 
	{
		if( !(0<=x+i && x+i<=14) || !(0<=y-i && y-i<=14) ) continue;
		else if(omok[y-i][x+i]==cnt%2+1) count++;
		else count=0;
		if(5<=count) return count;
	}
	
	count=0;
	for(i=0; i<15; i++)
	{
		for(j=0; j<15; j++)
		{
			if(omok[i][j]==0) count=1;	// 빈 공간이 있으면 
		}
		if(count==1) break;	// 반복문을 나감 
	}
	if(!count) return 10;
	
	return 0;
}

int _Input()	// 입력을 받아들임 
{
	int mouse_x;
	int mouse_y;
	/***********************
		while(1)
		{
			ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // 콘솔창 입력을 받아들임.
        
			if (rec.EventType == MOUSE_EVENT) // 마우스 이벤트일 경우
			{
				if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) // 좌측 버튼이 클릭되었을 경우
				{
					mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X값 받아옴
					mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y값 받아옴
					COORD Coor = { 0, 0 };
					//DWORD dw;
					if( !(0<mouse_x/2 && mouse_x/2<16) || !(0<mouse_y && mouse_y<16) || omok[mouse_y-1][mouse_x/2-1]!=0) continue;
					else
					{
						cnt++;
						omok[mouse_y-1][mouse_x/2-1]=cnt%2+1;
						x = mouse_x/2-1;
						y = mouse_y-1;
					}
					//FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 25, Coor, &dw); // 콘솔창 화면을 지운다.
					//system("cls");
					//printf("%d, %d\n", mouse_x/2, mouse_y); // 좌표를 출력한다.
					return 0;
				}
			}
		}
		*///////////////
    return 0;
}

int _Print()	// 오목판의 상태를 출력함 
{
	int i, j;
	
	printf("  ");
	for(i=0; i<15; i++)
	{
		printf("%2c", 'a'+i);
	}
	printf("\n");
	
	for(i=0; i<15; i++)
	{
		printf("%2c", 'A'+i);
		for(j=0; j<15; j++)
		{
			if(omok[i][j]==0) printf("┼");
			else if(omok[i][j]==1) printf("●");
			else if(omok[i][j]==2) printf("○");
		}
		printf("\n");
	}
	return 0;	
}

int _Sleep(int tick)	// tick/1000초 만큼 기다림 
{
	int t1, t2=0;
	
	t1=clock();
	while(t2-t1<=tick)	// 기다린 시간이 tick보다 크거나 같으면 나감 
	{
		t2=clock();
		if(_kbhit())	// 키보드 입력이 있으면 반환(1) 
		{
			_getch();	// 입력된 키보드 값 처리 
			return 1;
		}
	}
	return 0;
}
