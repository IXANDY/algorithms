#include <iostream>

int binary_search(int beg, int end, int* array, int find) {

    while(beg <= end) {

        int middle = (beg + end) / 2;

        if(array[middle] == find) {

            return 1;
        }
        else {

            if (array[middle] < find)
                beg = middle + 1;
            if (array[middle] > find)
                end = middle - 1;
        }
    }
    return 0;
}

int lower_bound(int beg, int end, int* array, int find) {

    int ans = end + 1;

    while(beg <= end) {

        int middle = (beg + end) / 2;

        if(array[middle] >= find) {

            end = middle - 1;
            ans = middle;
        }
        else {

            beg = middle + 1;
        }
    }
    return ans;
}

int upper_bound(int beg, int end, int* array, int find) {

    int ans = end + 1;

    while(beg <= end) {

        int middle = (beg + end) / 2;

        if(array[middle] > find) {

            end = middle - 1;
            ans = middle;
        }
        else {

            beg = middle + 1;
        }
    }
    return ans;
}

int main() {

    int size;
    std::cin >> size;
    int* arr = new int[size];

    for (int i = 0; i < size; ++i) {

        std::cin >> arr[i];
    }

    int reqm;
    std::cin >> reqm;
    int* reqArr = new int[reqm];

    for(int i = 0; i < reqm; ++i)
        std::cin >> reqArr[i];

    for(int i = 0; i < reqm; ++i) {

        std::cout << binary_search(0, size - 1, arr, reqArr[i]) << " ";
        std::cout << lower_bound(0, size - 1, arr, reqArr[i]) << " ";
        std::cout << upper_bound(0, size - 1, arr, reqArr[i]) << '\n';
    }

    return 0;
}
