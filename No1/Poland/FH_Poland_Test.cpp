#include"FH_Poland_Test.h"
#include<iostream>
using namespace std;
char AllSource[10000];

Proposition* NowProposition;
char ch;
char* NewChar;
void CutOffLine()
{
	cout << "----------------------------------------\n";
};
Proposition* InPut()
{
	NowProposition->clear();
	CutOffLine();
	cout << "请输入中缀命题，注意不要输入空格！" << endl << "在输入时用\"&&\"表示合取，用\"||\"表示析取，用\"!\"表示非，用\"^\"表示异或，用\"->\"表示蕴涵，用\"<->\"表示双蕴含！" << endl;
	CutOffLine();
	gets_s(AllSource);
	NowProposition = NowProposition->GetProposition(AllSource, strlen(AllSource));
	NowProposition->SetName(AllSource, NowProposition);
	return NowProposition;
};
void Start()
{
	NowProposition = InPut();
	do
	{
		CutOffLine();
		cout << "输入1转换为波兰式\n输入2转换为逆波兰式\n输入3转换为带括号的中缀式\n输入4列真值表\n输入5列主析取范式\n输入6列主合取范式！" << endl;
		CutOffLine();
		ch = getchar();
		if (ch == '1')
			printf("%s\n", NowProposition->ToPoland());
		else if (ch == '2')
			printf("%s\n", NowProposition->ToReversePoland());
		else if (ch == '3')
		{
			NewChar = NowProposition->ToNormal();
			if (NowProposition->GetIsBasic() == false)
			{
				NewChar[strlen(NewChar) - 1] = 0;
				NewChar++;
			}
			printf("%s\n", NewChar);
		}
		else if (ch == '4')
			NowProposition->TruthValueTable();
		else if (ch == '5')
		{
			CutOffLine();
			printf("主析取范式为：\n\t");
			NowProposition->PrincipalDisjunctiveNormalForm();
		}
		else if (ch == '6')
		{
			CutOffLine();
			printf("主合取范式为：\n\t");
			NowProposition->PrincipalConjunctiveNormalForm();
		}
		ch = getchar();
		CutOffLine();
		cout << "输入y并回车继续对该命题进行操作，输入其他字符放弃当前命题！" << endl;
		CutOffLine();
	} while (getchar() == 'y' && getchar() == '\n');
	CutOffLine();
	cout << "输入y并回车重新开始输入命题，输入其他字符退出程序！" << endl;
	CutOffLine();
};
