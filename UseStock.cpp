/*
Daniel O'Malley
UseStock.cpp
Date Created: 05/07/2016
CIS 2541 - Carolyn England - Intro to C++
Program #4 - Stock Sector Portfolio
Descr:
Final lab for the C++ class.
Stock program that calculates the gain and or loss of a stock portfolio.
User will input file and the program will output a record file.
Other definitions commented in
File containing main and other functions.  
*/

//begin main function

#include "Stock.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>


using namespace std;
//function prototypes
int readStockData(Stock stks[], int maxSize);
void sortStocks(Stock stks[], int size);
void calculatePortfolio(Stock stks[], int size);
string displayName(Sector s);
string displayStatus(Status st);

int readStockData(Stock stks[], int maxSize) {
	//create tokens to hold data
	string ts;
	string cn;
	int sec;
	int s;
	float pp;
	float cp;
	//create counter for "for" loop
	int i = 0;

	//prompt user for file location and open file for reading
	ifstream stockInput;
	string fileLoc;
	cout << "Enter the file location: ";
	cin >> fileLoc;
	stockInput.open(fileLoc, ios::in);

	//attempt to read file
	if (stockInput) {
		cout << "File read successfully." << endl;
	}
	else {
		cout << "Error reading file.";
		exit(-1);
	}

	for (i; i < maxSize && !stockInput.eof(); i++) {
		//read in values
		stockInput >> ts;
		getline(stockInput, cn, '#');
		stockInput >> sec;			
		stockInput >> s;
		stockInput >> pp;
		stockInput >> cp;
		//assign values
		stks[i].setTradingSymbol(ts);
		stks[i].setCompanyName(cn);
		stks[i].setSector(static_cast<Sector>(sec));
		stks[i].setNumShares(s);
		stks[i].setPurchasePrice(pp);
		stks[i].setCurrentPrice(cp);
	} 
	//close file and return number of times loop iterated
	stockInput.close();
	return i;
}

void sortStocks(Stock stks[], int size) {
	//use bubble sort to sort Stocks ascending by sector
	bool swap;
	Stock temp;
	do {
		swap = false;
		for (int i = 0; i < (size - 1); i++) {
			if (stks[i].getSector() > stks[i + 1].getSector()) {
				temp = stks[i];
				stks[i] = stks[i + 1];
				stks[i + 1] = temp;
				swap = true;
			}
		}
	} while (swap == true);
}

void calculatePortfolio(Stock stks[], int size) {
	//create filename for the save file
	string filename;
	ofstream stockFile;
	cout << "Enter the filename for the report:";
	cin >> filename;
	//open file for output
	stockFile.open(filename, ios::out);
	stockFile << "Prepared Portfolio Analysis Summarized by Sector" << endl;
	stockFile << "Long Term Capital Gain Tax Rate = 0.15" << endl << endl;
	int j = 0;
	for (int i = 1; i <= 5; i++) {
		//initialize token for sector gain and setor tax to zero
		float sectorGain = 0;
		float sectorTax = 0;
		/*	Format and output results
			using i to represent number of sectors and using j to represent number of Stock
			objects in array.
		*/
		stockFile << setw(10) << left << "Symbol" << setw(40) << left << " Company" << setw(10) << right << "Status" << endl;
		stockFile << setw(10) << left << "======" << setw(40) << left << " =======" << setw(10) << right << "======" << endl;
		while (stks[j].getSector() == (i * 10)){
			stockFile << setw(10) << left << stks[j].getTradingSymbol() << setw(40) << left  << stks[j].getCompanyName() << setw(10) << left << displayStatus(stks[j].currStatus()) << endl;
			if (stks[j].currStatus() == GAIN) {
				sectorGain += stks[j].gainAmt();
				sectorTax += stks[j].taxGainAmt();
			}
			j++;
		}
		stockFile << "\n";
		stockFile << setw(35) << right << "Summary for sector:" << setw(15) << right << displayName(stks[j - 1].getSector()) << endl;
		stockFile << setw(35) << right << "Gain amount:" << setw(15) << fixed << setprecision(2) << sectorGain << endl;
		stockFile << setw(35) << right << "Tax on gain:" << setw(15) << fixed << setprecision(2) << sectorTax << endl << endl;
	}
	stockFile.close();
	cout << "\nReport successfully generated with filename " << filename <<endl;
}

string displayName(Sector s) {
	switch (s) {
		case TECHNOLOGY: return "TECHNOLOGY";
			break;
		case HEALTH: return "HEALTH";
			break;
		case FINANCIAL: return "FINANCIAL";
			break;
		case CONSUMERGOODS: return "CONSUMER GOODS";
			break;
		case UTILITIES: return "UTILITIES";
			break;
	}
}

string displayStatus(Status st) {
	switch (st) {
		case GAIN: return "GAIN";
			break;
		case LOSS: return "LOSS";
			break;
		case BREAKEVEN: return "BREAKEVEN";
			break;
	}
}


void main() {
	int temp;
	const int ARR_SIZE = 25;
	Stock stockList[ARR_SIZE];

	temp = readStockData(stockList, ARR_SIZE);
	sortStocks(stockList, temp);
	calculatePortfolio(stockList, temp);
}

/*

PROGRAM OUTPUT:
	CONSOLE OUTPUT:
	Enter the file location: C:\Users\Cryogen\Desktop\P4_TEST.txt
	File read successfully.
	Enter the filename for the report:P4_Report

	Report successfully generated under P4_Report
	Press any key to continue . . .

	FILE OUTPUT:
	Prepared Portfolio Analysis Summarized by Sector
	Long Term Capital Gain Tax Rate = 0.15

	Symbol     Company                                    Status
	======     =======                                    ======
	CA         CA Inc                                 BREAKEVEN
	SYMC       Symantec Corp                          LOSS
	TWTR       Twitter Inc                            GAIN

	Summary for sector:     TECHNOLOGY
	Gain amount:          29.40
	Tax on gain:           4.41

	Symbol     Company                                    Status
	======     =======                                    ======
	JNJ        Johnson & Johnson                      GAIN
	LLY        Eli Lilly and Company                  GAIN
	RPTP       Raptor Pharmaceutical Corp             BREAKEVEN

	Summary for sector:         HEALTH
	Gain amount:          23.81
	Tax on gain:           3.57

	Symbol     Company                                    Status
	======     =======                                    ======
	BAC        Bank of America Corp                   LOSS
	WFC        Wells Fargo & Co                       BREAKEVEN
	V          Visa                                   LOSS

	Summary for sector:      FINANCIAL
	Gain amount:           0.00
	Tax on gain:           0.00

	Symbol     Company                                    Status
	======     =======                                    ======
	RDEN       Elizabeth Arden Inc                    LOSS
	AVP        Avon Products Inc                      BREAKEVEN
	COH        Coach Inc                              GAIN

	Summary for sector: CONSUMER GOODS
	Gain amount:          35.20
	Tax on gain:           5.28

	Symbol     Company                                    Status
	======     =======                                    ======
	EIX        Edison International                   BREAKEVEN
	HE         Hawaiian Electric Industries Inc       GAIN
	POR        Portland General Electric              LOSS

	Summary for sector:      UTILITIES
	Gain amount:         156.20
	Tax on gain:          23.43


*/