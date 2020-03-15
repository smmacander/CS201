#include <iostream>
#include <fstream>
using namespace std;

template<class elmtype>
int randomPartition(elmtype arr[], int l, int r);  //Standard partition process of QuickSort(). It considers the last element as pivot and moves all smaller element to left of it and greater elements to right 
template<class elmtype>
int kthSmallest(elmtype arr[], int l, int r, int k); //This function returns k'th smallest element in arr[l..r] using QuickSort based method. ASSUMPTION: ELEMENTS IN ARR[] ARE DISTINCT 
template<class elmtype>
void swap(elmtype *a, elmtype *b);

template<class elmtype>
class CDA{
    public:
        CDA(); //Default Constructor. The array should be of capacity 1, size 0 and ordered is false.
        CDA(int s); //For this constructor the array should be of capacity and size s with ordered = false
        elmtype& operator[](int i); //Traditional [] operator. Should print a message if i is out of bounds and return a reference to value of type elmtype stored in the class for this purpose.
        void AddEnd(elmtype v); //Increases the size of the array by 1 and stores vat the end of the array. Should double the capacity when the new element doesn't fit.  If ordered is true, check to be sure that the array is still in order. 
        void AddFront(elmtype v); //Increases the size of the array by 1 and stores vat the beginning of the array. Should double the capacity when the new element doesn't fit. The new element should be the item returned at index 0.  If ordered is true, check to be sure that the array is still in order.
        void DelEnd(); //reduces the size of the array by 1 at the end. Should shrink the capacity when only 25% of the array is in use after the delete. The capacity should never go below 1.
        void DelFront(); //reduces the size of the array by 1 at the beginning of the array. Should shrink the capacity when only 25% of the array is in use after the delete. The capacity should never go below 1.
        int Length(); //returns the size of the array
        int Capacity(); //returns the size of the array
        bool Ordered(); //returns the status of the ordered flag
        int SetOrdered(); //Check to see if the array is in order.  Set the order flag appropriately.  Return 1 if the array was ordered and -1 otherwise.
        elmtype Select(int k); //returns the kthsmallest element in the array.  If ordered is true then return the item at index k-1.  Otherwise use the quickselect algorithm. Quickselect should choose a random partition element.
        int Search(elmtype e); //If ordered is true, perform a binary searchof the array looking for the item e.  Otherwise perform linear search.  Returns the index of the item if found or -1 otherwise.
    private:
        elmtype *array;
        int back;
        int capacity;
        int front;
        bool ordered;
        int size;        
};

template<class elmtype>
CDA<elmtype>::CDA(){
    array = (elmtype *)malloc(sizeof(elmtype));
    back = 0;
    capacity = 1;
    front = 0;
    ordered = false;
    size = 0;
}

template<class elmtype>
CDA<elmtype>::CDA(int s){
    array = (elmtype *)malloc(s*sizeof(elmtype));
    back = s-1;
    capacity = s;
    front = 0;
    ordered = false;
    size = s;
}

template<class elmtype>
elmtype& CDA<elmtype>::operator[](int i){
    if(i > size){
        cout << "Out of bounds!" << endl;
        exit;
    }
    return *(array + ((front + i) % (capacity)));
}

template<class elmtype>
void CDA<elmtype>::AddEnd(elmtype v){
    if(size + 1 > capacity){
        capacity *= 2;
        array = (elmtype *)realloc(array, sizeof(elmtype)*capacity);
    }
    if(back == capacity - 1){
        back = 0;
        *(array + (back % capacity)) = v;
        size++;
        if((ordered == true) && (*(array + back) < *(array + (capacity - 1)))){
            ordered = false;
        }
    }
    else{
        back++;
        *(array + (back % capacity)) = v;
        size++;
        if((ordered == true) && (*(array + back) < *(array + (back - 1)))){
            ordered = false;
        }
    }
}

template<class elmtype>
void CDA<elmtype>::AddFront(elmtype v){
    if(size + 1 > capacity){
        capacity *= 2;
        array = (elmtype *)realloc(array, sizeof(elmtype)*capacity);
    }
    if(front == 0){
        front = capacity - 1;
        *(array + (front % capacity)) = v;
        size++;
        if((ordered == true) && (*(array + front) > *(array + (capacity - 1)))){
            ordered = false;
        }
    }
    else{
        front--;
        *(array + (front % capacity)) = v;
        size++;
        if((ordered == true) && (*(array + front) > *(array + (front + 1)))){
            ordered = false;
        }
    }
}

