#include "stdafx.h"
#include "FH_Poland_Main.h"
#include <string>
#include <stdlib.h>
#include <math.h>
Atoms* Head = new Atoms;
bool First = true;
bool First1 = true;
bool First2 = true;
bool* ValuesNow;
bool* BasesUse;
int BaseNum = 0;

void Proposition::clear()
{
	Head->Pro = NULL;
	Head->next = NULL;
	/*if (this)
	{
		if (a)
			delete a;
		if (b)
			delete b;
		TruthValueString = TruthValueHead = PriDisNormalForm = PriConjNormalForm = "";
	}*/
}

bool Proposition::check(string checkable)
{
	int LeftNum = 0;
	int RightNum = 0;
	for (int i = 0; i < checkable.length(); i++)
	{
		if (checkable[i] == '(')
			LeftNum++;
		if (checkable[i] == ')')
		{
			RightNum++;
			if (RightNum > LeftNum)
				return false;
		}
	}
	if (RightNum != LeftNum)
		return false;
	return true;
}

Proposition::Proposition(string nname = "", bool nIfBasic = false, int ntype = Not, Proposition* na = NULL, Proposition* nb = NULL, bool nTruthValue = false)
{
	name = nname;
	IfBasic = nIfBasic;
	type = ntype;
	a = na;
	b = nb;
	TruthValue = nTruthValue;
};

Proposition::~Proposition()
{
	//if (this)
	//{
	//	if (a)
	//		delete a;
	//	if (b)
	//		delete b;
	//}
}

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
		{
			TruthValueString += "T\t";
		}
		else
		{
			TruthValueString += "F\t";
		}
	}
	if (CalculateNow())
	{
		TruthValueString += "T\r\n";
		TruthValueNums += "T";
	}
	else
	{
		TruthValueString += "F\r\n";
		TruthValueNums += "F";
	}
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
	TruthValueString = "";
	TruthValueHead = "";
	TruthValueNums = "";
	for (temp = Head; temp != NULL; temp = temp->next)
	{
		TruthValueString += temp->Pro->name + "\t";
		TruthValueHead += temp->Pro->name + "   ";
	}
	TruthValueString = TruthValueString + name + "\r\n";
	Bigger(Head);
};

