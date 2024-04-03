#include <iostream>
#include "product.h"
#include "builder.h"
using namespace std;


int main()
{
    int option = 1;
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
    else {
        Director* director = new Director;

        cout << "<< Model-1 >>" << endl;
        director->setBuilder(new ConcreteBuilderModel1);
        director->make();
        Product* product_model1 = director->getProduct();
        product_model1->info();

        cout << "<< Model-2 >>" << endl;
        director->setBuilder(new ConcreteBuilderModel2);
        director->make();
        Product* product_model2 = director->getProduct();
        product_model2->info();

        delete director;
        delete product_model1;
        delete product_model2;
    }

    return 0;
}