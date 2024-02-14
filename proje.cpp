/*
          *************************************************************************************
          **             Name:Tuna Parlak                                                    **
          **             Number:b221202022                                                   **
          **             Assignment:Calculating a special matrix operation.                  **
          **                      Valla kopya çekmedim                                       **
          *************************************************************************************           */
//hocam filedan okurken output ekrana ne olursa olsun son 2 satýrý vermiyor neden olduðunu çözemedim dosyada düzgün gösteriyor ama.
#include <iostream>
#include <iomanip>
#include <ctime>
#include<fstream>
#include <string>
using namespace std;

int setCoreSize() {
    return rand() % 4 + 2;
}

int setInputSize() {
    return rand() % 16 + 5;
}

int** createCoreMatrix(int coreSize) {
    int** coreMatrix = new int* [coreSize];
    for (int i = 0; i < coreSize; i++) {
        coreMatrix[i] = new int[coreSize];
        for (int j = 0; j < coreSize; j++) {
            coreMatrix[i][j] = rand() % 11 + 10;
        }
    }
    return coreMatrix;
}

int** createInputMatrix(int inputSize) {
    int** inputMatrix = new int* [inputSize];
    for (int i = 0; i < inputSize; i++) {
        inputMatrix[i] = new int[inputSize];
        for (int j = 0; j < inputSize; j++) {
            inputMatrix[i][j] = rand() % 10 + 1;
        }
    }
    return inputMatrix;
}

int** calculateOutputMatrix(int** coreMatrix, int coreSize, int** inputMatrix, int inputSize) {
    int outputSize = inputSize - coreSize + 1;
    int** outputMatrix = new int* [outputSize];
    for (int i = 0; i < outputSize; i++) {
        outputMatrix[i] = new int[outputSize]();
    }

    int value = 0;
    for (int i = 0; i < outputSize; i++) {
        for (int j = 0; j < outputSize; j++) {
            value = 0;
            for (int a = 0; a < coreSize; a++) {
                for (int b = 0; b < coreSize; b++) {
                    value += coreMatrix[a][b] * inputMatrix[(coreSize + i - 1) - a][(coreSize + j - 1) - b];
                }
            }
            outputMatrix[i][j] = value / (coreSize * coreSize);
        }
    }

    return outputMatrix;
}

void printMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    srand(time(NULL));
    int option;
    //defining matrixes
    int** inputMatrix = nullptr;
    int** coreMatrix = nullptr;
    int** outputMatrix = nullptr; 
    int inputSize, coreSize, outputSize;
    //size of Matrix's
    coreSize = setCoreSize();
    inputSize = setInputSize();
    outputSize = inputSize - coreSize + 1;    
    ofstream writeFile;//File defining
    ifstream readFile;

    do {//Menu part
        cout << "Menu:" << endl;
        cout << "1 - Generate new matrices" << endl;
        cout << "2 - Read matrices from an existing file" << endl;
        cout << "Enter option: "; cin >> option;

        switch (option) {
        case 1://option 1
            //generating matrixes
            coreMatrix = createCoreMatrix(coreSize);
            inputMatrix = createInputMatrix(inputSize);           
            outputMatrix = calculateOutputMatrix(coreMatrix, coreSize, inputMatrix, inputSize);
            writeFile.open("data.txt",ios::out|ios::trunc);    
            if (writeFile.is_open()) {//checks does file exist
              
                writeFile << "Input Matrix elements: \n";//writing matrixes to file
                for (int i = 0; i < inputSize; i++) {
                    for (int j = 0; j < inputSize; j++) {
                        writeFile << inputMatrix[i][j] << setw(3);
                    }
                    writeFile << "\n";
                }
                writeFile << "Core Matrix elements: \n";
                for (int i = 0; i < coreSize; i++) {
                    for (int j = 0; j < coreSize; j++) {
                        writeFile << coreMatrix[i][j] << setw(2) << " ";
                    }
                    writeFile << "\n";
                }
                writeFile << "\n ";
                writeFile.close();
                cout << "New matrices generated and stored in file." << endl;
            }
            else {
                cout << "File can't be open for writing" << endl;
            }                    
            break;
            
        case 2://option 2
            if (inputMatrix != nullptr && coreMatrix != nullptr && outputMatrix != nullptr) {//if first '1' option selected this part just will read              
                readFile.open("data.txt", ios::in );
               
                if (readFile.is_open()) {//checks does file exist
                    
                    string str;
                    cout << "Matrix's read from data.txt" << endl;//reading file
                    for (int i = 0; i < inputSize; i++) {
                        getline(readFile, str);
                        cout << str << "\n";
                    }
                    for (int i = 0; i < coreSize; i++) {
                        getline(readFile, str);
                        cout << str << "\n";
                    }  
                    
                }
                cout << "\n";
                readFile.close();
                cout << "Output Matrix Elements:" << endl;
                printMatrix(outputMatrix, outputSize);
            }
            else {//if first '2' option selected this part will create matrix's ,write and read 
                cout << "Matrices have not been generated yet. First option is activated." << endl;
                coreMatrix = createCoreMatrix(coreSize);//generating matrix's
                inputMatrix = createInputMatrix(inputSize);
                outputMatrix = calculateOutputMatrix(coreMatrix, coreSize, inputMatrix, inputSize);
                writeFile.open("data.txt", ios::out);
                if (writeFile.is_open()) {//checks does file exist
                    
                    writeFile << "Input Matrix elements: \n";//writing matrixes to file
                    for (int i = 0; i < inputSize; i++) {
                        for (int j = 0; j < inputSize; j++) {
                            writeFile <<inputMatrix[i][j] << setw(3);
                        }
                        writeFile << "\n";
                    }
                    writeFile << " Core Matrix elements: \n";
                    for (int i = 0; i < coreSize; i++) {
                        for (int j = 0; j < coreSize; j++) {
                            writeFile << coreMatrix[i][j] << setw(2) << " ";
                        }
                        writeFile << "\n";
                    }
                    cout << "\n";
                    writeFile.close();
                    cout << "New matrices generated and stored in file." << endl;
                }
                else {
                    cout << "File can't be open for writing" << endl;
                }    
                readFile.open("data.txt", ios::in );
                if (readFile.is_open()) {//checks does file exist
                   
                    string str;
                    cout << "Matrix's read from data.txt" << endl;

                    for (int i = 0; i < inputSize; i++) {
                        getline(readFile, str);
                        cout << str << "\n";
                    }                   
                    for (int i = 0; i < coreSize; i++) {
                        getline(readFile, str);
                        cout << str << "\n";
                    }
                }
                cout << endl;
                readFile.close();
                cout << "Output Matrix Elements:" << endl;                
                printMatrix(outputMatrix, outputSize);
            }
            break;
        default:
            cout << "Invalid option. Please enter a valid option." << endl;
        }
    } while (option != 2); 
    //deallocating memory
    deleteMatrix(inputMatrix, inputSize);
    deleteMatrix(coreMatrix, coreSize);
    deleteMatrix(outputMatrix, outputSize); 
    return 0;
}