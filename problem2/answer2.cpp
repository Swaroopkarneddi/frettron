#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool canPartition(vector<int> &nums, int index, int sum1, int sum2, int sum3, int target1, int target2, int target3,
                  vector<int> &group1, vector<int> &group2, vector<int> &group3)
{
    if (index == nums.size())
    {
        // Check if we have reached the required ratios
        return (sum1 == target1 && sum2 == target2 && sum3 == target3);
    }

    // Try to add the current number to any of the three groups
    if (sum1 + nums[index] <= target1)
    {
        group1.push_back(nums[index]);
        if (canPartition(nums, index + 1, sum1 + nums[index], sum2, sum3, target1, target2, target3, group1, group2, group3))
        {
            return true;
        }
        group1.pop_back();
    }

    if (sum2 + nums[index] <= target2)
    {
        group2.push_back(nums[index]);
        if (canPartition(nums, index + 1, sum1, sum2 + nums[index], sum3, target1, target2, target3, group1, group2, group3))
        {
            return true;
        }
        group2.pop_back();
    }

    if (sum3 + nums[index] <= target3)
    {
        group3.push_back(nums[index]);
        if (canPartition(nums, index + 1, sum1, sum2, sum3 + nums[index], target1, target2, target3, group1, group2, group3))
        {
            return true;
        }
        group3.pop_back();
    }

    return false;
}

bool divideIntoGroups(vector<int> &nums, vector<int> &group1, vector<int> &group2, vector<int> &group3)
{
    int totalSum = accumulate(nums.begin(), nums.end(), 0);

    // Total ratio parts
    int ratioSum = 5 + 3 + 2;

    if (totalSum % ratioSum != 0)
    {
        return false; // Total sum must be divisible by 10
    }

    int target1 = totalSum * 5 / ratioSum;
    int target2 = totalSum * 3 / ratioSum;
    int target3 = totalSum * 2 / ratioSum;

    sort(nums.begin(), nums.end(), greater<int>()); // Sort in descending order for optimization

    return canPartition(nums, 0, 0, 0, 0, target1, target2, target3, group1, group2, group3);
}

void printGroups(const vector<int> &group1, const vector<int> &group2, const vector<int> &group3)
{
    cout << "Ram :";
    for (int num : group1)
        cout << num << " ";
    cout << endl;

    cout << "Sham :";
    for (int num : group2)
        cout << num << " ";
    cout << endl;

    cout << "Rahim :";
    for (int num : group3)
        cout << num << " ";
    cout << endl;
}

int main()
{
    bool a = true;
    vector<int> nums;
    while (a)
    {
        int temp;
        cin >> temp;
        if (temp == -1)
        {
            a = false;
        }
        else
        {
            nums.push_back(temp);
        }
    }
    vector<int> group1, group2, group3;

    if (divideIntoGroups(nums, group1, group2, group3))
    {
        cout << "Possible to divide into groups with ratio 5:3:2" << endl;
        printGroups(group1, group2, group3);
    }
    else
    {
        cout << "Not possible to divide into groups with ratio 5:3:2" << endl;
    }

    return 0;
}
