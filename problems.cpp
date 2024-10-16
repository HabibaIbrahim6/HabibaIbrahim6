// author : Habiba Ibrahim Abdeldayem Ibrahim

/*This program make the user to choose between for problems
   1. *Sentence Correction*: The user enters a sentence, and the program corrects it by capitalizing
   the first letter, converting the rest to lowercase, and removing any extra spaces. It also handles
    the removal of a leading quote if present.

 2. *Prime Number Finder*: The user inputs a number, and the program uses the Sieve of Eratosthenes
    algorithm to find and display all prime numbers up to that number.

 3. *Domino Chain Checker*: The user enters a list of dominos, and the program determines if a valid
    chain can be formed. A valid chain is formed when the right dots of one domino match the left dots
    of the next domino in sequence.

 4. *Arabic Message Alteration*: The program takes an Arabic message from a file and replaces specific
    words with alternatives from a predefined map. The altered message is then written to a new file
    and displayed on the console. The program uses UTF-8 encoding to handle Arabic text properly.

 The user chooses which function to execute based on their input. Depending on the choice, the program
 will either correct a sentence, find primes, check a domino chain, or alter an Arabic message..*/


#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <fstream>
#include <locale>
#include <codecvt>
#include <sstream>
#include <windows.h>
using namespace std;
class CorrectedSentence {
private:
    string sentence;
public:
    CorrectedSentence(string sent) {
        sentence = sent;
    }

    string corrected_u_L() {
        size_t start = sentence.find_first_not_of(" ");
        if (start != string::npos) {
            sentence = sentence.substr(start);
        } else {
            return "";
        }
        if (sentence[0] == '\"') {
            sentence.erase(0, 1);
        }
        if (islower(sentence[0])) {
            sentence[0] = toupper(sentence[0]);
        }
        for (int i = 1; i < sentence.size(); i++) {
            if (isupper(sentence[i])) {
                sentence[i] = tolower(sentence[i]);
            }
        }
        for (int i = 0; i < sentence.size() - 1; i++) {
            if (sentence[i] == ' ' && sentence[i + 1] == ' ') {
                sentence.erase(i + 1, 1);
                i--;
            }
        }

        size_t pos = sentence.find('.');
        if (pos != string::npos) {
            return sentence.substr(0, pos + 1);
        }

        return sentence;
    }
};

void findPrimes(int num) {
    vector<int> v;
    if (num <= 1) {
        cout << "[]" << endl;
        return;
    }
    for (int i = 2; i <= num; i++) {
        v.push_back(i);
    }
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j] % v[i] == 0) {
                v.erase(v.begin() + j);
                j--;
            }
        }
    }
    cout<<"[";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if(i!=v.size()-1){
            cout<<" ,";
        }
    }
    cout << "]"<<endl;
}
struct Domino {
    int leftDots;
    int rightDots;
};

bool isValidChain(const deque<Domino>& dominos) {
    for (size_t i = 0; i < dominos.size() - 1; ++i) {
        if (dominos[i].rightDots != dominos[i + 1].leftDots) {
            return false;
        }
    }
    return true;
}

