#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
using namespace std;

template <class elmtype>
int partition(elmtype arr[], int front, int back, int size, int capacity); //partition function
template <class elmtype>
int randomPartition(elmtype arr[], int front, int back, int size, int capacity); //partition function using random element
template <class elmtype>
elmtype kthSmallest(elmtype arr[], int front, int back, int k, int size, int capacity); //helper function for finding kthSmallest element that allows recursion
template <class elmtype>
int binarySearch(elmtype arr[], int l, int r, elmtype x); //binary search 
template <class elmtype>
void swap(elmtype *a, elmtype *b);  //swap function for partitioning
template <class elmtype>
int medianof3(elmtype arr[], int front, int back, int size, int capacity); //median of three for quicksort
template <class elmtype>
void optimizedQuickSort(elmtype arr[], int front, int back, int size, int capacity); //recursive quicksort 
template <class elmtype>
void helperInsertionSort(elmtype arr[], int front, int back, int size, int capacity); //helper insertion sort

template <class elmtype>
class CDA {
    public:
        CDA(); //constructor
        CDA(int s); //constructor of size s
        ~CDA(); //destructor
        CDA(const CDA& a); //copy constructor
        CDA<elmtype>& operator=(CDA<elmtype> &other);  //overloaded assignment operator
        elmtype& operator[](int i); //traditional bracket operator
        void AddEnd(const elmtype &item); //add item to the end of array
        void AddFront(const elmtype &item); //add item to the front of array
        void DelEnd(); //delete item from front of array
        void DelFront(); //delete item from front of array
        int Length(); //returns the size of the array
        int Capacity(); //returns the capacity of the array
        void Clear(); //frees any apace currently used and starts over with an array of capacity 1 and size 0
        bool Ordered(); //returns the status of the ordered 
        int SetOrdered(); //return 1 if the array was ordered and -1 otherwise
        elmtype Select(int k); //returns the kthsmallest element in the array. 
        void InsertionSort(); //insertion sort
        void QuickSort(); // quick sort
        void CountingSort(int m); //counting sort
        int Search(elmtype e); //returns the index of the item if found or -1 otherwise

    private:
        int capacity; //maximum capacity of array
        int size; //size of array
        bool isOrdered; //returns whether or not array is ordered
        int front; //index of first element in queue
        int back; //index of last element in queue
        elmtype *array; //pointer for array's memory

};

template <class elmtype>
CDA<elmtype>::CDA(){
    size = 0;
    capacity = 1;
    front = back = -1;
    isOrdered = false;
    array = (elmtype *)malloc(size*sizeof(elmtype));
}

template <class elmtype>
CDA<elmtype>::CDA(int s){
    size = s;
    capacity = s;
    front = 0;
    back = s-1;
    isOrdered = false;
    array = (elmtype *)malloc(size*sizeof(elmtype));
}

template <class elmtype>
CDA<elmtype>::~CDA(){
    //delete [] array;
    //double free error affecting this
}

template <class elmtype>
CDA<elmtype>::CDA(const CDA& a){
    array = new elmtype[a.capacity];
    size = a.size;
    front = a.front;
    back = a.back;
    capacity = a.capacity;
    isOrdered = a.isOrdered;
    memcpy(array, a.array, sizeof(elmtype)*capacity);
}

/*template <class elmtype>
CDA<elmtype> & CDA<elmtype>::operator=(const CDA &a){
    if(this == &a) return *this;
    delete[] array;
    array = new elmtype[a.capacity];
    capacity = capacity;
    size = size;
    front = front;
    back = back;
    isOrdered = isOrdered;
    for(int i = 0; i < size; i++){
        array[i] = a[i];
    }
    return array;
}*/

template <class elmtype>
CDA<elmtype>& CDA<elmtype>::operator=(CDA<elmtype> &other){
    if(this == &other) return *this;
    delete[] array; 
    array = new elmtype[capacity];
    capacity = other.capacity;
    size = other.size;
    front = other.front;
    back = other.back;
    isOrdered = other.isOrdered;
    for(int i = 0; i < size; i++){
        array[i] = array[i];
    }
    return *this;
}

template <class elmtype>
elmtype& CDA<elmtype>::operator [] (int i){
    if(i > size){
        cout << "Out of bounds!" << endl;
        exit;
    }
    return *(array + ((front + i) % (capacity)));
}

template <class elmtype>
void CDA<elmtype>::AddEnd(const elmtype &item){
    if(size + 1 > capacity){
        capacity *= 2;
        array = (elmtype *)realloc(array, sizeof(elmtype)*capacity);
    }

    if (front == -1){
        front = 0;
        back = 0;
    }

    else if (back == capacity-1)
        back = 0;
    
    else
        back = back+1;
    
    array[back] = item;
    if(array[back] < array[(back-1) % capacity]) isOrdered = false;
    size++;
}

