//get the K-th largest element in an array using max heap
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

template<class T>
int getKthLargest(vector<T> &vec, int K)
{
    priority_queue <int> pq;            //initialize max heap

    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){    //push value into p_queue
        pq.push(*it);
    }
    for(int i=0; i<K-1; ++i){       //pop out (K-1)th element
        pq.pop();
    }

    return pq.top();               //return the Kth element
}


int main()
{
    vector<int> vec{10, 5, 31, 50, 7, 1};
    
    int K = 4, ans;

    ans = getKthLargest(vec, K);

    cout << ans;    //the 4th largest element is 7
    
    system("pause");
    return 0;
}