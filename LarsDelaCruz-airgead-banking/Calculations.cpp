//
// Lars Dela Cruz 10/1/21.
//
#include <vector>
#include <iostream>
#include "Calculations.h"
#include "InvestmentInfo.h"

using namespace std;

const long MAX_AMOUNT = 9999999999999999;

// Default constructor
Calculations::Calculations() {}

/*
 *User input and builds InvestmentInfo object
 */
InvestmentInfo Calculations::calculateAnnualInvestment(DataInput& t_userData, bool t_monthlyDep) {
    double openAmt =  t_userData.getMInitialInvestAmt();
    double depAmt =  t_userData.getMMonthlyDep();
    int intRate =  t_userData.getMAnnualInt();
    int numYears =  t_userData.getMNumYears();
    vector<int> years;
    vector<vector<double>> yearEndBals;

    //object to store data
    InvestmentInfo investmentDetails;

    try {

        for (int i = 0; i < numYears; ++i) {
            years.push_back(i + 1);
        }

        if (t_monthlyDep == false) {
            // Calculate without monthly deposit
            yearEndBals = annualBalWithInt(openAmt, 0, intRate, numYears);
        } else {
            // Calculate with monthly deposits
            yearEndBals = annualBalWithInt(openAmt, depAmt, intRate, numYears);
        }

        investmentDetails.setMYears(years);
        investmentDetails.setMYearEndEarnedInterests(yearEndBals.at(0));
        investmentDetails.setMYearEndBalances(yearEndBals.at(1));

        return investmentDetails;
    }
    catch (runtime_error& except) {
        cout << except.what() << endl;
    }

}

/*
 * Calculate annual account balance and earned interest
 */
vector<vector<double>> Calculations::annualBalWithInt(double t_openAmount, double t_depositAmount, int t_intRate, int t_years) {
    vector<vector<double>> balanceAndInts;
    vector<double> annualInterestOnly;
    vector<double> annualBalWithInterest;
    double newBal;
    double yearEndInt;
    double precIntRate = (t_intRate/100.00)/12.00;
    double intTracker = 0;
    double intOnly = 0;

    for (int i = 0; i < (t_years * 12); ++i) {
        yearEndInt += ((intTracker + t_openAmount) + (t_depositAmount * (i+1))) * precIntRate;
        intTracker = yearEndInt;
        if (((i+1) % 12) == 0) {
            annualInterestOnly.push_back(yearEndInt - intOnly); 
            intOnly = yearEndInt;
            newBal = t_openAmount + (t_depositAmount * (i+1)) + yearEndInt; 
            annualBalWithInterest.push_back(newBal);
        }
    }

    if (newBal > MAX_AMOUNT ) {
        throw runtime_error("Unable to complete calculation. Amount too large.");
    }

    balanceAndInts.push_back(annualInterestOnly); 
    balanceAndInts.push_back(annualBalWithInterest); 

    return balanceAndInts;
}











