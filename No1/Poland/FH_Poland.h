#ifndef HF_POLAND_H
#define HF_POLAND_H

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
	char* name;
	void PrintTruthValueLine();
	void Bigger(Atoms*, bool, int);

	int GetLenth(int);

public:
	Proposition();
	Proposition(char* name, bool IfBasic, int type, Proposition* a, Proposition* b, bool TruthValue);
	Proposition(char* name, bool IfBasic, int type);
	bool CalculateNow();
	void TruthValueTable();
	char* ToPoland();
	char* ToReversePoland();
	char* ToNormal();
	Proposition* GetProposition(char* Source, int len);
	void SetTruthValue(bool);
	bool GetTruthValue();
	void SetName(char*, Proposition*);
	bool GetIsBasic();
	void PrincipalDisjunctiveNormalForm();//主析取范式
	void PrincipalConjunctiveNormalForm();//主合取范式
	void PrintNormalForm(int);
	void clear();
};

#endif // !HF_POLAND_H
