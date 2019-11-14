#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

//남녀 구분하는거 만들기

#define CLS system("cls")
#define END fseek(stdin, 0, SEEK_END)
#define UP 11
#define DOWN 12
#define LEFT 13
#define RIGHT 14
#define SPACE 15
#define ENTER 16
#define BACK 17

typedef enum Area
{
	서울특별시 = 10, 부산광역시, 대구광역시, 인천광역시, 광주광역시,
	대전광역시, 울산광역시, 경기도, 강원도, 충청북도, 충청남도,
	전라북도, 전라남도, 경상북도, 경상남도, 제주도
} Area;

typedef enum Sex
{
	남자 = 1,여자
} Sex;

typedef struct User {
	char id[41];
	char pw[41];
}User;

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
	User user;
	int MyStep[11];
	int OtherStep[12];
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

void print_Otherstep_count(OtherStep data);
void print_Mystep_count(MyStep data);
int KeyControl();
void IsCursor(char);
void Goto_xy(int, int);
void Delet_line(int, int);
void ClearReadBuffer();
void Page_Size();
void print_s(int, int);
void Goto_UP(XY, XY);
void Goto_DOWN(XY, XY);
void Goto_RIGHT(XY, XY);
void Goto_LEFT(XY, XY);
void Page_Main();
void Page_Main2_Desgin();
int Page_Main2(); // 회원가임 1 로그인 0
//회원가입
void Page_SingIn_Desgin();
int Page_SingIn(); // 성공시 1
//로그인
void Page_Login_Desgin();
int Page_Login(Person info[]); // 성공시 1
//메뉴
void Page_Menu_Desgin();
int Page_Menu();
// My step
void Page_MyStep_Desgin();
void Page_MyStep(Person * person);//미완성
//Other step
void Page_OtherStep_Desgin();//미완성
void Page_OtherStep(Person* person);//미완성

void Date_Mystep(int, int);//미완성
void Date_Otherstep(int, int);//미완성
void Print_MyStep(Person* person);
void Print_OtherStep(Person* person);//미완성

int X = 0, Y = 0;
MyStep myStep_B = { 0, };
OtherStep otherStep_B = { 0, };
MyStep myStep_G = { 0, };
OtherStep otherStep_G = { 0, };
People_num P_num = { 0, };




int main(void) {
	Person person[10];
	int page = 0, check = 0, index = 0;

	strcpy_s(person[0].user.id, sizeof(person[0].user.id),"son");
	strcpy_s(person[0].user.pw, sizeof(person[0].user.pw),"aaa");
	strcpy_s(person[1].user.id, sizeof(person[1].user.id),"son1");
	strcpy_s(person[1].user.pw,sizeof(person[1].user.pw),"aaaa");
	P_num.T_num = 2;
Main:
	Page_Main();
	page = Page_Main2();
	END;
	if (page == 0) {
		END;
		check = 0;
		index = Page_Login(person);
		page = Page_Menu();
		switch (page+1)
		{
		case 1: // 만팡소개
			break;
		case 2:// mystep 입력
			END;
			Page_MyStep(&person);
			break;
		case 3: //otherstep 입력
			
			break;
		case 4: //기본정보 수정
			break;
		case 5:
			break;
		case 6:
			page = 0;
			goto Main;
			break;
		default:
			break;
		}

	}
	else if (page == 1) {
		END;
		Page_SingIn(person);
		goto Main;
	}
}

