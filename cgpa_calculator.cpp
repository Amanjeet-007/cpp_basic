#include <iostream>
using namespace std;

int main(){
    int num_of_subject;
    double total_points,total_credit;

    //get input from user
    cout<<"Enter Number of Subjects : "<<endl;
    cin>>num_of_subject;
    for(int i = 1 ; i <= num_of_subject; i++){
        double credit_hours;
        double grade_point;
        cout<<"Enter Your Credit Hours Of Subject "<<i<<" :";
        cin>>credit_hours;
        cout<<"Enter Your Grade Point Of Subject "<<i<<" :";
        cin>>grade_point;

    //calculation
        total_points += (grade_point*credit_hours);
        total_credit += credit_hours;
    }

    double CGPA = (total_points/total_credit);
    cout<<"Your CGPA is "<<CGPA<<endl;
    return 0;
}
