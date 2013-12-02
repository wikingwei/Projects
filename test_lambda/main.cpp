
 
#pragma once
 

#include <stdio.h>
#include <tchar.h>


#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{  aaaa
	vector<int> v;
	for (int i = 0; i < 101; ++i)
	{
		v.push_back(i);
	}
	
	for_each(v.begin(), v.end(), [] (int n){
			cout << n;
			if (n % 2 == 0)
			{cout << " even\n"; }
			else
			{cout << " odd\n"; }
	});

	cout << endl;
	return 0; 
 
}