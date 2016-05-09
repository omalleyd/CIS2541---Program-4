/*
Daniel O'Malley
StockSectorPortfolio.cpp
Date Created: 05/02/2016
CIS 2541 - Carolyn England - Intro to C++
Program #4 - Stock Sector Portfolio
Descr:
Final lab for the C++ class.
Stock program that calculates the gain and or loss of a stock portfolio.
User will input file and the program will output a record file. 
Other definitions commented in
*/


#include "Stock.h"
const float Stock::LT_GAIN_TAX = .15;

//default constructor
Stock::Stock() {
	tradingSymbol = "";
	companyName = "";
	sector;
	shares = 0;
	purchasePrice = 0;
	currentPrice = 0;
}

//parameter constructor
Stock::Stock(string ts, string cn, Sector sec, int s, float pp, float cp){
	tradingSymbol = ts;
	companyName = cn;
	sector = sec;
	shares = s;
	purchasePrice = pp;
	currentPrice = cp;
}

//copy constructor
Stock::Stock(const Stock& s) {
	tradingSymbol = s.tradingSymbol;
	companyName = s.companyName;
	sector = s.sector;
	shares = s.shares;
	purchasePrice = s.purchasePrice;
	currentPrice = s.currentPrice;
}

//destructor
Stock::~Stock() {};

//mutators -- SETTERS
void Stock::setTradingSymbol(string ts) {
	tradingSymbol = ts;
}

void Stock::setCompanyName(string cn) {
	companyName = cn;
}

void Stock::setSector(Sector sec) {
	sector = sec;
}

void Stock::setNumShares(int s) {
	shares = s;
}
void Stock::setPurchasePrice(float pp){
	purchasePrice = pp;
}

void Stock::setCurrentPrice(float cp) {
	currentPrice = cp;
}

/*
		ACCESSORS ARE DECLARED INLINE
*/

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

float Stock::currValue() {
	return (static_cast<float>(getNumShares()) * getCurrentPrice());
}

Status Stock::currStatus() {
	if (getCurrentPrice() > (getPurchasePrice() + .05))
		return GAIN;
	else if (getCurrentPrice() < getPurchasePrice() - .05)
		return LOSS;
	else
		return BREAKEVEN;
}

float Stock::gainAmt() {
	if (currStatus() == GAIN)
		return ((getCurrentPrice() - getPurchasePrice()) * static_cast<float>(getNumShares()));
	else 
		return 0.0;
}

float Stock::taxGainAmt() {
	if (gainAmt() > 0)
		return (gainAmt() * LT_GAIN_TAX);
	else
		return 0.0;
}

Stock& Stock::operator= (const Stock& rhs) {
	tradingSymbol = rhs.tradingSymbol;
	companyName = rhs.companyName;
	sector = rhs.sector;
	shares = rhs.shares;
	purchasePrice = rhs.purchasePrice;
	currentPrice = rhs.currentPrice;
	return *this;
}