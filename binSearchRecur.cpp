//binary search recursive implementation with template
#include <iostream>
#include <vector>

using namespace std;

template <class T>
int binarySearch(vector<T> vec, int high, int low, const T &key)    //key's index to be searched
{
    int mid, loc;

    if(low<=high){    
        mid = ((high-low)/2)+low;

        if(vec[mid] == key){
            return mid;
        }
        else if(vec[mid]>key){
            return binarySearch(vec, mid-1,low,key);
        }
        else if(vec[mid]<key){
            return binarySearch(vec, high,mid+1,key);
        }
    }
    return -1;  //return -1 if key not found
}

int main()
{
    vector<char> vc {'a','b','c','d'};
    vector<int> vi {1,2,3,4,5};
    

    int char_Index = binarySearch(vc,(vc.size())-1,0,'c');      //search for location of 'c'
    cout << char_Index << endl;                                 //output:2

    int int_Index = binarySearch(vi,(vi.size())-1,0,4);         //search for location of 4
    cout << int_Index << endl;                                  //output:3

    system("pause");
    return 0;
}
