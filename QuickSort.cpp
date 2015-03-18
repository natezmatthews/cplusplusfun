#include <iostream>
using namespace std;

const int cap = 31;

class Array {

	public:

	Array();

	void Sort();
	
	void Print(int l, int r);

	private:

	void Swap(int left, int right);

	int* a;

};

Array::Array()
{
	a = new int [cap];
	for(int i = 0; i < cap; i++){
		cin >> a[i];
	}
}

void Array::Swap(int left, int right)
{
	if(right <= left)
		return;
	if(right < 0)
		return;
	if(left < 0)
		return;
	if(right > cap-1)
		return;
	if(left > cap-1)
		return;
	int l = left;
	int r = right;
	int hold;
	bool reg = true;
	while(l < r){
		if(a[l] > a[r]){
			hold = a[l];
			a[l] = a[r];
			a[r] = hold;
			Print(l,r);
			reg = !reg;
		}
		if(reg)
			r--;
		else
			l++;
	}
	Swap(left,l-1);
	Swap(l+1,right);
}

void Array::Sort()
{
	Swap(0,cap-1);
}

void Array::Print(int l, int r)
{
	for(int i = 0; i < cap; i++){
		cout << a[i];
		if(l == i || r == i)
			cout << '*';
		else cout << ' ';
	}
	cout << endl;
}

int main()
{	
	Array a;
	a.Print(0,cap-1);
	a.Sort();
	a.Print(-1,-1);
	return 0;
}
