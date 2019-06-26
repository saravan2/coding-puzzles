class Solution {
public:
    int numJewelsInStones(string J, string S) {
        int count = 0;
        unordered_set<char> jewels;
        for (unsigned int i=0; i < J.length(); i++)
            jewels.insert(J.at(i));
        
        for (unsigned int i= 0; i < S.length(); i++) {
            if (jewels.find(S.at(i)) != jewels.end())
                count++;
        }
        return count;
    }
};
