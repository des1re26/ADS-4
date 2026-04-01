// Copyright 2026
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
            int left_val = arr[left];
            int right_val = arr[right];

            if (left_val == right_val) {
                // Все элементы одинаковы
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            }

            // Считаем количество одинаковых элементов слева
            int left_count = 1;
            while (left + left_count <= right &&
                   arr[left + left_count] == left_val) {
                ++left_count;
            }

            // Считаем количество одинаковых элементов справа
            int right_count = 1;
            while (right - right_count >= left &&
                   arr[right - right_count] == right_val) {
                ++right_count;
            }

            count += left_count * right_count;
            left += left_count;
            right -= right_count;
        } else if (sum < value) {
            ++left;
        } else {
            --right;
        }
    }
    return count;
}

// Вспомогательная функция для бинарного поиска
int binarySearchFirst(int *arr, int start, int end, int target) {
    int result = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == target) {
            result = mid;
            end = mid - 1;
        } else if (arr[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return result;
}

int binarySearchLast(int *arr, int start, int end, int target) {
    int result = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == target) {
            result = mid;
            start = mid + 1;
        } else if (arr[mid] < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return result;
}

// Функция 3: Бинарный поиск - O(n log n)
int countPairs3(int *arr, int len, int value) {
    int count = 0;

    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        int first = binarySearchFirst(arr, i + 1, len - 1, target);

        if (first != -1) {
            int last = binarySearchLast(arr, first, len - 1, target);
            count += (last - first + 1);
        }

        // Пропускаем дубликаты
        while (i + 1 < len && arr[i] == arr[i + 1]) {
            ++i;
        }
    }

    return count;
}
