#ifndef HF_POLAND_MAIN_H
#define HF_POLAND_MAIN_H

#define And 1
#define Or 2
#define Not 3
#define ExclusiveOr 4
#define EOr 4
#define To 5
#define BothTo 6
#define BTo 6

#define AndNotion "&&"
#define OrNotion "||"
#define NotNotion "!"
#define EOrNotion "^"
#define ToNotion "->"
#define BToNotion "<->"

#define AndNotionLen 2
#define OrNotionLen 2
#define NotNotionLen 1
#define EOrNotionLen 1
#define ToNotionLen 2
#define BToNotionLen 3

#define Disjunctive 1
#define Conjunctive 2
#define BothNeed 3
using namespace std;
#include<iostream>


class Proposition;

struct Atoms
{
	Proposition* Pro;
	Atoms* next;
};

class Proposition
{
private:
	bool IfBasic;
	int type;
	Proposition * a;
	Proposition * b;
	bool TruthValue;
	void PrintTruthValueLine();
	void Bigger(Atoms*, bool, int);
	int ValueBackNum;

	int GetLenth(int);

public:
	string name;
	string TruthValueString;
	string TruthValueHead;
	string TruthValueNums;
	string PriDisNormalForm;//主析取范式
	string PriConjNormalForm;//主合取范式
	~Proposition();
	Proposition(string name, bool IfBasic, int type, Proposition* a, Proposition* b, bool TruthValue);
	bool CalculateNow();
	void TruthValueTable();
	string ToPoland();
	string ToReversePoland();
	string ToNormal();
	Proposition* GetProposition(string Source, int len);
	void SetTruthValue(bool);
	bool GetTruthValue();
	void SetName(string, Proposition*);
	bool GetIsBasic();
	void PrincipalDisjunctiveNormalForm();//主析取范式
	void PrincipalConjunctiveNormalForm();//主合取范式
	void PrintNormalForm(int);
	void clear();
	bool check(string checkable);

	int SetHeads(string m);
	void SetValuesGetPri(string ValuesString);
	void SetBases(int k, bool);
	void PrintBases(int m, int, bool);
};

#endif // !HF_POLAND_H
