#include <iostream>
using namespace std;
#include "CDA.cpp"

int main(){
	CDA<float> C(10);
	for (int i=0; i< C.Length();i++) C[i] = i;
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	//"0 1 2 3 4 5 6 7 8 9"
    C.DelFront();
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	//"1 2 3 4 5 6 7 8 9"
    C.DelEnd();
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    //"1 2 3 4 5 6 7 8"
    C.AddEnd(100.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	//"1 2 3 4 5 6 7 8 100"
    C.AddEnd(101.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	//"1 2 3 4 5 6 7 8 100 101"
    C.DelEnd(); C.DelEnd();
	C.AddFront(-100.0); C.AddFront(-200.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	//"-200 -100 1 2 3 4 5 6 7 8"

    CDA<int> A;
	for(int i=0; i<10;i++) A.AddEnd(i);
	cout << "SetOrdered is " << A.SetOrdered() << endl;
	//SetOrdered is 1
    for (int i=0; i< A.Length();i++) cout << A[i] << " ";  cout << endl;
    //0 1 2 3 4 5 6 7 8 9
    cout << "Select is " << A.Select(3) << endl;
	//Select is 2
    cout << "Search is " << A.Search(5) << endl;
	//Search is 5
    A.AddFront(10);
    cout << "SetOrdered is " << A.SetOrdered() << endl;
	//SetOrdered is -1
    for (int i=0; i< A.Length();i++) cout << A[i] << " ";  cout << endl;
    //"10 0 1 2 3 4 5 6 7 8 9"
    cout << "Select is " << A.Select(3) << endl;
	//Select is 2
}