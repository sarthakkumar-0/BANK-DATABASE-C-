#include "CubicProbing.h"

CubicProbing::CubicProbing(){
    num_acc=0;
    Account a;
    a.id="null";
    for (int i=0; i<100003; i++){
        bankStorage1d.push_back(a);
    }
}

void  CubicProbing :: merge(std::vector <int> &left , std::vector <int> &right , std::vector <int> &vec){
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

void CubicProbing :: mergesort(std::vector <int> &vec){
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

void CubicProbing::createAccount(std::string id, int count) {
    int h = hash (id);
    Account acc;
    acc.id= id ;
    acc.balance = count;
    int i = 0;
    bool flag = false ; 
    while (!flag  &&  i < /*(100003 - num_acc)*/ bankStorage1d.size() ){
        if (bankStorage1d[(h + (i*i*i)) % 100003].id == "null"){
            bankStorage1d[(h + (i*i*i)) % 100003] = acc;
            flag=true;
            num_acc++;
        }
        i++;
    }
}

std::vector<int> CubicProbing::getTopK(int k) {
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

int CubicProbing::getBalance(std::string id) {
    int h = hash(id);
    int i = 0;
    bool flag = false;
    while (!flag && i<num_acc){
        if (bankStorage1d[(h + (i*i*i)) % 100003].id == id){
            flag =true;
            return bankStorage1d[(h + (i*i*i)) % 100003].balance;
        }
        i++;
    }
    return -1;
}

void CubicProbing::addTransaction(std::string id, int count) {
    int h = hash(id);
    int i=0;
    bool flag =false ;
    while (!flag && i< num_acc){
        if (bankStorage1d[(h + (i*i*i)) % 100003].id == id){
            flag=true;
            bankStorage1d[(h + (i*i*i)) % 100003].balance += count;
            return;
        }
        i++;
    }
    createAccount(id, count);
}

bool CubicProbing::doesExist(std::string id) {
    int h = hash(id);
    int i=0; 
    bool flag = false ;
    while (!flag  &&  i < num_acc){
        if (bankStorage1d[(h + (i*i*i)) % 100003].id == id){
            flag =true;
            return true;
        }
        i++;
    }
    return false;
}

bool CubicProbing::deleteAccount(std::string id) {
    int h = hash (id);
    int i=0;
    bool flag = false;
    while (!flag  &&  i < num_acc){
        if (bankStorage1d[(h + (i*i*i)) % 100003].id == id){
            flag =true ;
            Account a;
            a.id = "null";
            bankStorage1d[((h + (i*i*i)) % 100003)] = a;
            num_acc--;
            return true;
        }
        i++;
    }
    return false; 
}

int CubicProbing::databaseSize() {
    return num_acc; // Placeholder return value
}

int CubicProbing::hash(std::string id) {
    int a = str_to_int(subs (id, 12,6)) + str_to_int(subs(id,15,5)) + str_to_int(subs(id,18,3)) - str_to_int (subs (id,4,6)) - str_to_int (subs(id,5,5));
    for (int i=0 ; i<4 ; i++){
        if (i%2 == 0){
            a += (int)id[i];
        }else{
            a -= (int)id[i];
        }
    }
    return abbs(a)% 100003;
}

// int CubicProbing::hash (std::string id){  //"CDAD7786825_7990768648"
                                             // 0123456789012345678901 
//     int a = str_to_int (subs(id, 4,3) )*131 + str_to_int (subs(id, 12,3))*21 +str_to_int(subs (id,18,3)) * 39;
//     for (int i=0 ; i<4 ; i++){
//         if (i%2 == 0){
//             a += (int)id[i];
//         }else{
//             a -= (int)id[i];
//         }
//     }
//     return abbs(a)% 100003;
// }

// int CubicProbing::hash(std::string id){  //"CDAD7786825_7990768648"
//     int a= 0;
//     for (int i=12; i<21 ;i++){
//         a += str_to_int (subs (id ,i ,2)) * 21;
//     }
//     return abbs(a)%100003;
// }

// int CubicProbing::hash(std::string id){
//     int a=0;
//     for (int i=0; i<id.size() ;i++){
//         a += (i*i)*(int)id[i];
//     }
//     return a;
// }

// int main(){
//     CubicProbing c;
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