int Proposition::GetLenth(int i = 1)
{
	if (i == 1)
	{
		if (IfBasic)
			return name.length();
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
			return name.length();
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

string Proposition::ToPoland()
{
	if (IfBasic)
	{
		return name;
	}
	switch (type)
	{
	case And:
		return AndNotion + a->ToPoland() + b->ToPoland();
	case Or:
		return OrNotion + a->ToPoland() + b->ToPoland();
	case Not:
		return NotNotion + a->ToPoland();
	case EOr:
		return EOrNotion + a->ToPoland() + b->ToPoland();
	case To:
		return ToNotion + a->ToPoland() + b->ToPoland();
	case BTo:
		return BToNotion + a->ToPoland() + b->ToPoland();
	default:
		return "";
	}
};

string Proposition::ToReversePoland()
{
	if (IfBasic)
	{
		return name;
	}
	switch (type)
	{
	case And:
		return a->ToReversePoland() + b->ToReversePoland() + AndNotion;
	case Or:
		return a->ToReversePoland() + b->ToReversePoland() + OrNotion;
	case Not:
		return a->ToReversePoland() + NotNotion;
	case EOr:
		return a->ToReversePoland() + b->ToReversePoland() + EOrNotion;
	case To:
		return a->ToReversePoland() + b->ToReversePoland() + ToNotion;
	case BTo:
		return a->ToReversePoland() + b->ToReversePoland() + BToNotion;
	default:
		return "";
	}
};

string Proposition::ToNormal()
{
	if (IfBasic)
	{
		return name;
	}
	switch (type)
	{
	case And:
		return "(" + a->ToNormal() + AndNotion + b->ToNormal() + ")";
	case Or:
		return "(" + a->ToNormal() + OrNotion + b->ToNormal() + ")";
	case Not:
		return NotNotion + a->ToNormal();
	case EOr:
		return "(" + a->ToNormal() + EOrNotion + b->ToNormal() + ")";
	case To:
		return "(" + a->ToNormal() + ToNotion + b->ToNormal() + ")";
	case BTo:
		return "(" + a->ToNormal() + BToNotion + b->ToNormal() + ")";
	default:
		return "";
	}
};

Proposition* Proposition::GetProposition(string Source, int len)
{
	Proposition* ans = new Proposition;
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
		Source = Source.substr(1);
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
				ans->b = GetProposition(Source.substr(j + 1), len - (j + 1));
				ans->TruthValue = false;
				ans->name == "";
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
				ans->b = GetProposition(Source.substr(j + 1), len - (j + 1));
				ans->TruthValue = false;
				ans->name == "";
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
				ans->b = GetProposition(Source.substr(j + 1), len - (j + 1));
				ans->TruthValue = false;
				ans->name == "";
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
				ans->b = GetProposition(Source.substr(j + 1), len - (j + 1));
				ans->TruthValue = false;
				ans->name == "";
				return ans;
			}
		case '^':
			if (j > 0)
			{
				ans->IfBasic = false;
				ans->type = EOr;
				ans->a = GetProposition(Source, j);
				ans->b = GetProposition(Source.substr(j + 1), len - (j + 1));
				ans->TruthValue = false;
				ans->name == "";
				return ans;
			}
		}
	}
	if (Source[0] == '!')
	{
		ans->IfBasic = false;
		ans->type = Not;
		ans->a = GetProposition(Source.substr(1), len - 1);
		ans->b = NULL;
		ans->TruthValue = false;
		ans->name == "";
		return ans;
	}
	string NewName = "";
	for (int i = 0; i < len; i++)
		NewName.push_back(Source[i]);
	//NewName.push_back('/0');
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
	if (!Head->Pro)
	{
		Head = NewHead;
		return ans;
	}

	for (TempHead = Head; TempHead != NULL && TempHead->Pro != NULL && strcmp(TempHead->Pro->name.c_str(), NewHead->Pro->name.c_str()) < 0; TempHead = TempHead->next)
	{
		int p = 0;
		p++;
	}
	if (TempHead == NULL || TempHead->Pro == NULL)
	{
		for (TempHead = Head; TempHead->next != NULL; TempHead = TempHead->next);
		TempHead->next = NewHead;
		return ans;
	}
	if (strcmp(TempHead->Pro->name.c_str(), NewHead->Pro->name.c_str()) == 0)
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

void Proposition::SetName(string SourceName, Proposition* Pro)
{
	Pro->name = SourceName;
};

bool Proposition::GetIsBasic()
{
	return IfBasic;
};

void Proposition::PrintNormalForm(int NormalFormType)
{
	if (NormalFormType == Disjunctive)
	{
		SetTruthValue(CalculateNow());
		if (!TruthValue)
			return;
		if (First)
			First = false;
		else
			PriDisNormalForm += OrNotion;
		PriDisNormalForm += "(";
		Atoms* temp;
		for (temp = Head; temp->next != NULL; temp = temp->next)
		{
			if (!(temp->Pro->TruthValue))
				PriDisNormalForm += NotNotion;
			PriDisNormalForm += temp->Pro->name;
			PriDisNormalForm += AndNotion;
		}
		if (!(temp->Pro->TruthValue))
			PriDisNormalForm += NotNotion;
		PriDisNormalForm += temp->Pro->name;
		PriDisNormalForm += ")";
	}
	else if(NormalFormType == Conjunctive)
	{
		SetTruthValue(CalculateNow());
		if (TruthValue)
			return;
		if (First)
			First = false;
		else
			PriConjNormalForm += AndNotion;
		PriConjNormalForm += "(";
		Atoms* temp;
		for (temp = Head; temp->next != NULL; temp = temp->next)
		{
			if (temp->Pro->TruthValue)
				PriConjNormalForm += NotNotion;
			PriConjNormalForm += temp->Pro->name;
			PriConjNormalForm += OrNotion;
		}
		if (temp->Pro->TruthValue)
			PriConjNormalForm += NotNotion;
		PriConjNormalForm += temp->Pro->name;
		PriConjNormalForm += ")";
	}
	else
	{
		if (ValuesNow[ValueBackNum++])
		{
			if (First1)
				First1 = false;
			else
				PriDisNormalForm += OrNotion;
			PriDisNormalForm += "(";
			Atoms* temp;
			for (temp = Head; temp->next != NULL; temp = temp->next)
			{
				if (!(temp->Pro->TruthValue))
					PriDisNormalForm += NotNotion;
				PriDisNormalForm += temp->Pro->name;
				PriDisNormalForm += AndNotion;
			}
			if (!(temp->Pro->TruthValue))
				PriDisNormalForm += NotNotion;
			PriDisNormalForm += temp->Pro->name;
			PriDisNormalForm += ")";
		}
		else
		{
			if (First2)
				First2 = false;
			else
				PriConjNormalForm += AndNotion;
			PriConjNormalForm += "(";
			Atoms* temp;
			for (temp = Head; temp->next != NULL; temp = temp->next)
			{
				if (temp->Pro->TruthValue)
					PriConjNormalForm += NotNotion;
				PriConjNormalForm += temp->Pro->name;
				PriConjNormalForm += OrNotion;
			}
			if (temp->Pro->TruthValue)
				PriConjNormalForm += NotNotion;
			PriConjNormalForm += temp->Pro->name;
			PriConjNormalForm += ")";
		}
	}
};

