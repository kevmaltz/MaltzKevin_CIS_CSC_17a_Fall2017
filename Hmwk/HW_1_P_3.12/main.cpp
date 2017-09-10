/* 
 * File  : main.cpp
 * Author: Kevin Maltz
 * Created on September 9, 2017, 2:11 PM
 */
/******************************************************************************
 * REPORT MONTHLY SALES TAX
 * ___________________________________________________________________________
 * This program asks the user for the month, year and total amount collected. 
 * The total, county, and state sales tax are then calculated based on stored
 * values for the respective tax rates. The information is then output in a
 * formatted report.
 * Ex.
 * 
 * Month:  October
 * ------------------------------
 * Total Collected : $24783.57
 * Sales           : $23380.73
 * County Sales Tax: $467.61
 * State Sales Tax : $935.23
 * Total sales Tax : $1402.84
 * ___________________________________________________________________________
 * INPUT
 *     month                    :Holds the month for the sales reported
 *     total                    :Total $ amount collected in the month
 *     year                     :Year of sales being reported
 * 
 * OUTPUT
 *     cntyTax                  :Holds the $ amount of county tax collected
 *     sales                    :Holds the raw sales amount for the month
 *     stTax                    :Holds the $ amount of state tax collected
 * 
 * CONSTANTS
 *     CT_RT                    :Holds the county tax rate as a decimal value
 *     ST_RT                    :Holds the state tax rate as a decimal value
 * ___________________________________________________________________________
 * EQUATION(S) USED
 *  
 *      sales = total / ( 1 + state tax rate + county tax rate )
 *      
 *      county tax = sales * county tax rate
 * 
 *      state tax = sales * state tax rate
 * 
 *      total tax = total - sales
 *      
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() 
{
    /**********************************************************************
     * CONSTANTS
     * --------------------------------------------------------------------
     * CNTY_RT                  :County tax rate in decimal form
     * ST_RT                    :State tax rate in decimal form
     **********************************************************************/
    const float CNTY_RT = 0.02;
    const float ST_RT = 0.04;
    
    //Variables
    string month;               //Sale month
    short year;                 //Sale year
    float cntyTax;              //$ amount of county sales tax paid
    float sales;                //Sales for the month, no tax included
    float stTax;                //$ amount of state sales tax paid
    float total;                //Total amount collected. Sales + sales tax
    
    //Input
    cout << "Enter sales month being reported (ex. January): ";
    cin >> month;
    cout << endl << "Enter Year: ";
    cin >> year;
    cout << endl << "Enter total amount collected(Sales + sales tax): ";
    cin >> total;
    

    //calculate sales and tax separately
    sales = total / ( 1 + ST_RT + CNTY_RT);
    stTax = sales * ST_RT;
    cntyTax = sales * CNTY_RT;
    
    //Format and Output
    cout << endl << endl;
    cout << showpoint << fixed << setprecision(2) << left;
    cout << "Month:  " << month << endl;
    cout << "------------------------------" << endl;
    cout << setw(16) << "Total Collected" << ": $" << total << endl;
    cout << setw(16) << "Sales" << ": $" << sales << endl;
    cout << setw(16) << "County Sales Tax" << ": $" << cntyTax << endl;
    cout << setw(16) << "State Sales Tax" << ": $" << stTax << endl;
    cout << setw(16) << "Total sales Tax" << ": $" << total - sales << endl;
    
    return 0;
}

