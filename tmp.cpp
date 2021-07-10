class Solution {
public:
    string removeOccurrences(string s, string part) {
        string ans;
        for (auto c : s) {
            ans += c;
            if (ans.size() > part.size()) {
                int sz = ans.size() - part.size();
                string t = ans.substr(sz);
                if (t == part) {
                    ans.resize(sz);
                }
            }
        }      
        return ans;
    }
};