#include <bits/stdc++.h>
using namespace std;

string getRandomString(int len)
{

    string randomString = "";

    for (int i = 0; i < len; i++)
    {
        randomString += ((rand() >> 1) & 1 ? '0' : '1');
    }

    return randomString;
}

string performXOR(const string &stringOP1, const string &stringOP2)
{

    int commonLength = stringOP1.size();
    string resultXOR = "";

    for (int i = 1; i < commonLength; i++)
    {
        resultXOR += (stringOP1[i] != stringOP2[i] ? '1' : '0');
    }

    return resultXOR;
}

string getRemainder(const string &dataBlock, const string &patternCRC)
{

    int patternSize = patternCRC.size(), dataSize = dataBlock.size();
    string resultRem;
    string currDividend = dataBlock.substr(0, patternSize);

    for (int i = patternSize - 1; i < dataSize; i++)
    {

        if (currDividend[0] == patternCRC[0])
        {
            currDividend = performXOR(currDividend, patternCRC);
        }
        else
        {
            currDividend = currDividend.substr(1, patternSize - 1);
        }

        if (i + 1 < dataSize)
        {
            currDividend += dataBlock[i + 1];
        }
    }

    resultRem = currDividend;
    return resultRem;
}

string generateTransmissionFrame(const string &dataBlock, const string &patternCRC)
{

    string transmissionFrame = dataBlock, dataBlockWithZeros = dataBlock;
    int patternSize = patternCRC.size();

    for (int i = 0; i < patternSize - 1; i++)
    {
        dataBlockWithZeros.append("0");
    }
    transmissionFrame += getRemainder(dataBlockWithZeros, patternCRC);

    return transmissionFrame;
}

string generateErrors(const string &transmissionFrame)
{
    int frameSize = transmissionFrame.size();
    int totMaxBitFlips = 1 + rand() % (frameSize - 1 + 1);
    vector<int> errorPositions;
    string frameWithError = transmissionFrame;

    for (int i = 0; i < totMaxBitFlips; i++)
    {
        errorPositions.push_back((0 + rand() % (frameSize - 1 - 0 + 1)));
    }

    for (auto &errPos : errorPositions)
    {
        frameWithError[errPos] = '1' - frameWithError[errPos] + '0';
    }

    return frameWithError;
}

bool determineValidity(const string &receivedFrame, const string &patternCRC)
{
    string resultRem = getRemainder(receivedFrame, patternCRC);
    bool isValid = true;
    cout << "Checking validity of " << receivedFrame << " with " << patternCRC << '\n';

    for (auto &remBit : resultRem)
    {
        if (remBit != '0')
        {
            isValid = false;
            break;
        }
    }

    if (!isValid)
    {
        cout << "Non-zero remainder obtained. " << resultRem << " So the received frame is invalid! Hence it is discarded\n";
    }
    else
    {
        cout << "The received frame is valid! Hence accepted\n";
    }
    return isValid;
}

int main()
{
    srand(time(0));
    string userChoice = "0";
    while (userChoice.size() != 1 || userChoice[0] != '3')
    {
        userChoice = "0";
        cout << "Type 1 for generating an n bit transmission frame from a random k bit datablock and a random n-k+1 bit CRC pattern\n";
        cout << "Type 2 for generating a 15 bit transmission frame from a random 10 bit datablock, introduce errors in it and check validity\n";
        cout << "Type 3 to quit\n";
        getline(cin, userChoice);
        if (userChoice == "3")
            return 0;
        else if (userChoice != "1" && userChoice != "2")
        {
            cout << "Please enter only 1, 2 or 3 \n\n";
            continue;
        }
        else if (userChoice == "1")
        {
            string userOpt = "0";
            int n = 7, k = 4;
            while (userOpt != "y" && userOpt != "n")
            {
                cout << "Do you want to give custom inputs? (Default inputs are n = 7 and k = 4) [y/n]\n";
                getline(cin, userOpt);
                if (userOpt != "y" && userOpt != "n")
                {
                    cout << "Please enter only y or n\n\n";
                    continue;
                }
            }
            if (userOpt == "y")
            {
                while (true)
                {
                    cout << "Enter the value of n\n";
                    cin >> n;
                    cout << "Enter the value of k\n";
                    cin >> k;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (n <= k || n <= 0 || k <= 0)
                    {
                        cout << "Please enter n strictly greater than k, and both positive\n\n";
                        continue;
                    }
                    else
                        break;
                }
                string dataBlock = getRandomString(k);
                string patternCRC = "0";
                while (patternCRC[0] == '0')
                {
                    patternCRC = getRandomString(n - k + 1);
                }
                string transmissionFrame = generateTransmissionFrame(dataBlock, patternCRC);
                cout << "Datablock " << dataBlock << " CRC Pattern " << patternCRC << " Transmission Frame " << transmissionFrame << '\n';
                if (determineValidity(transmissionFrame, patternCRC))
                {
                    cout << "The generated frame is valid and it generates valid CRC\n";
                }
                else
                {
                    cout << "Invalid frame and CRC generated!\n";
                }
            }
            else
            {
                cout << "Proceeding with default values n = 7 and k = 4\n";
                string dataBlock = getRandomString(k);
                string patternCRC = "0";
                while (patternCRC[0] == '0')
                {
                    patternCRC = getRandomString(n - k + 1);
                }
                string transmissionFrame = generateTransmissionFrame(dataBlock, patternCRC);
                cout << "Datablock " << dataBlock << " CRC Pattern " << patternCRC << " Transmission Frame " << transmissionFrame << '\n';
                if (determineValidity(transmissionFrame, patternCRC))
                {
                    cout << "The generated frame is valid and it generates valid CRC\n";
                }
                else
                {
                    cout << "Invalid frame and CRC generated!\n";
                }
            }
        }
        else
        {
            int n = 15, k = 10;
            string dataBlock = getRandomString(k);
            string patternCRC = "110101";
            string transmissionFrame = generateTransmissionFrame(dataBlock, patternCRC);
            cout << "Datablock " << dataBlock << " CRC Pattern " << patternCRC << " Transmission Frame before errors " << transmissionFrame << '\n';
            string receivedFrame = generateErrors(transmissionFrame);
            cout << "Received Frame after errors " << receivedFrame << '\n';
            bool isValid = determineValidity(receivedFrame, patternCRC);
            if (isValid)
            {
                cout << "Accepted\n";
            }
            else
            {
                cout << "Rejected\n";
            }
        }
        string userExit = "0";
        cout << "Do you wish to continue?\n";
        while (userExit != "y" || userExit != "n")
        {
            cout << "Please enter [y/n] only\n";
            getline(cin, userExit);
            if (userExit == "y")
                break;
            else if (userExit == "n")
                return 0;
        }
    }
    return 0;
}