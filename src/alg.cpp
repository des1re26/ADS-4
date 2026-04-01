

// Функция 1: Полный перебор (цикл в цикле)
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

// Функция 2: Движение с двух концов навстречу (метод двух указателей)
int countPairs2(int *arr, int len, int value) {
    int count = 0;
    int left = 0;
    int right = len - 1;

    while (left < right) {
        int current_sum = arr[left] + arr[right];
        if (current_sum == value) {
            // Подсчет всех возможных пар с одинаковым левым значением
            int left_val = arr[left];
            int right_val = arr[right];
            
            // Если значения одинаковы, то количество пар = C(n, 2)
            if (left_val == right_val) {
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            }
            
            // Подсчет количества одинаковых элементов слева
            int left_count = 1;
            while (left + 1 < right && arr[left + 1] == left_val) {
                ++left_count;
                ++left;
            }
            
            // Подсчет количества одинаковых элементов справа
            int right_count = 1;
            while (right - 1 > left && arr[right - 1] == right_val) {
                ++right_count;
                --right;
            }
            
            // Добавляем количество комбинаций: left_count * right_count
            count += left_count * right_count;
            
            ++left;
            --right;
        } else if (current_sum < value) {
            ++left;
        } else {
            --right;
        }
    }
    return count;
}

// Функция 3: Бинарный поиск для второго элемента
int binarySearch(int *arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            // Находим первое вхождение target
            int first = mid;
            while (first > left && arr[first - 1] == target) {
                --first;
            }
            return first;
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
    for (int i = 0; i < len - 1; ++i) {
        int target = value - arr[i];
        // Ищем target в подмассиве arr[i+1 .. len-1]
        int first_pos = binarySearch(arr, i + 1, len - 1, target);
        if (first_pos != -1) {
            // Нашли первое вхождение target, считаем сколько их всего
            int j = first_pos;
            while (j < len && arr[j] == target) {
                ++count;
                ++j;
            }
        }
    }
    return count;
}
