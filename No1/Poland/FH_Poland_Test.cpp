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
	cout << "��������׺���⣬ע�ⲻҪ����ո�" << endl << "������ʱ��\"&&\"��ʾ��ȡ����\"||\"��ʾ��ȡ����\"!\"��ʾ�ǣ���\"^\"��ʾ�����\"->\"��ʾ�̺�����\"<->\"��ʾ˫�̺���" << endl;
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
		cout << "����1ת��Ϊ����ʽ\n����2ת��Ϊ�沨��ʽ\n����3ת��Ϊ�����ŵ���׺ʽ\n����4����ֵ��\n����5������ȡ��ʽ\n����6������ȡ��ʽ��" << endl;
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
			printf("����ȡ��ʽΪ��\n\t");
			NowProposition->PrincipalDisjunctiveNormalForm();
		}
		else if (ch == '6')
		{
			CutOffLine();
			printf("����ȡ��ʽΪ��\n\t");
			NowProposition->PrincipalConjunctiveNormalForm();
		}
		ch = getchar();
		CutOffLine();
		cout << "����y���س������Ը�������в��������������ַ�������ǰ���⣡" << endl;
		CutOffLine();
	} while (getchar() == 'y' && getchar() == '\n');
	CutOffLine();
	cout << "����y���س����¿�ʼ�������⣬���������ַ��˳�����" << endl;
	CutOffLine();
};
