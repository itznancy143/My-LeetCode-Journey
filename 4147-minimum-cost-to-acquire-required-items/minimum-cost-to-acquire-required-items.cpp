class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long ans = 0;

        // Option 1: Buy only individual items
        long long option1 = 1LL * need1 * cost1 + 1LL * need2 * cost2;

        // Option 2: Buy common items for the minimum requirement
        long long common = min(need1, need2);

        long long option2 = common * costBoth
                          + 1LL * (need1 - common) * cost1
                          + 1LL * (need2 - common) * cost2;

        // Option 3: Buy only type 3 items
        long long option3 = 1LL * max(need1, need2) * costBoth;

        ans = min({option1, option2, option3});

        return ans;
    }
};