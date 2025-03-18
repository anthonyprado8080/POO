#include <iostream>

class MyClass {
public:
    static void msgFunc() {
        std::cout << "¡Bienvenido a la clase estática!" << std::endl;
    }
};

int main() {
    MyClass::msgFunc();

    return 0;
}
