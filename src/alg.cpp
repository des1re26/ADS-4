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
int binarySearchFirst(int *arr, int start, int end, int target) {
    int result = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == target) {
            result = mid;
            end = mid - 1;  // Ищем первое вхождение
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
        // Ищем первое вхождение target в подмассиве после i
        int first_pos = binarySearchFirst(arr, i + 1, len - 1, target);

        if (first_pos != -1) {
            // Нашли первое вхождение, считаем все вхождения target
            int j = first_pos;
            while (j < len && arr[j] == target) {
                ++count;
                ++j;
            }
        }

        // Пропускаем дубликаты текущего элемента
        while (i + 1 < len && arr[i] == arr[i + 1]) {
            ++i;
        }
    }
    return count;
}
