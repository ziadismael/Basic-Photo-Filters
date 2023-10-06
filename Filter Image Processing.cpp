/*
FCAI – OOP Programming – 2023 - Assignment 1 
Program: ImageFilterApplier.cpp
Last Modification Date: 6/10/2023
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

void menuSelect();  //  <= added in this commit
void saveImage();
void loadImage();
void filterBlacknWhite();
void resizeFlip(); 
void mergeImages();
void filterInvert(); 
void darklightImage(); 

int main(){
    cout<<"Ahlan ya user ya habibi"<<endl;
    cout<<"Please enter file name of the image to process: ";
    loadImage();
    menuSelect();
    return 0;
}

void menuSelect(){     //function responsible for handling the choice of the user till he exit    
    char selector;  //The choice of the user 
    string options[17]={"1-Black & White Filter","2-Invert Filter",
                        "3-Merge Filter", "4-Flip Image", "5-Darken and Lighten Image",
                        "6-Rotate Image","7-Detect image edges Filter","8-Enlarge Image",   
                        "9-Shrink Image","a-Mirror 1/2 Image","b-Shuffle Image",            
                        "c-Blur Image","d-Crop Image","e-Skew Image Right","f-Skew Image Up",
                        "s-Save the image to a file","0-Exit"};// <= array saveing the filters to choose from
    
    for (size_t i = 0; i < 17; i++){    // printing the menu to the user by the array we made
        cout << options[i] << endl;
    } 

    while (selector != '0'){    // while loop to make sure the use able to choose what to do till he exit by typing 0
        cout << "Please select a filter to apply or 0 to exit : " ; 
        cin >> selector ;
        switch (selector){ //Calling the functions by the input of the user
        case '1':
            filterBlacknWhite();
            break;
        case '2':
            filterInvert();
            break;
        case '3':
            mergeImages();
            break;
        case '4':
            resizeFlip();
            break;
        case '5':
            darklightImage();
            break;
        case 's':
            saveImage();
            break;
        case '0':
           break;
        default: // handling input errors
            cout<<"Invalid Input or Filter not created yet" << endl;
        }
    }
}

void loadImage(){   //responsible for loading the image into 2D array
    char image_name[100];
    cin >> image_name; // after taking image name
    strcat (image_name, ".bmp"); //making sure its the correct format 
    readGSBMP(image_name, image);
}

void saveImage(){   //responsible for saving the image from 2D array after applying filters
    char image_name[100];
    cout << "Enter the name of the new image : " ;
    cin>>image_name;
    strcat (image_name, ".bmp");
    writeGSBMP(image_name, image); //function from the "mpblib" library to convert array to image
    cout << "Done! Image has been saved as : " << image_name << endl;
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

void darklightImage(){ //responsible for lighten or darken by 50 %
  // taking the choice from the user either to darken or lighten
  int choice;
  cout << "Choose what you need from the following list :" << endl;
  cout << "1-Darken" << endl << "2-Lighten" << endl;
  cin >> choice;

  for (size_t i = 0; i < SIZE; i++) // nested loop for increasing or decreasing the brightness by 50 %
  {
    for (size_t j = 0; j < SIZE; j++)
    {
        if (choice == 1)
        {
          if((image[i][j] +(image[i][j] * 0.5) )<=0) image[i][j] = 0;
          else image[i][j] = image[i][j] - (image[i][j] ) * 0.5 ;
        }
        else
        {
          if((image[i][j] +(image[i][j] * 0.5) )>=255) image[i][j] = 255;
          else image[i][j] = image[i][j] +(image[i][j] ) * 0.5 ;
        }
    }
  }
}