void Proposition::PrincipalDisjunctiveNormalForm()
{
	First = true;
	Bigger(Head, false, Disjunctive);
	//PriDisNormalForm += "\r\n";
};

void Proposition::PrincipalConjunctiveNormalForm()
{
	First = true;
	Bigger(Head, false, Conjunctive);
	//PriConjNormalForm += "\r\n";
};

int Proposition::SetHeads(string m)
{
	int Num = 0;
	Head->Pro = NULL;
	Head->next = NULL;
	Atoms* NewHead;
	Atoms* NowHead = Head;
	int j;
	while (m.length() > 0)
	{
		while (m[0] == ' ')
		{
			m = m.substr(1);
			if (m.length() <= 0)
				goto SetHeadsOver;
		}
		NewHead = new Atoms;
		NewHead->next = NULL;
		for (j = 0; j < m.length(); j++)
		{
			if (m[j] == ' ')
				break;
		}
		NewHead->Pro = new Proposition(m.substr(0, j), true);
		Num++;
		if (Head->Pro == NULL)
			NowHead = Head = NewHead;
		else
		{
			NowHead->next = NewHead;
			NowHead = NewHead;
		}
		if (j == m.length())
			break;
		m = m.substr(j);
	}
SetHeadsOver:;
	return Num;
}

void Proposition::SetValuesGetPri(string ValuesString)
{
	First1 = First2 = true;
	TruthValueNums = "";
	ValuesNow = new bool[ValuesString.length()];
	for (int j = 0; j < ValuesString.length(); j++)
	{
		if (ValuesString[j] == 'T' || ValuesString[j] == 't' || (ValuesString[j] >= '1' && ValuesString[j] <= '9'))
		{
			ValuesNow[j] = true;
			TruthValueNums += "T";
		}
		else
		{
			ValuesNow[j] = false;
			TruthValueNums += "F";
		}
	}
	PriDisNormalForm = PriConjNormalForm = "";
	ValueBackNum = 0;
	Bigger(Head, false, BothNeed);
	delete ValuesNow;
}

void Proposition::SetBases(int k, bool WithOk)
{
	BaseNum = 0;
	Atoms* THead = Head;
	TruthValueString = "";
	for (int j = 0; j < k; j++)
	{
		TruthValueString += THead->Pro->name + "\t";
		THead = THead->next;
	}
	if (WithOk)
		TruthValueString += name;
	TruthValueString += "\r\n";
	BasesUse = new bool[k];
	PrintBases(0, k, WithOk);
	delete BasesUse;
}

void Proposition::PrintBases(int m, int MaxNum, bool WithOK)
{
	BasesUse[m] = false;
	if (MaxNum - m == 1)
	{
		for(int temp = 0; temp < MaxNum; temp++)
			TruthValueString += BasesUse[temp] ? "T\t" : "F\t";
		if (WithOK)
			TruthValueString += TruthValueNums[BaseNum++];
		TruthValueString += "\r\n";
	}
	else
	{
		PrintBases(m + 1, MaxNum, WithOK);
	}
	BasesUse[m] = true;
	if (MaxNum - m == 1)
	{
		for (int temp = 0; temp < MaxNum; temp++)
			TruthValueString += BasesUse[temp] ? "T\t" : "F\t";
		if (WithOK)
			TruthValueString += TruthValueNums[BaseNum++];
		TruthValueString += "\r\n";
	}
	else
	{
		PrintBases(m + 1, MaxNum, WithOK);
	}
}
