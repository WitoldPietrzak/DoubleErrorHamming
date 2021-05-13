//
// Created by Witek on 09.03.2020.
//

#ifndef TELE1_DOUBLEERRORCORRECT_H
#define TELE1_DOUBLEERRORCORRECT_H

void generateErrorVector(const int Message[],int errorVector[]);   // Generuje wektor błędu ( jeżeli jest zerowy, wiadomość jest ok)
void codeByte(int messageVector[], int codedMessageVector[]);   //koduje jeden bajt wiadomosci na 2 bajty zakodowanej wiadomosci
void decodeByte(int messageVector[],int decodedMessageVector[]); //odkodowuje 2 bajty zakodowanej wiadomosci na 1 bajt wiadomosci
bool repairByte(int messageVector[]);                          // naprawia jeden bajt wiadomości (True - brak błędu/błąd naprawiony False - nie udało się naprawić błędu)
bool singleErrorDetect(int errorVector[],int Message[]);     // sprawdza czy w wiadomości występuje pojedyńczy błąd, jeśli tak to go naprawia (True - udało się naprawić / False - nie udało się)
void repairMessageBit(int Message[], int bitNumber);         //  Naprawia zepsuty bit wiadomości
bool repairMultipleError(int errorVector[],int Message[]);  // Naprawia 2 zepsute bity (True - udało się naprawić / False - nie udało się)
bool checkIfNeedsRepair(const int errorVector[]);           // Sprawdza czy wiadomość wymaga naprawy (True- nie wymaga/ False - wymaga)

#endif //TELE1_DOUBLEERRORCORRECT_H
