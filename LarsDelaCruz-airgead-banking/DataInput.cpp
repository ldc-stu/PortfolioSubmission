//
// Lars Dela Cruz 10/1/21.
//
#include <iostream>
#include <vector>
#include "DataInput.h"

using namespace std;

// Default constructor
DataInput::DataInput() {
    DataInput::m_userPrompts = {
        "Initial Investment Amount:  ",
                "Monthly Deposit:  ",
                "Annual Interest:  ",
                "Number of Years:  "
    };
};

const vector<string> &DataInput::getMUserPrompts() const {
    return m_userPrompts;
}

double DataInput::getMInitialInvestAmt() const {
    return m_initialInvestAmt;
}

void DataInput::setMInitialInvestAmt(double t_initialInvestAmt) {
    m_initialInvestAmt = t_initialInvestAmt;
}

double DataInput::getMMonthlyDep() const {
    return m_monthlyDep;
}

void DataInput::setMMonthlyDep(double t_monthlyDep) {
    m_monthlyDep = t_monthlyDep;
}

double DataInput::getMAnnualInt() const {
    return m_annualInt;
}

void DataInput::setMAnnualInt(double t_annualInt) {
    m_annualInt = t_annualInt;
}

double DataInput::getMNumYears() const {
    return m_numYears;
}

void DataInput::setMNumYears(double t_numYears) {
    m_numYears = t_numYears;
}

void DataInput::printHeader() {
    cout << string(36, '*') << endl;
    cout << string(12, '*') << " Data Input " << string(12, '*') << endl;
}

/**
 *user input and set class members
 */
void DataInput::promptUser() {
    vector<double> depositDetails;
    char quitCmd = 'a';  

    while (quitCmd != 'q') {

        try {
            depositDetails.clear();
            printHeader();
            depositDetails = inputCapture();

        }
        catch (invalid_argument& except) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << except.what() << endl;
        }

        if (depositDetails.size() == 4 && enterCheck()) {
            setMInitialInvestAmt(depositDetails.at(0));
            setMMonthlyDep(depositDetails.at(1));
            setMAnnualInt(depositDetails.at(2));
            setMNumYears(depositDetails.at(3));

            quitCmd = 'q';
        }
    }
}


vector<double> DataInput::inputCapture() {
    vector<double> responses;
    vector<string> prompts = getMUserPrompts();

    for (int i = 0; i < prompts.size(); ++i) {
        string prompt = prompts.at(i);
        double userInput;
        cout << prompt;
        cin >> userInput;

        // Check for valid user input
        if (!cin || userInput < 0.01) {
            throw invalid_argument("\n\nAlphabetical characters and amounts less than .01 not allowed. \n\n"
            "Please try again.\n\n");
        }

        // Add user input to our vector
        responses.push_back(userInput);
    }
    return responses;
}

/**
 * validate specific key presses
 */
bool DataInput::enterCheck() {
    cout << "Press enter to continue . . .\n\n\n";
    return cin.get() == '\n';
}
