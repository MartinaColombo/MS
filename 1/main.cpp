
//Esercizio 1.1.1 e 1.1.2


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "random.h"

using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   int M=10000;
   int N=100;
   int L=M/N;

   double r=0;
   double sum_rm=0, sum_rs=0;
   double sum_prog_rm=0, sum_prog_rs=0;
   double sum2_prog_rm=0, sum2_prog_rs=0;   
   double mean_rm=0, mean_rs=0;
   double mean2_rm=0, mean2_rs=0;
   double error_prog_rm=0, error_prog_rs=0;
          
   
   ifstream Primes("Primes");
   ofstream output;
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;
   
   
   output.open("file.dat"); 
   
   for(int i=0;i<N; i++){
     sum_prog_rm=0;
     sum_prog_rs=0;
     sum2_prog_rm=0;
     sum2_prog_rs=0;
     mean_rm=0;
     mean_rs=0;
     mean2_rm=0;
     mean2_rs=0;
      for(int j=1; j<=i; j++){
        sum_rm=0;
        sum_rs=0;
        for(int k=0; k<L; k++){
          r=rnd.Rannyu();
          sum_rm+=r;
          sum_rs+=(r-0.5)*(r-0.5);
        }
      sum_prog_rm+=(sum_rm/L);
      sum2_prog_rm+=(sum_rm/L*sum_rm/L);
     
      sum_prog_rs+=(sum_rs/L);
      sum2_prog_rs+=(sum_rs/L*sum_rs/L);     
      
      }
      mean_rm=sum_prog_rm/(i+1);
      mean2_rm=sum2_prog_rm/(i+1);
     
      mean_rs=sum_prog_rs/(i+1);
      mean2_rs=sum2_prog_rs/(i+1);
      
      if(i==0){
        error_prog_rm=0;
        error_prog_rs=0;
      }
      else{
        error_prog_rm=sqrt((mean2_rm-mean_rm*mean_rm)/(i));
        error_prog_rs=sqrt((mean2_rs-mean_rs*mean_rs)/(i));
      }
      
      output<<i<<" "<<mean_rm<<" "<<error_prog_rm<<" "<<mean_rs<<" "<<error_prog_rs<<endl;
     
   }  
      
   output.close();
   
   
   
   /**************************************************************************************************/
   //Esercizio 1.1.3
   //Calcolo del chi quadro
   
   
   int tries=pow(10,2);
   N=pow(10,4);
   M=pow(10,2);
   vector<int> m(M);
   int chi=0;
   double inf=0, sup=0;
   
   output.open("chi_square.dat");
   for(int k=0; k<tries; k++){
     for(int i=0; i<N; i++){
       r=rnd.Rannyu(); 
         for(int j=0; j<M; j++){
           inf=(j*1./M);
           sup=((j+1)*1./M);
           if(r>=inf && r<sup){
             m[j]+=1;           
           }        
         }     
     }     
     for(int l=0; l<M; l++){
       chi+=(m[l]-(N/M))*(m[l]-(N/M))/(N/M);
     }  
     output<<k<<" "<<chi<<endl;   
     fill(m.begin(), m.end(), 0); 
     chi=0;  
     //cout<<endl<<endl;   
   }
   
   output.close(); 
   
   
   rnd.SaveSeed();
   return 0;
}
