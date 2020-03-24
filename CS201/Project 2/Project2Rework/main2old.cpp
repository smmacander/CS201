#include <iostream>
using namespace std;
#include "RBTree.cpp"

int main(){
RBTree<int,int> T;
cout << T.size() << endl;
//should be 0

T.insert(16,8);
T.insert(8,4);
T.insert(12,6);
T.insert(14,7);
T.insert(18,9);
T.insert(2,1);
T.insert(4,2);
T.insert(10,5);
T.insert(6,3);
T.insert(20,10);

T.inorder();
//2 4 6 8 10 12 14 16 18 20
T.preorder();
//12 4 2 8 6 10 16 14 18 20
T.postorder();
//2 6 10 8 4 14 20 18 16 12

RBTree<int,int> X;
X = T;
T = T;

Y.remove(6);
cout << T.size() << endl;
//10
cout << Y.size() << endl;
//9

Y.inorder();
//2 4 8 10 12 14 16 18 20
T.inorder();
//2 4 6 8 10 12 14 16 18 20

if(Y.search(24) == nullptr){
	cout << "returned nullptr" << endl;
}
if(Y.successor(20) == nullptr){
	cout << "returned nullptr" << endl;
}
if(Y.predecessor(2) == nullptr){
	cout << "returned nullptr" << endl;
}
//all these should return the nullptr

cout << Y.select(8) << endl;
//18
cout << Y.rank(8) << endl;
//3


cout << Y.rank(Y.select(8)) << endl;
cout << Y.select(Y.rank(8)) << endl;
//these two are whatever you pass into them, 8

Y.remove(16);
cout << Y.rank(2) << " " << Y.rank(4) << " " << Y.rank(8) << " " << Y.rank(10) << " " << Y.rank(12) << " " << Y.rank(14) << " " << Y.rank(18) << " " << Y.rank(20) << endl;
Y.remove(4);
cout << Y.rank(2) << " " << Y.rank(8) << " " << Y.rank(10) << " " << Y.rank(12) << " " << Y.rank(14) << " " << Y.rank(18) << " " << Y.rank(20) << endl;
Y.remove(12);
cout << Y.rank(2) << " " << Y.rank(8) << " " << Y.rank(10) << " " << Y.rank(14) << " " << Y.rank(18) << " " << Y.rank(20) << endl;
Y.remove(2);
cout << Y.rank(8) << " " << Y.rank(10) << " " << Y.rank(14) << " " << Y.rank(18) << " " << Y.rank(20) << endl;
Y.remove(14);
cout << Y.rank(8) << " " << Y.rank(10) << " " << Y.rank(18) << " " << Y.rank(20) << endl;
Y.remove(10);
cout << Y.rank(8) << " " << Y.rank(18) << " " << Y.rank(20) << endl;
Y.remove(18);
cout << Y.rank(8) << " " << Y.rank(20) << endl;
Y.remove(20);
cout << Y.rank(8) << endl;
Y.remove(8);
//should count down from 1-8 to just 1

cout << Y.size() << endl;
//0

Y.insert(2,2);
Y.insert(4,4);
Y.insert(6,6);
Y.insert(8,8);
Y.insert(10,10);
Y.insert(12,12);
Y.insert(14,14);
Y.insert(16,16);
Y.insert(18,18);
Y.insert(20,20);
Y.insert(22,22);
Y.insert(24,24);
Y.insert(26,26);
Y.insert(28,28);
Y.insert(30,30);

Y.inorder();
//2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
Y.preorder();
//8 4 2 6 16 12 10 14 20 18 24 22 28 26 30
Y.postorder();
//2 6 4 10 14 12 18 22 26 30 28 24 20 16 8

T = X;

cout << T.size() << endl;
//15

T.remove(10);
cout << T.select(14) << endl;
T.remove(22);
cout << T.select(13) << endl;
T.remove(30);
cout << T.select(12) << endl;
T.remove(24);
cout << T.select(11) << endl;
T.remove(26);
cout << T.select(10) << endl;
T.remove(28);
cout << T.select(9) << endl;
T.remove(8);
cout << T.select(8) << endl;
T.remove(2);
cout << T.select(7) << endl;
T.remove(16);
cout << T.select(6) << endl;
T.remove(4);
cout << T.select(5) << endl;
T.remove(6);
cout << T.select(4) << endl;
T.remove(20);
cout << T.select(3) << endl;
T.remove(12);
cout << T.select(2) << endl;
T.remove(18);
cout << T.select(1) << endl;
/*30
30
28
28
28
20
20
20
20
20
20
18
18
14*/

	return 0;
}
