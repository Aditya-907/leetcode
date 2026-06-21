import random

class Solution:

    def __init__(self, nums: List[int]):
        self.original = nums[:]
        self.nums = nums[:]

    def reset(self) -> List[int]:
        self.nums = self.original[:]
        return self.nums

    def shuffle(self) -> List[int]:
        arr = self.nums[:]

        for i in range(len(arr)):
            j = random.randint(i, len(arr) - 1)
            arr[i], arr[j] = arr[j], arr[i]

        return arr