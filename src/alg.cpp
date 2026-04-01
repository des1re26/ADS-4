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
            // Нашли пару
            if (arr[left] == arr[right]) {
                // Все элементы от left до right одинаковы
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                // Считаем количество одинаковых элементов слева
                int left_val = arr[left];
                int left_count = 0;
                while (left <= right && arr[left] == left_val) {
                    left_count++;
                    left++;
                }
                // Считаем количество одинаковых элементов справа
                int right_val = arr[right];
                int right_count = 0;
                while (right >= left && arr[right] == right_val) {
                    right_count++;
                    right--;
                }
                count += left_count * right_count;
            }
        } else if (sum < value) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}

// Вспомогательная функция для подсчета вхождений с помощью бинарного поиска
int countOccurrences(int *arr, int start, int end, int target) {
    // Находим первое вхождение
    int first = -1;
    int left = start;
    int right = end;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            first = mid;
            right = mid - 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (first == -1) return 0;

    // Находим последнее вхождение
    int last = first;
    left = first;
    right = end;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            last = mid;
            left = mid + 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return last - first + 1;
}

// Функция 3: Бинарный поиск - O(n log n)
int countPairs3(int *arr, int len, int value) {
    int count = 0;

    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        // Ищем target в оставшейся части массива
        int occurrences = countOccurrences(arr, i + 1, len - 1, target);
        count += occurrences;

        // Пропускаем дубликаты текущего элемента
        while (i + 1 < len && arr[i] == arr[i + 1]) {
            ++i;
        }
    }

    return count;
}
