#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int count = 0;

main(){

    srand(time(0));

    for(int i = 0; i < 5; i++){
        
        int NewRand;
        int random = rand() % 7 + 1;
        
        cout << "Random = " << random << endl;
        
        if(count != 0){
            if(random == count){

                NewRand = rand() % 7 + 1;
                cout << "Made a new rand: " << NewRand << endl;

                count = NewRand;
                
            }else{

                count = random;
            }

        }else{
            
            count = random;    
        }

        cout << "count = " << count << endl;
    }
}