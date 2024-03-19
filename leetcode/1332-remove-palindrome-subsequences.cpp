class Solution {
private:
    bool isPalindrome(const string& s) {
        return std::equal(s.cbegin(), (s.cbegin() + (s.size()/2)), s.crbegin());
    }
public:
    int removePalindromeSub(string s) {
        if (s.empty()) {
            return 0;
        }
        if (isPalindrome(s)) {
            return 1;
        }
        return 2;
    }
};