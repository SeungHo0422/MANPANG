#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define song "lala.wav"

int main()
{
	PlaySound(TEXT(song), NULL, SND_ASYNC | SND_LOOP);
	int a;
	printf("����? ");
	scanf("%d", &a);
	if (a == 0)
	{
		PlaySound(NULL, 0, 0);
		Sleep(1000);
		printf("�뷡�� �����߽��ϴ�. �Լ��� �����մϴ�.");
		return 0;
	}
}


	