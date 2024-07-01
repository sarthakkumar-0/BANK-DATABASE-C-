#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    Chaining();
    void merge (std::vector <int> &left , std::vector <int> &right , std::vector <int> &vec);
    void mergesort (std::vector <int> &vec);
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    int num_acc;
    int power (int base ,int exp){
        int res = base;
        if (exp == 0){
            return 1;
        }
        for (int i=1 ; i < exp; i++){
            res *= base; 
        }
        return res;
    }

    int str_to_int (std::string s){  //"4352"
        int sz=s.size();
        int res =0;
        for (int i=0; i<sz ; i++){
            res += (s[i]-48) * power( 10, (sz-i-1));
        }
        return res;
    }

    std::string subs (std::string s , int start , int len){
        std::string res = "";
        for (int i=0 ; i < len ; i++){
            res += s[start + i];
        }
        return res;
    }
    int abbs (int a){
        if ( a >= 0){
            return a;
        }else{
            return -a;
        }
    }
private:
    // Other data members and functions specific to Chaining
};

#endif // CHAINING_H
