#include "../gnublin.h"
#include <iostream>
using namespace std;

int main(void)
{
	int i = 0, max = 30, second = 1;
	while(i != max)
	{
		cout << "Hello Gnublin!" << endl;
		sleep(second);
		i++;
	}
	return 0;
}