bool findDominoChain(deque<Domino>& dominos, int index) {
    if (index == dominos.size()) {
        return true;
    }

    for (int i = index; i < dominos.size(); ++i) {
        if (index > 0 && dominos[index - 1].rightDots != dominos[i].leftDots) {
            continue;
        }

        swap(dominos[index], dominos[i]);
        if (findDominoChain(dominos, index + 1)) {
            return true;
        }
        swap(dominos[index], dominos[i]);
    }

    return false;
}
void alterArabicMessage() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    locale::global(locale(""));

    map<wstring, wstring> CypherMap;
    string nameFileWithWords;
    cout << "Enter the name of the file that contains the words and their alternatives: ";
    getline(cin, nameFileWithWords);

    wifstream fileWithWords(nameFileWithWords);
    fileWithWords.imbue(locale(fileWithWords.getloc(), new codecvt_utf8<wchar_t>));
    if (!fileWithWords.is_open()) {
        cout << "Unable to open file: " << nameFileWithWords << endl;
        return;
    }
    wstring line;
    while (getline(fileWithWords, line)) {
        size_t delimiterPos = line.find(L":");
        if (delimiterPos != wstring::npos) {
            wstring key = line.substr(0, delimiterPos);
            wstring value = line.substr(delimiterPos + 1);
            CypherMap[key] = value;
        }
    }
    fileWithWords.close();
    string nameFileMessage;
    cout << "Enter the name of the file that contains the message you want to cipher: ";
    getline(cin, nameFileMessage);

    wifstream inputFile(nameFileMessage);
    inputFile.imbue(locale(inputFile.getloc(), new codecvt_utf8<wchar_t>));
    if (!inputFile.is_open()) {
        cout << "Unable to open file: " << nameFileMessage << endl;
        return;
    }
    wofstream modifiedFile("ModifyMessage.txt");
    modifiedFile.imbue(locale(modifiedFile.getloc(), new codecvt_utf8<wchar_t>));
    while (getline(inputFile, line)) {
        wstringstream ss(line);
        wstring word;
        while (ss >> word) {
            if (CypherMap.find(word) != CypherMap.end()) {
                modifiedFile << CypherMap[word] << L" ";
            } else {
                modifiedFile << word << L" ";
            }
        }
        modifiedFile << endl;
    }

    inputFile.close();
    modifiedFile.close();
    wifstream modifiedFileInput("ModifyMessage.txt");
    modifiedFileInput.imbue(locale(modifiedFileInput.getloc(), new codecvt_utf8<wchar_t>));
    if (!modifiedFileInput.is_open()) {
        cout << "Unable to open ModifyMessage.txt" << endl;
        return;
    }

    cout << "Modified message from ModifyMessage.txt:" << endl;
    while (getline(modifiedFileInput, line)) {
        wcout << line << endl;
    }
    modifiedFileInput.close();

    cout << "The Cypher Messages were written in ModifyMessage.txt successfully" << endl;
}
int main() {
    cout << " 1-Sentence Correction\n"
         << " 2-Prime number finder \n"
         << " 3-Domino chain checker \n"
         << " 4-Arabic Message Alteration \n"
         << " 5-Choose 5 if you want to Exit the program\n";

    int choice;
    while (true) {
        cout << "Enter the number of the problem that you want to try (or 5 to exit): ";
        cin >> choice;
        cin.ignore();
        if (choice == 5) {
            break;
        }

        bool repeat= true;
        while (repeat) {
            switch (choice) {
                case 1: {
                    string sen;
                    string allSentences;
                    cout << "Enter a sentence (end with a period):" << endl;
                    while (true) {
                        getline(cin, sen);
                        allSentences += sen + " ";
                        if (sen.find('.') != string::npos) {
                            break;
                        }
                    }
                    CorrectedSentence c(allSentences);
                    cout << c.corrected_u_L() << endl;
                    break;
                }
                case 2: {
                    int num;
                    cout << "Enter the number up to which you want to find prime numbers: ";
                    cin >> num;
                    findPrimes(num);
                    break;
                }
                case 3: {
                    deque<Domino> dominos;
                    int num;
                    cout << "Enter the number of dominos: ";
                    cin >> num;
                    for (int i = 0; i < num; ++i) {
                        Domino d;
                        cout << "Enter the LeftDots and RightDots of domino " << i + 1 << ": ";
                        cin >> d.leftDots >> d.rightDots;
                        dominos.push_back(d);
                    }

                    if (findDominoChain(dominos, 0)) {
                        cout << "Valid domino chain formed:\n";
                        for (auto& domino : dominos) {
                            cout << domino.leftDots << " " << domino.rightDots << " | ";
                        }
                        cout << endl;
                    } else {
                        cout << "No valid domino chain can be formed.\n";
                    }
                    break;
                }
                case 4: {
                    alterArabicMessage();
                    break;
                }
                default: {
                    cout << "Invalid choice!" << endl;
                    repeat= false;
                }
            }
            char userChoice;
            cout << "Do you want to repeat this problem? (y/n): ";
            cin >> userChoice;
            if (tolower(userChoice) != 'y') {
                repeat = false;
            }
            cin.ignore();
        }
    }
    cout << "Exiting program!" << endl;
    return 0;
}
