#define _CRT_SECURE_NO_WARNINGS
#include "FH_Poland.h"
#include <string>
#include <stdlib.h>
#include <math.h>
Atoms* Head = (Atoms*)malloc(sizeof(Atoms));
bool First = true;

void Proposition::clear()
{
	Head->Pro = NULL;
	Head->next = NULL;
};

Proposition::Proposition(char* nname, bool nIfBasic, int ntype, Proposition* na, Proposition* nb = NULL, bool nTruthValue = false)
{
	name = nname;
	IfBasic = nIfBasic;
	type = ntype;
	a = na;
	b = nb;
	TruthValue = nTruthValue;
};

Proposition::Proposition(char* nname, bool nIfBasic, int ntype = Not)
{
	Proposition(nname, nIfBasic, ntype, NULL, NULL, false);
};

Proposition::Proposition()
{
	Proposition(NULL, false);
};

bool Proposition::CalculateNow()
{
	bool a1, a2;
	if (IfBasic)
		return TruthValue;
	switch (type)
	{
	case And:
		return TruthValue = (a->CalculateNow() && b->CalculateNow());
	case Or:
		return TruthValue = (a->CalculateNow() || b->CalculateNow());
	case Not:
		return TruthValue = !a->CalculateNow();
	case EOr:
		return TruthValue = (!a->CalculateNow() && b->CalculateNow()) || (a->CalculateNow() && !b->CalculateNow());
	case To:
		return TruthValue = (!a->CalculateNow() || b->CalculateNow());
	case BTo:
		return TruthValue = !((!a->CalculateNow() && b->CalculateNow()) || (a->CalculateNow() && !b->CalculateNow()));
	default:
		return false;
	}
};

void Proposition::SetTruthValue(bool MyBool)
{
	TruthValue = MyBool;
};

bool Proposition::GetTruthValue()
{
	return TruthValue;
};

void Proposition::PrintTruthValueLine()
{
	Atoms* No;
	for (No = Head; No != NULL; No = No->next)
	{
		if (No->Pro->GetTruthValue())
			printf("T\t");
		else
			printf("F\t");
	}
	if (CalculateNow())
		printf("T\n");
	else
		printf("F\n");
};

void Proposition::Bigger(Atoms* No, bool NeedToPrint = true, int NormalFormType = Disjunctive)
{
	No->Pro->SetTruthValue(false);
	if (No->next != NULL)
		Bigger(No->next, NeedToPrint, NormalFormType);
	else if (NeedToPrint)
		PrintTruthValueLine();
	else
		PrintNormalForm(NormalFormType);
	No->Pro->SetTruthValue(true);
	if (No->next != NULL)
		Bigger(No->next, NeedToPrint, NormalFormType);
	else if (NeedToPrint)
		PrintTruthValueLine();
	else
		PrintNormalForm(NormalFormType);
};

void Proposition::TruthValueTable()
{
	Atoms* temp;
	cout << "----------------------------------------\n";
	for (temp = Head; temp != NULL; temp = temp->next)
		printf("%s\t", temp->Pro->name);
	printf("%s\n", name);
	Bigger(Head);
};

int Proposition::GetLenth(int i = 1)
{
	if (i == 1)
	{
		if (IfBasic)
			return strlen(name);
		switch (type)
		{
		case And:
			return AndNotionLen + a->GetLenth() + b->GetLenth();
		case Or:
			return OrNotionLen + a->GetLenth() + b->GetLenth();
		case Not:
			return NotNotionLen + a->GetLenth();
		case EOr:
			return EOrNotionLen + a->GetLenth() + b->GetLenth();
		case To:
			return ToNotionLen + a->GetLenth() + b->GetLenth();
		case BTo:
			return BToNotionLen + a->GetLenth() + b->GetLenth();
		default:
			return 0;
		}
	}
	else if (i == 5)
	{
		if (IfBasic)
			return strlen(name);
		switch (type)
		{
		case And:
			return AndNotionLen + a->GetLenth() + b->GetLenth() + 2;
		case Or:
			return OrNotionLen + a->GetLenth() + b->GetLenth() + 2;
		case Not:
			return NotNotionLen + a->GetLenth();
		case EOr:
			return EOrNotionLen + a->GetLenth() + b->GetLenth() + 2;
		case To:
			return ToNotionLen + a->GetLenth() + b->GetLenth() + 2;
		case BTo:
			return BToNotionLen + a->GetLenth() + b->GetLenth() + 2;
		default:
			return 0;
		}
	}
	return 0;
};

