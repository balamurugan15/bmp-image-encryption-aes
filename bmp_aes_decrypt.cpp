#include <iostream>
#include <cstdio>
#include <fstream>
#include "aes.c"


  unsigned char key[16]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                 0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f}; 
				 
 unsigned char ciphertext[16];
 unsigned char plaintext[16];




using namespace std;


 unsigned char* temp;
 int* array;

 int** red;
 int** green;
 int** blue;

 int** vertical;       // arranged vertically
 int** horizontal;     // arranged horizontally


 unsigned char header[54];

 int width, height, padding, widthnew;
 
 long unsigned int key_schedule[60],idx;



int main(){

	 //cout<<" HELLLLOOOOO \n\n\n";



	 char* fname = "newfile.bmp";


	 unsigned char* ReadBMP(char* , int*);

	 temp = ReadBMP(fname,array);

	return 0;
}


unsigned char* ReadBMP(char* filename, int* array){

	 FILE* img = fopen(filename, "rb");   //read the file

	 FILE* newimg = fopen("decompfile.bmp","wb"); // write new bmp

	 FILE* dummy = fopen("bintext2.txt","a"); //write to text

	  std::fstream fs;
	  fs.open ("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);


	// unsigned char header[54];
	 fread(header, sizeof(unsigned char), 54, img); // read the 54-byte header

	 fwrite(header, sizeof(unsigned char), 54, newimg); // write header to new bmp




	   // extract image height and width from header
	 width = *(int*)&header[18];

	 height = *(int*)&header[22];


	cout<<"\n Height = "<<height<<'\n';

	 padding=0; //while ((width*3+padding) % 4!=0) padding++;
	 if((width*3) % 4 !=0)
		padding = 4 - ((width*3) % 4);

	 widthnew=width*3+padding;

	 cout<<"Widthnew = "<<widthnew;

	 unsigned char* data = new unsigned char[16];
	 
	 int flag  = 0;

	 while(! feof(img)) {
		 
		 char padding = 0x00;
        

	    int bytes = fread( data, sizeof(unsigned char), 16, img);
		if (!bytes) break;

        // If fread grabbed less than 16 bytes, that's our final line
        // Use the byte number for padding and pad N bytes of N
        //if ( bytes < BLOCK_LENGTH ){ padding = 0x00; }

        //while(bytes < 16)
         //   data[bytes++] = padding;
	
		for(int i=0; i < 16; i++)
            ciphertext[i] = data[i];
		
		 
		 
		 
		// First set of test vectors. 
		
		KeyExpansion(key,key_schedule,128);
		aes_decrypt(ciphertext,plaintext,key_schedule,128); 
		//aes_encrypt(plaintext,ciphertext,key_schedule,128);
		for(int i=0; i < 16; i++){
            data[i] = plaintext[i];
		}
		
		fwrite(data, sizeof(unsigned char), 16, newimg);
		
		
		//for (idx=0; idx < 16; idx++) 
		//  printf("%02x",ciphertext[idx]); 
		//puts(""); 
		//aes_decrypt(ciphertext,plaintext,key_schedule,128); 
		//for (idx=0; idx < 16; idx++) 
		//  printf("%02x",plaintext[idx]); 
		//puts(""); 
	  }

	  fs.close();

	 cout<<array<<'\n';
	// txtfile.close();
	 fclose(dummy);
	 fclose(img); //close the file
	 fclose(newimg); // close the new file



}





 



