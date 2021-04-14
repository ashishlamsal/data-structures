#pragma once

#include <string>
#include <cstddef>       // For size_t
#include <cstdint>       // For uintptr_t
#include <cstring>       // For strlen

static const int HASH_SEED = 5381;               // Starting point for first cycle
static const int HASH_MULTIPLIER = 33;           // Multiplier for each cycle
static const int HASH_MASK = unsigned(-1) >> 1;  // All 1 bits except the sign

int hashCode(int key) {
    return key & HASH_MASK;
}

int hashCode(bool key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(char key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(unsigned int key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(long key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(unsigned long key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(short key) {
    return hashCode(static_cast<int>(key));
}

int hashCode(unsigned short key) {
    return hashCode(static_cast<int>(key));
}

#ifdef _WIN64
int hashCode(uintptr_t key) {
    return hashCode(static_cast<unsigned long>(key));
}
#endif // _WIN64


int hashCode(void* key) {
    return hashCode(reinterpret_cast<uintptr_t>(key));
}

int hashCode(const char* base, size_t numBytes) {
    unsigned hash = HASH_SEED;
    for (size_t i = 0; i < numBytes; i++) {
        hash = HASH_MULTIPLIER * hash + base[i];
    }
    return hashCode(hash);
}

int hashCode(const char* str) {
    return hashCode(str, strlen(str));
}

int hashCode(const std::string& str) {
    return hashCode(str.data(), str.length());
}

int hashCode(double key) {
    return hashCode(reinterpret_cast<const char*>(&key), sizeof(double));
}

int hashCode(float key) {
    return hashCode(reinterpret_cast<const char*>(&key), sizeof(float));
}

int hashCode(long double key) {
    return hashCode(reinterpret_cast<const char*>(&key), sizeof(long double));
}