template <class elmtype>
void CDA<elmtype>::AddFront(const elmtype &item){
    if(size + 1 > capacity){
        capacity *= 2;
        array = (elmtype *)realloc(array, sizeof(elmtype)*capacity);
    }
    size++;
    if(front == -1){
        front = 0;
        back = 0;
    }
    else if ( front == 0)
        front = capacity - 1;

    else
        front = front-1;
    if(array[front] > array[(front + 1) % capacity]) isOrdered = false;
    array[front] = item;
}

template <class elmtype>
void CDA<elmtype>::DelEnd(){ 
    if (front == -1){ 
        exit;
    } 
    else if (front == back){
        front =  back = -1;
    }
    else if (back ==0)
        back = size - 1;

    else back = back-1;
    size--;
    if (size < capacity/4){
        CDA newCDA(capacity / 2);
        for(int i = 0; i < size; i++){
            newCDA.AddEnd(array[i]);
        }
        std::swap(array, newCDA.array);
        capacity /= 2;
    }
}

template <class elmtype>
void CDA<elmtype>::DelFront(){ 
    if (front == -1){ 
        exit;
    } 
    else if (front == back){
        front =  back = -1;
    }

    else
        if (front == size -1)
            front = 0;
        else 
            front = ((front+1)%capacity);
    size--;
    if (size < capacity/4){
        CDA newCDA(capacity / 2);
        for(int i = 0; i < size; i++){
            newCDA.AddEnd(array[i]);
        }
        std::swap(array, newCDA.array);
        capacity /= 2;
    }
}

template <class elmtype>
int CDA<elmtype>::Length(){
    return size;
}

template <class elmtype>
int CDA<elmtype>::Capacity(){
    return capacity;
}

template <class elmtype>
void CDA<elmtype>::Clear(){
    CDA newCDA(1);
    std::swap(array, newCDA.array);
    size = 0;
    capacity = 1;
    isOrdered = false;
}

template <class elmtype>
bool CDA<elmtype>::Ordered(){
    return isOrdered;
}

template <class elmtype>
int CDA<elmtype>::SetOrdered(){
    int n = size;
    if (n == 0 || n ==1 ){
        isOrdered = true;
        return 1;
    }

    for (int i = 0; i < n; i++){
        if(array[((front + i - 1) % (capacity))] > array[(front + i) % (capacity)] ){
            isOrdered = false;
            return -1;
        }
    }

    isOrdered = true;
    return 1;
    //return arraySortedOrNot(array, size);  
}

template <class elmtype>
elmtype CDA<elmtype>::Select(int k){
    if(isOrdered){
        //cout << " ##### I'm an ordered array, I'm going to pull the " << k << "th index! ##### " << endl;
        return array[(front + k - 1) % (capacity)];
    }
    //cout << " ##### I'm not ordered, I'm about to run the kthsmallest element algorithm! ##### " << endl;
    return kthSmallest(array, front, back, k, size, capacity);
}

template <class elmtype>
int CDA<elmtype>::Search(elmtype e){
    if(isOrdered){
        isOrdered = false;
        return binarySearch(array, 0, size, e);
    }
    else{  
        int index = 0;
        for(int i = front; i != back; i = (i+1)%capacity){
            if(array[i] == e)
                return index;
            index++;
        }
    }
    return -1;
}

template <class elmtype>
void CDA<elmtype>::InsertionSort(){
    helperInsertionSort(array, front, back, size, capacity);
    isOrdered = true;
}

template <class elmtype>
void CDA<elmtype>::QuickSort(){
    optimizedQuickSort(array, front, back, size, capacity);
    isOrdered = true;
}

template <class elmtype>
void CDA<elmtype>::CountingSort(int m){
    
    int max = m;
    int min = 0;
    int range = max - min + 1;
    vector<int> count(range), output(size), input(size);
    int inputIndex = 0;
    for(int i = front; i != back + 1; i = ((i+1)%capacity)){
        input[inputIndex] = array[i]; 
        inputIndex++;
    }
    for(int i = 0; i < input.size(); i++) 
        count[input[i]-min]++; 
          
    for(int i = 1; i < count.size(); i++) 
           count[i] += count[i-1]; 
    
    for(int i = input.size()-1; i >= 0; i--) 
    {  
         output[ count[input[i]-min] -1 ] = input[i];  
              count[input[i]-min]--;  
    }  
    int outputIndex = 0;
    for(int i = front; i != back + 1; i = ((i+1)%capacity)){
        array[i] = output[outputIndex];
        outputIndex++; 
    }
}


