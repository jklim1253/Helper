#pragma once

template<typename T, int N>
int GetArraySize(T(&arr)[N]) {
    return N;
}