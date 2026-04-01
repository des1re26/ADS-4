// Copyright 2025 NNTU-CS
#include <cstdint>
#include "alg.h"

int countPairs1(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value) {
                count++;
            }
        }
    }
    return count;
}

int countPairs2(int *arr, int len, int value) {
    int count = 0;
    int left = 0;
    int right = len - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) {
            if (arr[left] == arr[right]) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                int leftCount = 1;
                int rightCount = 1;
                while (left + 1 < right && arr[left] == arr[left + 1]) {
                    leftCount++;
                    left++;
                }
                while (right - 1 > left && arr[right] == arr[right - 1]) {
                    rightCount++;
                    right--;
                }
                count += leftCount * rightCount;
                left++;
                right--;
            }
        } else if (sum < value) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}

int binarySearch(int *arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int countPairs3(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        if (target < arr[i]) {
            continue;
        }
        int firstPos = binarySearch(arr, i + 1, len - 1, target);
        if (firstPos != -1) {
            int lastPos = firstPos;
            while (lastPos + 1 < len && arr[lastPos + 1] == target) {
                lastPos++;
            }
            int firstPosLeft = firstPos;
            while (firstPosLeft - 1 > i && arr[firstPosLeft - 1] == target) {
                firstPosLeft--;
            }
            int countTarget = lastPos - firstPosLeft + 1;
            
            if (arr[i] == target) {
                int countCurrent = 1;
                while (i + 1 < len && arr[i + 1] == arr[i]) {
                    countCurrent++;
                    i++;
                }
                count += countCurrent * (countCurrent - 1) / 2;
            } else {
                int countCurrent = 1;
                while (i + 1 < len && arr[i + 1] == arr[i]) {
                    countCurrent++;
                    i++;
                }
                count += countCurrent * countTarget;
            }
        }
    }
    return count;
}
