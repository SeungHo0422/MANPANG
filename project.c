#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <direct.h>


//남녀 구분하는거 만들기

#define CLS system("cls")
#define END fseek(stdin, 0, SEEK_END)
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ENTER 13
#define BACK 18 //8
#define ESC 27

typedef enum Area
{
	서울특별시 = 10, 부산광역시, 대구광역시, 인천광역시, 광주광역시,
	대전광역시, 울산광역시, 경기도, 강원도, 충청북도, 충청남도,
	전라북도, 전라남도, 경상북도, 경상남도, 제주도
} Area;

typedef enum Sex
{
	남자 = 1, 여자
} Sex;

typedef struct XY {
	int x;
	int y;
}XY;

typedef struct Member
{
	char name[41];
	int sex;
	int age;
	int s_num;
	int area;
} Member;

typedef struct Person
{
	Member member;
	int mystep[11];
	int otherstep[12];
} Person;

typedef struct MyStep {
	int step1[4];
	int step2[2];
	int step3[4];
	int step4[10];
	int step5[5];
	int step6[5];
	int step7[8];
	int step8[10];
	int step9[4];
	int step10[5];
	int step11[8];
} MyStep;

typedef struct OtherStep {
	int step1[5];
	int step2[4];
	int step3[2];
	int step4[4];
	int step5[10];
	int step6[5];
	int step7[8];
	int step8[8];
	int step9[5];
	int step10[4];
	int step11[10];
	int step12[3];
} OtherStep;

typedef struct People_num {
	int T_num;
	int B_num;
	int G_num;
}People_num;

void showMyStep(char* id);
int print_NUM(char num[],int Max, int count); // 숫자 출력 ESC = -1
int print_char(char str[], int count); // 문자 출력 ESC = -1 그외 = 1
int KeyControl();
void IsCursor(char); // 커서 보이기 HIde = 0,  Show = 1
void Goto_xy(int, int);
void Delet_line(int);
void Page_Size(); // 콘솔 창 크기
int filter_num(char* temp, int size); // 문자열에서 원하는 자리수만큼 숫자 받아오기

//디자인.h

//화살표 출력 및 이동
void print_s(int, int);
void Goto_UP(XY *, XY *);
void Goto_DOWN(XY *, XY *);
void Goto_RIGHT(XY *, XY *);
void Goto_LEFT(XY *, XY *);

// 메인메뉴
void Page_Main();

// 첫 메뉴 창
void Page_Main2_Desgin();
int Page_Main2(); 
// 회원가입 1 로그인 0

//회원가입
void Page_SingIn_Desgin();
int Page_SingIn(People_num * P_num);

//로그인
void Page_Login_Desgin();
int Page_Login(char * id); // 성공시 0 강제 종료 -1

//메뉴
void Page_Menu_Desgin();
int Page_Menu();

//소개 글
void Page_Mangpang();

// My step
void Page_MyStep_Desgin();
int Page_MyStep(Person* person);

//Other step
void Page_OtherStep_Desgin();
int Page_OtherStep(Person* person);

//data.h

//사용자 입력 데이터 출력 함수
void showOtherStep(char* id);
void showMyStep(char* id);

//프로그램 시작시 전체 데이터 로드
void Load_People_data(People_num * P_num);

//로그인시 사용자 데이터 로드
void Load_User(Person * person, char * id);
void Load_OtherStep(Person * person, char * id);
void Load_MyStep(Person * person, char * id);

//사용자 함수
void show_Mystep_count(MyStep * data);
void show_Otherstep_count(OtherStep * data);

//로그아웃시 id폴더에 파일 생성 및 저장
void Save_MyStep_File(char * id, Person * person);
void Save_OtherStep_File(char* id, Person * person);

//전체 데이터에 사용지 입력 데이터 반영
void Save_MyStep_Data(Person* person, MyStep* mystep);
void Save_OtherStep_Data(Person* person, OtherStep* otherstep);

//프로그램 종료시 전체 데이터 저장

//그래프 출력
void PrintGraph(int arr[], int len);
//정렬
void InsertionSort(int len, int arr[]);
MyStep rank_MyStep(MyStep my);
OtherStep rank_OtherStep(OtherStep other);

int X = 0, Y = 0;


int main(void) {
	Person person;
	People_num P_num = { 0, };
	MyStep mystep[2] = { {0,},{0,} }; 
	OtherStep otherstep[2] = { {0,},{0,} };

	char buf[255] = { '\0' };
	char id[21] = {'\0'};
	int page = 0, check = 0;
	int my_c = 0, ot_c = 0;
	int sex = 0;

	char MyStep_AnswerList_Step1[][30] = { "150대 또는 그 이하", "160대", "170대", "180대 이상" };
	char MyStep_AnswerList_Step2[][30] = { "YES", "NO" };
	char MyStep_AnswerList_Step3[][30] = { "반 병 이하", "한 병까지", "두 병까지", "두 병 이상" };
	char MyStep_AnswerList_Step4[][30] = { "내향", "외향", "차분", "지적", "상냥", "감성", "낙천", "냉혈", "열정", "유머러스" };
	char MyStep_AnswerList_Step5[][30] = { "고양이상", "강아지상", "토끼상", "곰상", "공룡상" };
	char MyStep_AnswerList_Step6[][30] = { "얼굴", "몸매", "패션", "성격", "취미" }; //구글폼에는 취미(ex. 농구를 잘한다! 요리를 잘한다!)라고 적혀있으나, 그냥 취미라고 하자
	char MyStep_AnswerList_Step7[][30] = { "영화", "운동", "집콕", "쇼핑", "공부", "술", "여행", "클럽" };
	char MyStep_AnswerList_Step8[][30] = { "코노", "도서관", "버스여행", "한강", "pc방", "놀이동산", "바다", "산", "룸카페", "맛집" };
	char MyStep_AnswerList_Step9[][30] = { "상의 매장", "하의 매장", "악세서리 매장", "모자 매장" };
	char MyStep_AnswerList_Step10[][30] = { "매일", "일주일에 5~6회", "일주일에 3~4회", "일주일에 1~2회", "그 이하" };
	char MyStep_AnswerList_Step11[][30] = { "발라드", "팝", "알엔비", "힙합", "재즈", "edm", "ccm", "락" };

	char OtherStep_AnswerList_Step1[][30] = { "고양이상", "강아지상", "토끼상", "곰상", "공룡상" };
	char OtherStep_AnswerList_Step2[][30] = { "150대 또는 그 이하", "160대", "170대", "180대 이상" };
	char OtherStep_AnswerList_Step3[][30] = { "상관없다", "싫다" };
	char OtherStep_AnswerList_Step4[][30] = { "반 병 이하", "한 병까지", "두 병까지", "두 병 이상" };
	char OtherStep_AnswerList_Step5[][30] = { "낙천", "냉혈", "적극적", "유머러스", "내향적", "외향적", "지적", "차분", "감성적", "상냥" };
	char OtherStep_AnswerList_Step6[][30] = { "매일", "일주일에 5~6회", "일주일에 3~4회", "일주일에 1~2회", "그 이하" };
	char OtherStep_AnswerList_Step7[][30] = { "팝", "발라드", "알엔비", "락", "힙합", "재즈", "edm", "ccm" };
	char OtherStep_AnswerList_Step8[][30] = { "운동", "집콕", "영화", "술", "여행", "공부", "클럽", "쇼핑" };
	char OtherStep_AnswerList_Step9[][30] = { "얼굴", "몸매", "성격", "패션", "취미" };
	char OtherStep_AnswerList_Step10[][30] = { "상의", "하의", "모자", "악세서리" };
	char OtherStep_AnswerList_Step11[][30] = { "한강", "맛집" "pc방", "룸카페", "코노", "도서관", "버스여행", "바다", "산", "놀이동산" };
	char OtherStep_AnswerList_Step12[][30] = { "연상", "동갑", "연하" };



	Load_People_data(&P_num);
MAIN:
	Page_Main();
	page = Page_Main2();
	id[0] = '\0';
	END;
	if (page == 0) { //로그인 페이지
		END;
		
		check = Page_Login(id);
		if (check == 0) {
			Load_MyStep(&person, id);
			Load_OtherStep(&person, id);
			Load_User(&person, id);
			sex = person.member.sex - 1;
		MENU:
			page = Page_Menu();
			Goto_xy(0, 1);
			printf("MY : %d", my_c);
			Goto_xy(0, 2);
			printf("OT : %d", ot_c);
			switch (page + 1)
			{
			case 1: // 만팡소개
				Page_Mangpang();
				goto MAIN;
				break;
			case 2:// mystep 입력
				END;
				my_c = Page_MyStep(&person);
				if (my_c == 11)
					Save_MyStep_Data(&person, &mystep[sex]);
				goto MENU;
				break;
			case 3: //otherstep 입력
				END;
				ot_c = Page_OtherStep(&person);
				if (my_c == 12)
					Save_OtherStep_Data(&person, &otherstep[sex]);
				goto MENU;
				break;
			case 4: //기본정보 수정
				break;
			case 5: //분석화면 보기
				break;
			case 6: //로그아웃
				page = 0;
				if (my_c == 11) {
					Save_MyStep_File(id, &person);
				}
				if (ot_c == 12) {
					Save_OtherStep_File(id, &person);
				}
				// 사용자 폴더에 입력 정보 저장
				// 비정상 종료사 저장X
				id[0] = '\0'; //id 정보 해제
				Page_Mangpang();
				goto MAIN;
				break;
			default:
				break;
			}

		}
		else
			goto MAIN;
	}
	else if (page == 1) { //회원가입 페이지
		END;
		check = Page_SingIn(&P_num);
		goto MAIN;
	}
	else if (page == -1) { //프로그램 종료

		return 0;
	}
	
}

