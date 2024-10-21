#include <iostream>
using namespace std;

int main() {
    // Write C++ code here
    double gross_sales;
    double gross_expenses;
    double net_profit;
    double Tax;
    double tax_percent = 0.12 ; // default on 12% tax
    std::cout <<"Enter Your Total Sales: ";
    std::cin  >> gross_sales;
    if(gross_sales <= 0 ){
        std::cout << "sales can't be 0. Enter valid number";
        std::cin  >> gross_sales;
    }
    else{
         std::cout <<"Enter Your Total Expenses: ";
         std::cin  >> gross_expenses;
         if(!gross_expenses){
             std::cout<<"Please Enter valid Expenses";
             std::cin  >> gross_expenses;
         }
         else{
             net_profit = gross_sales - gross_expenses ;
             Tax = net_profit * tax_percent;
             std::cout<<"Your Total Profit: "<<net_profit<<"\nYou have to pay Tax: "<<Tax;
         }
    }

    return 0;
}