// Copyright 2026 <Student Name>

#include "alg.h"

// Функция 1: Полный перебор (цикл в цикле) - O(n^2)
int countPairs1(int *arr, int len, int value) {
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

// Функция 2: Движение с двух концов навстречу - O(n)
int countPairs2(int *arr, int len, int value) {
    int count = 0;
    int left = 0;
    int right = len - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) {
            if (arr[left] == arr[right]) {
                // Если элементы одинаковы, то все пары между left и right
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                // Подсчитываем количество одинаковых элементов слева
                int left_val = arr[left];
                int left_count = 0;
                while (left <= right && arr[left] == left_val) {
                    ++left_count;
                    ++left;
                }
                
                // Подсчитываем количество одинаковых элементов справа
                int right_val = arr[right];
                int right_count = 0;
                while (left <= right && arr[right] == right_val) {
                    ++right_count;
                    --right;
                }
                
                count += left_count * right_count;
            }
        } else if (sum < value) {
            ++left;
        } else {
            --right;
        }
    }
    return count;
}

// Вспомогательная функция для бинарного поиска
int binarySearch(int *arr, int start, int end, int target) {
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == target) {
            // Находим первое вхождение
            while (mid > start && arr[mid - 1] == target) {
                --mid;
            }
            return mid;
        } else if (arr[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return -1;
}

// Функция 3: Бинарный поиск - O(n log n)
int countPairs3(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len - 1; ++i) {
        int target = value - arr[i];
        int first_pos = binarySearch(arr, i + 1, len - 1, target);
        if (first_pos != -1) {
            // Подсчитываем все вхождения target
            int j = first_pos;
            while (j < len && arr[j] == target) {
                ++count;
                ++j;
            }
        }
    }
    return count;
}