int print_NUM(char num[], int Max_num, int count) {
	int index = 0, sum = 0;
	int j = 0, i = 0;

	while (1)
	{
		if (_kbhit())
		{
			num[index] = _getch(); // num[index]안에 키보드에 압력받은 키 입력
			if (num[index] == BACK - 10)  // 백스페이스 키 입력시
			{
				if (index > 0)   // 배열에 입력된 값이 있을 경우
				{
					printf("\b \b"); // 콘솔창에서 뒤로 가기
					index--;
				}
				continue;

			}
			else if (num[index] == ENTER) // 엔터키 입력시
			{
				break;
			}
			else if (num[index] == ESC) {
				return -1;
			}
			else if (index >= count) // 글자수 넘어갈시
			{
				continue;
			}
			else if (num[index] >= '0' && num[index] <= '0'+Max_num) //Max_num내의 숫자 입력만 가능
			{
				printf("%c", num[index]);
				index++;
			}
		}
	}
	num[index] = '\0';
	return atoi(num);
}

int print_char(char str[], int count)
{

	int index = 0;

	while (1)
	{
		if (_kbhit())
		{
			str[index] = _getch();
			if (str[index] == BACK -10)
			{
				if (index > 0)
				{
					printf("\b \b");
					index--;
				}
				continue;

			}
			else if (str[index] == ENTER)
			{
				break;
			}
			else if (index >= count)
			{
				continue;
			}
			else if (str[index] == ESC)
			{
				return -1;
			}
			else
			{
				printf("%c", str[index]);
				index++;
			}
		}
	}
	str[index] = '\0';
	return 0;


}

int filter_num(char* temp, int size) {
	char* num;
	num = (char*)malloc(size*sizeof(char));
	int j = 0, n = 0;

	for (int i = 0; i < strlen(temp); i++) {
		if (temp[i] >= '0' && temp[i] <= '9') {
			num[j] = temp[i];
			j++;
		}
	}
	n = atoi(num);
	free(num);
	return n;
}

void Page_Size() {
	system("mode con cols=110  lines=30  | title = 만나라 팡팡이들아");
}

void Goto_xy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}//완성

int KeyControl() {
	int temp = _getch();

	if (temp == 224) {
		temp = _getch();

		switch (temp)
		{
		case 72:
			return UP;
			break;
		case 80:
			return DOWN;
			break;
		case 75:
			return LEFT;
			break;
		case 77:
			return RIGHT;
			break;
		default:
			break;
		}
	}
	else if (temp == 32) {
		return SPACE;
	}
	else if (temp == 13) {
		return ENTER;
	}
	else if (temp == 8) {
		return BACK;
	}
	else if (temp == ESC) {
		return ESC;
	}
	else {
		return temp;
	}
}

void print_s(int x, int y) {
	Goto_xy(x, y);
	printf("▶");
	X = x;
	Y = y;
}

void Goto_UP(XY* xy1, XY* xy2) {
	if (Y == xy1->y) {
		Goto_xy(xy1->x, xy1->y);
		printf("  ");
		Goto_xy(xy2->x, xy2->y);
		printf("▶");
		X = xy2->x;
		Y = xy2->y;
	}
}

void Goto_DOWN(XY* xy1, XY* xy2) {
	if (Y == xy1->y) {
		Goto_xy(xy1->x, xy1->y);
		printf("  ");
		Goto_xy(xy2->x, xy2->y);
		printf("▶");
		X = xy2->x;
		Y = xy2->y;
	}
}

void Goto_RIGHT(XY* xy1, XY* xy2) {
	if (X == xy1->x) {
		Goto_xy(xy1->x, xy1->y);
		printf("  ");
		Goto_xy(xy2->x, xy2->y);
		printf("▶");
		X = xy2->x;
		Y = xy2->y;
	}
}

void Goto_LEFT(XY* xy1, XY* xy2) {
	if (X == xy1->x) {
		Goto_xy(xy1->x, xy1->y);
		printf("  ");
		Goto_xy(xy2->x, xy2->y);
		printf("▶");
		X = xy2->x;
		Y = xy2->y;
	}
}

void IsCursor(char show)//커서숨기기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
// hide = 0 show = 1

void Delet_line(int y) {
	Goto_xy(0, y);
	for(int i =0;i<120;i++)
		printf(" ");
}

//Degin.h

