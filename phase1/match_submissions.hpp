#include <array>
#include <iostream>
#include <span>
#include <vector>
#include<cmath>
#include<unordered_set>
#define ll long long int
// -----------------------------------------------------------------------------

// You are free to add any STL includes above this comment, below the --line--.
// DO NOT add "using namespace std;" or include any other files/libraries.
// Also DO NOT add the include "bits/stdc++.h"

// OPTIONAL: Add your helper functions and data structures here

std::vector<ll> hashing(std::vector<int> &text, ll len){
    ll prime = 1.0e11+7;
    ll x = 1;
    ll hashed = 0;
    for(ll i =0; i<len; i++,x=(x*33)){
        if(hashed >= prime) hashed%=prime;
        hashed = (hashed+ ((x%prime)*text[i] % prime))%prime;
    }
    return {hashed, x};
}
void calculate_hashes(std::unordered_set<ll> &hash_set, std::vector<int> &text, ll len){
    ll prime = 1.0e11+7;
    ll x = 1;
    ll hashed = 0;
    for(ll i =0; i<len; i++,x = (x*33)){
        if(hashed >= prime) hashed%=prime;
        hashed+= ((x%prime)*text[i] % prime);
    }
    hashed = hashed % prime;

    hash_set.insert(hashed);
    for(int i = 1; i<=text.size()-len; i++){
        hashed = ((((hashed - text[i-1])/33 + prime) % prime) + (x*text[i+len-1] )%prime)%prime;
        hash_set.insert(hashed);
    }
}

std::array<int,5> rolling_hash(std:: vector<int> &submission1, std::vector<int> &submission2){
    

    
        for(int match_len =10; match_len <= std::min(submission1.size(),submission2.size()); match_len++){
            std::unordered_set<ll> hash_set;

            if(match_len > submission1.size() || match_len > submission2.size()){
                return {0,0,0,0,0};
             }
            calculate_hashes(hash_set, submission1, match_len);
        
            std::vector<ll> v = hashing(submission2,match_len);
            ll hashed = v[0], x= v[1];
            ll prime= 1.0e11+7;
            if(hash_set.find(hashed) != hash_set.end()){
                    std::cout << "Match found : len "<<match_len<<" "<<0<<'\n';
                }

            for(int i = 1; i<submission2.size()-match_len; i++){
                hashed = (((hashed - submission2[i-1])/33 + prime) % prime);
                hashed = (hashed + (x*submission2[i+match_len-1] )%prime) %prime;
                if(hash_set.find(hashed) != hash_set.end()){
                    std::cout << "Match found : len "<<match_len<<" "<<i<<'\n';
                }
            }
        }
    
return {0,0,0,0,0};
}

std::array<int, 5> match_submissions(std::vector<int> &submission1, 
        std::vector<int> &submission2) {
    // TODO: Write your code here

    std::cout << submission1.size()<<" "<<submission2.size()<<'\n';
    for(auto i : submission1){
        std::cerr << i<<" ";
    }
    std::cerr << '\n';
    std::cerr<< '\n';
    for(auto i : submission2){
        std::cerr << i<<" ";
    }
    std::cerr<<hashing(submission1, submission1.size())[0]<<'\n';;
    std::cerr << hashing(submission2, submission2.size())[0]<<'\n';
    std::array<int, 5> result = {0, 0, 0, 0, 0};
    auto A = rolling_hash(submission1, submission2);
    return result; // dummy return
    // End TODO
}

// int main(){
//     std::vector<int> submission1 = {1,2,3,258,5,6,7,8,9,10,11};
//     std::vector<int> submission2 = {1,2,3,258,5,6,7,8,9,10,12};
//     std::array<int, 5> result = match_submissions(submission1, submission2);
//     // for(int i = 0; i<5; i++){
//     //     std::cout << result[i]<<" ";
//     // }
//     // std::cout << '\n';
//     return 0;
// }