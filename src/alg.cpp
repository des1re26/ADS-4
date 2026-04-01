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
            // Подсчитываем все пары с текущими значениями
            int left_val = arr[left];
            int right_val = arr[right];
            
            // Считаем количество одинаковых элементов слева
            int left_count = 0;
            int i = left;
            while (i <= right && arr[i] == left_val) {
                left_count++;
                i++;
            }
            
            // Считаем количество одинаковых элементов справа
            int right_count = 0;
            int j = right;
            while (j >= left && arr[j] == right_val) {
                right_count++;
                j--;
            }
            
            if (left_val == right_val) {
                // Если значения одинаковы, используем формулу сочетаний
                count += (left_count * (left_count - 1)) / 2;
            } else {
                count += left_count * right_count;
            }
            
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
    int count = 0;
    
    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        
        // Бинарный поиск первого вхождения target
        int left = i + 1;
        int right = len - 1;
        int first = -1;
        
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
        
        if (first != -1) {
            // Находим последнее вхождение target
            left = first;
            right = len - 1;
            int last = first;
            
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
            
            count += (last - first + 1);
        }
        
        // Пропускаем дубликаты arr[i]
        while (i + 1 < len && arr[i] == arr[i + 1]) {
            ++i;
        }
    }
    
    return count;
}
