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
            // Нашли пару, теперь считаем все комбинации
            int left_val = arr[left];
            int right_val = arr[right];

            if (left_val == right_val) {
                // Если значения равны, то все элементы между left и right дают пары
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                // Считаем количество одинаковых элементов слева
                int left_count = 0;
                int temp_left = left;
                while (temp_left <= right && arr[temp_left] == left_val) {
                    left_count++;
                    temp_left++;
                }

                // Считаем количество одинаковых элементов справа
                int right_count = 0;
                int temp_right = right;
                while (temp_right >= left && arr[temp_right] == right_val) {
                    right_count++;
                    temp_right--;
                }

                count += left_count * right_count;
                left += left_count;
                right -= right_count;
            }
        } else if (sum < value) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}

// Вспомогательная функция бинарного поиска
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

// Функция 3: Бинарный поиск - O(n log n)
int countPairs3(int *arr, int len, int value) {
    int count = 0;

    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        // Ищем target в оставшейся части массива
        int pos = binarySearch(arr, i + 1, len - 1, target);

        if (pos != -1) {
            // Нашли target, считаем все его вхождения
            int first = pos;
            int last = pos;

            // Ищем первое вхождение
            while (first > i + 1 && arr[first - 1] == target) {
                first--;
            }

            // Ищем последнее вхождение
            while (last < len - 1 && arr[last + 1] == target) {
                last++;
            }

            // Добавляем количество вхождений
            count += (last - first + 1);
        }

        // Пропускаем дубликаты arr[i]
        while (i + 1 < len && arr[i] == arr[i + 1]) {
            i++;
        }
    }

    return count;
}
