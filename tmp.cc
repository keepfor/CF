class Solution {
public:
    string makeFancyString(string s) {
        string ans;
        for (int i = 0; i < s.size(); ++i) {
            int j = i;
            while (j < s.size() && s[j] == s[i]) {
                ++j;
            }
            int c = j - i;
            c = min(2, c);
            ans += string(s[i], c);
        }
        return ans;   
    }
};