/*
FCAI – OOP Programming – 2023 - Assignment 1 
Program: ImageFilterApplier.cpp
Last Modification Date: 13/10/2023
Team Members:   1- Mohamed Mahmoud Khamis Rezk               (20221129)    mohamedkhamis20045@gmail.com
                2- Ibrahem Medhat Mahmoud Mohamed El Zennary (20221003)    ibra.medhat@gmail.com
                3- Ziad Sherif Ahmed Mohamed Ismael          (20220143)    ziad.ismael.studymail@gmail.com
TA:
Purpose:
*/

#include <iostream>
#include <cstring>
#include <string>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE]; // => "SIZE" is defined to be a constant int = 256 (# of pixels in row/col.)

void menuSelect();  
void saveImage();
void loadImage();
void filterBlacknWhite();
void filterFlip(); 
void filterMerge();
void filterInvert(); 
void filterDarkenLighten();
void filterRotate();
void filterCrop(); 
void filterShrink(); //  <= added in this commit

int main(){
    cout<<"Ahlan ya user ya habibi"<<endl;
    cout<<"Please enter file name of the image to process: ";
    loadImage();
    menuSelect();
    return 0;
}


void menuSelect(){     //function responsible for handling the choice of the user till he exit    
    string selector;  //The choice of the user 
    string options[17]={"1-Black & White Filter","2-Invert Filter",
                        "3-Merge Filter", "4-Flip Image", "5-Darken and Lighten Image",
                        "6-Rotate Image","7-Detect image edges Filter","8-Enlarge Image",   
                        "9-Shrink Image","a-Mirror 1/2 Image","b-Shuffle Image",            
                        "c-Blur Image","d-Crop Image","e-Skew Image Right","f-Skew Image Up",
                        "s-Save the image to a file","0-Exit"};// <= array saveing the filters to choose from
    
    for (size_t i = 0; i < 17; i++){    // printing the menu to the user by the array we made
        cout << options[i] << endl;
    } 
    while (selector[0] != '0'){    // while loop to make sure the user's able to choose what to do till he exit by typing 0
        cout << "Please select a filter to apply , '0' to exit or 's' to save : " ; 
        cin >> selector ;
        if (selector.length() == 1){
            switch (selector[0]){ //Calling the functions by the input of the user
            case '1':
                filterBlacknWhite();
                break;
            case '2':
                filterInvert();
                break;
            case '3':
                filterMerge();
                break;
            case '4':
                filterFlip();
                break;
            case '5':
                filterDarkenLighten();
                break;
            case '6':
                filterRotate();
                break;
            case '9':
              filterShrink();
              break;
            case 'd':
                filterCrop();
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
        else{
            cout << "Invalid Input or Filter not created yet" << endl;
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
    cout << "Filter has been applied." << endl;
}
void filterFlip(){
    string selector;
    char image_copy[SIZE][SIZE];

    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            image_copy[i][j] = image[i][j]; //making a copy of the 2D array
        }
    }   
    cout<<"Flip (h)orizontally or (v)ertically? ";
    while (true)
    {
        cin>>selector;
        if (selector[0]=='h' && selector.length() == 1){
            for(size_t i=0; i<SIZE/2; i++){ // we only need to go to half of the array cuz if we continue it will revert the flip
                for(size_t j=0; j<SIZE; j++){
                    int temp = image[i][j];                //  <=
                    image[i][j] = image_copy[SIZE-1-i][j]; //  <=  this three lines of code responsible for swapping pixels
                    image[SIZE-i-1][j] = temp;             //  <=
                }
            }
        cout << "Filter has been applied." << endl;
        break;// make sure to exit from the while loop if the user entered valid input
        }
        else if(selector[0]=='v' && selector.length() == 1){
            for(size_t i=0; i<SIZE; i++){
                for(size_t j=0; j<SIZE/2; j++){
                    int temp = image[i][j];
                    image[i][j] = image_copy[i][SIZE-1-j];
                    image[i][SIZE-j-1] = temp;
                }
            }
        cout << "Filter has been applied." << endl;
        break;// make sure to exit from the while loop if the user entered valid input
        }
        else{
            cout<<"invalid choice. Type (h) to flip horizontally and (v) to flip vertically."<<endl;
        }
    }
        
    
    
}
void filterMerge(){
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
    cout << "Filter has been applied." << endl;
}
void filterDarkenLighten(){ //responsible for lighten or darken by 50 %
  // taking the choice from the user either to darken or lighten
  string selector;
  cout << "Do you want to (d)arken or (l)ighten? " << endl;
  while (true)
  {
    cin >> selector;
    if (selector.length() == 1 && (selector == "l" || selector == "d"))
    {
        for (size_t i = 0; i < SIZE; i++) // nested loop for increasing or decreasing the brightness by 50 %
        {
            for (size_t j = 0; j < SIZE; j++)
            {
                if (selector == "d")
                {
                    if((image[i][j] +(image[i][j] * 0.5) ) <= 0) // keep the image in our range of colors 
                        image[i][j] = 0;   
                    else 
                        image[i][j] = image[i][j] - (image[i][j] ) * 0.5 ;
                }
                else if (selector == "l")
                {
                    if((image[i][j] +(image[i][j] * 0.5) ) >= 255) // keep the image in our range of colors 
                        image[i][j] = 255; 
                    else 
                        image[i][j] = image[i][j] +(image[i][j] ) * 0.5 ;
                }
            }
        }
        cout << "Filter has been applied." << endl;
        break; // make sure to exit from the while loop if the user entered valid input
    }
    else
        cout << "Invalid choice. Please Type (d) to Darken or (l) to Lighten." << endl;
  }
    
}
void filterRotate(){
    string selector;
    cout<<"Rotate (90) , (180) , (270) ?"<<endl;
    while (true)
    {   
        cin>>selector;
        if (selector == "360"){
            cout << "Filter has been applied." << endl;
            return; //returns the same photo
        }
        else if (selector == "90"){
            unsigned char image_rotated[SIZE][SIZE]; //creating a new 2d array to store the new rotated image
            for (size_t i=0;i<SIZE;i++){
                for (size_t j=0;j<SIZE;j++){
                    image_rotated[j][SIZE-1-i]=image[i][j];
                }
            }
            for (size_t i=0;i<SIZE;i++){
                for (size_t j=0;j<SIZE;j++){
                    image[i][j]=image_rotated[i][j]; //storing the new values in the original image
                }
            }
            cout << "Filter has been applied." << endl;
            break;// make sure to exit from the while loop if the user entered valid input
        }
        else if (selector == "180"){
            unsigned char image_rotated[SIZE][SIZE]; //creating a new 2d array to store the new rotated image
            for (int i=0;i<SIZE;i++){
                for (int j=0;j<SIZE;j++){
                    image_rotated[SIZE-1-i][SIZE-1-j]=image[i][j]; 
                }
            }
            for (int i=0;i<SIZE;i++){
                for (int j=0;j<SIZE;j++){
                    image[i][j]=image_rotated[i][j];//storing the new values in the original image
                }
            }
            cout << "Filter has been applied." << endl;
            break;// make sure to exit from the while loop if the user entered valid input
        }
        else if (selector == "270"){
            unsigned char image_rotated[SIZE][SIZE];
            for (size_t i=0;i<SIZE;i++){
                for (size_t j=0;j<SIZE;j++){
                    image_rotated[SIZE-1-j][i] = image[i][j];
                }
            }
            for (size_t i = 0; i < SIZE; i++) {
                for (size_t j = 0; j < SIZE; j++) {
                    image[i][j] = image_rotated[i][j]; // Storing the rotated values in the original image
                }
            }
            cout<<"Filter Has Been Applied!"<<endl;
            break; // make sure to exit from the while loop if the user entered valid input
        }
        else{
            cout<<"Invalid Input! Type '90' , '180' or '360' to apply the filter : "<<endl;
        }
    }
    
}
void filterCrop(){
    int x{}, y{}, l{}, w{};
    cout<<"Please enter x, y, l and w consececutivly: ";
    cin>>x>>y>>l>>w; 
    unsigned char image_cropped[SIZE][SIZE];
    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            image_cropped[i][j]=255;
        }
    }   
    for(size_t i=x; i<(x+l); i++){
        for(size_t j=y; j<(y+w); j++){
            image_cropped[i][j]=image[i][j];
        }
    }
    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            image[i][j]=image_cropped[i][j];
        }
    }
    cout<<"Filter has been applied."<<endl;
}

