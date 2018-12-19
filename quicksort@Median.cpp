/*
Implementation of quicksort with pivot chosen from mid value of arr[low], arr[mid],arr[high]
*/
#include <iostream>
#include <array>

using namespace std;

template<class T, size_t N>
T findMedian(array<T, N> &arr, int low, int high)
{
    T m;
    int mid =(low+high)/2;
    T a = arr[low], b = arr[mid], c = arr[high];        //get the value between arr[low], arr[mid],arr[high] 
    
    if(a<=b && a<=c){
        m = (b <=c) ? b : c ;
    }

    else if(b<=a && b<= c){
        m = (a <=c) ? a : c;
    }

    else if(c<=a && c<=b){
        m = (a<=b) ? a : b;
    }

    return m;
}

template<class T, size_t N>
int divide(array<T, N> &arr, int low, int high)
{
    T k = findMedian(arr, low, high);               //choose median 
    
    do{
        while(low < high && arr[high] >= k) --high;
        if(low<high){
            arr[low] = arr[high];
            ++low;
        }
        while(low < high && arr[low] <=k) ++low;
        if(low<high){
            arr[high] = arr[low];
            --high;
        }
    }while(low!=high);
    arr[low] = k;

    return low;
}

template<class T, size_t N>
void quicksort(array<T, N> &arr, int low, int high)
{
    if(low>=high){
        return;
    }
    int mid = divide(arr, low, high);
    quicksort(arr, low, mid-1);
    quicksort(arr, mid+1, high);
}


int main()
{
    array<int, 9> arr = {7,8,2,2,10,10,19,36,4};

    quicksort(arr,0,arr.size()-1);

    for(int i=0; i<arr.size(); ++i){
        cout << arr[i] << ' ';      //output: 2 2 2 7 8 10 10 19 36
    }

    cout << endl;

    system("pause");
    return 0;

}