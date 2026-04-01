// Copyright 2025 NNTU-CS
#include <cstdint>
#include "alg.h"

int countPairs1(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
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
                int leftVal = arr[left];
                int rightVal = arr[right];
                int leftCount = 0;
                int rightCount = 0;
                while (left < len && arr[left] == leftVal) {
                    leftCount++;
                    left++;
                }
                while (right >= 0 && arr[right] == rightVal) {
                    rightCount++;
                    right--;
                }
                count += leftCount * rightCount;
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
    int i = 0;
    while (i < len) {
        int target = value - arr[i];
        if (target < arr[i]) {
            i++;
            continue;
        }
        int pos = binarySearch(arr, i + 1, len - 1, target);
        if (pos != -1) {
            int leftCount = 1;
            while (i + leftCount < len && arr[i + leftCount] == arr[i]) {
                leftCount++;
            }
            int rightCount = 1;
            while (pos + rightCount < len && arr[pos + rightCount] == target) {
                rightCount++;
            }
            if (arr[i] == target) {
                count += leftCount * (leftCount - 1) / 2;
            } else {
                count += leftCount * rightCount;
            }
            i += leftCount;
        } else {
            i++;
        }
    }
    return count;
}
