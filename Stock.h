/*
Daniel O'Malley
Stock.h
Date Created: 05/02/2016
CIS 2541 - Carolyn England - Intro to C++
Program #4 - Stock Sector Portfolio
Descr:
Final lab for the C++ class.
Stock program that calculates the gain and or loss of a stock portfolio.
User will input file and the program will output a record file.
Other definitions commented in
*/
#include <iostream>

using namespace std;

#ifndef STOCK_H
#define STOCK_H

enum Sector { TECHNOLOGY = 10, HEALTH = 20, FINANCIAL = 30, CONSUMERGOODS = 40, UTILITIES = 50 };
enum Status { GAIN, LOSS, BREAKEVEN };

class Stock {
private:
	string tradingSymbol, companyName;
	Sector sector;
	int shares;
	float purchasePrice, currentPrice;
public:
	static const float LT_GAIN_TAX; //public static named constant
	//constructors
	Stock();
	Stock(string, string, Sector, int, float, float);
	Stock(const Stock&);
	//destructor
	~Stock();
	//mutators
	void setTradingSymbol(string);
	void setCompanyName(string);
	void setSector(Sector);
	void setNumShares(int);
	void setPurchasePrice(float);
	void setCurrentPrice(float);
	//Accessors - Inline declaration  
	string getTradingSymbol() const { return tradingSymbol; }
	string getCompanyName() const { return companyName; }
	Sector getSector() { return sector; }
	int getNumShares() { return shares; }
	float getPurchasePrice() const { return purchasePrice; }
	float getCurrentPrice() const { return currentPrice; }

	/**********************************************************************************************************************************************
	 * Public Methods:
	 * • CurrValue Returns the current value of the stock (Number of Shares * Current Price)
	 * • CurrStatus Returns enumerated type of GAIN, LOSS, or BREAKEVEN depending upon whether stock has GAIN (current price is greater
	 *   than purchase price plus 5 cents), LOSS (current price is less than purchase price minus 5 cents), or BREAKEVEN (current
	 *   price is within plus or minus 5 cents of purchase price)
	 * • GainAmt If Status method returns GAIN, calculate and return amount of gain, otherwise return 0.0. The gain of a stock is calculated as
	 *   number of shares times the difference between the current and purchase price.
	 * • TaxGainAmt If GainAmt method returns non-negative number, calculate and return calculated tax on gain amount using long term capital gain
	 *   tax rate, otherwise return 0.0. Use a Stock class public static named constant for the long term capital gain tax rate which is 15%.
	 **********************************************************************************************************************************************/
	float currValue();
	Status currStatus();
	float gainAmt();
	float taxGainAmt();

	//overload = operator for bubble sort
	Stock& operator= (const Stock& rhs);
};

#endif