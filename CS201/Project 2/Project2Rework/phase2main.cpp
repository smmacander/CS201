#include <iostream>
#include <cstdlib>
using namespace std;
#include "RBTree.cpp"

void printErrors(string errors, int numOfErrors){
	if(numOfErrors < 5){
		cout << errors << " passed " << endl;
	}else if(numOfErrors < 100){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1" << endl;
	}else if (numOfErrors < 1000){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors ADD+1" << endl;
	}else if (numOfErrors < 10000){
		cout << errors << " caused " << numOfErrors << " of errors ADD+1" << endl;
	}else{
		cout << errors << " caused " << numOfErrors << " of errors" << endl;
	}
}

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void removeIndex(int removeIndex);

int main(int argc, char **argv){
	int testToRun = atoi(argv[1]);
	switch (testToRun){
		case 1:
			test1();
			break;
		case 2:
			test2();
			break;
		case 3:
			test3();
			break;
		case 4:
			test4();
			break;
		case 5:
			test5();
			break;
		case 6:
			test6();
			break;
		case 7:
			test7();
			break;
	}
	return 0;
}


void test1(){
	string K[10] = {"A","B","C","D","E","F","H","I","J","K"};
	int V[10] = {10,9,8,7,6,5,4,3,2,1};
	
	RBTree<string,int> T1, T2(K,V,10);
	T2.postorder();
	cout << endl;
	//A C B E H F J K I D
	
	for(int i=0; i<10; i++) T1.insert(K[i],V[i]);
	// T1 and T2 should be identical trees
	
	T1.insert("AA",11);
	T1.insert("AB",12);
	T1.insert("AC",13);
	cout << *(T1.search("AB")) << endl;
	// Should output 12
	
	cout << T1.rank("H") << endl;
	//Should output 10
	
	cout << T1.select(3) << endl;
	//Should output AB 
	
	T1.preorder();
	cout << endl;
	//Should output D B AA A AC AB C I F E H K J
	
	T1.inorder();
	cout << endl;
	//Should output	A AA AB AC B C D E F H I J K
	
	cout << T1.remove("HA") << endl;
	//Should output 0
	
	cout << T1.remove("AA") << endl;
	//Should output 1
	
	cout <<T1.rank("J") << endl;
	//Should output 11
	
	T1.inorder();
	cout << endl;
	//Should output	A AB AC B C D E F H I J K
	cout << "Finished without failing" << endl << endl;
}

void test2(){
	
	RBTree<int,int> X;
	for (int i=100;i>=0;i--) X.insert(i,100-i);
	X.preorder(); 
    cout << endl;
	X.postorder();
    cout << endl;
	X.inorder();
    cout << endl;
	RBTree<int,int> Y = X;
	for (int i=0; i < 98; i++){
		X.rank(i);
		X.remove(i);
	}
	Y.preorder();
    cout << endl;
	Y.postorder();
    cout << endl;
	Y.inorder();
    cout << endl;
	cout << "Finished without failing" << endl << endl;
}

void test3(){
	int rankError = 0;
	int selectError = 0;
	int searchError = 0;
    RBTree<int,int> X;
	for (int i=100000;i>=0;i--) X.insert(i,100000-i);
	for (int i=1;i<100000;i++) {
		// cout << i+1 << " is i+1" << endl;
		// cout << X.rank(i) << " is rank" << endl;
		if(X.rank(i) != i+1) rankError++; //cout << "Rank error before delete" << endl;
		if(X.select(i) != i-1) selectError++; //cout << "Select error before delete" << endl;
		if(*(X.search(i)) != 100000-i) searchError++;//cout << "Search error before delete" << endl;
	}
	printErrors("Rank",rankError);
	printErrors("Select",selectError);
	printErrors("Search",searchError);
	cout << "Finished without failing" << endl << endl;
}

void test4(){
	removeIndex(11);
}

void test5(){
	removeIndex(17);
}

void test6(){
	RBTree<int,int> X;
	int predErrors = 0;
	int succErrors = 0;
    int size = 10000;
	for (int i=size;i>=0;i--) X.insert(i,size-i);
	for (int i=0; i < X.size(); i++){
		if(i == 0){
            if(X.predecessor(i) != NULL) cout << "Doesn't return NULL for predecessor" << endl;
		}
        else if(*(X.predecessor(i)) != i-1){
			cout << "i: " << i << " predecessor: " << *(X.predecessor(i)) << endl;
            predErrors++;
            printf("pred error %d\n",predErrors);
        }
	}
	printErrors("Pred errors",predErrors);
	for (int i=X.size()-1; i >= 0; i--){
		if(i == size){
            if(X.successor(i) != NULL) cout << "Doesn't return NULL for successor" << endl;
		}
        else if(*(X.successor(i)) != i+1){ 
            succErrors++;
            //printf("pred error %d\n",predErrors);
        }
	}	
	printErrors("Succ Errors",succErrors);
	cout << "Finished without failing" << endl << endl;
}