char* Proposition::ToPoland()
{
	char* ans = (char*)malloc(sizeof(char) * (1 + GetLenth()));
	if (IfBasic)
	{
		strcpy(ans, name);
		return ans;
	}
	switch (type)
	{
	case And:
		strcpy(ans, AndNotion);
		strcat(ans, a->ToPoland());
		strcat(ans, b->ToPoland());
		return ans;
	case Or:
		strcpy(ans, OrNotion);
		strcat(ans, a->ToPoland());
		strcat(ans, b->ToPoland());
		return ans;
	case Not:
		strcpy(ans, NotNotion);
		strcat(ans, a->ToPoland());
		return ans;
	case EOr:
		strcpy(ans, EOrNotion);
		strcat(ans, a->ToPoland());
		strcat(ans, b->ToPoland());
		return ans;
	case To:
		strcpy(ans, ToNotion);
		strcat(ans, a->ToPoland());
		strcat(ans, b->ToPoland());
		return ans;
	case BTo:
		strcpy(ans, BToNotion);
		strcat(ans, a->ToPoland());
		strcat(ans, b->ToPoland());
		return ans;
	default:
		return NULL;
	}
};

char* Proposition::ToReversePoland()
{
	char* ans = (char*)malloc(sizeof(char) * (1 + GetLenth()));
	if (IfBasic)
	{
		strcpy(ans, name);
		return ans;
	}
	switch (type)
	{
	case And:
		strcpy(ans, a->ToReversePoland());
		strcat(ans, b->ToReversePoland());
		strcat(ans, AndNotion);
		return ans;
	case Or:
		strcpy(ans, a->ToReversePoland());
		strcat(ans, b->ToReversePoland());
		strcat(ans, OrNotion);
		return ans;
	case Not:
		strcpy(ans, a->ToReversePoland());
		strcat(ans, NotNotion);
		return ans;
	case EOr:
		strcpy(ans, a->ToReversePoland());
		strcat(ans, b->ToReversePoland());
		strcat(ans, EOrNotion);
		return ans;
	case To:
		strcpy(ans, a->ToReversePoland());
		strcat(ans, b->ToReversePoland());
		strcat(ans, ToNotion);
		return ans;
	case BTo:
		strcpy(ans, a->ToReversePoland());
		strcat(ans, b->ToReversePoland());
		strcat(ans, BToNotion);
		return ans;
	default:
		return NULL;
	}

};

char* Proposition::ToNormal()
{
	char* ans = (char*)malloc(sizeof(char) * (1 + GetLenth(5)));
	if (IfBasic)
	{
		strcpy(ans, name);
		return ans;
	}
	switch (type)
	{
	case And:
		strcpy(ans, "(");
		strcat(ans, a->ToNormal());
		strcat(ans, AndNotion);
		strcat(ans, b->ToNormal());
		strcat(ans, ")");
		return ans;
	case Or:
		strcpy(ans, "(");
		strcat(ans, a->ToNormal());
		strcat(ans, OrNotion);
		strcat(ans, b->ToNormal());
		strcat(ans, ")");
		return ans;
	case Not:
		strcpy(ans, NotNotion);
		strcat(ans, a->ToNormal());
		return ans;
	case EOr:
		strcpy(ans, "(");
		strcat(ans, a->ToNormal());
		strcat(ans, EOrNotion);
		strcat(ans, b->ToNormal());
		strcat(ans, ")");
		return ans;
	case To:
		strcpy(ans, "(");
		strcat(ans, a->ToNormal());
		strcat(ans, ToNotion);
		strcat(ans, b->ToNormal());
		strcat(ans, ")");
		return ans;
	case BTo:
		strcpy(ans, "(");
		strcat(ans, a->ToNormal());
		strcat(ans, BToNotion);
		strcat(ans, b->ToNormal());
		strcat(ans, ")");
		return ans;
	default:
		return NULL;
	}
};

