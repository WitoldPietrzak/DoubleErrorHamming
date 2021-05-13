//
// Created by Witek on 09.03.2020.
//

#include "DoubleErrorCorrect.h"
#include <iostream>

const int messageBits=8;
const int checkBits=8;
const int totalBits=messageBits+checkBits;

int matrixH[checkBits][totalBits]={
        {0,1,1,1,1,0,0,0, 1,0,0,0,0,0,0,0},
        {0,1,1,0,0,1,1,0, 0,1,0,0,0,0,0,0},
        {1,1,0,1,1,0,0,1, 0,0,1,0,0,0,0,0},
        {1,1,1,1,0,0,1,1, 0,0,0,1,0,0,0,0},
        {1,0,0,1,1,0,1,0, 0,0,0,0,1,0,0,0},
        {0,0,1,0,1,1,0,1, 0,0,0,0,0,1,0,0},
        {0,1,0,1,1,1,1,1, 0,0,0,0,0,0,1,0},
        {1,1,0,0,1,1,0,0, 0,0,0,0,0,0,0,1}};
void generateErrorVector(const int Message[],int errorVector[]){              //Tworzy Iloczyn Macierzy i wiadomości
    for(int i=0;i<checkBits;i++){
        errorVector[i]=0;
        for(int j=0;j<totalBits;j++){
            if(matrixH[i][j]){
                errorVector[i]+=Message[j];
            }
            errorVector[i]%=2;
        }
    }
}


bool singleErrorDetect(int errorVector[],int Message[]){
    bool flag;
    for(int i=0;i<totalBits;i++){
        flag=true;
        for(int j=0;j<checkBits;j++){
            if(matrixH[j][i]!=errorVector[j]){               //Porównuję wektor błędu z kolumnami, kiedy znajdę taką która mu odpowiada  przerywam pętlę
                flag=false;
                break;
            }
        }
        if(flag){                                            // Jeżeli znalazłem odpowiednią kolumnę wywołuję funkcję naprawiającą
            repairMessageBit(Message,i);
            generateErrorVector(Message,errorVector);
            return true;
        }
    }
    return false;
}


void repairMessageBit(int Message[], int bitNumber){              //Neguje bit do naprawy
    if(Message[bitNumber]) Message[bitNumber]=0;
    else Message[bitNumber]=1;
}

bool repairMultipleError(int errorVector[],int Message[]){
    int temporaryErrorVector[checkBits];

    for(int i=0;i<totalBits;i++){
        for(int j=0;j<checkBits;j++){
            temporaryErrorVector[j]=(errorVector[j]+matrixH[j][i])%2;            //Odejmuje od wektora błędu każdą kolumę sprawdzając czy otrzymany wektor odpowiada innej kolumnie
        }                                                                          //Jeżeli tak, to odjęta i otrzymana kolumna zawierają błędy więc wywołuję dla nich funkcje naprawiajaca

        if(singleErrorDetect(temporaryErrorVector,Message)){
            singleErrorDetect(temporaryErrorVector,Message);
            generateErrorVector(Message,errorVector);
            return true;
        }


    }
    return false;
}



bool checkIfNeedsRepair(const int errorVector[]){             //Sprawdzam czy wektor błędu jest równy [0,0,0,0,0,0,0,0]
    for(int i=0;i<checkBits;i++){
        if(errorVector[i]!=0){
            return false;
        }
    }
    return true;
}

void codeByte(int messageVector[], int codedMessageVector[]){
    int checkBit[checkBits]={0, 0, 0, 0, 0, 0, 0, 0};                     //Koduję słowo używając macierzy H
    for (int i=0;i<checkBits;i++){
        for(int j=0;j<messageBits;j++){
            if(matrixH[i][j]){
                checkBit[i]+=messageVector[j];                           //Jeżeli macierz H ma na polu odpowiadającemu bitowi wiadomości 1, liczę ten bit
            }
        }
        if(checkBit[i] % 2) checkBit[i]=1;                       //Sprawdzam czy suma liczonych bitów jest parzysta, jeśli nie, bit parzystości przyjmuje wartość 1
        else checkBit[i]=0;
    }
    for(int i=0;i<messageBits;i++){
        codedMessageVector[i]=messageVector[i];
    }
    for(int i=0;i<checkBits;i++){
        codedMessageVector[i+8]=checkBit[i];
    }
}

bool repairByte(int messageVector[]){

        int vec[8]={0,0,0,0,0,0,0,0};                       //Tworzę wektor błędów i wyznaczam jego wartość
        generateErrorVector(messageVector,vec);

        if(checkIfNeedsRepair(vec)){
            return true;
        }

        if(!singleErrorDetect(vec,messageVector)){
            return repairMultipleError(vec,messageVector);
        }
        return true;


}

void decodeByte(int messageVector[],int decodedMessageVector[]){
    for(int i=0;i<messageBits;i++){
        decodedMessageVector[i]=messageVector[i];
    }
}