void Page_Main() {
	Page_Size();
	IsCursor(0);
	Goto_xy(0, 6);
	printf("      ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
	printf("      ♥                                                                                            ♥\n");
	printf("      ♥    ■■      ■■       ■       ■■    ■  ■■■■     ■      ■■    ■  ■■■■■   ♥\n");
	printf("      ♥    ■ ■    ■ ■      ■■      ■ ■   ■  ■    ■    ■■     ■ ■   ■  ■           ♥\n");
	printf("      ♥    ■  ■  ■  ■    ■    ■    ■  ■  ■  ■■■■   ■  ■    ■  ■  ■  ■    ■■   ♥\n");
	printf("      ♥    ■   ■■   ■   ■■■■■   ■   ■ ■  ■        ■■■■   ■   ■ ■  ■      ■   ♥\n");
	printf("      ♥    ■    ■    ■  ■        ■  ■    ■■  ■       ■      ■  ■    ■■  ■■■■■   ♥\n");
	printf("      ♥                                                                                            ♥\n");
	printf("      ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
	printf("\n\n\n\n");
	printf("                                       -시작하려면 space를 눌려주세요-\n");
	while (1) {
		if (KeyControl() == SPACE)
			break;
	}
}//완성

void Page_Main2_Desgin() {
	Page_Size();
	Goto_xy(0, 6);
	printf("     ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
	printf("     ♥                                                                                                ♥\n");
	printf("     ♥      ■■      ■■       ■       ■■    ■  ■■■■     ■      ■■    ■  ■■■■■     ♥\n");
	printf("     ♥      ■ ■    ■ ■      ■■      ■ ■   ■  ■    ■    ■■     ■ ■   ■  ■             ♥\n");
	printf("     ♥      ■  ■  ■  ■    ■    ■    ■  ■  ■  ■■■■   ■  ■    ■  ■  ■  ■    ■■     ♥\n");
	printf("     ♥      ■   ■■   ■   ■■■■■   ■   ■ ■  ■        ■■■■   ■   ■ ■  ■      ■     ♥\n");
	printf("     ♥      ■    ■    ■  ■        ■  ■    ■■  ■       ■      ■  ■    ■■  ■■■■■     ♥\n");
	printf("     ♥                                                                                                ♥\n");
	printf("     ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
	Goto_xy(48, 19);
	printf("◎로그인하기");//Y=19
	Goto_xy(48, 20);
	printf("◎회원가입하기"); //Y =20
	Goto_xy(48, 21);
	printf("◎프로그램 종료"); //Y =21
}

int Page_Main2() {
	int key = 0;

	Page_Main2_Desgin();
	IsCursor(0);
	XY xy[3] = { { 46,19 },{ 46,20 },{46,21} };
	print_s(xy[0].x, xy[0].y);
	while (1) {
		key = KeyControl();
		if (key == DOWN) {
			if (Y == xy[0].y)
				Goto_DOWN(&xy[0], &xy[1]);
			if (Y == xy[1].y)
				Goto_DOWN(&xy[1], &xy[2]);
		}
		if (key == UP) {
			if (Y == xy[1].y)
				Goto_DOWN(&xy[1], &xy[0]);
			if (Y == xy[2].y)
				Goto_DOWN(&xy[2], &xy[1]);
		}
		if (key == ENTER)
			break;
	}

	CLS;

	if (Y == xy[0].y) {
		return 0; //로그인
	}
	else if (Y == xy[1].y) {
		return 1; //회원가입
	}
	else if (Y == xy[2].y) {
		return -1; // 프로그램 종료
	}
}

void Page_Login_Desgin() {
	Page_Size();
	Goto_xy(0, 6);
	printf("                ---------------------------------------------------------------------------\n\n");
	printf("                           ■        ■■■■■    ■■■■    ■■■  ■■    ■\n");
	printf("                           ■        ■      ■   ■             ■    ■ ■   ■\n");
	printf("                           ■        ■      ■  ■      ■■    ■    ■  ■  ■\n");
	printf("                           ■        ■      ■   ■      ■     ■    ■   ■ ■\n");
	printf("                           ■■■■  ■■■■■    ■■■■    ■■■  ■    ■■\n\n");
	printf("                ---------------------------------------------------------------------------\n");
	printf("\n\n");
}

int Page_Login(char * id) {
	//로그인
	char temp[43] = { '\0' };
	char pw[21] = { '\0' };
	char buf[255] = { '\0' };
	int n = 0;
	int key = 0;
	FILE* fp = NULL;

	CLS;
	Page_Login_Desgin();

	if (n == 0) {
		while (1)
		{
			key = 0;
			id[0] = '\0';

			Delet_line(17);
			Goto_xy(0, 17);
			printf("                                           ♡  ID   : ");//X=54 Y=17
			n = print_char(id, 20);
			if (n == 0) {
				strcpy_s(temp, sizeof(temp), "d://User//User_DATA//");
				strcat_s(temp, sizeof(temp), id);
				n = _chdir(temp);

				// 사용자 정보가 저장되어 있는 디렉토리로 작업 경로 변겅
				// 변경 시 -> 아이디 존재 -> 0
				// 변경 실패 시 -> 아이디 존재 X -> -1

				if (n == -1) {
					Goto_xy(40, 18);
					printf("아이디가 존재하지 않습니다.\n");
					key = KeyControl();
					print_char(temp, 0);
					Delet_line(18);
					continue;
				}
				else {
					// 아이디 존재 시
					fopen_s(&fp, "기본정보.txt", "rt"); // 기본정보 파일 열기
					if (fp != NULL) {
						pw[0] = '\0';
						fscanf_s(fp, "%s", pw, sizeof(pw));
						// 비밀 번호 입력 및 확인
						while (1) {
							Delet_line(19);
							Goto_xy(0, 19);
							printf("                                           ♡  PW   : ");
							temp[0] = '\0';
							n = print_char(temp, 20);
							if (n == 0) {
								printf("\n");
								key = strncmp(temp, pw, strlen(pw));
								if (key == 0) {
									return 1;
								}
								else {
									Goto_xy(45, 21);
									printf("비밀번호가 틀렸습니다.");
									print_char(temp, 0);
									Delet_line(21);
									continue;
								}
							}
							else if (n == -1) {// ESC로 강제종료시
								fclose(fp);
								return -1;
							}
						}
						fclose(fp);
					}
				}
			}
			else if (n == -1) {  // ESC로 강제종료시
				return -1;
			}
			return 0;
		}
	}
}

void Page_Menu_Desgin() {
	Page_Size();
	IsCursor(0);
	Goto_xy(0, 5);
	printf("                                               --------------\n");
	printf("                                                    MENU                   \n");
	printf("                                               --------------              \n");
	printf("                                                  |      |                 \n");
	printf("                                 ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡\n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                         1. MANPANG 소개                   \n");	//X=39,Y=12
	printf("                                         2. My STEP 입력하기               \n");
	printf("                                         3. Other's STEP 입력하기          \n");
	printf("                                         4. 기본 회원 정보 수정            \n");
	printf("                                         5. 분석 화면 보기                 \n");
	printf("                                         6. HOME(로그아웃)                 \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                 ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡\n");

}

int Page_Menu() {
	int key = 0;
	int index = 0;
	XY xy[6] = {
		{39,12},{39,13},{39,14},{39,15},{39,16},{39,17}
	};
	Page_Menu_Desgin();
	print_s(39, 12);
	while (1) {
		key = KeyControl();
		if (key == ENTER)
			break;
		if (key == UP) {
			if (index != 0) {
				Goto_UP(&xy[index], &xy[index - 1]);
				index--;
			}
		}
		if (key == DOWN) {
			if (index != 5) {
				Goto_DOWN(&xy[index], &xy[index + 1]);
				index++;
			}
		}
	}
	return index;
};

void Page_Mangpang() {
	printf("                                                              \n");
	printf("       What's MANPANG?                                        \n");
	printf("   ♡===========================================♡              \n");
	printf("                                                              \n");
	printf("      MANPANG은                                               \n");
	printf("                                                              \n");
	printf("      \"만나라, 팡팡이들아!\"의 줄임말로,                        \n");
	printf("      광운대학교에 재학 중인 남녀 학생들이                       \n");
	printf("      서로의 성향을 조금 더 재미있게 알아가기 위해                \n");
	printf("      만들게 된                                                \n");
	printf("                                                              \n");
	printf("      \"광운대 학생들의 연애 성향 통계 프로그램\"                \n");
	printf("                                                              \n");
	printf("      입니다.                                                  \n");
	printf("                                                              \n");
	printf("   ♡===========================================♡             \n");
	printf("                                                              \n");
}

void Page_SingIn_Desgin() {
	system("mode con cols=110  lines=50  | title = 만나라 팡팡이들아");


	printf("\n");
	printf("\n");
	printf("\n");
	printf("                                       ♥♥♥          ♥♥♥     \n");
	printf("                                     ♥♥♥♥♥      ♥♥♥♥♥   \n");
	printf("                                   ♥♥♥♥♥♥♥  ♥♥♥♥♥♥♥ \n");
	printf("                                   ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥ \n");
	printf("                                    ♥♥♥♥♥♥♥♥♥♥♥♥♥♥  \n");
	printf("        ♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♥♥♥♥♥♥♥♥♥♥♥♥♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡\n");
	printf("                                        ♥♥♥♥♥♥♥♥♥♥                                \n");
	printf("                                          ♥♥♥♥♥♥♥♥                                  \n");
	printf("                                            ♥♥♥♥♥♥                                    \n");
	printf("                                             ♥♥♥♥♥                                     \n");
	printf("                                               ♥♥♥                                       \n");
	printf("                                                 ♥                                         \n\n\n\n");


}

int Page_SingIn(People_num * P_num) {
	char temp_id[43] = { '\0' }; // 생성하고 싶은 아이디을 저장
	char temp[21] = { '\0' }; // 임시 저장 문자열
	char num[11] = { '\0' };
	int n = 0, key = 0;
	FILE* fp = NULL;
	Y = 16;
	X = 0;
	

	// 작업 디렉토리를 데이터가 저장된 디렉토리로 이동
	IsCursor(1);
	while (1) {
		temp_id[0] = '\0';
		temp[0] = '\0';
		strncpy_s(temp_id, sizeof(temp_id), "d://User//User_DATA//", strlen("d://User//User_DATA//"));
		CLS;
		Page_SingIn_Desgin();
		Goto_xy(0, 18);
		printf("                   ID(20자 이내 영어,숫자) : "); //X=45 Y=16
		n = print_char(temp,20);//아이디 입력
		if (n == -1)
			return -1;
		strncat_s(temp_id, sizeof(temp_id), temp, strlen(temp));

		// 해당 아이디의 파일 생성
		// 만약 파일이 존재하면 ERROR = -1 
		// -> 아이디가 존재
		// 존재하지 않을시 = 0
		// -> 아이디가 존재 X -> 아이디 파일 생성

		n = _mkdir(temp_id);
		if (n == -1) {
			CLS;
			Page_SingIn_Desgin();
			printf("                                    이미 존재하는 아이디입니다.\n");
			printf("                                          다시 입력하세요.\n");
			while(KeyControl() != ENTER){}
		}
		else {
			n = _chdir(temp_id);
			fopen_s(&fp, "기본정보.txt", "wt");
			break;
		}
	}
	IsCursor(1);

	Goto_xy(0, 20);
	printf("                   PW(20자 이내 영어,숫자) : ");
	temp[0] = '\0';
	n = print_char(temp, 20);
	if (n == -1)
		return -1;
	if (fp != NULL)
		fprintf(fp, "%s\n", temp);
	//비밀번호 입력 및 파일에 저장

	Goto_xy(0, 22);
	printf("                   닉네임(20자 이내 영어,숫자) : "); // X=45 Y=22
	temp[0] = '\0';
	n = print_char(temp, 20);
	if (n == -1)
		return -1;
	if (fp != NULL)
		fprintf(fp, "%s\n", temp);
	//닉네임 입력 및 파일에 저장

	XY xy_B = { 44,24 };
	XY xy_G = { 64,24 };

	IsCursor(0);
	Goto_xy(0, 24);
	printf("                   성별 선택               :   1.남자              2.여자");
	print_s(xy_B.x, xy_B.y);
	while (1) {
		key = KeyControl();
		if (key == RIGHT)
			Goto_RIGHT(&xy_B, &xy_G);//남자
		if (key == LEFT)
			Goto_LEFT(&xy_G, &xy_B);//여자
		if (key == ENTER)
			break;
		if (key == ESC)
			return -1;
		else
			continue;
	}
	// 성별 선택
	printf("\n\n");
	if (X == xy_B.x) {
		fprintf(fp, "%d %s\n", 1, "남자");
		P_num->B_num++;
	}
	else if (X == xy_G.x)
	{
		fprintf(fp, "%d %s\n", 2, "여자");
		P_num->G_num++;
	}
	// 성별저장 및 성별관련 총인원 증가

	IsCursor(1);
	Goto_xy(0, 26);
	printf("                   나이(숫자만 입력)       : ");
	n = print_NUM(num, 9, 2);
	if (n == -1)
		return -1;
	if (fp != NULL)
		fprintf(fp, "나이 : %d\n", n);

	Goto_xy(0, 28);
	printf("                   학번(숫자만 입력)       : ");
	num[0] = '\0';
	n = print_NUM(num, 9, 10);
	if (n == -1)
		return -1;
	if (fp != NULL)
		fprintf(fp, "학번 : %d\n", n);

	XY xy_area[16] = {
		{12,32},{27,32},{42,32},{57,32},{72,32},{87,32},
		{12,34},{27,34},{42,34},{57,34},{72,34},{87,34},
		{12,36},{27,36},{42,36},{57,36}
	};
	IsCursor(0);
	Goto_xy(0, 30);
	printf("                   거주 지역 선택");
	Goto_xy(14, 32);
	printf("1.서울특별시   2.부산광역시   3.대구광역시   4.인천광역시   5.광주광역시   6.대전광역시\n");
	Goto_xy(14, 34);
	printf("7.울산광역시   8.경기도       9.강원도       10.충청북도    11.충청남도    12.전라북도");
	Goto_xy(14, 36);
	printf("13.전라남도    14.경상북도    15.경상남도    16.제주도\n\n");

	print_s(xy_area[0].x, xy_area[0].y);
	X = xy_area[0].x;
	Y = xy_area[0].y;
	n = 0;
	while (1) {
		//커서이동
		key = KeyControl();
		if (key == ESC)
			return -1;
		if (key == ENTER)
			break;
		if (key == UP) {
			if (Y != 32) {
				Goto_UP(&xy_area[n], &xy_area[n - 6]);
				n -= 6;
			}
		}
		if (key == DOWN) {
			if (X == 72 || X == 87) {
				if (Y != 34) {
					Goto_DOWN(&xy_area[n], &xy_area[n + 6]);
					n += 6;
				}
			}
			else {
				if (Y != 36) {
					Goto_DOWN(&xy_area[n], &xy_area[n + 6]);
					n += 6;
				}
			}
		}
		if (key == LEFT) {
			if (X != 12) {
				Goto_LEFT(&xy_area[n], &xy_area[n - 1]);
				n--;
			}
		}
		if (key == RIGHT) {
			if (Y == 32 || Y == 34) {
				if (X != 87) {
					Goto_RIGHT(&xy_area[n], &xy_area[n + 1]);
					n++;
				}
			}
			else if (Y == 36) {
				if (X != 57) {
					Goto_RIGHT(&xy_area[n], &xy_area[n + 1]);
					n++;
				}
			}
		}
		X = xy_area[n].x;
		Y = xy_area[n].y;
	}
	if (fp != NULL) {
		fprintf(fp, "지역번호 : %d\n", n);
	}
	// 지역 선택 및 저장
	P_num->T_num++;
	return 0;
}

void Page_MyStep_Desgin() {

	system("mode con cols=110  lines=20  | title = 만나라 팡팡이들아");
	Goto_xy(0, 4);
	printf("           ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
	printf("           ♥                                                                                  ♥\n");
	printf("           ♥    ■■      ■■               ■■■■  ■■■■■  ■■■■■  ■■■■■     ♥\n");
	printf("           ♥    ■ ■    ■ ■   ■    ■   ■             ■      ■          ■       ■    ♥\n");
	printf("           ♥    ■  ■  ■  ■    ■  ■     ■■■■      ■      ■■■■■  ■■■■■     ♥\n");
	printf("           ♥    ■   ■■   ■     ■■             ■     ■      ■          ■             ♥\n");
	printf("           ♥    ■    ■    ■      ■       ■■■■      ■      ■■■■■  ■             ♥\n");
	printf("           ♥                       ■                                                         ♥\n");
	printf("           ♥                                                                                  ♥\n");
	printf("           ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
	printf("\n\n\n\n");

}

int Page_MyStep(Person* person) {
	int temp = 0;
	char num[2];
	int i = 0;

	CLS;
	Page_MyStep_Desgin();
	IsCursor(1);
	for (i = 0; i < 11; i++) {
		Delet_line(14);
		Delet_line(15);
		Delet_line(16);
		temp = 0;
		print_s(13, 14);
		switch (i)
		{
		case 0:
			printf("1. 키가 몇이야 ?");
			Goto_xy(13, 15);
			printf("(1: 150대 또는 그 이하, 2: 160대, 3: 170대, 4: 180대 이상)");
			Goto_xy(32, 14);
			break;
		case 1:
			printf("2. 혹시 지금 흡연자야 ?");
			Goto_xy(13, 15);
			printf("(1: YES, 2: NO)");
			Goto_xy(39, 14);
			break;
		case 2:
			printf("3. 주량이 어떻게 되니 ?");
			Goto_xy(13, 15);
			printf("(1: 반 병 이하, 2: 한 병까지, 3: 두 병까지, 4: 두 병 이상)");
			Goto_xy(39, 14);
			break;
		case 3:
			printf("4. 너의 성격을 가장 잘 표현해주는 키워드 한 가지는 ?");
			Goto_xy(13, 15);
			printf("(1: 내향, 2: 외향, 3: 차분, 4: 지적, 5: 상냥)");
			Goto_xy(13, 16);
			printf("(6: 감성, 7: 낙천, 8: 냉혈, 9: 열정, 10: 유머러스)");
			Goto_xy(68, 14);
			break;
		case 4:
			printf("5. 너가 생각하기에 너의 얼굴상은 어떤 부류에 속하는 것 같아 ?");
			Goto_xy(13, 15);
			printf("(1: 고양이, 2: 강아지, 3: 토끼, 4: 곰, 5: 공룡) ");
			Goto_xy(77, 14);
			break;
		case 5:
			printf("6. 내가 이것만큼은 자신있다!!!!하는게 어디야 ?");
			Goto_xy(13, 15);
			printf("(1: 얼굴, 2: 몸매, 3: 패션, 4: 성격, 5: 취미(ex.농구를 잘한다!요리를 잘한다!))  ");
			Goto_xy(63, 14);
			break;
		case 6:
			printf("7. 너가 제일 좋아하는 활동이 뭐야 ?");
			Goto_xy(13, 15);
			printf("(1: 영화, 2: 운동, 3: 집콕, 4: 쇼핑, 5: 공부, 6: 술, 7: 여행, 8: 클럽)  ");
			Goto_xy(51, 14);
			break;
		case 7:
			printf("8. 너가 지금 제일 가고 싶은 장소가 어디야 ?");
			Goto_xy(13, 15);
			printf("(1: 코노, 2: 도서관, 3: 버스여행, 4: 한강, 5: pc방)");
			Goto_xy(13, 16);
			printf("(6: 놀이동산, 7: 한강, 8: 바다, 9: 산, 10: 룸카페) ");
			Goto_xy(59, 14);
			break;
		case 8:
			printf("9. 너가 쇼핑을 하러 왔다면 가장 먼저 향하는 매장은 ?");
			Goto_xy(13, 15);
			printf("(1: 상의 매장, 2: 하의 매장, 3: 악세서리 매장, 4: 모자 매장)");
			Goto_xy(68, 14);
			break;
		case 9:
			printf("10. 사랑하는 상대가 있다면, 일주일에 보통 몇 번정도 만날 것 같아 ?");
			Goto_xy(13, 15);
			printf("(1: 매일, 2: 일주일에 5~6회, 3: 일주일에 3~4회, 4: 일주일에 1~2회, 5: 그 이하)");
			Goto_xy(82, 14);
			break;
		case 10:
			printf("11. 너가 제일 좋아하는 음악 장르가 뭐야 ?");
			Goto_xy(13, 15);
			printf("(1: 발라드, 2: 팝, 3: 알엔비, 4: 힙합, 5: 락, 6: 재즈, 7: edm, 8: ccm)");
			Goto_xy(57, 14);
			break;
		default:
			break;
		}
		// 질문 출력
		num[0] = '\0';
		temp = print_NUM(num, 9, 2);
		if (temp == -1) { //ESC를 누를 경우 강제 종료
			break;
		}
		person->mystep[i] = temp; // 질문 번호에 해당되는 인덱스 번호의 배열안에 사용자가 선택한 질문 번호 저장


		Goto_xy(14, 14);
	}
	return i;
}

void Page_OtherStep_Desgin() {
	Page_Size();
	Goto_xy(0,4);
	printf(" ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
	printf(" ♥                                                                                                        ♥\n");
	printf(" ♥     ■■■■       ■     ■                              ■■■■  ■■■■■ ■■■■■ ■■■■■   ♥\n");
	printf(" ♥    ■      ■      ■     ■                             ■             ■     ■         ■       ■  ♥\n");
	printf(" ♥   ■        ■ ■■■■■ ■         ■■   ■   ■■    ■             ■     ■         ■       ■  ♥\n");
	printf(" ♥   ■        ■     ■     ■■■■  ■  ■  ■  ■        ■■■■      ■     ■■■■■ ■■■■■   ♥\n");
	printf(" ♥   ■        ■     ■     ■    ■ ■■■■ ■ ■                ■     ■     ■         ■           ♥\n");
	printf(" ♥    ■      ■      ■     ■    ■  ■      ■■                 ■     ■     ■         ■           ♥\n");
	printf(" ♥     ■■■■       ■     ■    ■   ■■   ■            ■■■■      ■     ■■■■■ ■           ♥\n");
	printf(" ♥                                                                                                        ♥\n");
	printf(" ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");

}

int Page_OtherStep(Person* person) {
	int temp = 0;
	char num[2];
	int i = 0;
	CLS;
	Page_OtherStep_Desgin();
	IsCursor(1);
	for (i = 0; i < 12; i++) {
		Delet_line(16);
		Delet_line(17);
		Delet_line(18);
		temp = 0;
		print_s(13, 16);
		switch (i)
		{
		case 0:
			printf("1. 너가 좋아하는 상대의 얼굴상을 동물로 비유해보면 뭐야 ?");
			Goto_xy(13, 17);
			printf("(1 : 강아지, 2 : 고양이, 3 : 토끼, 4 : 곰, 5 : 공룡)");
			Goto_xy(73, 16);
			break;
		case 1:
			printf("2. 너가 가장 원하는 상대의 키는 대략 어느 구간에 속해 ?");
			Goto_xy(13, 17);
			printf("(1 : 150대 또는 그 이하, 3 : 160대, 3 : 170대, 4 :180대 이상)");
			Goto_xy(71, 16);
			break;
		case 2:
			printf("3. 만약 너가 좋아하고 있는 상대방이 흡연자면 어떨 것 같아 ?");
			Goto_xy(13, 17);
			printf("(1 : 상관없다, 2 : 싫다)");
			Goto_xy(75, 16);
			break;
		case 3:
			printf("4. 상대방의 주량이 대충 어느정도까지 받아줬으면 좋겠어 ?");
			Goto_xy(13, 17);
			printf("(1 : 반병 이하, 2 : 한 병까지, 3 : 두 병까지, 4 : 두 병 이상)");
			Goto_xy(72, 16);
			break;
		case 4:
			printf("5. 너가 원하는 상대의 성격을 키워드로 표현해보자면 ?");
			Goto_xy(13, 17);
			printf("(1 : 낙천적, 2 : 냉혈적, 3 : 적극적, 4 : 유머러스적, 5 : 내향적)");
			Goto_xy(13, 18);
			printf("(6 : 외향적, 7 : 지적, 8 : 차분, 9 : 감성적, 10 : 상냥)");
			Goto_xy(68, 16);
			break;
		case 5:
			printf("6. 사랑하는 상대와 일주일에 몇 번 정도 만났으면 좋겠어 ?");
			Goto_xy(13, 17);
			printf("(1 : 매일, 2 : 일주일에 5~6회, 3 : 일주일에 3~4회, 4 : 일주일에 1~2회, 5 : 그 이하)");
			Goto_xy(72, 16);
			break;
		case 6:
			printf("7. 너가 상대와 같이 음악을 듣는다면 선곡하고 싶은 장르는 ?");
			Goto_xy(13, 17);
			printf("(1 : 팝, 2 : 발라드, 3 : 알엔비, 4 : 락, 5 : 힙합, 6 : 재즈, 7 : edm, 8 : ccm)");
			Goto_xy(74, 16);
			break;
		case 7:
			printf("8. 상대와 같이 하고 싶은 활동이 뭐야 ?");
			Goto_xy(13, 17);
			printf("(1 : 운동, 2 : 집콕, 3 : 영화, 4 : 술, 5 : 여행, 6 : 공부, 7 : 클럽, 8 : 쇼핑)");
			Goto_xy(54, 16);
			break;
		case 8:
			printf("9. 상대를 바라볼 때 중요시 하는 요소가 뭐야 ?");
			Goto_xy(13, 17);
			printf("(1 : 얼굴, 2 : 몸매, 3 : 성격, 4 : 패션, 5 : 취미)");
			Goto_xy(61, 16);
			break;
		case 9:
			printf("10.상대와 커플템을 맞춘다면 가장 맞추고 싶은 게 뭐야 ?");
			Goto_xy(13, 17);
			printf("(1 : 상의, 2 : 하의, 3 : 모자, 4 : 악세서리)");
			Goto_xy(70, 16);
			break;
		case 10:
			printf("11.상대와 지금 바로!!!같이 가고 싶은 장소가 어디야 ?");
			Goto_xy(13, 17);
			printf("(1 : 한강, 2 : 맛집, 3 : pc방, 4 : 룸카페, 5 : 코노)");
			Goto_xy(13, 18);
			printf("(6 : 도서관, 7 : 버스여행. 8 : 바다, 9 : 산, 10 : 놀이동산)");
			Goto_xy(68, 16);
			break;
		case 11:
			printf("12. 연상이 좋아? 동갑이 좋아? 아니면 연하가 좋아?");
			Goto_xy(13, 17);
			printf("(1 : 연상, 2 : 동갑, 3 : 연하)");
			Goto_xy(65, 16);
			break;
		default:
			break;
		}
		// 질문 출력
		num[0] = '\0';
		temp = print_NUM(num, 9, 2);
		if (temp == -1)//ESC를 누를 경우 강제 종료
			break;
		person->otherstep[i] = temp; // 질문 번호에 해당되는 인덱스 번호의 배열안에 사용자가 선택한 질문 번호 저장

		Goto_xy(14, 14);
	}
	return i;

}

void showMyStep(char* id)
{
	FILE* fp;
	char temp[43] = { '\0' };
	int n = 0, temp_n = 0;
	int ansnum; char anstext[20];

	temp[0] = '\0';
	strcpy_s(temp, sizeof(temp), "d://User//User_DATA//");
	strncat_s(temp, sizeof(temp), id, strlen(id));
	n = _chdir(temp);

	if (n == 0)
	{
		fopen_s(&fp, "MyStep.txt", "rt");
		if (fp != NULL)
		{
			while (n == 0)
			{
				fscanf_s(fp, "%d", &temp_n);
				switch (temp_n)
				{
				case 1:
					printf("1. 키가 몇이야?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext,sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 2:
					printf("2. 혹시 지금 흡연자야?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 3:
					printf("3. 주량이 어떻게 되니?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 4:
					printf("4. 너의 성격을 가장 잘 표현해주는 키워드 한 가지는?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 5:
					printf("5. 너가 생각하기에 너의 얼굴상은 어떤 부류에 속하는 것 같아?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 6:
					printf("6. 내가 이것만큼은 자신있다!!! 하는게 어디야?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 7:
					printf("7. 너가 제일 좋아하는 활동이 뭐야?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 8:
					printf("8. 너가 지금 제일 가고 싶은 장소가 어디야?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 9:
					printf("9. 너가 쇼핑을 하러 왔다면 가장 먼저 향하는 매장은?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 10:
					printf("10. 사랑하는 상대가 있다면, 일주일에 보통 몇 번정도 만날 것 같아?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 11:
					printf("11. 너가 제일 좋아하는 음악 장르가 뭐야?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				default:
					break;

				}
			}
		}
	}
}

void showOtherStep(char* id)
{
	FILE* fp;
	char temp[43] = { '\0' };
	int n = 0, temp_n = 0;
	int ansnum; char anstext[20];

	temp[0] = '\0';
	strcpy_s(temp, sizeof(temp), "d://User//User_DATA//");
	strncat_s(temp, sizeof(temp), id, strlen(id));
	n = _chdir(temp);

	if (n == 0)
	{
		fopen_s(&fp, "OtherStep.txt", "rt");
		if (fp != NULL)
		{
			while (n == 0)
			{
				fscanf_s(fp, "%d", &temp_n);
				switch (temp_n)
				{
				case 1:
					printf("1. 너가 좋아하는 상대의 얼굴상을 동물로 비유해보자면?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", &anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 2:
					printf("2. 너가 가장 원하는 상대의 키는 대략 어느 구간에 속해?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 3:
					printf("3. 만약 너가 좋아하고 있는 상대방이 흡연자면 어떨것 같아?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 4:
					printf("4. 너가 바라는 상대방의 주량은?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 5:
					printf("5. 너가 원하는 상대의 성격을 키워드로 표현해보자면?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 6:
					printf("6. 사랑하는 상대와 일주일에 몇 번 정도 만났으면 좋겠어?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 7:
					printf("7. 너가 상대와 같이 음악을 듣는다면 선곡하고 싶은 장르는?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 8:
					printf("8. 상대와 같이 하고싶은 활동은?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 9:
					printf("9. 상대를 바라볼 때 중요시 하는 요소는?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 10:
					printf("10. 상대와 커플템을 맞춘다면 가장 맞추고 싶은 것은?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 11:
					printf("11. 상대와 지금 바로!! 같이 가고 싶은 장소는?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
					break;
				case 12:
					printf("12. 연상/연하/동갑 중 고르자면?  ");
					fscanf_s(fp, "%d", &ansnum);
					printf("%d: ", ansnum);
					fscanf_s(fp, "%s", anstext, sizeof(anstext));
					printf("%s\n", anstext);
				default:
					break;

				}
			}
		}
	}
}

//data.h

//로그인시 사용자에 대한 불러오기
void Load_User(Person * person, char* id) {
	// 로그인 후 사용자 데이터 받아오기
	FILE* fp;
	char temp[43] = { '\0' };
	int n = 0, temp_n = 0;
	long f;

	temp[0] = '\0';
	strcpy_s(temp, sizeof(temp), "d://User//User_DATA//");
	strncat_s(temp, sizeof(temp), id, strlen(id));
	n = _chdir(temp);

	if(n == 0) {
		// 기본정보 불러오기
		fopen_s(&fp, "기본정보.txt", "rt");
		if (fp != NULL) {
			fscanf_s(fp, "%d", &temp_n); // 비밀번호 넘기기
			fscanf_s(fp, "%s", person->member.name, sizeof(person->member.name)); //닉네임 받아오기
			fscanf_s(fp, "%d", &person->member.sex); // 성별 받아오기
			fgets(temp, sizeof(temp), fp); // 개행문자 제거
			for (int i = 1; i < 4;i++) {
				temp[0] = '0';
				fgets(temp,sizeof(temp),fp);
				switch (i) {
				case 1: //나이
					person->member.age = filter_num(temp, 2);
					break;
				case 2: //학번
					person->member.s_num = filter_num(temp, 10);
					break;
				case 3: //지역번호
					person->member.area = filter_num(temp, 1);
					break;
				default:
					break;
				}
			}
			fclose(fp);
		}

	}
}

void Load_MyStep(Person* person, char* id) {
	// 로그인 후 사용자 데이터 받아오기
	FILE* fp;
	char temp[43] = { '\0' };
	int n = 0, temp_n = 0;

	temp[0] = '\0';
	strcpy_s(temp, sizeof(temp), "d://User//User_DATA//");
	strncat_s(temp, sizeof(temp), id, strlen(id));
	n = _chdir(temp);
	
	if (n == 0) {
		// MyStep 정보 불러오기
		fp = NULL;
		fopen_s(&fp, "MyStep.txt", "rt");
		if (fp != NULL)
		{
			for(temp_n = 0; temp_n < 11; temp_n++) {
				n = 0;
				// 질문 번호 읽어오기
				// 각각 질문에 사용자가 선택한 번호를 배열에 저장
				if (temp_n == 0) {
					//1번 질문일때 키 숫자를 제외함
					fscanf_s(fp, "%d", &person->mystep[1]); //선지 숫자 받기
					fgets(temp, 43, fp); // 그외 넘기기
				}
				else {
					fgets(temp, 43, fp);
					n = filter_num(temp, 2);
					person->mystep[temp_n] = n;
				}
			}
			fclose(fp);
		}
		
	}
}

void Load_OtherStep(Person* person, char* id) {
	// 로그인 후 사용자 데이터 받아오기
	FILE* fp;
	char temp[43] = { '\0' };
	int n = 0, temp_n = 0;

	temp[0] = '\0';
	strcpy_s(temp, sizeof(temp), "d://User//User_DATA//");
	strncat_s(temp, sizeof(temp), id, strlen(id));
	n = _chdir(temp);

	if (n == 0) {
		//Other step 불러오기
		fp = NULL;
		fopen_s(&fp, "OtherStep.txt", "rt");
		if (fp != NULL)
		{
			for (temp_n = 0; temp_n < 12; temp_n++) {
				n = 0;
				// 질문 번호 읽어오기
				// 각각 질문에 사용자가 선택한 번호를 배열에 저장
				if (temp_n == 1) { 
					//2번 질문일때 키 숫자를 제외함
					fscanf_s(fp, "%d", &person->otherstep[1]); //선지 숫자 받기
					fgets(temp, 43, fp); // 그외 넘기기
				}
				else {
					fgets(temp, 43, fp);
					n = filter_num(temp, 2);
					person->otherstep[temp_n] = n;
				}
			}
			fclose(fp);
		}
	}
}

void Load_People_data(People_num* P_num) {
	int n = 0;
	FILE* fp = NULL;

	n = _chdir("D://User//DATA");

	if (n == 0) {
		fopen_s(&fp, "Person_Number.txt", "rt");
		if (fp != NULL) {
			fscanf_s(fp, "%d", &P_num->T_num);
			fscanf_s(fp, "%d", &P_num->B_num);
			fscanf_s(fp, "%d", &P_num->G_num);
		}
	}

}

// 관리지용 함수
void show_Mystep_count(MyStep * data)
{
	printf("< MyStep >\n");
	printf("step1 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data->step1[0], data->step1[1], data->step1[2], data->step1[3]);
	printf("step2 - 1번:%d명 2번:%d명\n", data->step2[0], data->step2[1]);
	printf("step3 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data->step3[0], data->step3[1], data->step3[2], data->step3[3]);
	printf("step4 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명 9번:%d명 10번:%d명\n", data->step4[0], data->step4[1], data->step4[2], data->step4[3], data->step4[4], data->step4[5], data->step4[6], data->step4[7], data->step4[8], data->step4[9]);
	printf("step5 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data->step5[0], data->step5[1], data->step5[2], data->step5[3], data->step5[4]);
	printf("step6 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data->step6[0], data->step6[1], data->step6[2], data->step6[3], data->step6[4]);
	printf("step7 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명\n", data->step7[0], data->step7[1], data->step7[2], data->step7[3], data->step7[4], data->step7[5], data->step7[6], data->step7[7]);
	printf("step8 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명 9번:%d명 10번:%d명\n", data->step8[0], data->step8[1], data->step8[2], data->step8[3], data->step8[4], data->step8[5], data->step8[6], data->step8[7], data->step8[8], data->step8[9]);
	printf("step9 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data->step9[0], data->step9[1], data->step9[2], data->step9[3]);
	printf("step10 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data->step10[0], data->step10[1], data->step10[2], data->step10[3], data->step10[4]);
	printf("step11 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명\n", data->step11[0], data->step11[1], data->step11[2], data->step11[3], data->step11[4], data->step11[5], data->step11[6], data->step11[7]);
}

void show_Otherstep_count(OtherStep * data)
{
	printf("< OtherStep >\n");
	printf("step1 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data->step1[0], data->step1[1], data->step1[2], data->step1[3], data->step1[4]);
	printf("step2 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data->step2[0], data->step2[1], data->step2[2], data->step2[3]);
	printf("step3 - 1번:%d명 2번:%d명\n", data->step3[0], data->step3[1]);
	printf("step4 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data->step4[0], data->step4[1], data->step4[2], data->step4[3]);
	printf("step5 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명 9번:%d명 10번:%d명\n", data->step5[0], data->step5[1], data->step5[2], data->step5[3], data->step5[4], data->step5[5], data->step5[6], data->step5[7], data->step5[8], data->step5[9]);
	printf("step6 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data->step6[0], data->step6[1], data->step6[2], data->step6[3], data->step6[4]);
	printf("step7 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명\n", data->step7[0], data->step7[1], data->step7[2], data->step7[3], data->step7[4], data->step7[5], data->step7[6], data->step7[7]);
	printf("step8 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명\n", data->step8[0], data->step8[1], data->step8[2], data->step8[3], data->step8[4], data->step8[5], data->step8[6], data->step8[7]);
	printf("step9 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data->step9[0], data->step9[1], data->step9[2], data->step9[3], data->step9[4]);
	printf("step10 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data->step10[0], data->step10[1], data->step10[2], data->step10[3]);
	printf("step11 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명 9번:%d명 10번:%d명\n", data->step11[0], data->step11[1], data->step11[2], data->step11[3], data->step11[4], data->step11[5], data->step11[6], data->step11[7], data->step11[8], data->step11[9]);
	printf("step12 - 1번:%d명 2번:%d명 3번:%d명\n", data->step12[0], data->step12[1], data->step12[2]);
}

//로그아웃 시 사용자 정보 저장
void Save_MyStep_File(char* id, Person* person){
	// 로그아웃 시 현제 MyStep 정보 저장
	char buf[43] = { '\0' };
	int n = 0, i = 0;
	FILE* fp = NULL;

	// id에 따른 폴더 이동
	strncpy_s(buf, sizeof(buf), "d://User//User_DATA//", sizeof("d://User//User_DATA//"));
	strncat_s(buf, sizeof(buf), id, strlen(id));

	n = _chdir(buf);
	
	if (n == 0) {
		fopen_s(&fp, "MyStep.txt", "wt");
		if (fp != NULL) {
			for (i = 0; i < 11; i++) {
				fprintf_s(fp, "%d ", person->mystep[i]);
				switch (i)
				{
				case 0:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "150대 또는 그 이하");
						break;
					case 2:
						fprintf(fp, "%s\n", "160대");
						break;
					case 3:
						fprintf(fp, "%s\n", "170대");
						break;
					case 4:
						fprintf(fp, "%s\n", "180대 이상");
						break;
					default:
						break;
					}
					break;
				case 1:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "YES");
						break;
					case 2:
						fprintf(fp, "%s\n", "NO");
						break;
					default:
						break;
					}
					break;
				case 2:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "반 병 이하");
						break;
					case 2:
						fprintf(fp, "%s\n", "한 병까지");
						break;
					case 3:
						fprintf(fp, "%s\n", "두 병까지");
						break;
					case 4:
						fprintf(fp, "%s\n", "두 병 이상");
						break;
					default:
						break;
					}
					break;
				case 3:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "내향");
						break;
					case 2:
						fprintf(fp, "%s\n", "외향");
						break;
					case 3:
						fprintf(fp, "%s\n", "차분");
						break;
					case 4:
						fprintf(fp, "%s\n", "지적");
						break;
					case 5:
						fprintf(fp, "%s\n", "상냥");
						break;
					case 6:
						fprintf(fp, "%s\n", "감성");
						break;
					case 7:
						fprintf(fp, "%s\n", "낙천");
						break;
					case 8:
						fprintf(fp, "%s\n", "냉혈");
						break;
					case 9:
						fprintf(fp, "%s\n", "열정");
						break;
					case 10:
						fprintf(fp, "%s\n", "유머러스");
						break;
					default:
						break;
					}
					break;
				case 4:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "고양이상");
						break;
					case 2:
						fprintf(fp, "%s\n", "강아지상");
						break;
					case 3:
						fprintf(fp, "%s\n", "토끼상");
						break;
					case 4:
						fprintf(fp, "%s\n", "곰상");
						break;
					case 5:
						fprintf(fp, "%s\n", "공룡상");
						break;
					default:
						break;
					}
					break;
				case 5:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "얼굴");
						break;
					case 2:
						fprintf(fp, "%s\n", "몸매");
						break;
					case 3:
						fprintf(fp, "%s\n", "패션");
						break;
					case 4:
						fprintf(fp, "%s\n", "성격");
						break;
					case 5:
						fprintf(fp, "%s\n", "취미 (ex. 농구를 잘한다! 요리를 잘한다!)");
						break;
					default:
						break;
					}
					break;
				case 6:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "영화");
						break;
					case 2:
						fprintf(fp, "%s\n", "운동");
						break;
					case 3:
						fprintf(fp, "%s\n", "집콕");
						break;
					case 4:
						fprintf(fp, "%s\n", "쇼핑");
						break;
					case 5:
						fprintf(fp, "%s\n", "공부");
						break;
					case 6:
						fprintf(fp, "%s\n", "술");
						break;
					case 7:
						fprintf(fp, "%s\n", "여행");
						break;
					case 8:
						fprintf(fp, "%s\n", "클럽");
						break;
					default:
						break;
					}
					break;
				case 7:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "코노");
						break;
					case 2:
						fprintf(fp, "%s\n", "도서관");
						break;
					case 3:
						fprintf(fp, "%s\n", "버스여행");
						break;
					case 4:
						fprintf(fp, "%s\n", "한강");
						break;
					case 5:
						fprintf(fp, "%s\n", "pc방");
						break;
					case 6:
						fprintf(fp, "%s\n", "놀이동산");
						break;
					case 7:
						fprintf(fp, "%s\n", "바다");
						break;
					case 8:
						fprintf(fp, "%s\n", "산");
						break;
					case 9:
						fprintf(fp, "%s\n", "룸카페");
						break;
					case 10:
						fprintf(fp, "%s\n", "맛집");
						break;
					default:
						break;
					}
					break;
				case 8:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "상의 매장");
						break;
					case 2:
						fprintf(fp, "%s\n", "하의 매장");
						break;
					case 3:
						fprintf(fp, "%s\n", "악세서리 매장");
						break;
					case 4:
						fprintf(fp, "%s\n", "모자 매장");
						break;
					default:
						break;
					}
					break;
				case 9:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "매일");
						break;
					case 2:
						fprintf(fp, "%s\n", "일주일에 5~6회");
						break;
					case 3:
						fprintf(fp, "%s\n", "일주일에 3~4회");
						break;
					case 4:
						fprintf(fp, "%s\n", "일주일에 1~2회");
						break;
					case 5:
						fprintf(fp, "%s\n", "그 이하");
						break;
					default:
						break;
					}
					break;
				case 10:
					switch (person->mystep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "발라드");
						break;
					case 2:
						fprintf(fp, "%s\n", "팝");
						break;
					case 3:
						fprintf(fp, "%s\n", "힙합");
						break;
					case 4:
						fprintf(fp, "%s\n", "재즈");
						break;
					case 5:
						fprintf(fp, "%s\n", "edm");
						break;
					case 6:
						fprintf(fp, "%s\n", "ccm");
						break;
					case 7:
						fprintf(fp, "%s\n", "락");
						break;
					default:
						break;
					}
					break;
				}
			}
		}
	}

}

void Save_OtherStep_File(char* id, Person* person) {
	// 로그아웃 시 현제 OtherStep 정보 저장
	char buf[43] = { '\0' };

	int n = 0, i = 0;
	FILE* fp = NULL;

	// id에 따른 폴더 이동
	strncpy_s(buf, sizeof(buf), "d://User//User_DATA//", sizeof("d://User//User_DATA//"));
	strncat_s(buf, sizeof(buf), id, strlen(id));

	n = _chdir(buf);
	
	if (n == 0) {
		fopen_s(&fp, "OtherStep.txt", "wt");
		if (fp != NULL) {
			for (i = 0; i < 11; i++) {
				fprintf_s(fp, "%d ", person->otherstep[i]);
				switch (i)
				{
				case 0:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "강아지상");
						break;
					case 2:
						fprintf(fp, "%s\n", "고양이상");
						break;
					case 3:
						fprintf(fp, "%s\n", "토끼상");
						break;
					case 4:
						fprintf(fp, "%s\n", "곰상");
						break;
					case 5:
						fprintf(fp, "%s\n", "공룡상");
						break;
					default:
						break;
					}
					break;
				case 1:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "150대 또는 그 이하");
						break;
					case 2:
						fprintf(fp, "%s\n", "160대");
						break;
					case 3:
						fprintf(fp, "%s\n", "170대");
						break;
					case 4:
						fprintf(fp, "%s\n", "180대 이상");
						break;
					default:
						break;
					}
					break;
				case 2:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "상관없다");
						break;
					case 2:
						fprintf(fp, "%s\n", "싫다");
						break;
					}
					break;
				case 3:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "반 병 이하");
						break;
					case 2:
						fprintf(fp, "%s\n", "한 병까지");
						break;
					case 3:
						fprintf(fp, "%s\n", "두 병까지");
						break;
					case 4:
						fprintf(fp, "%s\n", "두 병 이상");
						break;
					default:
						break;
					}
					break;
				case 4:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "낙천");
						break;
					case 2:
						fprintf(fp, "%s\n", "냉혈");
						break;
					case 3:
						fprintf(fp, "%s\n", "적극");
						break;
					case 4:
						fprintf(fp, "%s\n", "유머러스");
						break;
					case 5:
						fprintf(fp, "%s\n", "내향");
						break;
					case 6:
						fprintf(fp, "%s\n", "외향");
						break;
					case 7:
						fprintf(fp, "%s\n", "지적");
						break;
					case 8:
						fprintf(fp, "%s\n", "차분");
						break;
					case 9:
						fprintf(fp, "%s\n", "감성");
						break;
					case 10:
						fprintf(fp, "%s\n", "상냥");
						break;
					default:
						break;
					}
					break;
				case 5:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "매일");
						break;
					case 2:
						fprintf(fp, "%s\n", "일주일에 5~6회");
						break;
					case 3:
						fprintf(fp, "%s\n", "일주일에 3~4회");
						break;
					case 4:
						fprintf(fp, "%s\n", "일주일에 1~2회");
						break;
					case 5:
						fprintf(fp, "%s\n", "그 이하");
						break;
					default:
						break;
					}
					break;
				case 6:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "팝");
						break;
					case 2:
						fprintf(fp, "%s\n", "발라드");
						break;
					case 3:
						fprintf(fp, "%s\n", "알앤비");
						break;
					case 4:
						fprintf(fp, "%s\n", "락");
						break;
					case 5:
						fprintf(fp, "%s\n", "힙합");
						break;
					case 6:
						fprintf(fp, "%s\n", "재즈");
						break;
					case 7:
						fprintf(fp, "%s\n", "edm");
						break;
					case 8:
						fprintf(fp, "%s\n", "ccm");
						break;
					default:
						break;
					}
					break;
				case 7:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "운동");
						break;
					case 2:
						fprintf(fp, "%s\n", "집콕");
						break;
					case 3:
						fprintf(fp, "%s\n", "영화");
						break;
					case 4:
						fprintf(fp, "%s\n", "술");
						break;
					case 5:
						fprintf(fp, "%s\n", "여행");
						break;
					case 6:
						fprintf(fp, "%s\n", "공부");
						break;
					case 7:
						fprintf(fp, "%s\n", "클럽");
						break;
					case 8:
						fprintf(fp, "%s\n", "쇼핑");
						break;
					default:
						break;
					}
					break;
				case 8:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "얼굴");
						break;
					case 2:
						fprintf(fp, "%s\n", "몸매");
						break;
					case 3:
						fprintf(fp, "%s\n", "성격");
						break;
					case 4:
						fprintf(fp, "%s\n", "패션");
						break;
					case 5:
						fprintf(fp, "%s\n", "취미 (ex. 농구를 잘한다! 요리를 잘한다!)");
						break;
					default:
						break;
					}
					break;
				case 9:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "상의 매장");
						break;
					case 2:
						fprintf(fp, "%s\n", "하의 매장");
						break;
					case 3:
						fprintf(fp, "%s\n", "모자 매장");
						break;
					case 4:
						fprintf(fp, "%s\n", "악세사리 매장");
					default:
						break;
					}
					break;
				case 10:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "한강");
						break;
					case 2:
						fprintf(fp, "%s\n", "맛집");
						break;
					case 3:
						fprintf(fp, "%s\n", "pc방");
						break;
					case 4:
						fprintf(fp, "%s\n", "룸카페");
						break;
					case 5:
						fprintf(fp, "%s\n", "코노");
						break;
					case 6:
						fprintf(fp, "%s\n", "도서관");
						break;
					case 7:
						fprintf(fp, "%s\n", "버스여행");
						break;
					case 8:
						fprintf(fp, "%s\n", "바다");
						break;
					case 9:
						fprintf(fp, "%s\n", "산");
						break;
					case 10:
						fprintf(fp, "%s\n", "놀이동산");
						break;
					default:
						break;
					}

				case 11:
					switch (person->otherstep[i])
					{
					case 1:
						fprintf(fp, "%s\n", "연상");
						break;
					case 2:
						fprintf(fp, "%s\n", "동갑");
						break;
					case 3:
						fprintf(fp, "%s\n", "연하");
						break;
					default:
						break;
					}
				}
			}
		}
	}
	
}