Proposition* Proposition::GetProposition(char* Source, int len)
{
	Proposition* ans = (Proposition*)malloc(sizeof(Proposition));
	int NumR = 0;
	int NumL = 0;
	int j;
	while (Source[0] == '(' && Source[len - 1] == ')')
	{
		for (j = len - 1; j >= 0; j--)
		{
			switch (Source[j])
			{
			case ')':
				NumR++;
				do
				{
					j--;
					if (Source[j] == ')')
					{
						NumR++;
						continue;
					}
					if (Source[j] == '(')
					{
						NumL++;
					}
				} while (NumL < NumR);
			}
			if (NumL >= NumR)
				break;
		}
		if (j > 0)
			break;
		Source++;
		len -= 2;
	}
	for (int j = len - 1; j >= 0; j--)
	{
		switch (Source[j])
		{
		case ')':
			NumR++;
			do
			{
				j--;
				if (Source[j] == ')')
				{
					NumR++;
					continue;
				}
				if (Source[j] == '(')
				{
					NumL++;
				}
			} while (NumL < NumR);
			break;
		case '>':
			if (j > 1 && Source[j - 1] == '-' && Source[j - 2] == '<')
			{
				ans->IfBasic = false;
				ans->type = BTo;
				ans->a = GetProposition(Source, j - 2);
				ans->b = GetProposition(Source + j + 1, len - (j + 1));
				ans->TruthValue = false;
				ans->name = NULL;
				return ans;
			}
		}
	}
	for (int j = len - 1; j >= 0; j--)
	{
		switch (Source[j])
		{
		case ')':
			NumR++;
			do
			{
				j--;
				if (Source[j] == ')')
				{
					NumR++;
					continue;
				}
				if (Source[j] == '(')
				{
					NumL++;
				}
			} while (NumL < NumR);
			break;
		case '>':
			if (j > 0 && Source[j - 1] == '-')
			{
				ans->IfBasic = false;
				ans->type = To;
				ans->a = GetProposition(Source, j - 1);
				ans->b = GetProposition(Source + j + 1, len - (j + 1));
				ans->TruthValue = false;
				ans->name = NULL;
				return ans;
			}
		}
	}
	for (int j = len - 1; j >= 0; j--)
	{
		switch (Source[j])
		{
		case ')':
			NumR++;
			do
			{
				j--;
				if (Source[j] == ')')
				{
					NumR++;
					continue;
				}
				if (Source[j] == '(')
				{
					NumL++;
				}
			} while (NumL < NumR);
			break;
		case '&':
			if (j > 0 && Source[j - 1] == '&')
			{
				ans->IfBasic = false;
				ans->type = And;
				ans->a = GetProposition(Source, j - 1);
				ans->b = GetProposition(Source + j + 1, len - (j + 1));
				ans->TruthValue = false;
				ans->name = NULL;
				return ans;
			}
		}
	}
	for (int j = len - 1; j >= 0; j--)
	{
		switch (Source[j])
		{
		case ')':
			NumR++;
			do
			{
				j--;
				if (Source[j] == ')')
				{
					NumR++;
					continue;
				}
				if (Source[j] == '(')
				{
					NumL++;
				}
			} while (NumL < NumR);
			break;
		case '|':
			if (j > 0 && Source[j - 1] == '|')
			{
				ans->IfBasic = false;
				ans->type = Or;
				ans->a = GetProposition(Source, j - 1);
				ans->b = GetProposition(Source + j + 1, len - (j + 1));
				ans->TruthValue = false;
				ans->name = NULL;
				return ans;
			}
		case '^':
			if (j > 0)
			{
				ans->IfBasic = false;
				ans->type = EOr;
				ans->a = GetProposition(Source, j);
				ans->b = GetProposition(Source + j + 1, len - (j + 1));
				ans->TruthValue = false;
				ans->name = NULL;
				return ans;
			}
		}
	}
	if (Source[0] == '!')
	{
		ans->IfBasic = false;
		ans->type = Not;
		ans->a = GetProposition(Source + 1, len - 1);
		ans->b = NULL;
		ans->TruthValue = false;
		ans->name = NULL;
		return ans;
	}
	char* NewName = (char*)malloc((len + 1) * sizeof(char));
	for (int i = 0; i < len; i++)
		NewName[i] = Source[i];
	NewName[len] = 0;
	ans->IfBasic = true;
	ans->type = Not;
	ans->a = NULL;
	ans->b = NULL;
	ans->TruthValue = false;
	ans->name = NewName;
	Atoms* NewHead = (Atoms*)malloc(sizeof(Atoms));
	Atoms* TempHead;
	Atoms* tip;
	NewHead->next = NULL;
	NewHead->Pro = ans;
	if (Head->Pro == NULL)
	{
		Head = NewHead;
		return ans;
	}
	for (TempHead = Head; TempHead != NULL && strcmp(TempHead->Pro->name, NewHead->Pro->name) < 0; TempHead = TempHead->next);
	if (TempHead == NULL)
	{
		for (TempHead = Head; TempHead->next != NULL; TempHead = TempHead->next);
		TempHead->next = NewHead;
		return ans;
	}
	if (strcmp(TempHead->Pro->name, NewHead->Pro->name) == 0)
		return TempHead->Pro;
	if (TempHead == Head)
	{
		Head = NewHead;
		Head->next = TempHead;
		return ans;
	}
	tip = TempHead;
	for (TempHead = Head; TempHead->next != tip; TempHead = TempHead->next);
	TempHead->next = NewHead;
	NewHead->next = tip;
	return ans;
};

