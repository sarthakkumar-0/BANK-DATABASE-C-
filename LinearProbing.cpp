#include "LinearProbing.h"

LinearProbing::LinearProbing(){
    num_acc=0;
    Account a;
    a.id="null";
    for (int i=0; i<100000; i++){
        bankStorage1d.push_back(a);
    }
}

void  LinearProbing :: merge(std::vector <int> &left , std::vector <int> &right , std::vector <int> &vec){
    int l1 = left.size();
    int l2 = right.size();

    int i=0 ,j=0 ,k=0;
    while (i < l1  && j < l2){
        if (left[i] >= right[j] ){
            vec[k] = left[i];
            i++;
        }else{
            vec[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < l1) {
        vec[k] = left[i];
        i++;
        k++;
    }
    while (j <l2){
        vec[k] = right[j];
        j++;
        k++;
    }
}

void LinearProbing :: mergesort(std::vector <int> &vec){
    int l = vec.size();
    if (l <= 1){
        return;
    }
    int m = l/2 ;
    std::vector <int> left (vec.begin() , vec.begin()+ m);
    std::vector <int> right (vec.begin() + m , vec.end());

    mergesort(left);
    mergesort(right);
    
    merge (left ,right, vec);

}

void LinearProbing::createAccount(std::string id, int count) {
    int h = hash (id);
    Account acc;
    acc.id= id ;
    acc.balance = count;
    int i = 0;
    bool flag = false ; 
    while (!flag  &&  i < (100000 - num_acc) ){     ////////////seee
        if (bankStorage1d[(h + (i)) % 100000].id == "null"){
            bankStorage1d[(h + (i)) % 100000] = acc;
            flag=true;
            num_acc++;
        }
        i++;
    }
    // std::cout<< "acc is created with acc number "<<id << " and hash value "<<h <<std::endl; 
}

std::vector<int> LinearProbing::getTopK(int k) {
    std::vector <int> balances ;
    for (int i=0; i < bankStorage1d.size() ; i++){
        if (bankStorage1d[i].id != "null"){
            balances.push_back(bankStorage1d[i].balance);
        }
    }
    mergesort(balances);
    if ( k >= balances.size()){
        return balances;
    }
    std::vector <int> res (balances.begin() , balances.begin() + k);
    return res;
}

int LinearProbing::getBalance(std::string id) {
    int h = hash(id);
    int i = 0;
    bool flag = false;
    while (!flag && i<num_acc ){
        if (bankStorage1d[(h + (i)) % 100000].id == id){
            flag =true;
            return bankStorage1d[(h + (i)) % 100000].balance;
        }
        i++;
    }
    return -1; // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count) {
    int h = hash(id);
    int i=0;
    bool flag =false ;
    while (!flag && i<num_acc){
        if (bankStorage1d[(h + (i)) % 100000].id == id){
            flag=true;
            bankStorage1d[(h + (i)) % 100000].balance += count;
            return;
        }
        i++;
    }
    createAccount(id, count);
}

bool LinearProbing::doesExist(std::string id) {
    int h = hash(id);
    int i=0; 
    bool flag = false ;
    while (!flag  &&  i < num_acc){
        if (bankStorage1d[(h + (i)) % 100000].id == id){
            flag =true;
            return true;
        }
        i++;
    }
    return false;
}

bool LinearProbing::deleteAccount(std::string id) {
    int h = hash (id);
    int i=0;
    bool flag = false;
    while (!flag  &&  i < num_acc){
        if (bankStorage1d[(h + (i)) % 100000].id == id){
            flag =true ;
            Account a;
            a.id = "null";
            bankStorage1d[((h + (i)) % 100000)] = a;
            num_acc--;
            return true;
        }
        i++;
    }
    return false; 
}

int LinearProbing::databaseSize() {
    return num_acc; // Placeholder return value
}

int LinearProbing::hash(std::string id) {

        int a = str_to_int(subs (id, 12,6)) + str_to_int(subs(id,15,3)) + str_to_int(subs(id,18,3)) - str_to_int (subs (id,4,6)) - str_to_int (subs(id,7,4));
    for (int i=0 ; i<4 ; i++){
        if (i%2 == 0){
            a += (int)id[i];
        }else{
            a -= (int)id[i];
        }
    }
    return abbs(a)% 100000;
}

// int LinearProbing::hash (std::string id){  //"CDAD7786825_7990768648"
//     int a = str_to_int (subs(id, 4,3) )*131 + str_to_int (subs(id, 12,3))*21 +str_to_int(subs (id,18,3)) * 39;
//     for (int i=0 ; i<4 ; i++){
//         if (i%2 == 0){
//             a += (int)id[i];
//         }else{
//             a -= (int)id[i];
//         }
//     }
//     return abbs(a)% 100000;
// }

// int LinearProbing::hash(std::string id){  //"CDAD7786825_7990768648"
//     int a= 0;
//     for (int i=12; i<21 ;i++){
//         a += str_to_int (subs (id ,i ,2)) * 21;
//     }
//     return abbs(a)%100000;
// }

// int LinearProbing::hash(std::string id){
//     int a=0;
//     for (int i=0; i<id.size() ;i++){
//         a += (int)id[i];
//     }
//     return a;
// }