template<class elmtype>
void CDA<elmtype>::DelEnd(){
    if(capacity > 1){
        back--;
        size--;
        if(capacity < size/4){
            elmtype* newArray;
            newArray = new elmtype[size];
            for(int i = 0; i < size; i++){
                *(newArray + i) = *(array + ((front + i) % (capacity)));
            }
            std::swap(array, newArray);
            capacity /= 2;
            front = 0;
            back = size - 1;
        }
    }
}

template<class elmtype>
void CDA<elmtype>::DelFront(){
    if(capacity > 1){
        front++;
        size--;
        if(capacity < size/4){
            elmtype* newArray;
            newArray = new elmtype[size];
            for(int i = 0; i < size; i++){
                *(newArray + i) = *(array + ((front + i) % (capacity)));
            }
            std::swap(array, newArray);
            capacity /= 2;
            front = 0;
            back = size - 1;
        }
    }
}

template<class elmtype>
int CDA<elmtype>::Length(){
    return size;
}

template<class elmtype>
int CDA<elmtype>::Capacity(){
    return capacity;
}

template<class elmtype>
bool CDA<elmtype>::Ordered(){
    return ordered;
}

template<class elmtype>
int CDA<elmtype>::SetOrdered(){
    elmtype current;
    elmtype currentPlusOne;
    for(int i = 0; i < size - 1; i++){
        current = *(array + ((front + i)%capacity));
        currentPlusOne = *(array + (front + i + 1)%capacity);
        if(current > currentPlusOne){
            ordered = false;
            return -1;
        }
    }
    ordered = true;
    return 1;
}

template<class elmtype>
elmtype CDA<elmtype>::Select(int k){
    if(ordered == true){
        return this->operator[](k-1);
        //return *(array + ((front + k - 1)%capacity));
    }
    else{
        CDA<elmtype> temp = *this;
        return kthSmallest(temp, 0, size, k);
    }
}

template<class elmtype>
int CDA<elmtype>::Search(elmtype e){
    if(ordered == true){
        CDA <elmtype> temp = *this;
        return binarySearch(temp, 0, size - 1, e);
    }
    else{
        CDA <elmtype> temp = *this;
        return linearSearch(temp, size, e);
    }

}

//HELPER FUNCTIONS BELOW/////////////////////////////////////////////////////////////////////////////////
template<class elmtype>
int kthSmallest(CDA<elmtype> array, int l, int r, int k){
    int pos = randomPartition(array, l, r); 
  
    // If position is same as k 
    if (pos-l == k-1) 
        return array[pos]; 
    if (pos-l > k-1)  // If position is more, recur for left subarray 
        return kthSmallest(array, l, pos-1, k); 
  
    // Else recur for right subarray 
    return kthSmallest(array, pos+1, r, k-pos+l-1); 
}

template<class elmtype>
void swap(elmtype *a, elmtype *b){ 
    elmtype temp = *a; 
    *a = *b; 
    *b = temp; 
} 

template<class elmtype>
int partition(CDA<elmtype> array, int l, int r) 
{ 
    int x = array[r], i = l; 
    for (int j = l; j <= r - 1; j++) 
    { 
        if (array[j] <= x) 
        { 
            swap(&array[i], &array[j]); 
            i++; 
        } 
    } 
    swap(&array[i], &array[r]); 
    return i; 
} 

template<class elmtype>
int randomPartition(CDA<elmtype> array, int l, int r){
    int n = r-l+1; 
    int pivot = rand() % n; 
    swap(&array[l + pivot], &array[r]); 
    return partition(array, l, r); 
}

template<class elmtype>
int binarySearch(CDA<elmtype> array, int l, int r, elmtype x){
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        if (array[mid] == x) 
            return mid; 
  
        if (array[mid] > x) 
            return binarySearch(array, l, mid - 1, x); 
  
        return binarySearch(array, mid + 1, r, x); 
    } 
    return -1; 
}

template<class elmtype>
int linearSearch(CDA<elmtype> array, int n, elmtype x){
    int i; 
    for (i = 0; i < n; i++) 
        if (array[i] == x) 
            return i; 
    return -1; 
}