void print_Mystep_count(MyStep data)
{
	printf("< MyStep >\n");
	printf("step1 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data.step1[0], data.step1[1], data.step1[2], data.step1[3]);
	printf("step2 - 1번:%d명 2번:%d명\n", data.step2[0], data.step2[1]);
	printf("step3 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data.step3[0], data.step3[1], data.step3[2], data.step3[3]);
	printf("step4 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명 9번:%d명 10번:%d명\n", data.step4[0], data.step4[1], data.step4[2], data.step4[3], data.step4[4], data.step4[5], data.step4[6], data.step4[7], data.step4[8], data.step4[9]);
	printf("step5 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data.step5[0], data.step5[1], data.step5[2], data.step5[3], data.step5[4]);
	printf("step6 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data.step6[0], data.step6[1], data.step6[2], data.step6[3], data.step6[4]);
	printf("step7 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명\n", data.step7[0], data.step7[1], data.step7[2], data.step7[3], data.step7[4], data.step7[5], data.step7[6], data.step7[7]);
	printf("step8 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명 9번:%d명 10번:%d명\n", data.step8[0], data.step8[1], data.step8[2], data.step8[3], data.step8[4], data.step8[5], data.step8[6], data.step8[7], data.step8[8], data.step8[9]);
	printf("step9 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data.step9[0], data.step9[1], data.step9[2], data.step9[3]);
	printf("step10 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data.step10[0], data.step10[1], data.step10[2], data.step10[3], data.step10[4]);
	printf("step11 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명\n", data.step11[0], data.step11[1], data.step11[2], data.step11[3], data.step11[4], data.step11[5], data.step11[6], data.step11[7]);
}

void print_Otherstep_count(OtherStep data)
{
	printf("< OtherStep >\n");
	printf("step1 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data.step1[0], data.step1[1], data.step1[2], data.step1[3], data.step1[4]);
	printf("step2 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data.step2[0], data.step2[1], data.step2[2], data.step2[3]);
	printf("step3 - 1번:%d명 2번:%d명\n", data.step3[0], data.step3[1]);
	printf("step4 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data.step4[0], data.step4[1], data.step4[2], data.step4[3]);
	printf("step5 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명 9번:%d명 10번:%d명\n", data.step5[0], data.step5[1], data.step5[2], data.step5[3], data.step5[4], data.step5[5], data.step5[6], data.step5[7], data.step5[8], data.step5[9]);
	printf("step6 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data.step6[0], data.step6[1], data.step6[2], data.step6[3], data.step6[4]);
	printf("step7 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명\n", data.step7[0], data.step7[1], data.step7[2], data.step7[3], data.step7[4], data.step7[5], data.step7[6], data.step7[7]);
	printf("step8 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명\n", data.step8[0], data.step8[1], data.step8[2], data.step8[3], data.step8[4], data.step8[5], data.step8[6], data.step8[7]);
	printf("step9 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명\n", data.step9[0], data.step9[1], data.step9[2], data.step9[3], data.step9[4]);
	printf("step10 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명\n", data.step10[0], data.step10[1], data.step10[2], data.step10[3]);
	printf("step11 - 1번:%d명 2번:%d명 3번:%d명 4번:%d명 5번:%d명 6번:%d명 7번:%d명 8번:%d명 9번:%d명 10번:%d명\n", data.step11[0], data.step11[1], data.step11[2], data.step11[3], data.step11[4], data.step11[5], data.step11[6], data.step11[7], data.step11[8], data.step11[9]);
	printf("step12 - 1번:%d명 2번:%d명 3번:%d명\n", data.step12[0], data.step12[1], data.step12[2]);
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

void ClearReadBuffer(char arr[]) {
	arr[strlen(arr) - 1] = 0;
}

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

void Goto_UP(XY * xy1,XY * xy2) {
	if(Y == xy1->y) {
		Goto_xy(xy1->x, xy1->y);
		printf("  ");
		Goto_xy(xy2->x, xy2->y);
		printf("▶");
		X = xy2->x;
		Y = xy2->y;
	}
}

void Goto_DOWN(XY * xy1, XY * xy2) {
	if(Y == xy1->y) {
		Goto_xy(xy1->x, xy1->y);
		printf("  ");
		Goto_xy(xy2->x, xy2->y);
		printf("▶");
		X = xy2->x;
		Y = xy2->y;
	}
}

void Goto_RIGHT(XY * xy1,XY * xy2) {
	if(X == xy1->x){
		Goto_xy(xy1->x, xy1->y);
		printf("  ");
		Goto_xy(xy2->x, xy2->y);
		printf("▶");
		X = xy2->x;
		Y = xy2->y;
	}
}

void Goto_LEFT(XY * xy1, XY * xy2) {
	if (X == xy1->x ){
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
	printf("                                                                                                                      ");
}

void Page_Main() {
	Page_Size();
	IsCursor(0);
	printf("\n\n\n\n\n\n");
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
	printf("\n\n\n\n\n\n");
	printf("     ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
	printf("     ♥                                                                                                ♥\n");
	printf("     ♥      ■■      ■■       ■       ■■    ■  ■■■■     ■      ■■    ■  ■■■■■     ♥\n");
	printf("     ♥      ■ ■    ■ ■      ■■      ■ ■   ■  ■    ■    ■■     ■ ■   ■  ■             ♥\n");
	printf("     ♥      ■  ■  ■  ■    ■    ■    ■  ■  ■  ■■■■   ■  ■    ■  ■  ■  ■    ■■     ♥\n");
	printf("     ♥      ■   ■■   ■   ■■■■■   ■   ■ ■  ■        ■■■■   ■   ■ ■  ■      ■     ♥\n");
	printf("     ♥      ■    ■    ■  ■        ■  ■    ■■  ■       ■      ■  ■    ■■  ■■■■■     ♥\n");
	printf("     ♥                                                                                                ♥\n");
	printf("     ♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
	printf("\n\n\n\n");
	Goto_xy(48, 19);
	printf("◎로그인하기");//Y=19
	Goto_xy(48, 20);
	printf("◎회원가입하기"); //Y =20
}

int Page_Main2() {
	int key = 0;

	Page_Main2_Desgin();
	IsCursor(0);
	XY xy_l = { 46,19 };
	XY xy_s = { 46,20 };
	print_s(xy_l.x, xy_l.y);
	while (1) {
		key = KeyControl();
		if (key == DOWN)
			Goto_DOWN(&xy_l, &xy_s);
		if (key == UP)
			Goto_UP(&xy_s, &xy_l);
		if (key == ENTER)
			break;
	}

	CLS;

	if (Y == xy_l.y) {
		return 0; //로그인
	}
	else if (Y == xy_s.y) {
		return 1; //회원가입
	}
}

void Page_Login_Desgin() {
	Page_Size();
	printf("\n\n\n\n\n\n");
	printf("                ---------------------------------------------------------------------------\n\n");
	printf("                           ■        ■■■■■    ■■■■    ■■■  ■■    ■\n");
	printf("                           ■        ■      ■   ■             ■    ■ ■   ■\n");
	printf("                           ■        ■      ■  ■      ■■    ■    ■  ■  ■\n");
	printf("                           ■        ■      ■   ■      ■     ■    ■   ■ ■\n");
	printf("                           ■■■■  ■■■■■    ■■■■    ■■■  ■    ■■\n\n");
	printf("                ---------------------------------------------------------------------------\n");
	printf("\n\n");
	printf("                                           ♡  ID   : ");//X=54 Y=17
	if (Y == 18) {
		printf("\n                                           ♡  PW   : ");
	}

}

int Page_Login(Person info[]) {
	int be = 0;
	char id[41];
	char pw[21];
	int i = 0;
	int index = 0;
	while (Y != 18) {
		CLS;
		Page_Login_Desgin();
		id[0] = '\0';
		gets_s(id, sizeof(id));
		for (i = 0; i < P_num.T_num; i++) {
			if (!strncmp(id, info[i].user.id, strlen(id))) {
				be++;
				break;
			}
		}
		if (be == 0) {
			CLS;
			Page_Login_Desgin();
			Goto_xy(0, 19);
			printf("\n                                           ");
			printf("아이디가 존재하지 않습니다.\n");
			printf("                                           ");
			printf(" 다시 입력하시기 바랍니다.\n");
			Sleep(700);
		}
		else if (be == 1) {
			Y = 18;
		}
	}
	while (1) {
		Y = 18;
		index = i;
		CLS;
		Page_Login_Desgin();
		Goto_xy(54, 17);
		printf("%s", id);
		Goto_xy(54, 18);
		pw[0] = '\0';
		gets_s(pw, sizeof(pw));
		if (!strncmp(pw, info[i].user.pw, strlen(pw))) {
			break;
		}
		else {
			Y = 0;
			CLS;
			Page_Login_Desgin();
			Goto_xy(0, 19);
			printf("\n                                           ");
			printf("비밀번호가 틀렸습니다.\n");
			printf("                                           ");
			printf("다시 입력하시기 바랍니다.\n");
			Sleep(700);
		}

	}
	return index;
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
	printf("                                         6. HOME                           \n");
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

int Page_SingIn(Person person[]) {
	int sex = 0;
	int area = 0;
	int i = 0, overlap = 0, ok = 0;
	int key = 0;
	Y = 16;
	X + 0;
	IsCursor(1);
	while (ok == 0) {
		ok = 0;
		overlap = 0;
		CLS;
		Page_SingIn_Desgin();
		Goto_xy(0, 18);
		printf("                   ID(20자 이내 영어,숫자) : "); //X=45 Y=16
		gets_s(person[P_num.T_num].user.id, sizeof(person[P_num.T_num].user.id));//아이디 입력
		for (i = 0; i < P_num.T_num; i++) {
			if (!strncmp(person[P_num.T_num].user.id, person[i].user.id, strlen(person[P_num.T_num].user.id))) {
				overlap++;
				break;
			}
		}
		if (overlap == 0) {
			ok++;
		}
		else {
			CLS;
			Page_SingIn_Desgin();
			printf("                                    이미 존재하는 아이디입니다.\n");
			printf("                                          다시 입력하세요.\n");
			Sleep(700);
		}
	}
	IsCursor(1);
	Goto_xy(0, 20);
	printf("                   PW(20자 이내 영어,숫자) : "); gets_s(person[P_num.T_num].user.pw, sizeof(person[P_num.T_num].user.pw));

	do {
		ok = 0;
		overlap = 0;
		Goto_xy(0, 22);
		END;
		printf("                   닉네임(20자 이내)       : "); // X=45 Y=22
		gets_s(person[P_num.T_num].member.name, sizeof(person[P_num.T_num].member.name));
		for (i = 0; i < P_num.T_num; i++) {
			if (!strncmp(person[P_num.T_num].member.name, person[i].member.name, strlen(person[P_num.T_num].member.name))) {
				overlap++;
				break;
			}
		}
		if (overlap == 0) {
			ok++;
		}
		else {
			Delet_line(22);
			Goto_xy(0, 22);
			printf("                                    이미 존재하는 닉네임입니다.\n");
			printf("                                          다시 입력하세요.\n");
			Sleep(700);
			Delet_line(22);
			Delet_line(23);
		}
	} while (ok == 0);

	XY xy_B = { 44,24 };
	XY xy_G = { 64,24 };

	IsCursor(0);
	Goto_xy(0, 24);
	printf("                   성별 선택               :   1.남자              2.여자");
	print_s(xy_B.x, xy_B.y);
	while (1) {
		key = KeyControl();
		if (key == RIGHT)
			Goto_RIGHT(&xy_B, &xy_G, key);//남자
		if (key == LEFT)
			Goto_LEFT(&xy_G, &xy_B, key);//여자
		if (key == ENTER)
			break;
		else
			continue;
	}
	printf("\n\n");
	if (X == xy_B.x) {
		person->member.sex = 남자;
	}
	else if (X == xy_G.x)
	{
		person->member.sex = 여자;
	}

	IsCursor(1);
	Goto_xy(0, 26);
	printf("                   나이(숫자만 입력)       : "); scanf_s("%d", &person[P_num.T_num].member.age);
	Goto_xy(0, 28);
	printf("                   학번(숫자만 입력)       : "); scanf_s("%d", &person[P_num.T_num].member.s_num);

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
	int index = 0;
	while (1) {
		key = KeyControl();
		if (key == ENTER)
			break;
		if (key == UP) {
			if (Y != 32) {
				Goto_UP(&xy_area[index], &xy_area[index - 6]);
				index -= 6;
			}
		}
		if (key == DOWN) {
			if (X == 72 || X == 87) {
				if (Y != 34) {
					Goto_DOWN(&xy_area[index], &xy_area[index + 6]);
					index += 6;
				}
			}
			else {
				if (Y != 36) {
					Goto_DOWN(&xy_area[index], &xy_area[index + 6]);
					index += 6;
				}
			}
		}
		if (key == LEFT) {
			if (X != 12) {
				Goto_LEFT(&xy_area[index], &xy_area[index - 1]);
				index--;
			}
		}
		if (key == RIGHT) {
			if (Y == 32 || Y == 34) {
				if (X != 87) {
					Goto_RIGHT(&xy_area[index], &xy_area[index + 1]);
					index++;
				}
			}
			else if (Y == 36) {
				if (X != 57) {
					Goto_RIGHT(&xy_area[index], &xy_area[index + 1]);
					index++;
				}
			}
		}
		X = xy_area[index].x;
		Y = xy_area[index].y;
	}
	person->member.area = index + 10;

	person[P_num.T_num].member.area = area + 11;
	person[P_num.T_num].member.sex = sex;

	P_num.T_num++;
	if (sex == 1) {
		P_num.B_num++;
	}
	else if (sex == 2) {
		P_num.G_num++;
	}
	//성별저장 및 성별관련 총인원 증가
	return 1;
}

void Page_MyStep_Desgin() {

	system("mode con cols=110  lines=20  | title = 만나라 팡팡이들아");
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

void Page_MyStep(Person* person) {
	int temp = 0;
	CLS;
	Page_MyStep_Desgin();
	IsCursor(1);
	for (int i = 0; i < 11; i++) {
		temp = 0;
		Delet_line(14);
		Delet_line(15);
		print_s(13, 14);
		switch (i)
		{
		case 0:
			printf("1. 키가 몇이야 ?");
			Goto_xy(13, 15);
			printf("150대 또는 그 이하 : 1, 160대 : 2, 170대 : 3, 180대 이상 : 4)");
			Goto_xy(32, 14);
			break;
		case 1:
			printf("2. 혹시 지금 흡연자야 ?");
			Goto_xy(13, 15);
			printf("(YES : 1, NO : 2)");
			Goto_xy(39, 14);
			break;
		case 2:
			printf("3. 주량이 어떻게 되니 ?");
			Goto_xy(13, 15);
			printf("(반 병 이하 : 1, 한 병까지 : 2, 두 병까지 : 3, 두 병 이상 : 4)");
			break;
		case 3:
			printf("4. 너의 성격을 가장 잘 표현해주는 키워드 한 가지는 ?");
			Goto_xy(13, 15);
			printf("(내향 : 1, 외향 : 2, 차분 : 3, 지적 : 4, 상냥 : 5)");
			Goto_xy(13, 16);
			printf("(감성 : 6, 낙천 : 7, 냉혈 : 8, 열정 : 9, 유머러스 : 10) : ");
			break;
		case 4:
			printf("5. 너가 생각하기에 너의 얼굴상은 어떤 부류에 속하는 것 같아 ?");
			Goto_xy(13, 15);
			printf("고양이 : 1, 강아지 : 2, 토끼 : 3, 곰 : 4, 공룡 : 5) : ");
			break;
		case 5:
			printf("6. 내가 이것만큼은 자신있다!!!!하는게 어디야 ?\n");
			Goto_xy(13, 15);
			printf("얼굴 : 1, 몸매 : 2, 패션 : 3, 성격 : 4, 취미(ex.농구를 잘한다!요리를 잘한다!) : 5) : ");
			break;
		case 6:
			printf("7. 너가 제일 좋아하는 활동이 뭐야 ?");
			Goto_xy(13, 15);
			printf("영화 : 1, 운동 : 2, 집콕 : 3, 쇼핑 : 4, 공부 : 5, 술 : 6, 여행 : 7, 클럽 : 8) : ");
			break;
		case 7:
			printf("8. 너가 지금 제일 가고 싶은 장소가 어디야 ?");
			Goto_xy(13, 15);
			printf("(코노 : 1, 도서관 : 2, 버스여행 : 3, 한강 : 4, pc방: 5)");
			Goto_xy(13, 16);
			printf("(놀이동산 : 6, 한강 : 7, 바다 : 8, 산 : 9, 룸카페 : 10) : ");
			break;
		case 8:
			printf("9. 너가 쇼핑을 하러 왔다면 가장 먼저 향하는 매장은 ?");
			Goto_xy(13, 15);
			printf("상의 매장 : 1, 하의 매장 : 2, 악세서리 매장 : 3, 모자 매장 : 4) : ");
			break;
		case 9:
			printf("10. 사랑하는 상대가 있다면, 일주일에 보통 몇 번정도 만날 것 같아 ?");
			Goto_xy(13, 15);
			printf("(매일 : 1, 일주일에 5~6회 : 2, 일주일에 3~4회 : 3, 일주일에 1~2회 : 4, 그 이하 : 5) : ");
			break;
		case 10:
			printf("11. 너가 제일 좋아하는 음악 장르가 뭐야 ?");
			Goto_xy(13, 15);
			printf("(발라드 : 1, 팝 : 2, 알엔비 : 3, 힙합 : 4, 락 : 5, 재즈 : 6, edm : 7, ccm : 8) : ");
			break;
		default:
			break;
		}
		// 질문 출력
		scanf_s("%d", &temp);

		person->MyStep[i] = temp;

		if ((person->member).sex == 남자) {
			switch (i)
			{
			case 0:
				myStep_B.step1[temp - 1]++;
				break;
			case 1:
				myStep_B.step2[temp - 1]++;
				break;
			case 2:
				myStep_B.step3[temp - 1]++;
				break;
			case 3:
				myStep_B.step4[temp - 1]++;
				break;
			case 4:
				myStep_B.step5[temp - 1]++;
				break;
			case 5:
				myStep_B.step6[temp - 1]++;
				break;
			case 6:
				myStep_B.step7[temp - 1]++;
				break;
			case 7:
				myStep_B.step8[temp - 1]++;
				break;
			case 8:
				myStep_B.step9[temp - 1]++;
				break;
			case 9:
				myStep_B.step10[temp - 1]++;
				break;
			default:
				break;
			}
		}
		else if ((person->member).sex == 여자) {
			switch (i)
			{
			case 0:
				myStep_G.step1[temp - 1]++;
				break;
			case 1:
				myStep_G.step2[temp - 1]++;
				break;
			case 2:
				myStep_G.step3[temp - 1]++;
				break;
			case 3:
				myStep_G.step4[temp - 1]++;
				break;
			case 4:
				myStep_G.step5[temp - 1]++;
				break;
			case 5:
				myStep_G.step6[temp - 1]++;
				break;
			case 6:
				myStep_G.step7[temp - 1]++;
				break;
			case 7:
				myStep_G.step8[temp - 1]++;
				break;
			case 8:
				myStep_G.step9[temp - 1]++;
				break;
			case 9:
				myStep_G.step10[temp - 1]++;
				break;
			default:
				break;
			}
		}
		//데이터 관리

		Goto_xy(14, 14);
	}
}

void Page_OtherStep_Desgin() {

}

void Page_OtherStep(Person* person) {

}