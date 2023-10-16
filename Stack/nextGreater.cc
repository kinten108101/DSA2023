#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> nextGreater(const vector<int>& arr){
	size_t size = arr.size();
	vector<int> ret;
    for (int i = 0; i < size; i++) {
    	int next_greater_val = -1;
    	for (int j = i + 1; j < size && next_greater_val == -1; j++) {
    		if (arr[j] > arr[i])
    			next_greater_val = arr[j];
    	}
    	ret.push_back(next_greater_val);
    }
    return ret;
}