#include "container.h"
#include <iostream>
#include <fstream>

//constructors
template <typename T> Container<T>::Container(){
    first.K = "";
    first.V = "";
}
template <typename T> Container<T>::Container(const Container *container){
    first.K = "";
    first.V = "";
    first.branches = container->first.branches;
}


//destructor
template <typename T> Container<T>::~Container(){
    first.branches.clear();
}
template <typename T> void Container<T>::deleteALL(){
    first.branches.clear();
}


//count functions
void countcheck(Data* branch, int* c){
    if (branch->branches.empty()) (*c)++;
    else{
        for (int i = 0; i < (int)(branch->branches.size()); i++) countcheck(&(branch->branches[i]), c);
    }
}
template <typename T> int Container<T>::count(){
    int c = 0;
    std::cout << "count begin" << std::endl;
    for (int i = 0; i < (int)(first.branches.size()); i++){
        countcheck(&(first.branches[i]), &c);
    }
    std::cout << "count end" << std::endl;
    return c;
}

//file work
template <typename T> void Container<T>::writefile(std::string path){
    std::ofstream file;
    file.open(path, std::ofstream::out | std::ofstream::trunc);
    if (file.is_open()){
        std::vector<Data> vec = areBelong("");
        for (int i = 0; i < (int)vec.size(); i++){
            file << vec[i].K << "\n" << vec[i].V << "\n";
        }
        file.close();
    }
    else std::cout << "Can't open file";
}
template <typename T> void Container<T>::readfile(std::string path){
    std::ifstream file;
    file.open(path);
    if (file.is_open()){
        deleteALL();
        std::string str1, str2;
        while (!(file.eof()))
        {
            getline(file, str1);
            getline(file, str2);
            add(str1, str2);
        }
        file.close();
    }
    else std::cout << "Can't open file";
}


//delete functions
void searchToDelete(int j, Data* branch, std::string K){
    std::cout << "step " << j << std::endl;
    int check = -1;
    for (int i = 0; i < (int)(branch->branches.size()); i++){
        if (branch->branches[i].K[j] == K[j]) check = i;
    }
    if (check != -1){
        if (branch->branches[check].K == K){
            branch->branches.erase(branch->branches.begin() + check);
            std::cout << "deleted " << std::endl;
        }
        else searchToDelete(j+1, &(branch->branches[check]), K);
    }
    else std::cout << "No matching identifier" << std::endl;
}
template <typename T> void Container<T>::del(std::string K){
    int check = -1;
    if (K.length() != 0){
        for (int i = 0; i < (int)(first.branches.size()); i++){
            if (first.branches[i].K[0] == K[0]) check = i;
        }
        if (check != -1) searchToDelete(1, &(first.branches[check]),K);
        else std::cout << "No matching identifier" << std::endl;
    }
}


//isBelong functions
bool scan(int j, Data branch, std::string K){
    if (j == (int)K.length()) return true;
    else{
        int ch = -1;
        for (int i = 0; i < (int)(branch.branches.size()); i++){
            if (branch.branches[i].K[j] == K[j]) ch = i;
        }
        if (ch != -1) return scan(j+1, branch.branches[ch], K);
        else return false;
    }
}
template <typename T> bool Container<T>::isBelong(std::string K){
    int check = -1;
    if (K.length() == 0) return false;
    for (int i = 0; i < (int)(first.branches.size()); i++){
        if (first.branches[i].K[0] == K[0]) check = i;
    }
    if (check != -1) return scan(1,first.branches[check],K);
    else return false;
}

//areBelong functions
void search(Data* branch, std::vector<Data>* vec){
    for (int i = 0; i < (int)(branch->branches.size()); i++) search(&(branch->branches[i]), vec);
    if (branch->branches.size() == 0){
        Data temp;
        temp.K = branch->K;
        temp.V = branch->V;
        vec->push_back(temp);
    }
}
void scanALL(int j, Data* branch, std::string key, std::vector<Data>* vec){
    if (j == (int)key.length()) search(branch, vec);
    else{
        int check = -1;
        for (int i = 0; i < (int)(branch->branches.size()); i++){
            if (branch->branches[i].K[j] == key[j]) check = i;
        }
        if (check != -1) scanALL(j+1, &(branch->branches[check]), key, vec);
    }
}
template <typename T> std::vector<Data> Container<T>::areBelong(std::string key){
    int check = -1;
    std::vector<Data> vec;
    if (key.length() != 0){
        for (int i = 0; i < (int)(first.branches.size()); i++){
            if (first.branches[i].K[0] == key[0]) check = i;
        }
        if (check != -1) scanALL(1,&(first.branches[check]),key, &vec);
    }
    else search(&first, &vec);
    return vec;
}

