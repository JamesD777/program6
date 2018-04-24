/*
 * James Dunlap
 * jcd160230@utdallas.edu
 * 3377.501
 */

#include "cdk.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <string>
#include <sstream>
#include <algorithm>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

//binary file header
class BinaryFileHeader{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};
//max string length size
const int maxRecordStringLength = 25;

//binary file record
class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main(){
  //object pointers for the header and record
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  
  //open the binary file
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  
  //read the header
  binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
  
  //convert to hex and uppercase
  stringstream stream;
  stream << hex << myHeader->magicNumber;
  string mN( stream.str() );
  transform(mN.begin(), mN.end(), mN.begin(), ::toupper);
  
  //convert to strings with correct formatting
  string vN = to_string(myHeader->versionNumber);
  string nR = to_string(myHeader->numRecords);
  mN = "Magic: 0x" + mN;
  vN = "Version: " + vN;
  nR = "numRecords: " + nR;

  //set up cdk
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  //Initialize the Cdk screen

  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);
  //print error if it failed to be created
  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  //add header to martix
  setCDKMatrixCell(myMatrix, 1, 1, mN.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, vN.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, nR.c_str());
  
  //loop through recordss, adding them to the matrix
  for(uint64_t i = 0; i < 4 && i < myHeader->numRecords; i++){
    binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));

    string temp = "strlen: ";
    temp += to_string(myRecord->strLength);

    setCDKMatrixCell(myMatrix, i+2, 1, temp.c_str());
    setCDKMatrixCell(myMatrix, i+2, 2, myRecord->stringBuffer);
  }
  //draw the matrix
  drawCDKMatrix(myMatrix, true);

  /* pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
  binInfile.close();


}
