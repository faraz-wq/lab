#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;


class Graph{
    public:
    int vertices = 6;
        int edges = 5;
        vector<vector<int>> graph = {{1},{0,2,3},{1,4,5},{1,4},{2,3},{2}};
        vector<bool> visited;
    void addEdge(int a, int b){
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
    void initialize_visited(){
            visited.assign(vertices,false);
        }
        void parallel_dfs(int i){
            stack<int> s;
            s.push(i);
            visited[i] = true;

            while(s.empty() != true){
                int current = s.top();
                cout << current << " ";
                #pragma omp critical
                    s.pop();
                #pragma omp parallel for
                    for(auto j = graph[current].begin(); j != graph[current].end();j++){
                        if(visited[*j] == false){
                            #pragma omp critical
                            {
                                s.push(*j);
                                visited[*j] = true;
                            }
                        }
                    }
                
            }
        }
        void parallel_bfs(int i){
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while(q.empty() != true){
                
                    int current = q.front();
                    cout << current << " ";
                    #pragma omp critical
                        q.pop();
                    
                #pragma omp parallel for
                    for(auto j = graph[current].begin(); j != graph[current].end();j++){
                        if(visited[*j] == false){
                            #pragma omp critical
                                q.push(*j);
                                visited[*j] = true;
                        }
                    }
                
            }
        }
};
int main(int argc, char const *argv[])
{
   Graph g;
    cout << "Parallel Depth First Search: \n";
    g.initialize_visited();
   g.parallel_dfs(0);
   cout << endl;
   cout << "Parallel Breadth First Search: \n";
    g.initialize_visited();
    g.parallel_bfs(0);
    return 0;
}
    