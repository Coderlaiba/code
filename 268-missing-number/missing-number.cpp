class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int xorALL=0;
        int n=nums.size();
        for(int i=0;i<=n;i++)
        xorALL^=i;
        for(int num:nums)
        xorALL^=num;
        return xorALL;
    }
};