#include "FileIO.h"

FileIO::FileIO(int mode):mode(mode)//by default goes to level loading mode
{
//    line=0;
    if (mode==LOAD_LEVEL)
    {


    }
    else if (mode==SAVE_STATE)
    {


    }
    else if(mode==LOAD_STATE)
    {


    }

}

FileIO::~FileIO()
{
    closeFile();
}

int FileIO::openFile(string filename)//by default loads lev1.txt, returns 1 if file loaded succesfully, 0 if there's an error opening the file, and -1 if unspecifed mode is passed
{
    if(mode==LOAD_LEVEL || mode==LOAD_STATE)
    {
        inFile.open(filename);
        return !inFile.fail();
    }
    else if(mode==SAVE_STATE)
    {
        outFile.open(filename);
        return !outFile.fail();
    }
    else//if mode is unspecified
    {
        return -1;
    }

}

bool FileIO::checkFile()//checks if the loaded file is according to the speecified format, For format details, view Levels\ReadMe.txt
{
    bool valid=true;
    int line=1;
    if (mode==LOAD_LEVEL)//file is valid if characters on each line are less than 20, since this is our set dimensions for the board
    {
        while(!inFile.eof())
        {
            if (line ==1 && inFile.peek() == EOF)  // peek the character without reading it, just in case the file is not empty, so that cursor doesn't need to be reset
            {
                valid=false;
                break;
            }
            else
            {
                string outputText;
                getline(inFile, outputText);
                line++;
                if (outputText.length() <=COL)
                    continue;
                else
                {
                    valid=false;
                    break;
                }
            }
        }
    }
    else if (mode==SAVE_STATE)
    {


    }
    else if(mode==LOAD_STATE)
    {


    }
    //Resetting file cursors to beginning, by def if we arrive here this means that the file is valid
    inFile.clear();
    inFile.seekg(0, inFile.beg);
    outFile.clear();
//    outFile.seekg(0, outFile.beg);
    return valid;
}
void FileIO::closeFile()
{
    inFile.close();
    outFile.close();
}

void FileIO::handleFile(List* worldEnt,Board* gameBoard)//does the processing of the loaded file
{
    char outputChar;
    const int offsetX=2;//can be corrected for all resolutions with a little fitting, CORRECT THIS
    const int offsetY=2;
    Point spawnPoint(gameBoard->bounds.x + offsetX,gameBoard->bounds.y + offsetY);//offset of 2 for 1024 added to correct spawn points
    Point startPoint=spawnPoint;
    Brick* b = NULL;
    if (mode==LOAD_LEVEL)
    {
        while(inFile.get(outputChar))
        {
//            cout << "Output Char: " << outputChar << endl;
            if(outputChar=='1')
            {
                b=new OneHitBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='2')
            {
                b=new TwoHitBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='3')
            {
                b=new ThreeHitBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='s')
            {
                b=new SteelBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='m')
            {
                b=new MobileBrick(gameBoard->gSpriteSheetTexture,gameBoard,spawnPoint);
                spawnPoint++;
            }
            else if (outputChar=='\n')// || outputChar=='\n')
            {
                ++startPoint;
                spawnPoint=startPoint;
                b=NULL;
            }
            else//(outputChar==' ')// || outputChar=='\n') //case for spaces and all unspecified characters
            {
                b=NULL;
                spawnPoint++;
            }
            if(b)
            {
                worldEnt->append(b);
            }
        }
        return;
    }
    else if (mode==SAVE_STATE)
    {


    }
    else if(mode==LOAD_STATE)
    {


    }
}



