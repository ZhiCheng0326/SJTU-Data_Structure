//get the K-th largest element in an array using min heap
#include<iostream>
#include<queue>

using namespace std;

int getKthLargest(int K, int arr[], int arrSize)
{
    if(K > arrSize) return -1;                  //-1 means getFailed

    priority_queue<int, vector<int>, greater<int>> pq;  

    for(int i=0; i<K; ++i){
        pq.push(arr[i]);                        //build min heap with first-K element in arr
    }

    for(int i=K; i<arrSize; ++i){               //compare (K+1)th element with top of the p_queue
        if(arr[i] > pq.top()){
            pq.pop();                           //remove top if it is smaller than element in arr
            pq.push(arr[i]);
        }
    }

    return pq.top();

}

int main()
{
    int arr[] = {10, 5, 31, 50, 7, 1};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    int K = 4;

    int ans = getKthLargest(K, arr, arrSize);

    cout << ans;    //output: 7

    system("pause");
    return 0;

}