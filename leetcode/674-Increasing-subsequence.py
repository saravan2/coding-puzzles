class Solution:
    def findLengthOfLCIS(self, nums: List[int]) -> int:
        max_len = 0
        curr_count = 0
        for i in range(len(nums)):
            if i == 0 or nums[i] > nums[i-1]:
                curr_count += 1
                max_len = max(max_len, curr_count)
            else:
                curr_count = 1
        return max_len
