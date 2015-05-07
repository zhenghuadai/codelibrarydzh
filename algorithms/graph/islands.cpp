/*
 * =====================================================================================
 *
 *       Filename:  islands.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2015 09:17:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DAI ZHENGHUA (), djx.zhenghua@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "common.h"
class Solution {
public:
void DFS(vector<vector<char>>& grid, int row, int col)
{
    grid[row][col] = 'V';
    if(row -1 >=0 && grid[row-1][col] == 1) DFS(grid, row-1, col);
    if(col -1 >=0 && grid[row][col-1] == 1) DFS(grid, row, col-1);

    if(row +1 < grid.size() && grid[row+1][col] == 1) DFS(grid, row+1, col);
    if(col +1 < grid[row].size() && grid[row][col+1] == 1) DFS(grid, row, col+1);
}
struct Pos{ int row, col; Pos(int r, int c):row(r),col(c){}};
struct Int2{int v0,v1; Int2(int v0, int v1):v0(v0),v1(v1){}};
void BFS_Q(vector<vector<char>>& grid, int row, int col)
{
    queue<Pos> Q;
    Q.push(Pos(row, col));
    grid[row][col] = 'V';
    while(!Q.empty()){
        auto p = Q.front();
        Q.pop();
        int r = p.row, c = p.col;
        if(r -1 >=0 && grid[r-1][c] == 1) { grid[r-1][c] = 'V'; Q.push(Pos(r-1, c));}
        if(c -1 >=0 && grid[r][c-1] == 1) { grid[r][c-1] = 'V';Q.push(Pos(r, c-1));}

        if(r +1 < grid.size() && grid[r+1][c] == 1){ grid[r+1][c] = 'V'; Q.push(Pos(r+1, c));}
        if(c +1 < grid[r].size() && grid[r][c+1] == 1){ grid[r][c+1] = 'V'; Q.push(Pos(r, c+1));}
    }
}

int numIslands_travel(vector<vector<char>>& grid) {
    int islands = 0;
    for(int row = 0; row <grid.size(); row ++){
        vector<char>& r = grid[row];
        for(int col = 0; col <r.size(); col ++){
            if(grid[row][col] == 1){
                islands ++;
                BFS_Q(grid, row, col);
            }
        }
    }
    return islands;
}

int numIslands(vector<vector<char>>& grid) {
    int islands = 0;
    int L = 0;
    if(grid.size() == 0 ) return 0;
    vector<Int2> Union;
    vector<int> C(grid[0].size(), INT_MAX);

    for(int row = 0; row <grid.size(); row ++){
        vector<char>& r = grid[row];
        for(int col = 0; col <r.size(); col ++){
            int color0 = INT_MAX, color1 = INT_MAX;
            if(grid[row][col] == 0)continue;
            if(col -1 >=0 && grid[row][col-1] == 1) color1 = C[col-1];
            if(row -1 >=0 && grid[row-1][col] == 1) color0 = C[col];
            if(color0 == INT_MAX && color1 == INT_MAX) {
                C[col] = L++;
            }else if( color0 == color1){
                C[col] = color0;
            }else if(color0 != INT_MAX && color1 != INT_MAX){
                if(color0 > color1){std::swap(color0, color1); }
                Union.push_back(Int2(color0, color1));
                C[col] = color0;
            }else{
                C[col] = (color0 < color1)?color0:color1;
            }
        }
    }
    vector<int> V(L, 0);
    for(int i = 0; i<L; i++){
        V[i] = i;
    }
    for(auto it = Union.begin(); it != Union.end(); it++){
        int v0 = it->v0;
        int v1 = it->v1;
        while(V[v0] != v0){v0 = V[v0];}
        while(V[v1] != v1){v1 = V[v1];}
        if(v0 > v1) std:swap(v0, v1);
        V[v1] = v0;
    }
    for(int i = 0; i<L; i++){
        if(V[i] == i){
            islands ++;
        }
    }

    return islands;
}

};

int test_numIslands(vector<vector<char>>& grid) {
    Solution s;
    return s.numIslands(grid);
}
