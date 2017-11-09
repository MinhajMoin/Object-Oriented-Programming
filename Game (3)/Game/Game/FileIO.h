#ifndef FILEIO_H
#define FILEIO_H
#include <fstream>
#include "Game.h"
class List;
using namespace std;

class FileIO
{
public:
    FileIO(int=LOAD_LEVEL);
    ~FileIO();
    enum FILEIO_MODES {LOAD_LEVEL,SAVE_STATE,LOAD_STATE};
    int openFile(string);
    bool checkFile();//checks if the loaded file is in correct format
    void handleFile(List*,Board*);//does the processing of the loaded file
    void closeFile();
private:
    //
    const int COL=20;//num of possible brick columns for level loading
    ifstream inFile;
    ofstream outFile;
    int mode;//at a time one mode will be active



};

#endif // FILEIO_H
