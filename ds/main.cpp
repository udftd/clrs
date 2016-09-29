#include <iostream>
#include "List.hpp"

using namespace std;

int main()
{
	List<int> L;
	L.push_back(10);
	auto x = L.back();
	cout << "x " << x << endl;

	return 0;
}
