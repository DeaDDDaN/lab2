#ifndef CONTAINER_H
#define CONTAINER_H
#include <string>
#include <vector>

struct Data{
    std::string K, V;
    std::vector <Data> branches;
};

template <typename T> class Container
{
private:
    Data first;
public:
    Container();
    Container(const Container *container);
    ~Container();
    void deleteALL();
    int count();
    void writefile(std::string path);
    void readfile(std::string path);
    void add(std::string K, std::string V);
    void del(std::string K);
    bool isBelong(std::string K);
    std::vector<Data> areBelong(std::string key);
    bool operator== (Container<T> *container);
    std::string& operator[] (const std::string K);
};

#endif // CONTAINER_H
