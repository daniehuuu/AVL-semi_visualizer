#pragma once
template <class T> void swapT(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <class T, class K>
void ascendinly_fill_container(T& container, size_t size, K absoluteMin,
    K absoluteMax, bool not_duplicated_values) {
    K elem, local_interval_min = absoluteMin, module = absoluteMax - absoluteMin;
    long double intervalDivision, local_interval_max;

    if (absoluteMin > absoluteMax)
        return;

    if (absoluteMin == absoluteMax && not_duplicated_values)
        return;

    if (absoluteMin == absoluteMax &&
        !not_duplicated_values) // same as vector<T> container(size, value)
    {
        for (size_t i = 0; i < size; i++)
            container[i] = absoluteMin;
    }

    if (module < size && not_duplicated_values)
        return;

    if (not_duplicated_values)
        intervalDivision = static_cast<long double>(module) / size;
    else
        intervalDivision = static_cast<long double>(module) / (rand() % size + 1);

    local_interval_max = absoluteMin + intervalDivision;

    for (size_t i = 0; i < size; i++) {
        if (local_interval_min > absoluteMax)
            local_interval_min = absoluteMax;

        if (local_interval_max > absoluteMax)
            local_interval_max = absoluteMax;

        elem =
            rand() % static_cast<K>(local_interval_max - local_interval_min + 1) +
            local_interval_min;

        // std::cout << i + 1 << "\tRange: " << local_interval_min << " - (int)"
        //           << local_interval_max << "\telem = " << elem << "\n"; // Range
        //           //of number for each iteration
        container[i] = local_interval_min = elem; // element == new local minimun
        local_interval_max += intervalDivision;

        if (not_duplicated_values)
            local_interval_min++;
    }
    // std::cout << intervalDivision << "\n";
}

template <class T> void permutate(T& container, size_t size) {
    size_t randIndex;
    for (size_t i = size - 1; i > 0; i--) {
        randIndex = rand() % i; //[0; i) there is a change always. If u want [0; i]
        // use rand() % (i + 1).
        swapT(container[i], container[randIndex]);
    }
}