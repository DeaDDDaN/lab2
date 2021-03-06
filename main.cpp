#include "mainwindow.h"
#include "container.h"
#include <cassert>
#include <iostream>
#include <QApplication>


int main(int argc, char *argv[])
{
    Container<int> container;
    std::cout << container.count();
    assert(container.count() == 0);     //1

    container.add("12", "st. AAA");
    assert(container.count() == 1);
    container.add("12", "st. BBB");
    assert(container.count() == 1);     //2

    assert(container.isBelong("12"));   //3

    assert(container["12"] == "st. AAA"); //4

    container.del("12");
    container.add("13", "st. FFF");
    std::cout << container.count() << std::endl;       //5
    //assert(container.count() == 0);

    assert(!container.isBelong("12")); //6

    container.deleteALL();
    Container<int> container2;
    assert(container.operator==(&container2)); //7

    container.add("12", "st. AAA");
    container.add("13", "st. FFF");
    Container<int> container3(&container);   //8
    assert(container3.operator==(&container));
    std::string& p = container3.operator[]("12");
    p = "BBB";
    std::cout << container3["12"] << std::endl;
    assert((container3.operator==(&container)));

    Container<int> containerf1;
    containerf1.add("12", "st. AAA");
    containerf1.add("13", "st. FFF");
    containerf1.writefile("C:\\Users\\DeaDD\\Desktop\\lab2empty.txt");
    Container<int> containerf2;
    containerf2.readfile("C:\\Users\\DeaDD\\Desktop\\lab2empty.txt");       //9
    assert(containerf1.operator==(&containerf2));


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
