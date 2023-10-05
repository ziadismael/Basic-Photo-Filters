/*
FCAI – OOP Programming – 2023 - Assignment 1 
Program: ImageFilterApplier.cpp
Last Modification Date: 4/10/2023
Team Members:   1- Mohamed Mahmoud Khamis Rezk               (20221129)
                2- Ibrahem Medhat Mahmoud Mohamed El Zennary (20221003)
                3- Ziad Sherif Ahmed Mohamed Ismael          (20220143)
TA:
Purpose:
*/

#include <iostream>
#include <cstring>
#include <string>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE]; // => "SIZE" is defined to be a constant int = 256 (# of pixels in row/col.)

void saveImage();
void loadImage();
void filterBlacknWhite();
void resizeFlip(); 
void mergeImages();
void filterInvert(); //  <= added in this commit

int main(){
    cout<<"Ahlan ya user ya habibi"<<endl;
    cout<<"Please enter file name of the image to process: ";
    loadImage();
    // menu function here
    return 0;
}

void loadImage(){   //responsible for loading the image into 2D array
    char image_name[100];
    cin >> image_name; // after taking image name
    strcat (image_name, ".bmp"); //making sure its the correct format 
    readGSBMP(image_name, image);
}

void saveImage(){   //responsible for saving the image from 2D array after applying filters
    char image_name[100];
    cin>>image_name;
    strcat (image_name, ".bmp");
    writeGSBMP(image_name, image); //function from the "mpblib" library to convert array to image
}

void filterBlacknWhite(){ 
    for (size_t i=0; i<SIZE; i++){
        for (size_t j=0; j<SIZE; j++){ //iterating through each pixel i,j
            if(image[i][j]<=127) // applying the average as a threshold for black
                image[i][j] = 0;
            else
                image[i][j] = 255; // turning any pixel > 127 into white 
        }
    }
}

void resizeFlip(){
    char selector;
    char image_copy[SIZE][SIZE];
    cout<<"Flip (h)orizontally or (v)ertically? ";
    cin>>selector;
    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            image_copy[i][j] = image[i][j]; //making a copy of the 2D array
        }
    }
    if (selector=='h'){
        for(size_t i=0; i<SIZE/2; i++){ // we only need to go to half of the array cuz if we continue it will revert the flip
            for(size_t j=0; j<SIZE; j++){
                int temp = image[i][j];                //  <=
                image[i][j] = image_copy[SIZE-1-i][j]; //  <=  this three lines of code responsible for swapping pixels
                image[SIZE-i-1][j] = temp;             //  <=
            }
        }
    }
    else if(selector=='v'){
        for(size_t i=0; i<SIZE; i++){
            for(size_t j=0; j<SIZE/2; j++){
                int temp = image[i][j];
                image[i][j] = image_copy[i][SIZE-1-j];
                image[i][SIZE-j-1] = temp;
            }
        }
    }
    else{
        cout<<"invalid choice. Type (h) to flip horizontally and (v) to flip vertically."<<endl;
        resizeFlip();  // Handling errors
    }
}
void mergeImages(){
  //declaring and intializing the name and the array of the second image
  char second_image_name[100];
  unsigned char second_image [SIZE][SIZE];

  cout << "Enter the name of the other image you need to merge : "  ;
  cin >> second_image_name ;
  
  strcat (second_image_name, ".bmp"); //making sure its the correct format 
  readGSBMP(second_image_name, second_image); //loading the second image into the second 2D array

  for (size_t i = 0; i < SIZE; i++) //nested loop for merging the two images by taking the average of each pixel
  {
      for (size_t j = 0; j < SIZE; j++)
        image[i][j] = (image[i][j] + second_image[i][j])/2 ;  
  }
  
}
void filterInvert(){
    for (size_t i=0;i<SIZE;i++){
        for (size_t j=0;j<SIZE;j++){
            image[i][j]=255-image[i][j];
        }
    }
}
