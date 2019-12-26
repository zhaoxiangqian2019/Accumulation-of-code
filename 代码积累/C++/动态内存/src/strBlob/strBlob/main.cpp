#include "strBlob.h"

int main()
{
	strBlob blob1;
	cout << blob1.size() << endl;
	cout << blob1.useCount() << endl;

	{
		strBlob blob2({ "Hello", "Morning", "Best Wishes" });
		blob1 = blob2;
		blob2.push_back("Good Luck");
		cout << blob1.size() << endl;
		cout << blob1.useCount() << endl;
		cout << blob2.useCount() << endl;
	}
	blob1.printBlob();
	cout << blob1.useCount() << endl;

	strBlob blob3({ "apple", "pear", "banana", "orange" });
	blob3.printBlob();
	cout << blob3.useCount() << endl;

	system("pause");
	return 0;
}