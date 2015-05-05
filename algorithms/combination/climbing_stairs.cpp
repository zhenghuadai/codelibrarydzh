class Solution {
public:
   int climbStairs(int n) {
        if(n == 1) return 1;
        if(n == 2) return 2;
        int NN = 0;
        int n1 = 1, n2 = 2;
        for(int i = 3; i<=n; i++){
            NN = n1 + n2;
            n1 = n2;
            n2 = NN;
        }
        return NN;
    }
};
static void test()
{
}
APPEND_TO_TEST(); 