void Save_MyStep_Data(Person* person, MyStep* mystep) {
	for (int i = 0; i < 11; i++) {
		switch (i)
		{
		case 0:
			mystep->step1[person->mystep[i] - 1]++;
			break;
		case 1:
			mystep->step2[person->mystep[i] - 1]++;
			break;
		case 2:
			mystep->step3[person->mystep[i] - 1]++;
			break;
		case 3:
			mystep->step4[person->mystep[i] - 1]++;
			break;
		case 4:
			mystep->step5[person->mystep[i] - 1]++;
			break;
		case 5:
			mystep->step6[person->mystep[i] - 1]++;
			break;
		case 6:
			mystep->step7[person->mystep[i] - 1]++;
			break;
		case 7:
			mystep->step8[person->mystep[i] - 1]++;
			break;
		case 8:
			mystep->step9[person->mystep[i] - 1]++;
			break;
		case 9:
			mystep->step10[person->mystep[i] - 1]++;
			break;
		case 10:
			mystep->step11[person->mystep[i] - 1]++;
			break;
		default:
			break;
		}
	}
}

void Save_OtherStep_Data(Person* person, OtherStep* otherstep) {
	for (int i = 0; i < 12; i++) {
		switch (i)
		{
		case 0:
			otherstep->step1[person->otherstep[i] - 1]++;
			break;
		case 1:
			otherstep->step2[person->otherstep[i] - 1]++;
			break;
		case 2:
			otherstep->step3[person->otherstep[i] - 1]++;
			break;
		case 3:
			otherstep->step4[person->otherstep[i] - 1]++;
			break;
		case 4:
			otherstep->step5[person->otherstep[i] - 1]++;
			break;
		case 5:
			otherstep->step6[person->otherstep[i] - 1]++;
			break;
		case 6:
			otherstep->step7[person->otherstep[i] - 1]++;
			break;
		case 7:
			otherstep->step8[person->otherstep[i] - 1]++;
			break;
		case 8:
			otherstep->step9[person->otherstep[i] - 1]++;
			break;
		case 9:
			otherstep->step10[person->otherstep[i] - 1]++;
			break;
		case 10:
			otherstep->step11[person->otherstep[i] - 1]++;
			break;
		case 11:
			otherstep->step12[person->otherstep[i] - 1]++;
			break;
		default:
			break;
		}
	}
}

