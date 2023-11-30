#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

/*notation: 
perfect means 'v', a digit is in the right place
good means 'o', a digit is in the wrong place
no means 'x', a digit is not in the number to guess
*/

//print all possible remaining choices for the number to guess
void print_chioces(vector<int>& choices){
    int size=choices.size();
    for(int i=0;i<size;i++){
        cout<<choices[i]<<'\t';
    }
}

int main()
{
    //store all the possible choices for the number to guess
    vector<int> choices;

    //initialize all possible numbers
    for(int a=1;a<=9;a++){
        for(int b=0;b<=9;b++){
            if(a==b) continue; //skip on repeated digits
            for(int c=0;c<=9;c++){
                if(c==a || c==b) continue; //skip on repeated digits
                for(int d=0;d<=9;d++){
                    if(d==a || d==b || d==c) continue; //skip on repeated digits
                    choices.push_back(a*1000+b*100+c*10+d);
                }     
            }
        }
    }
    //generate a random number for the first guess
    srand (time(NULL));
    int start_num=choices[rand() % choices.size()];

    //store all possible numbers
    vector<int> alln;
    for(int a=1;a<=9;a++){
        for(int b=0;b<=9;b++){
            if(a==b) continue;
            for(int c=0;c<=9;c++){
                if(c==a || c==b) continue;
                for(int d=0;d<=9;d++){
                    if(d==a || d==b || d==c) continue;
                    alln.push_back(a*1000+b*100+c*10+d);
                }     
            }
        }
    }

    //num is the number of the current guess, hint is it's corresponding hint code (how many prefect, good and wrong digits are there)
    int num=1;
    string hint="xxxx";
    cout<<"write 0 to exit, write hint in style of: vvox"<<endl;
    cout<<"random start: "<<start_num<<endl;
    while(true){
        //receive a new guess from user
        cout<<"number: ";
        cin>>num;
        if(num==0) break;
        cout<<"hint: ";
        cin>>hint;
        if(hint=="vvvv") break;
        //exit if guessed correctly or num==0

        //start checking all remaining possible numbers and remove the ones that are not consistent with the current guess number+hint
        int size=choices.size();
        int removed=0;
        string check="";
        int check_perfect=0, check_good=0, check_no=4;
        int a1,a2,b1,b2,c1,c2,d1,d2;
        for(int i=0;i<size-removed;i++){
            check="";
            check_perfect=0;
            check_good=0;
            check_no=4;
            //current choice to compare is a1b1c1d1
            int a1=choices[i]/1000;
            int b1=(choices[i]/100)%10;
            int c1=(choices[i]/10)%10;
            int d1=choices[i]%10;

            //current guess number is a2b2c2d2
            int a2=num/1000;
            int b2=(num/100)%10;
            int c2=(num/10)%10;
            int d2=num%10;

            //check how many perfects digits are there
            check_perfect+=(a1==a2)+(b1==b2)+(c1==c2)+(d1==d2);
            check_no-=check_perfect;
            //check how many good digits are there
            check_good+=(a1==b2||a1==c2||a1==d2)+(b1==a2||b1==c2||b1==d2)+(c1==a2||c1==b2||c1==d2)+(d1==a2||d1==b2||d1==c2);
            check_no-=check_good;
            //compute the hint string in the case the guessed number is the possible choice we are comparing
            for(int k=0;k<check_perfect;k++){
                check+="v";
            }
            for(int k=0;k<check_good;k++){
                check+="o";
            }
            for(int k=0;k<check_no;k++){
                check+="x";
            }
            //if the just computed hint is different from the actual one give by the user, the current choice cannot be the number to guess: remove it from the vector of possible choices
            if(hint!=check){
                removed++;
                choices.erase(choices.begin()+i);
                i--;
            }
        }

        //print all remaining choices and say how many are there
        size=choices.size();
        print_chioces(choices);
        cout<<endl<<"possible numbers: "<<size<<endl;

    }
  
  return 0;
}