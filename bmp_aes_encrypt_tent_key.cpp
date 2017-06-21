#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdint.h>
#include "aes.c"


  unsigned char key[16]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                 0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f}; 
				 
 unsigned char ciphertext[16];
 unsigned char plaintext[16];




using namespace std;
std::fstream fs;


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
 
 
 union u_double
{
    double  dbl;
    uint64_t a1;
}my1;
 
 
double u = (double) 1.5;
double tpast[] = { (double) 0.5, (double) 0.7};
double tnow[] = { 0x0000000000000000LL, 0x0000000000000000LL};


void genkey(){
	int i,j,k;
	
	for(i=0;i<2;i++){
		
		if( (double) (0.5) >  tpast[i])
			tnow[i] = tpast[i] * u;
		else
			tnow[i] = u * ( 1 - tpast[i]);
	}
	
	
	/*if( (double) (0.5) >  t2past)
		t2now = t2past * u;
	else
		t2now = u * ( 1 - t2past); */
	
	
	for(i=0,k=0; i<2;i++){
		
		my1.dbl = tnow[i];
		for(j=7; j>=0; j--,k++){
			key[k] = (my1.a1 >> (j * 8));
		}	
	}
	tpast[0] = tnow[0];
	tpast[1] = tnow[1];
	
	fs<<tpast[0]<<tpast[1]<<endl<<endl;
			
}



int main(){

	 //cout<<" HELLLLOOOOO \n\n\n";



	 char* fname = "Myfile.bmp";


	 unsigned char* ReadBMP(char* , int*);

	 temp = ReadBMP(fname,array);

	return 0;
}


unsigned char* ReadBMP(char* filename, int* array){

	 FILE* img = fopen(filename, "rb");   //read the file

	 FILE* newimg = fopen("newfile.bmp","wb"); // write new bmp

	 FILE* dummy = fopen("bintext.txt","a"); //write to text

	  
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

	 //widthnew=width*3+padding;

	 cout<<"Widthnew = "<<width<<endl;;

	 unsigned char* data = new unsigned char[16];
	 
	 int flag  = 0;
	 int j=0;
	 while(! feof(img)) {
		 
		 char padding = 0x00;
        

	    int bytes = fread( data, sizeof(unsigned char), 16, img);
		//cout<<"Bytes = "<<bytes<<"\n j = "<<j++<<endl;
		if (!bytes) break;

        // If fread grabbed less than 16 bytes, that's our final line
        // Use the byte number for padding and pad N bytes of N
        //if ( bytes < BLOCK_LENGTH ){ padding = 0x00; }

        while(bytes < 16){
		   cout<<"padding....";
           data[bytes++] = padding;
		}
		
		
		for(int i=0; i < 16; i++){
            plaintext[i] = data[i];
		}
		
		 
		// First set of test vectors. 
		
		genkey();
		
		KeyExpansion(key,key_schedule,128);
		aes_encrypt(plaintext,ciphertext,key_schedule,128);
		
		
		for(int i=0; i < 16; i++){
            data[i] = ciphertext[i];
		}
		
		fwrite(data, sizeof(unsigned char), 16, newimg);
		
		
		//for (idx=0; idx < 16; idx++) 
		//  printf("%02x",ciphertext[idx]); 
		//puts(""); 
		//aes_decrypt(ciphertext,plaintext,key_schedule,128); 
		//for (idx=0; idx < 16; idx++) 
		//  printf("%02x",plaintext[idx]); 
		//puts("");
		j++;
	  }

	  cout<<"j = "<<j<<endl;
	  fs.close();

	 //cout<<array<<'\n';
	// txtfile.close();
	 fclose(dummy);
	 fclose(img); //close the file
	 fclose(newimg); // close the new file



}





 