//Helper functions for recursive algorithms
//#############################################################################################################################################################
template <class elmtype>
elmtype kthSmallest(elmtype arr[], int front, int back, int k, int size, int capacity){
    if(k > 0 && k <= size){
        int pos = randomPartition(arr, front, back, size, capacity);
        //cout << "Pos = " << pos << endl;
        //cout << "k = " << k <<endl;
        if (pos == k-1){ 
            //cout << "I think " << pos-front << "==" << k-1 << endl;
            return arr[pos];
        }
    
        if (pos > k-1){
            int newSize;
            if(front > back){
                newSize = (back + capacity) - front;
            }
            else newSize = back - front;

            return kthSmallest(arr, front, ((pos-1) % capacity), k, newSize, capacity);
        }
        //cout << "K: " << k << " Position " << pos << endl;

        int newSize;
        if(front > back){
                newSize = (back + capacity) - front;
            }
        else newSize = back - front;
        //cout << " k-pos+front-1: " << k-pos+front-1 << endl;

        return kthSmallest(arr, (pos+1) % capacity, back, (k-pos+front) % capacity, newSize, capacity);   
    }

    return arr[back];
}

template <class elmtype>
int partition(elmtype arr[], int front, int back, int size, int capacity){
    //cout << endl << "Front: " << front << " Back: " << back << " Size: " << size << " Capacity: " << capacity << endl;
    elmtype x = arr[back];
    int i = front;
    for (int j = front; j != back; j = ((j + 1) % capacity)){
        if(arr[j] <= x){
            swap(&arr[i], &arr[j]);
            i = (i + 1) % capacity;
        }
    }
    swap(arr[i], arr[back]);
    return i;
}

template <class elmtype>
int randomPartition(elmtype arr[], int front, int back, int size, int capacity){
    //cout << endl << "Front: " << front << " Back: " << back << " Size: " << size << " Capacity: " << capacity << endl;
    int n = size;
    int pivot = rand() % n;
    swap(&arr[(front + pivot) % capacity], &arr[back]);
    return partition(arr, front, back, size, capacity);  
}

template <class elmtype>
void swap(elmtype *a, elmtype *b) 
{ 
    elmtype temp = *a; 
    *a = *b; 
    *b = temp; 
} 

template <class elmtype>
int binarySearch(elmtype arr[], int l, int r, elmtype x){
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
        if (arr[mid] == x) 
            return mid;
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1; 
}

template <class elmtype>
int medianof3(elmtype arr[], int front, int back, int size, int capacity){
    int mid = (front + size/2) % capacity;
    if(arr[front] < arr[back]){
        if(arr[mid] < arr[front]){ //bac
            swap(&arr[front], &arr[back]);
            return partition(arr, front, back, size, capacity);
        }
        else if(arr[back] < arr[mid]){ //acb
            return partition(arr, front, back, size, capacity);
        }
        else{
            swap(&arr[mid], &arr[back]); //abc
            return partition(arr, front, back, size, capacity);
        }
    }
    else if(arr[mid] < arr[back]){ //bca
        return partition(arr, front, back, size, capacity);
    }
    else if(arr[front] < arr[mid]){//cab
        swap(&arr[front], &arr[back]);
        return partition(arr, front, back, size, capacity);
    }
    else{
        swap(&arr[mid], &arr[back]); //cba
        return partition(arr, front, back, size, capacity);
    }
}

template <class elmtype>
void helperInsertionSort(elmtype arr[], int front, int back, int size, int capacity){
    int i, j;
    elmtype key;
    for (i = ((front + 1)%capacity); i != back + 1; i = (i+1)%capacity){
        key = arr[i];
        //cout << "Key: " << key << endl;
        if(i == 0){
            j = capacity - 1;
        }
        else{
            j = i - 1;
        }
        int oneBeforeFront = front - 1;
        while(j != oneBeforeFront && arr[j] > key){
            //cout << "Front: " << front << " j: " << j << endl;
            //cout << "Arr[j]: " << arr[j] << endl;
            arr[(j + 1)%capacity] = arr[j];
            if(j == 0){
                j = capacity - 1;
            }
            else{
                j--;
            }
        }
        //cout << "Front: " << front << endl;
        //cout << "j + 1 (should be front): " << j + 1 << endl;
        arr[(j + 1)%capacity] = key; 
    }
}

template <class elmtype>
void optimizedQuickSort(elmtype arr[], int low, int high, int size, int capacity){
    while(low != high){
        if(abs(low-high) < 10){
            helperInsertionSort(arr, low, high, size, capacity);
            break;
        }
        else{
            int pivot = medianof3(arr, low, high, size, capacity);
            if(abs(pivot - low) < abs(high - pivot)){
                if(pivot == 0){
                    pivot = capacity - 1;
                }
                else{
                    pivot--;
                }
                optimizedQuickSort(arr, low, pivot, size, capacity);
                low = (pivot + 1)%capacity;
            }
            else{
                optimizedQuickSort(arr, ((pivot+1)%capacity), high, size, capacity);
                if(pivot == 0){
                    high = capacity - 1;
                }
                else{
                    high = pivot-1;
                }
            }
        }
    }
}



