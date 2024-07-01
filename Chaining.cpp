#include "Chaining.h"

Chaining::Chaining() {
    num_acc=0;
    // std::vector<Account> v;
    // for(int i=0;i<100000;i++){
    //     bankStorage2d.push_back(v);
    // }
    bankStorage2d = std::vector<std::vector<Account> >(100000);
    // std::cout<<"initialize"<<std::endl;
}

int Chaining::hash(std::string id) {

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

// int Chaining::hash(std::string id){
//     int a=0;
//     for (int i=0; i<id.size() ;i++){
//         a += (int)id[i];
//     }
//     return a;
// }

void  Chaining :: merge(std::vector <int> &left , std::vector <int> &right , std::vector <int> &vec){
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

void Chaining :: mergesort(std::vector <int> &vec){
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

void Chaining::createAccount(std::string id, int count) {
    int h = hash(id);
    Account acc;
    acc.balance = count;
    acc.id = id;
    bankStorage2d[h].push_back(acc);
    num_acc++;
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector <int> balances;
    for (int i=0;  i < bankStorage2d.size() ;i++){
        for (int j=0 ; j< bankStorage2d[i].size(); j++){
            balances.push_back(bankStorage2d[i][j].balance);
        }
    }
    mergesort(balances);
    if (k >= balances.size()){
        return balances;
    }
    std::vector <int> res (balances.begin() , balances.begin() + k);
    // std::cout<<"get topk executed"<<std::endl;
    return res;
}

int Chaining::getBalance(std::string id) {
    int h= hash (id);
    for (int i=0 ; i< bankStorage2d[h].size(); i++){
        if (bankStorage2d[h][i].id == id){
            return bankStorage2d[h][i].balance;
        }
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    int h = hash (id);
    for (int i=0 ; i< bankStorage2d[h].size(); i++){
        if (bankStorage2d[h][i].id == id){
            bankStorage2d[h][i].balance += count;
            return;
        }
    }
    createAccount(id,count);
}

bool Chaining::doesExist(std::string id) {
    int h = hash (id);
    std:: vector <Account>:: iterator it;
    for (it = bankStorage2d[h].begin() ; it!=bankStorage2d[h].end() ; it++){
        if (it->id == id){
            return true;
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id) {
    int h = hash (id);
    for (int i=0 ; i< bankStorage2d[h].size(); i++){
        Account a = bankStorage2d[h][i];
        if (a.id == id){           
            bankStorage2d[h].erase(bankStorage2d[h].begin()+i);
            num_acc--;
            return true;
        }
    }
    return false; // Placeholder return value
}

int Chaining::databaseSize() {
    return num_acc; // Placeholder return value
}

// int main(){
//     Chaining c;
//     c.createAccount("CDAD7786825_7990768648" , 654);
//     c.createAccount("CDAD7786825_7990768649" , 1654);
//     c.createAccount("CDAD7786825_7990768640" , 2654);
//     c.createAccount("CDAD7786825_7990768647" , 2654);
//     c.createAccount("CDAD7786825_7990768634" , 3654);
//     c.createAccount("CDAD7786825_7990768645" , 4654);
//     c.createAccount("CDAD7786825_7990768644" , 6554);
//     c.createAccount("CDAD7786825_7990768624" , 6654);
//     c.createAccount("CDAD7786825_7990768642" , 65554);
//     c.createAccount("CDAD7786825_7990768641" , 6514);
//     std::cout<<"executed"<<std::endl;
//     std::cout<<c.doesExist("CDAD7786825_7990468647")<<std::endl;
//     c.addTransaction("CDAD7786825_7990768644" , -554); 
//     std::vector <int> topbal = c.getTopK(3);
//     std::cout<<topbal[0] <<" "<<topbal[1]<< " "<< topbal[2]<< " "<<std::endl;

//     std::cout<< c.getBalance("CDAD7786825_7990768644")<<std::endl;
//     std::cout<< c.deleteAccount("CDAD7786825_7990768641")<<std::endl; //1
//     std::cout<<c.doesExist("CDAD7786825_7990768641")<<std::endl;//0
//     std::cout<< c.databaseSize ()<<std::endl; //9
//     return 0;
// }

