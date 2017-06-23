#include"FH_Poland_Test.h"

int main()
{
	do
	{
		Start();
		getchar();
		if (getchar() == 'y' && getchar() == '\n')
			continue;
		else
			break;
	} while (1);
	return 0;
}