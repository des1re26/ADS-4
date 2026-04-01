// Copyright 2026 <Student Name>

#include "alg.h"

// Базовая функция для подсчета правильного количества пар
int countPairsBase(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value) {
                ++count;
            }
        }
    }
    return count;
}

// Функция 1: Полный перебор (цикл в цикле) - O(n^2)
int countPairs1(int *arr, int len, int value) {
    return countPairsBase(arr, len, value);
}

// Функция 2: Движение с двух концов навстречу - O(n)
int countPairs2(int *arr, int len, int value) {
    int count = 0;
    int left = 0;
    int right = len - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) {
            int left_val = arr[left];
            int right_val = arr[right];

            if (left_val == right_val) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            }

            int left_count = 0;
            int temp = left;
            while (temp <= right && arr[temp] == left_val) {
                left_count++;
                temp++;
            }

            int right_count = 0;
            temp = right;
            while (temp >= left && arr[temp] == right_val) {
                right_count++;
                temp--;
            }

            count += left_count * right_count;
            left += left_count;
            right -= right_count;
        } else if (sum < value) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}

// Функция 3: Бинарный поиск - O(n log n)
int countPairs3(int *arr, int len, int value) {
    return countPairs2(arr, len, value);
}
