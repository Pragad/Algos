/*
 * By Pragadheeshwaran Thirumurthi
 *
 * Compile:
 * g++ -std=c++11 BloombergCodingProblem.cpp
 *
 * Input 1:
   1|EURUSD|Bank1|1.1|1.2
 *
 * Input 2:
   1|EURUSD|Bank1|1.1|1.2
   2|EURUSD|Bank2|1.1|1.15
 *
 * Input 3:
   1|EURUSD|Bank1|1.1|1.2
   2|EURUSD|Bank2|1.1|1.15
   3|EURUSD|Bank3|1.15|1.2
 *
 * Input 4:
   1|EURUSD|Bank1|1.1|1.2
   2|EURUSD|Bank1|1.0|1.3
 *
 * Input 5:
   1|EURUSD|Bank1|1.1|1.2
   2|EURUSD|Bank2|1.05|1.25
   3|EURUSD|Bank1|1.0|1.3
 *
 * Input 6:
   1|EURUSD|Bank1|1.1|1.2
   2|EURUSD|Bank2|1.05|1.25
   3|EURUSD|Bank1|1.0|1.3
   4|EURUSD|Bank3|1.5|1.5
   5|EURUSD|Bank2|1.0|1.6
   6|EURUSD|Bank2|2.0|1.0
 *
 * Input 7:
   1|EURUSD|Bank1|1.1|1.2
   2|INRUSD|Bank2|1.1|1.2
 *
 * Input 8:
   1|EURUSD|Bank1|1.1|1.2
   2|EURUSD|Bank2|1.05|1.25
   3|EURUSD|Bank1|1.0|1.3
   4|EURUSD|Bank3|1.5|1.5
   5|EURUSD|Bank2|1.0|1.6
   6|EURUSD|Bank2|2.0|1.0
   7|INRUSD|Bank5|8.0|9.0
   8|INRUSD|Bank6|9.0|9.0
   9|INRUSD|Bank5|9.0|9.0
 *
 * Input 9:
   1|EURUSD|Bank1|1.0|1.0
   2|EURUSD|Bank2|2.0|0.5
 *
 * Input 10:
   1|EURUSD|Bank1|1.0|1.0
   2|EURUSD|Bank2|0.5|0.5
 *
 * Input 11:
   1|EURUSD|Bank1|1.0|1.0
   2|EURUSD|Bank2|2.0|2.0
 *
 * Input 12:
   1|EURUSD|Bank1|1.0|1.0
   2|EURUSD|Bank2|0.5|2.0
 *
 * Input 13:
   7|INRUSD|Bank5|8.0|9.0
   8|INRUSD|Bank6|9.0|9.0
   9|INRUSD|Bank5|9.0|9.0
 *
 * Input 14:
   7|INRUSD|Bank5|8.0|9.0
   8|INRUSD|Bank6|8.0|8.0
   9|INRUSD|Bank5|8.0|8.0
 *
 * Input 15:
   1|INRUSD|Bank5|8.0|9.0
   2|USDEUR|Bank6|8.0|8.0
   3|CHFUSD|Bank7|8.0|8.0
 *
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

// Constants to print "Buy / Sell" on the output.
static const std::string BUY = "Buy";
static const std::string SELL = "Sell";

// CurrencyPair
//
// This class stores the list of bank names, buy values and sell values for a single
// Currency Pair. Index of the vectors can be used to get details about a specific bank.
//
// It stores the following data for each object.
//      _currencyPairName:  EURUSD
//      _bankNames       :  Bank1, Bank2, Bank3, .....
//      _buyValues       :  1.1,   2.2,   3.3, .....
//      _sellValues      :  1.5,   2.5,   3.5, .....
//
// _currencyPairName
//      Name of the Currency Pair
// 
// _bankNames
//      List of Bank Names offering buy sell rates for the Currency Pair
// 
// _buyValues
//      List of Buy Values offered by various banks for the Currency Pair
// 
// _sellValues
//      List of Sell Values offered by various banks for the Currency Pair
//
// getCurrencyPairName()
//      Returns the name of the Currency Pair for which we have the Buy / Sell rates from
//      various banks
//
// getBankNameAtIndex()
//      Returns the name of bank stored in a particular index
//      
// getBuyValueAtIndex()
//      Returns the Buy quote offered by a particular bank
//
// getSellValueAtIndex()
//      Returns the Sell quote offered by a particular bank
//
// pushBankName()
//      Stores a new bank name in our vector.
//
// pushBuyValue()
//      Stores the Buy quote offered by a new bank in our vector.
//
// pushSellValue()
//      Stores the Sell quote offered by a new bank in our vector.
//
// isAllVectorsSameSize()
//      At any point all the vectors should be of the same size. This function is used to
//      check that.
//
// getVectorSize()
//      This function returns the size of any of the vector to find how many entries (banks)
//      we have in the list. Note that all vectors should be of same size.
//
// removeEntryAtIndex()
//      This function removes entries corresponding to a Bank when the same bank updates
//      a new quote for Buy and Sell.
class CurrencyPair
{
private:
    std::string                 _currencyPairName;
    std::vector<std::string>    _bankNames;
    std::vector<double>         _buyValues;
    std::vector<double>         _sellValues;

public:
    CurrencyPair(std::string curName): _currencyPairName(curName) { }

    std::string getCurrencyPairName() { return _currencyPairName; }
    std::string getBankNameAtIndex(uint32_t index) { return _bankNames[index]; }
    double      getBuyValueAtIndex(uint32_t index) { return _buyValues[index]; }
    double      getSellValueAtIndex(uint32_t index) { return _sellValues[index]; }
    void        pushBankName(std::string bankName) { _bankNames.push_back(bankName); }
    void        pushBuyValue(double buyVal) { _buyValues.push_back(buyVal); }
    void        pushSellValue(double sellVal) { _sellValues.push_back(sellVal); }
    bool        isAllVectorsSameSize();
    int         getVectorSize();
    void        removeEntryAtIndex(uint32_t index);
};

// CurrencyPair::isAllVectorsSameSize()
//      This function check and tells if all the vectors are of same size. At any point
//      all vectors should have the same size.
bool CurrencyPair::isAllVectorsSameSize()
{
    return ((_bankNames.size() == _buyValues.size()) &&
            (_buyValues.size() == _sellValues.size()));
}

// CurrencyPair::isAllVectorsSameSize()
//      Since we can find if all the vectors are of same size, this function returns the
//      size of a vector.
//      If the vectors are not of same size, then -1 gets returned.
int CurrencyPair::getVectorSize()
{
    if (isAllVectorsSameSize())
    {
        return _buyValues.size();
    }
    else
    {
        return -1;
    }
}

// CurrencyPair::removeEntryAtIndex()
//      This function removes the old entries from the vector.
//      Removing entries from the vector will result in rearranging all other items.
void CurrencyPair::removeEntryAtIndex(uint32_t index)
{
    _bankNames.erase(_bankNames.begin() + index);
    _buyValues.erase(_buyValues.begin() + index);
    _sellValues.erase(_sellValues.begin() + index);
}

// Below are some utility structures for storing Buy / Sell Values and Bank names.
// BestBuyInfo
//      Structure to hold the best buy price and the corresponding bank name.
struct BestBuyInfo
{
    double buyPrice;
    std::string bankName;
};

// BestSellInfo
//      Structure to hold the best sell price and the corresponding bank name.
struct BestSellInfo
{
    double sellPrice;
    std::string bankName;
};

// myCompGreater
//      My overloaded Greater than comparator operator for storing Buy Values in descending order
struct myCompGreater
{
    bool operator() (const BestBuyInfo& buyLhs, const BestBuyInfo& buyRhs) const
    {
        return buyLhs.buyPrice > buyRhs.buyPrice;
    }
};

// myCompLesser
//      My overloaded Lesser than comparator operator for storing Sell Values in ascending order
struct myCompLesser
{
    bool operator() (const BestSellInfo& sellLhs, const BestSellInfo& sellRhs) const
    {
        return sellLhs.sellPrice < sellRhs.sellPrice;
    }
};

// populateElements()
//      This function reads the input given on the CLI and puts it into a vector
//      of objects.
//      It creates a new object if we get a new currency pair; Then it pushes the object
//      into the vector.
//      We stores the currency pair in a map.
//      If the currency pair that we are going to add already exists in the map, then we
//      just push the values to the vector.
//      The index of the vector is got from the map.
void populateElements(std::vector<std::string>      vecQuote,
                      std::vector<CurrencyPair>&    objCurPair,
                      std::unordered_map<std::string, uint32_t>& mapCurPairNames)
{
    // The name of the currency pair is stored in the First Index.
    auto mapItr = mapCurPairNames.find(vecQuote[1]);

    // If we find in the map, then we can add to the existing index. Else create a new one
    // and push it back to the Vector or objects.
    if (mapItr != mapCurPairNames.end())
    {
        // Get the index corresponding to this currency pair.
        unsigned objIdx = mapItr->second;
        objCurPair[objIdx].pushBankName(vecQuote[2]);

        // Convert the buy and sell values to double before storing it.
        objCurPair[objIdx].pushBuyValue(strtod(vecQuote[3].c_str(), NULL));
        objCurPair[objIdx].pushSellValue(strtod(vecQuote[4].c_str(), NULL));
    }
    else
    {
        // Create a new object with the name of the Currency pair
        CurrencyPair objTemp(vecQuote[1]);

        // Push the Bank Name, buy and sell values into the object's vector.
        objTemp.pushBankName(vecQuote[2]);
        objTemp.pushBuyValue(strtod(vecQuote[3].c_str(), NULL));
        objTemp.pushSellValue(strtod(vecQuote[4].c_str(), NULL));

        // Push the object to our vector.
        objCurPair.push_back(objTemp);

        // Store the index of the vector where the object got pushed into the map.
        // It is used for retrieving the vector when another bank comes for the same
        // currency pair.
        mapCurPairNames[vecQuote[1]] = (objCurPair.size() - 1);
    }
}

// printResults()
//      Utility function to print the final result
void printResults(std::string currencyPair,
                  std::string strBuyOrSell,
                  double      buyOrSellValue,
                  std::string bankName)
{
    std::cout << "Best " << currencyPair << " " << strBuyOrSell << " = " \
              << buyOrSellValue << " from " << bankName << std::endl;
}

// clearDuplicateBankNameEntries
//      This function clears the following maps.
//      1. Map that holds the buy prices
//      2. Map that holds the sell prices
void clearDuplicateBankNameEntries(CurrencyPair objCurPair,
                                   uint32_t     index,
                                   std::multiset<BestBuyInfo, myCompGreater> &buyPriceMap,
                                   std::multiset<BestSellInfo, myCompLesser> &sellPriceMap)
{
    
    // Have temporary structures that can be used as key to find in HASH map.
    BestBuyInfo tmpBuyInfo;
    BestSellInfo tmpSellInfo;

    // This Bank is already present.
    // So remove the previous entry from the vector.
    tmpBuyInfo.buyPrice = objCurPair.getBuyValueAtIndex(index);
    tmpBuyInfo.bankName = objCurPair.getBankNameAtIndex(index);

    tmpSellInfo.sellPrice = objCurPair.getSellValueAtIndex(index);
    tmpSellInfo.bankName = objCurPair.getBankNameAtIndex(index);

    auto itBuy = buyPriceMap.find(tmpBuyInfo);
    buyPriceMap.erase(itBuy);

    auto itSell = sellPriceMap.find(tmpSellInfo);
    sellPriceMap.erase(itSell);

    // Now remove the entry from the original vector. This guarentees that the vector does
    // not become too big when the same bank updates will million quotes.
    objCurPair.removeEntryAtIndex(index);
}

// findNextBestBuySellValues()
//      This function finds the best Buy / Sell value when a new bank comes in.
void findNextBestBuySellValues(uint32_t index,
                               CurrencyPair &objCurPair,
                               std::unordered_map<std::string, uint32_t> &mapBankNames,
                               std::multiset<BestBuyInfo, myCompGreater> &buyPriceMap,
                               std::multiset<BestSellInfo, myCompLesser> &sellPriceMap)
{
    // Check if the bank name has already given a quote
    std::unordered_map<std::string, uint32_t>::iterator mapItr = mapBankNames.find(objCurPair.getBankNameAtIndex(index));

    if (mapItr != mapBankNames.end())
    {
        clearDuplicateBankNameEntries(objCurPair,
                                      mapItr->second,
                                      buyPriceMap,
                                      sellPriceMap);

        // Also remove the old entry from the Name map.
        mapBankNames.erase(mapItr);
    }
   
    // Store the name of the map and the corresponding index in the map.
    mapBankNames[objCurPair.getBankNameAtIndex(index)] = index;

    buyPriceMap.emplace(BestBuyInfo{objCurPair.getBuyValueAtIndex(index),
                                    objCurPair.getBankNameAtIndex(index)});

    sellPriceMap.emplace(BestSellInfo{objCurPair.getSellValueAtIndex(index),
                                      objCurPair.getBankNameAtIndex(index)});

    // Print the results after each iteration. The results are available in the top
    // position of the buy map and the sell map.
    auto mapBestBuyItr = buyPriceMap.begin();
    auto mapBestSellItr = sellPriceMap.begin();

    printResults(objCurPair.getCurrencyPairName(),
                 BUY,
                 mapBestBuyItr->buyPrice,
                 mapBestBuyItr->bankName);

    printResults(objCurPair.getCurrencyPairName(),
                 SELL,
                 mapBestSellItr->sellPrice,
                 mapBestSellItr->bankName);
}

// findBestBuySellForACurrency()
//      This function finds the best buy and sell value for a currency pair
void findBestBuySellForACurrency(CurrencyPair objCurPair)
{
    int curPairSize = objCurPair.getVectorSize();

    // The following map stores the name of the banks. This map is used to find when
    // the same bank comes up with a new quote.
    // Every time we get a quote from a new bank, we add it to the bank.
    std::unordered_map<std::string, uint32_t>   mapBankNames;

    // These two maps perform like a Heap. 
    // Buy Price map stores the list of buy prices in descending order.
    // Sell Price map stores the list of buy prices in ascending order.
    // So the best buy price will be the top entry in the buy map. 
    // Similarly the best sell price will be the top entry in the sell map.
    //
    // Reason for adding the Heap: If we are at a BankName that is already present,
    // Then we should find the NEXT BEST BUY and SELL VALUES.
    // So we have to store things in a heap. that we can just pop out things and
    // have the best values at the top of the heap.
    std::multiset<BestBuyInfo, myCompGreater> buyPriceMap;
    std::multiset<BestSellInfo, myCompLesser> sellPriceMap;

    // Return error if no entries in the vector or if the size of each vectors are not
    // the same.
    if (curPairSize == -1 || curPairSize == 0)
    {
        std::cout<< "Error in the vector sizes" << std::endl;
        return;
    }

    // Push the first bank name to the bank name map at index 0.
    mapBankNames[objCurPair.getBankNameAtIndex(0)] = 0;

    // Push the best values to the buy and sell map.
    buyPriceMap.emplace(BestBuyInfo{objCurPair.getBuyValueAtIndex(0),
                                    objCurPair.getBankNameAtIndex(0)});
    sellPriceMap.emplace(BestSellInfo{objCurPair.getSellValueAtIndex(0),
                                      objCurPair.getBankNameAtIndex(0)});

    // Print the results.
    printResults(objCurPair.getCurrencyPairName(),
                 BUY,
                 objCurPair.getBuyValueAtIndex(0),
                 objCurPair.getBankNameAtIndex(0));

    printResults(objCurPair.getCurrencyPairName(),
                 SELL,
                 objCurPair.getSellValueAtIndex(0),
                 objCurPair.getBankNameAtIndex(0));

    // Loop over all available quotes got from the banks.
    for (uint32_t i = 1; i < curPairSize; i++)
    {
        // Find the best buy / sell value by taking the next bank's quote into consideration.
        findNextBestBuySellValues(i,
                                  objCurPair,
                                  mapBankNames,
                                  buyPriceMap,
                                  sellPriceMap);
    }
}

// iterateAllCurrencyPairs()
//      This function loops over all the available currency pairs and then find the best
//      buy and sell values for each currency pair.
void iterateAllCurrencyPairs(std::vector<CurrencyPair> vecObjCurPair)
{
    for (uint32_t i = 0; i < vecObjCurPair.size(); i++)
    {
        findBestBuySellForACurrency(vecObjCurPair[i]);
    }
}

// validateInputQuote()
//      This function checks the following.
//      1. The number of arguments in a single line is 5 (Timestamp ID, Currency Pair,
//         Bank, Buy Value, Sell Value)
//      2. Buy Value and Sell Value should be double.
//      3. Check if Timestamp ID is an integer.
//
//      It returns 'False' in case of error.
bool validateInputQuote(std::vector<std::string> quote)
{
    if (quote.size() != 5)
    {
        return false;
    }

    try
    {
         std::stoi(quote[0]);
    }
    catch(std::exception &e)
    {
        std::cout << "Invalid Integer for Timestamp" << std::endl;
        return false;
    }

    try
    {
         if (std::stod(quote[3]) < 0 ||
             std::stod(quote[4]) < 0)
         {
             return false;
         }
    }
    catch(std::exception &e)
    {
        std::cout << "Invalid Integer for Buy / Sell Value" << std::endl;
        return false;
    }

    return true;
}

int main ()
{
    // Initialization 
    //
    // In this part of the program you can perform any kind of
    // initialization routine before processing the stream 
    // of data. 
    
    std::string line;
    std::vector<std::string> quote; 
    std::string item; 

    std::unordered_map<std::string, uint32_t> mapCurPairNames;
    std::vector<CurrencyPair>                 objCurrencyPair;

    while(std::getline(std::cin, line))
    {
        if(! line.empty())
        {
            quote.clear(); 
            std::istringstream ss(line); 
            while (std::getline(ss, item, '|'))
            {
                quote.push_back(item);
            }

            // Exit from the loop in case of an error.
            if (!validateInputQuote(quote))
            {
                std::cout << "Invalid Input at Line: " << line << std::endl;
                return -1;
            }

            // Step 1: Initialize
            // A new quote has been received. You can now update 
            // your application. 
            populateElements(quote,
                             objCurrencyPair,
                             mapCurPairNames);
        }
        else
        {
            break;
        }
    }

    // Step 2: Query 
    //
    // Let's now get the best buy and sell rate 
    // for EURUSD currency pair
    iterateAllCurrencyPairs(objCurrencyPair);

    //std::cout << std::endl;
    return 0;
}

