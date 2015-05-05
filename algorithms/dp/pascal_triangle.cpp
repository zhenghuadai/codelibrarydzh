/*
 * =====================================================================================
 *
 *       Filename:  pascal_triangle.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2015 03:08:38 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "common.h"
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if(numRows == 0) return vector<vector<int>>();
        vector<vector<int>> R;
        R.push_back(vector<int>(1, 1));
        if(numRows == 1) return R;
        R.push_back(vector<int>(2, 1));
        if(numRows == 2) return R;
        for(int i = 3; i<= numRows; i++){
            R.push_back(vector<int>(i, 1));
            vector<int>& lastv = R[i-2];
            vector<int>& curv = R[i-1];
            for(int j = 1; j < i - 1; j++){
                curv[j] = lastv[j] + lastv[j-1];
            }
        }
        
        return R;
    }
};
