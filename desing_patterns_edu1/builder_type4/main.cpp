#include <iostream>
#include "product.h"
#include "builder.h"
using namespace std;


int main()
{
    int option = 0;

    // using constructor of product: bad
    if (option) {
        cout << "<< Model-1 >>" << endl;
        Product* product_model1 = new Product("I7", "32GB", "512GB");
        product_model1->info();

        cout << endl;
        cout << "<< Model-2 >>" << endl;
        Product* product_model2 = new Product("I3", "16GB", "256GB");
        product_model2->info();

        delete product_model1;
        delete product_model2;
    }
    // using builder for product: good
    else {
#if 1
        cout << "<< Model-1 >>" << endl;
        Product* product_model1 = Builder().start()
            ->setCPU("I7")->setRAM("32GB")->setSSD("512GB")->build();
        product_model1->info();

        cout << endl;
        cout << "<< Model-2 >>" << endl;
        Product* product_model2 = Builder().start()
            ->setCPU("I3")->setRAM("16GB")->setSSD("256GB")->build();
        product_model2->info();

        delete product_model1;
        delete product_model2;
#else
        cout << "<< Model-1 >>" << endl;
        Product& product_model1 = Builder().start()
            .setCPU("I7").setRAM("32GB").setSSD("512GB").build();
        product_model1.info();

        cout << endl;
        cout << "<< Model-2 >>" << endl;
        Product& product_model2 = Builder().start()
            ->setCPU("I3")->setRAM("16GB")->setSSD("256GB")->build();
        product_model2.info();
#endif
    }
    return 0;
}
