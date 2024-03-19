class Solution {
public:
    vector<int> findArray(vector<int>& pref) {
        //if (pref.empty()) {
        //    return vector<int>();
        //}

        //vector<int> original(pref.size());
        //original[0] = pref[0];
        //for (int i = 1; i < pref.size(); i++) {
        //    original[i] = pref[i] ^ pref[i-1];
        //}
        //return original;

        for (int i = pref.size() - 1; i > 0; i--) {
            pref[i] ^= pref[i-1];
        }

        return pref;
    }
};