//add functions
Data* searchToAdd(int j, Data* branch, std::string K){
    if (j == (int)K.length()){
        std::cout << "The identifier of this adress already exists in the list" << std::endl;
        return NULL;
    }
    int check = -1;
    for (int i = 0; i < (int)(branch->branches.size()); i++){
        if (branch->branches[i].K[j] == K[j]) check = i;
    }
    if (check != -1) return searchToAdd(j+1, &(branch->branches[check]), K);
    else return branch;
}
void addFunction(Data* branch, std::string K, std::string V){
    Data newdata;
    if (branch->K.length() == K.length() - 1){
        newdata.K = K;
        newdata.V = V;
        branch->branches.push_back(newdata);
    }
    else{
        newdata.K = K.substr(0, branch->K.length() + 1);
        newdata.V = "";
        branch->branches.push_back(newdata);
        addFunction(&(branch->branches[branch->branches.size() - 1]), K, V);
    }
}
template <typename T> void Container<T>::add(std::string K, std::string V){
    int check = -1;
    Data* p = NULL;
    for (int i = 0; i < (int)(first.branches.size()); i++){
        if (first.branches[i].K[0] == K[0]) check = i;
    }
    if (check == -1) p = searchToAdd(0, &first, K);
    else if (check != -1) p = searchToAdd(1,&(first.branches[check]),K);
    if (p != NULL) addFunction(p, K, V);
}


//operator ==
void sort(std::vector<Data>*vec){
    for (int i = 0; i < (int)vec->size()-1; i++){
        for (int j = i+1; j < (int)vec->size(); j++){
            if ((*vec)[i].K == (*vec)[j].K){
                if ((*vec)[i].V > (*vec)[j].V){
                    Data temp = *vec[i].data();
                    *vec[i].data() = *vec[j].data();
                    *vec[j].data() = temp;
                }
            }
            if ((*vec)[i].K > (*vec)[j].K){
                Data temp = *vec[i].data();
                *vec[i].data() = *vec[j].data();
                *vec[j].data() = temp;
            }
        }
    }
}
template <typename T> bool Container<T>::operator==(Container<T> *container){
    if (first.branches.size() == container->first.branches.size()){
        std::vector<Data> data1;
        std::vector<Data> data2;
        search(&first, &data1);
        search(&container->first, &data2);
        sort(&data1);
        sort(&data2);
        if (data1.size() != data2.size()) return false;
        else{
            for (int i = 0; i < (int)data1.size(); i++){
                if (data1.data()->K != data2.data()->K || data1.data()->V != data2.data()->V) return false;
            }
            return true;
        }
    }
    else return false;
}

//operator []
/*Data* operatorSearch(int j, Data* branch, std::string K){
    if (j == (int)K.length()) return branch;
    int check = -1;
    for (int i = 0; i < (int)(branch->branches.size()); i++){
        if (branch->branches[i].K[j] == K[j]) check = i;
    }
    if (check != -1) return searchToAdd(j+1, &(branch->branches[check]), K);
    else return NULL;
}*/
template <typename T> std::string& Container<T>::operator[](const std::string K){
    std::vector<Data> vec;
    if (K.length() == 0){
        std::cout << "This identifier doesn't exist. The reference is set to the adress of the tree head." << std::endl;
        return first.V;
    }
    else{
        vec = areBelong(K);
        if (vec.size() == 1) return vec.data()->V;
        else{
            std::cout << "Wrong identifier. The reference is set to the adress of the tree head." << std::endl;
            return first.V;
        }
    }
}

template class Container<int>;
