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
