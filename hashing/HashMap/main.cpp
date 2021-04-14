#include "Vector.h"
#include "HashCode.h"
#include "HashMap.h"

int main()
{
    std::cout << "===============" << std::endl;
    HashMap<int, char> h11;
    h11[1] = 'a';
    h11[4] = 'b';
    h11[7] = 'c';
    h11[6] = 'f';
    h11[8] = 'y';
    // h11[70] = 't';
    // h11[27] = 'r';
    //h11.remove(1);
    std::cout << h11.size() << std::endl;
    std::cout << h11.isEmpty() << std::endl;
    //h11.clear();
    std::cout << h11[7] << std::endl;
    std::cout << "===============" << std::endl;
    
    for (auto&& i : h11)
        std::cout << i.key << "=" << i.value << std::endl;
    
    std::cout << "===============" << std::endl;
    for (auto&& ptr = h11.begin(); ptr != h11.end(); ptr++) {
        std::cout << ptr->key << " =  " << ptr->value << std::endl;
    }
    
    // Vector<int> v1{ 1,2,3,4 };
    // v1.push_back(2);
    // v1.push_back(3);
    // v1.push_back(5);
    // v1.push_back(5);
    // v1.pop_back();
    // v1[0] = 9;
    // v1.pop_back();
    // v1.remove(2);

    // Vector<int> v2(4);
    // v2.push_back(50);
    // v2.push_back(80);
    // v1 = v1 + 30;

    // std::cout << "Printing:" << v1.size() << std::endl;
    // for (auto&& i : v1)
    //     std::cout << i << std::endl;

    // v1.clear();
    // for (auto&& i : v1)
    //     std::cout << i << std::endl;

    // std::cout << "===============" << std::endl;

    // HashMap<int, char> h1;
    // h1.put(1, 'a');
    // h1[1] = 'a';
    // h1[4] = 'b';
    // h1[7] = 'c';
    // h1.remove(1);
    // std::cout << h1.containsKey(1) << std::endl;
    // std::cout << h1[7] << std::endl;

    // for (auto&& i : h1)
    //     std::cout << i << std::endl;

    return 0;
}