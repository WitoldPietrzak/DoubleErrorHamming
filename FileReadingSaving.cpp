//
// Created by Witek on 09.03.2020.
//

#include <fstream>
#include <iostream>
#include "FileReadingSaving.h"
#include "DoubleErrorCorrect.h"


bool readBinary8bit(std::vector<unsigned char>&message,std::string fileName){
    message.clear();
    std::ifstream file;
    file.open(fileName,std::ios::binary);
    auto* buffor= new unsigned char;
    if(!file.is_open()){
        std::cout<<"Nie udalo sie otworzyc pliku "<<fileName<<std::endl;
        return false;
    }
    while (file.read((char*)(buffor), sizeof(char))){
        message.push_back(*buffor);
    }
    file.close();
    return true;
}

bool readBinary16bit(std::vector<uint16_t>&message,std::string fileName){
    message.clear();
    std::ifstream file;
    file.open(fileName,std::ios::binary);
    auto* buffor= new unsigned char[sizeof(uint16_t)];
    uint16_t* bf= nullptr;
    if(!file.is_open()){
        std::cout<<"Nie udalo sie otworzyc pliku "<<fileName<<std::endl;
        return false;
    }
    while (file.read((char*)(buffor), sizeof(uint16_t))){
        bf=(uint16_t*)(buffor);
       message.push_back(*bf);
    }
    file.close();
    return true;
}

bool saveBinary8bit(std::vector<unsigned char>message,std::string fileName){
    std::ofstream file;
    file.open(fileName,std::ios::binary);
    if(!file.is_open()){
        std::cout<<"Nie udalo sie otworzyc pliku "<<fileName<<std::endl;
        return false;
    }
    while (!message.empty()){
        file.write((char*)(&message[0]), sizeof(unsigned char));
        message.erase(message.begin());
    }
    file.close();
    return true;
}

bool saveBinary16bit(std::vector<uint16_t>message,std::string fileName){
    std::ofstream file;
    file.open(fileName,std::ios::binary);
    if(!file.is_open()){
        std::cout<<"Nie udalo sie otworzyc pliku "<<fileName<<std::endl;
        return false;
    }
    while (!message.empty()){
        file.write((char*)(&message[0]), sizeof(uint16_t));
        message.erase(message.begin());
    }
    file.close();
    return true;
}

void convert8bitToVector(unsigned char message,int messageVector[]){
    for(int i=7;i>=0;i--){
        messageVector[i]=message%2;
        message/=2;
    }
}

void convert16bitToVector(uint16_t message,int messageVector[]){
    for(int i=15;i>=0;i--){
        messageVector[i]=message%2;
        message/=2;
    }
}

void convertVectorTo8bit(unsigned char &message,int messageVector[]){
    message=0;
    for(int i=7;i>=0;i--){
        if(messageVector[i]) message += (0b1 << (7-i));
    }
}

void convertVectorTo16bit(uint16_t &message,int messageVector[]){
    message=0;
    for(int i=15;i>=0;i--){
        if(messageVector[i]) message += (0b1 << (15-i));
    }
}

bool codeMessage(std::string readFileName,std::string saveFileName){
    std::vector<unsigned char>message;
    std::vector<uint16_t>codedMessage;
    int messageVector[8];
    int codedMessageVector[16];
    if(!readBinary8bit(message,readFileName)) return false;
    for(int i=0;i<message.size();i++){
        convert8bitToVector(message[i],messageVector);
        codeByte(messageVector,codedMessageVector);
        codedMessage.push_back(0);
        convertVectorTo16bit(codedMessage[i],codedMessageVector);
    }
    return saveBinary16bit(codedMessage, saveFileName);

}

bool decodeMessage(std::string readFileName,std::string saveFileName){
    std::vector<uint16_t >message;
    std::vector<unsigned char>decodedMessage;
    int messageVector[16];
    int decodedMessageVector[8];
    if(!readBinary16bit(message,readFileName)) return false;
    for(int i=0;i<message.size();i++){
        convert16bitToVector(message[i],messageVector);
        if(!repairByte(messageVector)) return false;
        decodeByte(messageVector,decodedMessageVector);
        decodedMessage.push_back(0);
        convertVectorTo8bit(decodedMessage[i],decodedMessageVector);
    }
    return saveBinary8bit(decodedMessage, saveFileName);
}