void filterShrink(){
    unsigned char temp_image[SIZE][SIZE]; 
    int x {}; // x is the scale that will allow us to controlo the loop behavior
    for (size_t i = 0; i < SIZE; i++) // make the temp photo white
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            temp_image[i][j] = 255 ;
        }   
    }

    string selector;
    cout << "Choose an option to shrink with : " << endl << "1- 1/2" << endl << "2- 1/3" << endl << "3- 1/4" << endl;
    while (true)// for handling input errors
    {
        cin >> selector;

        if(selector == "1") x = 2;
        else if(selector == "2") x = 3 ;
        else if(selector == "3") x = 4;
        else{
            cout << "Invalid Input ! choose '1' for 1/2 , '2' for 1/3 or '3' for 1/4 : " ;
            continue;// return the user back to enter the correct input 
        }
        
        // main nested loops that shrunken the image by taking the average of X pixels and put it in one pixel the temp image
        for (size_t i = 0; i < SIZE - 1; i += x) {
            for (size_t j = 0; j < SIZE - 1; j += x) {
                if( x == 4)
                temp_image[i / x][j / x] = (image[i][j] + image[i][j + 1] + image[i + 1][j] + image[i + 1][j + 1]) / x;
                else if (x == 3)
                temp_image[i / x][j / x] = (image[i][j] + image[i][j + 1] + image[i + 1][j]) / x;
                else if (x == 2)
                temp_image[i / x][j / x] = (image[i][j] + image[i][j + 1] ) / x;
            }
        }
        break; // get out of the while loop if the user enters valid input
    }
    //Uptading the original image to the Shrunken Image
    for (size_t i = 0; i < SIZE ; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            image[i][j] = temp_image[i][j];
        }
    }
}

