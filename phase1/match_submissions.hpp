#include <array>
#include <iostream>
#include <span>
#include <vector>
#include<cmath>
#include<map>
#define ll long long 

// -----------------------------------------------------------------------------

// You are free to add any STL includes above this comment, below the --line--.
// DO NOT add "using namespace std;" or include any other files/libraries.
// Also DO NOT add the include "bits/stdc++.h"

// OPTIONAL: Add your helper functions and data structures here


//for submission 2
std::pair<ll,ll> hashing(std::vector<int> &text, ll len){
    ll prime = 1.0e9+7;
    // std::cout<<"prime: "<<prime<<std::endl;
    ll x = 1;
    ll hashed = 0;
    for(ll i =0; i<len; i++,x=(x%prime*33)){
       
        hashed = (hashed%prime+ (((x%prime)*text[i]) % prime))%prime;
    }
    x=x%prime;
    x/=33;
    
    hashed=hashed%prime;
    return {hashed, x};
}

//for submission 1
void calculate_hashes(std::map<ll,ll> &hash_set, std::vector<int> &text, ll len){
    ll prime = 1.0e9+7;
    ll x = 1;
    ll hashed = 0;
    for(ll i =0; i<len; i++,x = (x%prime*33)%prime){
       
        hashed= (hashed%prime+(((x%prime)*text[i]) % prime))%prime;
    }
    hashed = hashed % prime;
    x=x%prime;
    x/=33;
    
    hash_set[hashed]=0;
    for(int i = 1; i<=text.size()-len; i++){
        hashed = ((((hashed - text[i-1])/33 + prime) % prime) + ((x%prime)*text[i+len-1]%prime )%prime)%prime;
        if(hash_set.find(hashed)==hash_set.end())
        hash_set[hashed]=i;
    }
}

std::array<int,5> rolling_hash(std:: vector<int> &submission1, std::vector<int> &submission2){
    

    
        for(int match_len =10; match_len < std::min(submission1.size(),submission2.size()); match_len++){
            std::map<ll,ll>hash_set;

            if(match_len > submission1.size() || match_len > submission2.size()){
                return {0,0,0,0,0};
             }
            calculate_hashes(hash_set, submission1, match_len);
        
            std::pair<ll,ll> v = hashing(submission2,match_len);
            ll hashed = v.first, x= v.second;
            ll prime= 1.0e9+7;
            if(hash_set.find(hashed) != hash_set.end()){
                
                    std::cout << "Match found : len1 "<<hashed<<" "<<match_len<<" "<<0<<'\n';
                    std::cout << "Key "<<hash_set[hashed]<<'\n';

                }

            for(int i = 1; i<submission2.size()-match_len; i++){
                hashed = (((hashed - submission2[i-1])/33 + prime) % prime);
                hashed = (hashed + ((x%prime)*submission2[i+match_len-1] )%prime) %prime;
                hashed=hashed%prime;
                if(hash_set.find(hashed) != hash_set.end()){
                    std::cout << "Match found : len2 "<<match_len<<" "<<i<<'\n';
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
    std::cerr<<hashing(submission1, submission1.size()).first<<'\n';;
    std::cerr << hashing(submission2, submission2.size()).second<<'\n';
    std::array<int, 5> result = {0, 0, 0, 0, 0};
    auto A = rolling_hash(submission1, submission2);
    return result; // dummy return
    // End TODO
}

// int main(){
//     std::vector<int> submission1 = {1,2,3,258,5,6,7,8,9,10,11};
//     std::vector<int> submission2 = {1,2,3,258,5,6,7,8,9,10,12};
//     std::array<int, 5> result = match_submissions(submission1, submission2);
//     for(int i = 0; i<5; i++){
//         std::cout << result[i]<<" ";
//     }
//     std::cout << '\n';
//     return 0;
// }