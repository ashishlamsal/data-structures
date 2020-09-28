#include <iostream>

void towerOfHanoi(int n, char from_rod, char aux_rod, char to_rod){
    if (n==1){
        std::cout << "Move disk "<< n << " from " << from_rod << " to " << to_rod << std::endl;
        return;
    }
    towerOfHanoi(n-1, from_rod, to_rod, aux_rod );
    std::cout << "Move disk "<< n << " from " << from_rod << " to " << to_rod << std::endl;
    towerOfHanoi(n-1, aux_rod, from_rod, to_rod);
}

int main() {
    // A to C using B
    towerOfHanoi(3,'A','B','C');
}
