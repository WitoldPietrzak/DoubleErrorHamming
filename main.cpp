#include <iostream>
#include "FileReadingSaving.h"
#include "DoubleErrorCorrect.h"
std::string messageFileName="wiadomosc.txt";
std::string codedMessageFileName="coded "+messageFileName;
std::string decodedMessageFileName="decoded "+messageFileName;



int main() {
    int menuChoice=0;
    do {
        std::cout << "Wybierz operacje: \n 1 - zakoduj wiadomosc \n 2 - odkoduj wiadomosc \n 0 - zakoncz program \n";
        std::cin >> menuChoice;
        if(!menuChoice) return 0;
        if(menuChoice==1) {
            std::cout<<"Podaj nazwe pliku do zakodowania \n";
            std::cin>>messageFileName;
            std::cout<<"Podaj nazwe pliku po zakodowaniu \n";
            std::cin>>codedMessageFileName;
            if(codeMessage(messageFileName, codedMessageFileName)){
                std::cout<<"Wiadomosc zakodowana poprawnie\n\n\n";
            }
            else{
                std::cout<<"Nie udalo sie zakodowac wiadomosci\n\n\n";
            }
        }
        if(menuChoice==2){
            std::cout<<"Podaj nazwe pliku do odkodowania \n";
            std::cin>>codedMessageFileName;
            std::cout<<"Podaj nazwe pliku po odkodowaniu \n";
            std::cin>>decodedMessageFileName;
            if(decodeMessage(codedMessageFileName, decodedMessageFileName)){
                std::cout<<"Wiadomosc odkodowana poprawnie\n\n\n ";
            }
            else{
                std::cout<<"Nie udalo sie odkodowac wiadomosci\n\n\n";
            }
        }
    }while(1);


    return 0;
}

