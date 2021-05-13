//
// Created by Witek on 09.03.2020.
//

#ifndef TELE1_FILEREADINGSAVING_H
#define TELE1_FILEREADINGSAVING_H


#include <stdint-gcc.h>
#include <vector>

bool readBinary8bit(std::vector<unsigned char>&message,std::string fileName);
bool readBinary16bit(std::vector<uint16_t>&message,std::string fileName);
bool saveBinary8bit(std::vector<unsigned char>message,std::string fileName);
bool saveBinary16bit(std::vector<uint16_t>message,std::string fileName);
void convert8bitToVector(unsigned char message,int messageVector[]);
void convert16bitToVector(uint16_t message,int messageVector[]);
bool codeMessage(std::string readFileName,std::string saveFileName);
bool decodeMessage(std::string readFileName,std::string saveFileName);


#endif //TELE1_FILEREADINGSAVING_H
