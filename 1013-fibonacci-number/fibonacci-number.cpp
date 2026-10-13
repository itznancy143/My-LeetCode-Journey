class Solution {
public:
    int fib(int n) { // bottom-up with DP
        int f[n+1];
        if (n == 1){
            return 1;
        }
        if (n == 0){
            return 0;
        }
        f[0] = 0;
        f[1] = 1;
        for(int i = 2; i <= n; i++){
            f[i] = f[i-1]+f[i-2];
        }
        return f[n];
    }
};