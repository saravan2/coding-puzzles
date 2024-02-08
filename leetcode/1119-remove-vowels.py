class Solution:
    def removeVowels(self, s: str) -> str:
        ret: str = ''
        removeSet: set = set('aeiou')
        for ch in s:
            if ch not in removeSet:
                ret += ch
        return ret
        