#include "common.h"
namespace {

class Solution {
    void getMedian(int& a0, int& a1, int& a2){
        if(a0 > a1) {
           if(a2 > a0){
           } else if(a2 < a1){
               std::swap(a0, a1);
           }else{
               std::swap(a0, a2);
           }
        }else{ // a0 <= a1
            if( a2 <= a0){
                
            }else if( a1 < a2){
                std::swap(a0, a1);
            }else{
                std::swap(a0, a2);
            }
        }
    }
    
    int divide(vector<int>& nums, int L, int R){
        getMedian(nums[L], nums[(L+R)/2], nums[R]);
        int pivot = nums[L];
        while(L < R){
            while(L<R && nums[R] <= pivot) R--;
            nums[L] = nums[R];
            while(L<R && nums[L] > pivot) L++;
            nums[R] = nums[L];
        }
        nums[L] = pivot;
        return L;
    }
    
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 0) return 0;
        int L = 0;
        int R = n-1;
        
        while(L < R){
            int s = divide(nums, L, R);
            if( s == k -1){
                return nums[s];
            }else if( s < k - 1){
                L = s + 1;
            }else{
                R = s - 1;
            }
            
        }
        return nums[L];
    }

};

} /// end namespace

int test_findKthLargest(vector<int>& nums, int k) {
    Solution s;
    return s.findKthLargest(nums, k);
}
