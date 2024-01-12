class Solution:
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        if int(max(s)) > limit: return 0
        val = int(s)
        x = 10 ** len(s)
        l, v = divmod(start, x)
        if v > val: l += 1
        r, v = divmod(finish, x)
        if v < val: r -= 1
        
        if l > r: return 0
        
        def f(x):
            if x < 0: return 0
            elif x == 0: return 1
            vals = [int(c) for c in str(x)]
            
            cur = 1
            ans = 0
            for x in vals:
                ans *= (limit + 1)
                if cur:
                    cur = 0
                    for i in range(limit + 1):
                        if i < x: ans += 1
                        elif i == x: cur = 1
                        else: break
            return ans + cur
        return f(r + 1) - f(l)
        # return f(r) - f(l - 1)



s = Solution()
res = s.numberOfPowerfulInt(15, 215, 6, "10")
# start = 15, finish = 215, limit = 6, s = "10"
print(res)
