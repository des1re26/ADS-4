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
        int current_sum = arr[left] + arr[right];
        
        if (current_sum == value) {
            int left_val = arr[left];
            int right_val = arr[right];
            
            if (left_val == right_val) {
                // Все элементы между left и right одинаковы
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            }
            
            // Подсчет одинаковых элементов слева
            int left_count = 1;
            while (left + 1 < right && arr[left + 1] == left_val) {
                left_count++;
                left++;
            }
            
            // Подсчет одинаковых элементов справа
            int right_count = 1;
            while (right - 1 > left && arr[right - 1] == right_val) {
                right_count++;
                right--;
            }
            
            count += left_count * right_count;
            left++;
            right--;
        } else if (current_sum < value) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}

// Бинарный поиск с подсчетом вхождений
int countOccurrences(int *arr, int start, int end, int target) {
    int first = -1;
    int last = -1;
    
    // Поиск первого вхождения
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
    
    // Поиск последнего вхождения
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
    
    for (int i = 0; i < len; i++) {
        int target = value - arr[i];
        // Ищем target в массиве после позиции i
        int occurrences = countOccurrences(arr, i + 1, len - 1, target);
        count += occurrences;
        
        // Пропускаем дубликаты текущего элемента
        while (i + 1 < len && arr[i] == arr[i + 1]) {
            i++;
        }
    }
    
    return count;
}
