
class Solution:
    def maxLength(self, nums):

        def gcd(a, b):
            while b:
                a, b = b, a % b
            return a

        def lcm(a, b):
            return (a // gcd(a, b)) * b

        n = len(nums)
        ans = 1

        for i in range(n):
            prod = 1
            g = 0
            L = 1

            for j in range(i, n):
                x = nums[j]

                prod *= x
                g = gcd(g, x)
                L = lcm(L, x)

                if prod == g * L:
                    ans = max(ans, j - i + 1)

        return ans