void Proposition::SetName(char* SourceName, Proposition* Pro)
{
	Pro->name = SourceName;
};

bool Proposition::GetIsBasic()
{
	return IfBasic;
};

void Proposition::PrintNormalForm(int NormalFormType)
{
	SetTruthValue(CalculateNow());
	if (NormalFormType == Disjunctive)
	{
		if (!TruthValue)
			return;
		if (First)
			First = false;
		else
			printf(OrNotion);
		printf("(");
		Atoms* temp;
		for (temp = Head; temp->next != NULL; temp = temp->next)
		{
			if (!(temp->Pro->TruthValue))
				printf(NotNotion);
			printf(temp->Pro->name);
			printf(AndNotion);
		}
		if (!(temp->Pro->TruthValue))
			printf(NotNotion);
		printf(temp->Pro->name);
		printf(")");
	}
	else
	{
		if (TruthValue)
			return;
		if (First)
			First = false;
		else
			printf(AndNotion);
		printf("(");
		Atoms* temp;
		for (temp = Head; temp->next != NULL; temp = temp->next)
		{
			if (temp->Pro->TruthValue)
				printf(NotNotion);
			printf(temp->Pro->name);
			printf(OrNotion);
		}
		if (temp->Pro->TruthValue)
			printf(NotNotion);
		printf(temp->Pro->name);
		printf(")");
	}
};

void Proposition::PrincipalDisjunctiveNormalForm()
{
	First = true;
	Bigger(Head, false, Disjunctive);
	printf("\n");
};

void Proposition::PrincipalConjunctiveNormalForm()
{
	First = true;
	Bigger(Head, false, Conjunctive);
	printf("\n");
};