//그래프 
void PrintGraph(int arr[], int len)
{
	int i = 0;
	int j;

	printf("\n\n**********************************  GRAPH  *************************************\n\n");
	while (i < len) {
		printf("%2d번 : ", i + 1);
		for (j = 0;j < arr[i];j++) {
			printf("▣");
		}
		if (j != 0) printf(" ");
		printf("%d", j);
		printf("\n");
		i++;
	}
	printf("----------------|---------|---------|---------|---------|---------|-----> data\n");
	printf("                5         10        15        20        25        30");
	printf("\n\n*********************************************************************************\n\n");
}

// 랭크 관련 함수
MyStep rank_MyStep(MyStep my)
{
	MyStep rankedMy;
	int i;

	for (i = 0; i < 4; i++)
		rankedMy.step1[i] = my.step1[i];
	for (i = 0; i < 2; i++)
		rankedMy.step2[i] = my.step2[i];
	for (i = 0; i < 4; i++)
		rankedMy.step3[i] = my.step3[i];
	for (i = 0; i < 10; i++)
		rankedMy.step4[i] = my.step4[i];
	for (i = 0; i < 5; i++)
		rankedMy.step5[i] = my.step5[i];
	for (i = 0; i < 5; i++)
		rankedMy.step6[i] = my.step6[i];
	for (i = 0; i < 8; i++)
		rankedMy.step7[i] = my.step7[i];
	for (i = 0; i < 10; i++)
		rankedMy.step8[i] = my.step8[i];
	for (i = 0; i < 4; i++)
		rankedMy.step9[i] = my.step9[i];
	for (i = 0; i < 5; i++)
		rankedMy.step10[i] = my.step10[i];
	for (i = 0; i < 8; i++)
		rankedMy.step11[i] = my.step11[i];


	InsertionSort(4, rankedMy.step1);   // 10  7.5  5  2.5
	InsertionSort(2, rankedMy.step2);   // 10  5
	InsertionSort(4, rankedMy.step3);   // 10  7.5  5  2.5
	InsertionSort(10, rankedMy.step4);  // 10  9  8  7  6  5  4  3  2  1  
	InsertionSort(5, rankedMy.step5);   // 10  8  6  4  2
	InsertionSort(5, rankedMy.step6);   // 10  8  6  4  2
	InsertionSort(8, rankedMy.step7);   // 10  8.6  7.4  6.2  5  3.8  2.6  1.4
	InsertionSort(10, rankedMy.step8);  // 10  9  8  7  6  5  4  3  2  1
	InsertionSort(4, rankedMy.step9);   // 10  7.5  5  2.5
	InsertionSort(5, rankedMy.step10);  // 10  8  6  4  2
	InsertionSort(8, rankedMy.step11);  // 10  8.6  7.4  6.2  5  3.8  2.6  1.4

	return rankedMy;
}

