#include <iostream>
using namespace std;

void pointsCalculatedforOne(int &points, int level, int softDropAmount){

    int currentPoints;
        
    currentPoints = 40 * (level + 1);

    points = currentPoints + points;

    points = points + softDropAmount;

    //we can delete this or the last cout in main
    cout << "Current points is " << points << endl;
}

void pointsCalculatedforTwo(int &points, int level, int softDropAmount){

    int currentPoints;
        
    currentPoints = 100 * (level + 1);

    points = currentPoints + points;

    points = points + softDropAmount;

    //we can delete this or the last cout in main
    cout << "Current points is " << points << endl;
}

void pointsCalculatedforThree(int &points, int level, int softDropAmount){

    int currentPoints;
        
    currentPoints = 300 * (level + 1);

    points = currentPoints + points;

    points = points + softDropAmount;

    //we can delete this or the last cout in main
    cout << "Current points is " << points << endl;
}

void pointsCalculatedforFour(int &points, int level, int softDropAmount){

    int currentPoints;
        
    currentPoints = 1200 * (level + 1);

    points = currentPoints + points;

    points = points + softDropAmount;

    //we can delete this or the last cout in main
    cout << "Current points is " << points << endl;
}

main(){

    int points = 0;
    int& check = points;
    int level = 0;
    int softDropAmount = 0;
    int lineclear = 0;
    int n = 1;

    while(n != 0){

        cout << "start loop(press -1 to exit)" << endl;
        cin >> n;

        if(n == -1){

            break;
        }

        cout << "What level are you on?" << endl;
        cin >> level;

        cout << "lines cleared" << endl;
        cin >> lineclear;

        cout << "soft drop" << endl;
        cin >> softDropAmount;

        if(lineclear == 1){

            pointsCalculatedforOne(check, level, softDropAmount);

        }else if(lineclear == 2){

            pointsCalculatedforTwo(check, level, softDropAmount);

        }else if(lineclear == 3){

            pointsCalculatedforThree(check, level, softDropAmount);

        }else if(lineclear == 4){

            pointsCalculatedforFour(check, level, softDropAmount);
            
        }

    }
        //we can delete this or the cout in the methods
        cout << "Final points " << check << endl;
}