void removeIndex(int removeIndex){
	int rankError = 0;
	int selectError = 0;
	int searchError = 0;
    RBTree<int,int> X;
	int size = 100000;
	bool error;
    for (int i=size;i>=0;i--) X.insert(i,size-i);
	for (int i=0;i<size;i+=removeIndex) X.remove(i);
	for (int i=1;i<size-size/removeIndex;i++){
        error = false;
        int part1Answer = i / removeIndex;
		int answer = i+(i+(i+(i+(i+(i + i / removeIndex)/removeIndex)/removeIndex)/removeIndex)/removeIndex)/removeIndex;

		//printf("i is %d, Select %d, Rank %d, Search %d\n",i, answer, i-i/removeIndex, size-i);
        if(X.select(i) != answer){	
			error = true;			
			selectError++;
			cout << "i is " << i << " Select error after delete " << X.select(i)  << " should be " <<  answer << " or " << part1Answer << endl;
		}
		//if(error){
			//X.print2DMain();
			//cout << "#############" << endl;
		//}
		if (i%removeIndex) {
			//cout << i << " is i" << endl;
			if(X.rank(i) != i-i/removeIndex){
                rankError++; 
                cout << "Rank error after delete " << X.rank(i) << " should be " << i << " - " << i-i/removeIndex << endl;
			}
            if(*(X.search(i)) != size-i) searchError++; //cout << "Search error after delete" << endl;
			/*
			X.print2DMain();
			cout << "#############" << endl << "About to remove i: " << i << endl;
			*/
            X.remove(i);
			//X.print2DMain();
			/*
			cout << "#############" << endl << "About to insert i: " << i << endl;
			*/
			X.insert(i,size-i);
			/*
			X.print2DMain();
			cout << "#############" << endl;
			*/
		}
	}
	printErrors("Rank after delete",rankError);
	printErrors("Select after delete",selectError);
	printErrors("Search after delete",searchError);
	cout << "Finished without failing" << endl << endl;
}

void test7(){
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

T.print2DMain();
cout << T.size() << endl;

T.inorder();
cout << endl;
//2 4 6 8 10 12 14 16 18 20
T.preorder();
cout << endl;
//12 4 2 8 6 10 16 14 18 20
T.postorder();
cout << endl;
//2 6 10 8 4 14 20 18 16 12

RBTree<int,int> X;
X = T;
X.print2DMain();
T = T;

X.remove(6);
cout << T.size() << endl;
//10
cout << X.size() << endl;
//9

X.inorder();
//2 4 8 10 12 14 16 18 20

cout << endl;
T.inorder();
//2 4 6 8 10 12 14 16 18 20

if(X.search(24) == nullptr){
	cout << "returned nullptr" << endl;
}
if(X.successor(20) == nullptr){
	cout << "returned nullptr" << endl;
}
if(X.predecessor(2) == nullptr){
	cout << "returned nullptr" << endl;
}
//all these should return the nullptr

cout << X.select(8) << endl;
//18
cout << X.rank(8) << endl;
//3


cout << X.rank(X.select(8)) << endl;
cout << X.select(X.rank(8)) << endl;
//these two are whatever you pass into them, 8

X.remove(16);
cout << X.rank(2) << " " << X.rank(4) << " " << X.rank(8) << " " << X.rank(10) << " " << X.rank(12) << " " << X.rank(14) << " " << X.rank(18) << " " << X.rank(20) << endl;
X.remove(4);
cout << X.rank(2) << " " << X.rank(8) << " " << X.rank(10) << " " << X.rank(12) << " " << X.rank(14) << " " << X.rank(18) << " " << X.rank(20) << endl;
X.remove(12);
cout << X.rank(2) << " " << X.rank(8) << " " << X.rank(10) << " " << X.rank(14) << " " << X.rank(18) << " " << X.rank(20) << endl;
X.remove(2);
cout << X.rank(8) << " " << X.rank(10) << " " << X.rank(14) << " " << X.rank(18) << " " << X.rank(20) << endl;
X.remove(14);
cout << X.rank(8) << " " << X.rank(10) << " " << X.rank(18) << " " << X.rank(20) << endl;
X.remove(10);
cout << X.rank(8) << " " << X.rank(18) << " " << X.rank(20) << endl;
X.remove(18);
cout << X.rank(8) << " " << X.rank(20) << endl;
X.remove(20);
cout << X.rank(8) << endl;
X.remove(8);
//should count down from 1-8 to just 1

cout << X.size() << endl;
//0

X.insert(2,2);
X.insert(4,4);
X.insert(6,6);
X.insert(8,8);
X.insert(10,10);
X.insert(12,12);
X.insert(14,14);
X.insert(16,16);
X.insert(18,18);
X.insert(20,20);
X.insert(22,22);
X.insert(24,24);
X.insert(26,26);
X.insert(28,28);
X.insert(30,30);

X.inorder();
//2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
X.preorder();
//8 4 2 6 16 12 10 14 20 18 24 22 28 26 30
X.postorder();
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

}