OtherStep rank_OtherStep(OtherStep other)
{
	OtherStep rankedOther;
	int i;

	for (i = 0; i < 5; i++)
		rankedOther.step1[i] = other.step1[i];
	for (i = 0; i < 4; i++)
		rankedOther.step2[i] = other.step2[i];
	for (i = 0; i < 2; i++)
		rankedOther.step3[i] = other.step3[i];
	for (i = 0; i < 4; i++)
		rankedOther.step4[i] = other.step4[i];
	for (i = 0; i < 10; i++)
		rankedOther.step5[i] = other.step5[i];
	for (i = 0; i < 5; i++)
		rankedOther.step6[i] = other.step6[i];
	for (i = 0; i < 8; i++)
		rankedOther.step7[i] = other.step7[i];
	for (i = 0; i < 8; i++)
		rankedOther.step8[i] = other.step8[i];
	for (i = 0; i < 5; i++)
		rankedOther.step9[i] = other.step9[i];
	for (i = 0; i < 4; i++)
		rankedOther.step10[i] = other.step10[i];
	for (i = 0; i < 10; i++)
		rankedOther.step11[i] = other.step11[i];
	for (i = 0; i < 3; i++)
		rankedOther.step12[i] = other.step12[i];



	InsertionSort(5, rankedOther.step1);   // 10  8  6  4  2
	InsertionSort(4, rankedOther.step2);   // 10  7.5  5  2.5
	InsertionSort(2, rankedOther.step3);   // 10  5
	InsertionSort(4, rankedOther.step4);   // 10  7.5  5  2.5
	InsertionSort(10, rankedOther.step5);  // 10  9  8  7  6  5  4  3  2  1
	InsertionSort(5, rankedOther.step6);   // 10  8  6  4  2
	InsertionSort(8, rankedOther.step7);   // 10  8.6  7.4  6.2  5  3.8  2.6  1.4
	InsertionSort(8, rankedOther.step8);   // 10  8.6  7.4  6.2  5  3.8  2.6  1.4
	InsertionSort(5, rankedOther.step9);   // 10  8  6  4  2
	InsertionSort(4, rankedOther.step10);  // 10  7.5  5  2.5
	InsertionSort(10, rankedOther.step11); // 10  9  8  7  6  5  4  3  2  1
	InsertionSort(3, rankedOther.step12);  // 10  6  2

	return rankedOther;
}

// 정렬 함수
void InsertionSort(int len, int arr[])
{
	int i = 0, j = 0;
	int tmp = 0;
	for (j = 1; j < len; j++)
	{
		tmp = arr[j];
		i = j - 1;
		while (i >= 0 && arr[i] < tmp)
		{
			arr[i + 1] = arr[i];
			i--;
		}
		arr[i + 1] = tmp;
	}
}

