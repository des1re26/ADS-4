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
                int leftVal = arr[left];
                int rightVal = arr[right];
                int leftCount = 0;
                int rightCount = 0;
                while (left <= right && arr[left] == leftVal) {
                    leftCount++;
                    left++;
                }
                while (left <= right && arr[right] == rightVal) {
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
    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        if (target < arr[i]) {
            continue;
        }
        int pos = binarySearch(arr, i + 1, len - 1, target);
        if (pos != -1) {
            if (arr[i] == target) {
                int cnt = 1;
                while (i + cnt < len && arr[i + cnt] == target) {
                    cnt++;
                }
                count += cnt * (cnt - 1) / 2;
                i += cnt - 1;
            } else {
                int cntLeft = 1;
                while (i + cntLeft < len && arr[i + cntLeft] == arr[i]) {
                    cntLeft++;
                }
                int cntRight = 1;
                while (pos + cntRight < len && arr[pos + cntRight] == target) {
                    cntRight++;
                }
                count += cntLeft * cntRight;
                i += cntLeft - 1;
            }
        }
    }
    return count;
}
