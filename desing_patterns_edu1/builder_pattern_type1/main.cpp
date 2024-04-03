#include "product.h"

#include <iostream>
using namespace std;


int main()
{
    cout << "<< Model-1 >>" << endl;
    Product* product_model1 = new Product("I7", "32GB", "512GB");
    product_model1->info();

    cout << endl;
    cout << "<< Model-2 >>" << endl;
    Product* product_model2 = new Product("I3", "16GB", "256GB");
    product_model2->info();

    delete product_model1;
    delete product_model2;
    return 0;
}