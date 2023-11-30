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
    int moves=0;
    double avg_moves=0;
    int n_iterations=100;
    for(int iteration=0;iteration<n_iterations;iteration++){
        
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
        int moves=0;
        int n_win=alln[rand()%alln.size()];
        cout<<"try to guess "<<n_win<<"  ";
        int bestnum=start_num;
        int check_perfect=0, check_good=0, check_no=4;
        int a1,a2,b1,b2,c1,c2,d1,d2;
        string check="";

        while(true){
            cout<<".";
            num = bestnum;
            //compute hint
            check="";
            check_perfect=0;
            check_good=0;
            check_no=4;
            
            int a1=n_win/1000;
            int b1=(n_win/100)%10;
            int c1=(n_win/10)%10;
            int d1=n_win%10;

            
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
            hint=check;
            //cout<<num<<" "<<hint<<endl;//todo remove
            if(hint=="vvvv") break;
            //exit if guessed correctly or num==0

            //start checking all remaining possible numbers and remove the ones that are not consistent with the current guess number+hint
            int size=choices.size();
            int removed=0;
            check_perfect=0; check_good=0; check_no=4;
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
            //print_chioces(choices);
            //cout<<endl<<"possible numbers: "<<size<<endl;

            //Find the best next number to guess, wich would maximize the information gained (would remove the most number of remaining choices)

            //store in allh all the possible hints (xxxx,oxxx,ooxx ...)
            vector<string> allh;
            string s="";
            int p=0,g=0,n=0;
            for(int p=0;p<=4;p++){
                for(int g=0;g+p<=4;g++){
                    n=4-p-g;
                    for(int k=0;k<p;k++){
                        s+="v";
                    }
                    for(int k=0;k<g;k++){
                        s+="o";
                    }
                    for(int k=0;k<n;k++){
                        s+="x";
                    }
                    allh.push_back(s);
                    s="";
                }
            }

            
            int bestval=0;
            bestnum=0;
            int alln_size=alln.size();
            int allh_size=allh.size();
            vector<int> c_choices;
            //for each possible number to be the next guess
            for(int z=0;z<alln_size;z++){
                double avg=0,avg_count=0;
                //for each possible hint that could be retured from that guess
                for(int v=0;v<allh_size;v++){
                    //compute, as before (using a copy of the choices vector) the number of remaining choices
                    c_choices=choices;

                    int size=c_choices.size();
                    removed=0;
                    string check="";
                    int check_perfect=0, check_good=0, check_no=4;
                    int a1,a2,b1,b2,c1,c2,d1,d2;
                    for(int i=0;i<size-removed;i++){
                        check="";
                        check_perfect=0;
                        check_good=0;
                        check_no=4;
                        int a1=c_choices[i]/1000;
                        int b1=(c_choices[i]/100)%10;
                        int c1=(c_choices[i]/10)%10;
                        int d1=c_choices[i]%10;

                        int a2=alln[z]/1000;
                        int b2=(alln[z]/100)%10;
                        int c2=(alln[z]/10)%10;
                        int d2=alln[z]%10;

                        //check perfects
                        check_perfect+=(a1==a2)+(b1==b2)+(c1==c2)+(d1==d2);
                        check_no-=check_perfect;
                        //check good
                        check_good+=(a1==b2||a1==c2||a1==d2)+(b1==a2||b1==c2||b1==d2)+(c1==a2||c1==b2||c1==d2)+(d1==a2||d1==b2||d1==c2);
                        check_no-=check_good;
                        for(int k=0;k<check_perfect;k++){
                            check+="v";
                        }
                        for(int k=0;k<check_good;k++){
                            check+="o";
                        }
                        for(int k=0;k<check_no;k++){
                            check+="x";
                        }

                        if(allh[v]!=check){
                            removed++;
                            c_choices.erase(c_choices.begin()+i);
                            i--;
                        }
                    }

                    //the pair (number to be next guess, hint retured) is valid only if not all choices are deleted
                    if(removed!=size){ 
                        avg+=removed;
                        avg_count++;
                    }
                }
                //for each possible number take the average of the number of removed possible choices for all possible hint retured. This average tells you an estimation of how many removed choices you will probably get.
                avg=avg/avg_count;

                //if the number of removed choices is better than the best one so far, save this number as the best to be the next guess
                if(avg>bestval){
                    bestval=avg;
                    bestnum=alln[z];
                }
                //if the number of removed choices is not better, but equal to the best one so far, check if it could be the number to guess (it is still in the remaining choices). If this is the case, use it as the best number to be the next guess, because there is a little probablity that it's the number to guess and you win.
                if(avg==bestval){
                    bool is_in_choices=false;
                    for(int is_in=0;is_in<choices.size()&&!is_in_choices;is_in++){
                        if(alln[z]==choices[is_in]){
                            bestval=avg;
                            bestnum=alln[z];
                            is_in_choices=true;
                        }
                    }
                }
            }

            //if you have only one remaining number, the guess that number, is the winning one.
            if(choices.size()==2) bestnum=choices[0];
            moves++;
        }
        moves++;
        avg_moves+=moves;
        if(moves==4) cout<<'\t';
        cout<<'\t'<<"solved in "<<moves<<" moves"<<endl;
    }
    avg_moves=avg_moves/n_iterations;
    cout<<"average moves to solve: "<<avg_moves<<endl;
    return 0;
}