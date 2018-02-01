 void myStrcat(char firStr[], int firLength, char secStr[], int secLength)

{

	for (int i=0;i<secLength;i++) {
    firStr[i+firLength] = secStr[i];
  }
   firStr[firLength+secLength] = 0;

}