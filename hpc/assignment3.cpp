#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;

void minimum(vector<int> array){
    
    int min_ele = INT_MAX;
    #pragma omp parallel for reduction(min: min_ele)
        for(auto i = array.begin(); i != array.end();i++){
            if(*i < min_ele){
                min_ele = *i;
            } 
        }
    cout << "Minimum Element(Parallel Reduction): " << min_ele << endl;
}

void maximum(vector<int> array){
   
    int max_ele = INT_MIN;
    #pragma omp parallel for reduction(max: max_ele)
        for(auto i = array.begin(); i != array.end();i++){
            if(*i > max_ele){
                max_ele = *i;
            } 
        }
    cout << "Maximum Element(Parallel Reduction): " << max_ele << endl;
    
}

void sum(vector<int> array){
   
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
        for(auto i = array.begin(); i != array.end();i++){
            sum += *i; 
        }
    cout << "Summation(Parallel Reduction): " << sum << endl;
    
}
void average(vector<int> array){
    int avg = 0;
    #pragma omp parallel for reduction(+: avg)
        for(auto i = array.begin(); i != array.end();i++){
            avg += *i; 
        }
    cout << "Average(Parallel Reduction): " << avg / array.size() << endl;
    
}

int main(){
    cout << "Enter number of elements in array: ";
    int N;
    int MAX = 1000;
    cin >> N;
    vector<int> array;
    for(int i = 0; i < N; i++){
        array.push_back(rand() % MAX);
    }
    minimum(array);
    maximum(array);
    sum(array);
    average(array);
    return 0;
}