#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        if (nums1.empty() && nums2.empty()){
            return NULL;
        }
        if(nums1.empty()){
            if(nums2.size() % 2 == 0){
                return (nums2[nums2.size()/2] + nums2[nums2.size()/2 - 1]) / 2;
            } else{
                return (nums2[nums2.size()/2]) / 2;
            }
        }
        if(nums2.empty()){
            if(nums1.size() % 2 == 0){
                return (nums1[nums1.size()/2] + nums1[nums1.size()/2 - 1]) / 2;
            } else{
                return (nums1[nums1.size()/2]) / 2;
            }
        }
        return findLocAt(nums1, nums2, 0, nums1.size(), 0, nums2.size(), (nums1.size() + nums2.size()) / 2);
    }

    double findLocAt(std::vector<int>& nums1, std::vector<int>& nums2, int v1_start, int v1_end, int v2_start, int v2_end, int order){
        bool evenFlag= true;
        if ((v1_end - v1_start + v2_end - v2_start) % 2 == 1){
            evenFlag = false;
        }
        int n1_mid_value = nums1[(v1_start + v1_end)/2];
        int n2_loc = numLoc(nums2, n1_mid_value);
        if ((v1_start + v1_end)/2 + n2_loc + 1 < order){
            return findLocAt(nums1, nums2, (v1_start + v1_end)/2 + 1, v1_end, n2_loc+1, v2_end, order-(v1_start + v1_end)/2 + n2_loc + 1);
        } else if(evenFlag && (v1_start + v1_end)/2 + n2_loc + 1 == order){
            int locv1 = n1_mid_value;
            int locv2 = std::min(nums2[n2_loc+1], nums1[(v1_start + v1_end)/2]);
            return (locv1 + locv2) / 2;
        } else if(!evenFlag && (v1_start + v1_end)/2 + n2_loc + 1 == order){
            return n1_mid_value;
        } else{
            return findLocAt(nums1,nums2,v1_start,(v1_start + v1_end)/2-1,v2_start,n2_loc-1,(v1_start + v1_end)/2 + n2_loc + 1 - order);
        }
    }

    int numLoc(std::vector<int>& nums, int value){
        int low=0, high=nums.size();
        while(low < high){
            if(nums[(low + high) / 2] < value){
                low = (low + high) / 2 + 1;
            } else if(nums[(low + high) / 2] == value){
                return (low + high) / 2;
            } else{
                high = (low + high) / 2 - 1;
            }
        }
        return low;
    }

};

int main(){
    Solution s;
    int arr1[5] = {1,3};
    int arr2[4] = {2};
    std::vector<int> v1(&arr1[0],&arr1[2]);
    std::vector<int> v2(&arr2[0],&arr2[1]);
//    s.numLoc(v2, 1);
    std::cout << s.findMedianSortedArrays(v1,v2);
}