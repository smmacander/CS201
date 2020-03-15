#include <iostream>
#include <fstream>
using namespace std;
#include "CDA.cpp"

void test1(ostream &fp);
int printWrapper = 0;
int main(int argc, char **argv){
	int testToRun = atoi(argv[1]);
	switch (testToRun){
		case 1:
			test1(cout);
			break;
    }
}

void test1(ostream &fp){
	if(printWrapper) fp << "Running test 1" << endl;
    CDA<int> C(20);
    for (int i=0; i< C.Length();i++) C[i] = i*10;
    for (int i=0; i< C.Length();i++) fp << C[i] << " "; fp << endl;
    C.DelFront();
    for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
    C.DelEnd();
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
    C.AddEnd(1000);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
	C.AddEnd(1001);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
    C.DelEnd(); C.DelEnd();
    C.AddFront(-100); C.AddFront(-200);
	for (int i=0; i< C.Length();i++) fp << C[i] << " ";  fp << endl;
    fp << "Capacity is " << C.Capacity() << endl;

    CDA<int> A;
    int temp = 0;
	for(int i=0; i<20;i++){
		A.AddEnd(i*10);
		if(A.Capacity() != temp){
			temp = A.Capacity();
			fp << "Capacity is " << temp << " ";
		}
	}
    fp << endl;
	fp << "Capacity is " << A.Capacity() << endl;
    fp << "SetOrdered is " << A.SetOrdered() << endl;
    for (int i=0; i< A.Length();i++) fp << A[i] << " ";  fp << endl;
    fp << "Select is " << A.Select(3) << endl;
	fp << "Search is " << A.Search(50) << endl;
	for (int i=0; i< A.Length();i++) fp << A[i] << " "; fp << endl;
	A.AddFront(11); 
	for (int i=0; i< A.Length();i++) fp << A[i] << " "; fp << endl;
	fp << "SetOrdered is " << A.SetOrdered() << endl;
	fp << "Ordered is " << A.Ordered() << endl;
	fp << "Select is " << A.Select(3) << endl;
	fp << "Search is " << A.Search(50) << endl;
}