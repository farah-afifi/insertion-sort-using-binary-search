#include <iostream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include<vector>
#include <fstream>
#include <random>
#include <time.h>
using namespace std;
using namespace std::chrono;
int count1 = 0 ,count2 = 0 ;
void loadDataFromFile(int* arr , int n){
    ifstream file;
    file.open("file.txt");
    int num;
    for(int i = 0 ; i < n ;i++){
        file >> num;
        arr[i] = num;
    }
}

int binarySearch(int * arr , int start, int end , int key)
{
    if (start >= end){
        return (key > arr[start]? start + 1 : start);
    }
    else{
        count2++;
        int mid = (end + start)/2;
        if(arr[mid] == key)
                return mid + 1;
        else if (arr[mid] > key)
            return binarySearch(arr , start , mid - 1 ,key);
        else if (arr[mid] < key)
            return binarySearch(arr , mid + 1 , end  ,key);
    }
}


void BinaryInsertionSort(int * arr , int n){
    int i, j, key;
    for(int i = 1 ; i < n ; i++){
        key = arr[i];

        j = i;
        int loc = binarySearch(arr  , 0 , j - 1 , key );

        while ( j > loc ){
            count2++;
            arr[j] = arr [j - 1];
            j--;
        }
        arr[j] = key;
    }
}
void insertionSort(int * arr ,  int n){
    int i , j , key;

    for( i = 1 ; i < n ; i++)
    {
        int key = arr[i];
        for(j = i ; j > 0 && arr[j - 1] > key ; j--){
            count1++;
            arr[j] = arr[j - 1];
        }
        arr[j] = key;
    }
}


int main()
{
    int* a ,arr[100000];
    fstream f2;
    f2.open("performance.csv",ios::out);
    f2 << "normal insertion sort" << "," << "binary insertion sort"  << "," << "nCompNormInsertion" << "," << "Binary" << endl;
    loadDataFromFile(arr , 100000);

    for(int i = 1 ; i < 101 ; i++){
        count1 = 0;
        count2 = 0;
        a = new int[i*100];

        for(int j = 0 ; j < i*100 ; j++)
            a[j] = arr[j];

        auto start = high_resolution_clock::now();
        insertionSort(a,i*100);
        auto stop = high_resolution_clock::now();
        auto time_taken_1 = duration_cast<nanoseconds>(stop - start);


        f2 << time_taken_1.count() << "," ;

        ///----------------------
        for(int j = 0 ; j < i*100 ; j++)
            a[j] = arr[j];

        start = high_resolution_clock::now();
        BinaryInsertionSort(a , i*100);
        stop = high_resolution_clock::now();
        auto time_taken = duration_cast<nanoseconds>(stop - start);

        f2 << time_taken.count() << "," ;
        f2 << count1 << "," << count2 << endl;
    }

    for(int i = 0 ; i < 10000 ; i++)
        cout << a[i] << endl;

    cout << "Performance file is ready" << endl;
    return 0;
}
