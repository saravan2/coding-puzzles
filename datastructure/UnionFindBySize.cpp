#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class UnionFindBySize {
private:
    std::vector<int> parent;
    std::vector<int> size;
public:
    UnionFindBySize(int n) : size(n, 1) {
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
        }
    }

    int largestbysize() {
        std::vector<int>:: iterator it = std::max_element(size.begin(), size.end());
        if (it == size.end()) {
            return 0;
        } else {
            return *it;
        }
    }

    int find(int node) {
        if (node != parent[node]) {
            parent[node] = find(parent[node]);
        }
        return parent[node];
    }

    void connect(int source, int destination) {
        int source_parent = find(source);
        int dest_parent = find(destination);

        if (source_parent != dest_parent) {
            if (size[source_parent] < size[dest_parent]) {
                parent[source_parent] = dest_parent;
                size[dest_parent] += size[source_parent];
            } else {
                parent[dest_parent] = source_parent;
                size[source_parent] += size[dest_parent];
            }
        } 
    }

    void printParent() {
        for (int i = 0; i < parent.size(); i++) {
            std::cout << "Parent of " << i << ": " << parent[i] << std::endl;
        }
    }

    void printSize() {
        for (int i = 0; i < size.size(); i++) {
            std::cout << "Size of " << i << ": " << size[i] << std::endl;
        }
    }
};

int longestConsecutive(std::vector<int> &nums)
{
    int n = nums.size();
    if (n <= 1)
    {
        return n;
    }
    std::unordered_map<int, int> elemToIndex;
    UnionFindBySize ufs(n);
    ufs.printParent();
    ufs.printSize();
    std::cout << "-----------------" << std::endl;
    for (int i = 0; i < n; i++)
    {
        elemToIndex[nums[i]] = i;
        std::cout << "Element: " << nums[i] << " Index: " << i << std::endl;
    }
    std::cout << "-----------------" << std::endl;
    for (int i = 0; i < n; i++)
    {
        if (elemToIndex.count(nums[i] + 1))
        {
            ufs.connect(elemToIndex[nums[i]], elemToIndex[(nums[i] + 1)]);
        }
        if (elemToIndex.count(nums[i] - 1))
        {
            ufs.connect(elemToIndex[nums[i]], elemToIndex[(nums[i] - 1)]);
        }
    }
    ufs.printParent();
    ufs.printSize();
    std::cout << "-----------------" << std::endl;
    return ufs.largestbysize();
}

int main(int argc, char const *argv[]) {
    std::vector<int> nums = {0,3,7,2,5,8,4,6,0,1};
    std::cout << longestConsecutive(nums) << std::endl;
    return 0;
}
