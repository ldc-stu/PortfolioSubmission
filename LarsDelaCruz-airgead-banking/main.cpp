#include <string>
#include <iostream>
#include "DataInput.h"
#include "Calculations.h"
#include "ReportGenerator.h"
#include "InvestmentInfo.h"

using namespace std;

void startApp() {
    bool restart = true;

    try {
        do {
            // Prompt user input
            DataInput userData;
            userData.promptUser();

            Calculations calculations;
            InvestmentInfo acctWithNoMonthlyDep = calculations.calculateAnnualInvestment(userData);
            InvestmentInfo acctWithMonthlyDep = calculations.calculateAnnualInvestment(userData, true);

            ReportGenerator balanceAndInterestReport;
            balanceAndInterestReport.reportGenerator(acctWithNoMonthlyDep, acctWithMonthlyDep);

            // Prompt user to continue or exit
            restart = balanceAndInterestReport.additionalSessionCheck();
        } while (restart);
    }
    catch (runtime_error& except) {
        cout << "Something went wrong." <<  except.what() << endl;
    }
}

int main() {

    startApp();

    return 0;
}
