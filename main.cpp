#include "mymatrix.h"

void print(MyMatrix<int> m)
{
      std::cout << m << std::endl;
}

int main()
{
    MyMatrix<int> m(3,2);

    std::cout << m  << m.size_i() << " " << m.size_j() << "\n\n";
//    m.pop_i();
//    std::cout << m  << m.size_i() << " " << m.size_j() << "\n\n";

//    m.push_i();
//    std::cout << m << m.size_i() << " " << m.size_j() << "\n\n";

//    m.push_j();
//    std::cout << m << m.size_i() << " " << m.size_j() << "\n\n";
//    m.pop_j();
//    std::cout << m << m.size_i() << " " << m.size_j() << "\n\n";

    std::cin >>m;
  //  std::cout << m << std::endl;
    std::cout << std::endl;

    MyMatrix<int> m2(m.transpose());

    std::cout << m2 << std::endl;
    std::cout << std::endl;


    std::cout << m*m2 <<std::endl;


    std::cout << "Hello World!" << std::endl;
    return 0;
}

