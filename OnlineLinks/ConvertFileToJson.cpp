#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// ---------------------------------------------------------------------------------------
// ConvertFileToJson::
// ---------------------------------------------------------------------------------------
namespace
{
    string START_TAG = "*START ZBG*";
    string END_TAG = "*END ZBG*";
}

class ConvertFileToJson
{
private:
    string _inFileName;
    string _outFileName;
    vector<string> _inFileLines;
    vector<string> _outFileLines;

    void printVector(const vector<string>&);


public:
    ConvertFileToJson(string fileName) : _inFileName(fileName),
                                         _outFileName("ZBGoutputJSON.txt") { }
    bool convertToJson();
    bool openAndReadFile();
    bool writeOutputToFile();
};

// ---------------------------------------------------------------------------------------
// ConvertFileToJson::printVector
// ---------------------------------------------------------------------------------------
void
ConvertFileToJson::printVector(const vector<string>& dataVecs)
{
    cout << endl;

    for(vector<string>::size_type i = 0; i < dataVecs.size(); i++)
    {
        cout << dataVecs[i] << endl;
    }
    cout << endl;
}

// ---------------------------------------------------------------------------------------
// ConvertFileToJson::openAndReadFile
// ---------------------------------------------------------------------------------------
bool
ConvertFileToJson::openAndReadFile()
{
    string line;
    ifstream ifile;
    bool isStartTagSeen = false;
    bool isEndTagSeen = false;

    ifile.open(_inFileName);
    if (ifile.is_open())
    {
        while (!ifile.eof())
        {
            getline(ifile, line);
            if (line == START_TAG)
            {
                isStartTagSeen = true;
                isEndTagSeen = false;

                // We can continue as we don't want to insert the TAG
                continue;
            }
            else if (line == END_TAG)
            {
                isEndTagSeen = true;
                isStartTagSeen = false;

                // We can continue as we don't want to insert the TAG
                continue;
            }

            // We should insert lines that are only within START ZBG and END ZBG
            if (isStartTagSeen && !isEndTagSeen)
            {
                _inFileLines.push_back(line);
            }
        }

        // As we have reached the EOF, time to close the file
        ifile.close();
    }
    else
    {
        cout << "Unable to open the file" << endl;
        return false;
    }

    printVector(_inFileLines);
}

// ---------------------------------------------------------------------------------------
// ConvertFileToJson::writeOutputToFile
// ---------------------------------------------------------------------------------------
bool
ConvertFileToJson::writeOutputToFile()
{
    ofstream ofile;

    ofile.open(_outFileName);
    if (ofile.is_open())
    {
        // Write all vector lines to the file
        for (auto line : _outFileLines)
        {
            ofile << line << "\n";
        }

        // As we are done writing, close the file
        ofile.close();
    }
    else
    {
        cout << "Unable to open the file" << endl;
        return false;
    }
}

// ---------------------------------------------------------------------------------------
// ConvertFileToJson::convertToJson
// ---------------------------------------------------------------------------------------
bool
ConvertFileToJson::convertToJson()
{
    openAndReadFile();
}

// ---------------------------------------------------------------------------------------
// Main Function
// ---------------------------------------------------------------------------------------
int main()
{
    ConvertFileToJson objConvertFile("ZBGtransactions.txt");
    objConvertFile.convertToJson();

    cout << endl;
    return 0;
}
