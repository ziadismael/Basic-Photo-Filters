/*
FCAI – OOP Programming – 2023 - Assignment 1 
Program: Basic Filter Applier
Last Modification Date: 18/10/2023
Team Members:   1- Mohamed Mahmoud Khamis Rezk               (20221129)    mohamedkhamis20045@gmail.com
                2- Ibrahem Medhat Mahmoud Mohamed El Zennary (20221003)    ibra.medhat@gmail.com
                3- Ziad Sherif Ahmed Mohamed Ismael          (20220143)    ziad.ismael.studymail@gmail.com
TA:
Purpose: This program is designed and implemented to apply various types of filters on an image
*/

#include <iostream>
#include <string>
#include <cstring>
#include "bmplib.cpp"
#include <cmath>

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image_greyed[SIZE][SIZE];
bool isGreyed = false;

void loadImageRGB();
void saveImageRGB();
void saveImageGS();
void toGreyScale();
void toBlacknWhite();
void invertImage();
void mergeImage();
void flipImage();
void imageBrightness();
void rotateImage();
void detectImageEdges();
void mirrorImage();
void cropImage();
void skewImageHorizontally();
void skewImageVertically();
void shrinkImage();
void blurImage();
void menuSelect();
void enlargeImage();
void shuffleImage();

int main(){
    cout<<"Ahlan ya user ya habibi"<<endl;
    cout<<"Please enter file name of the image to process: ";
    loadImageRGB();
    menuSelect();
    return 0;
}

void loadImageRGB(){
    char image_name[100];
    cin >> image_name; // after taking image name
    strcat (image_name, ".bmp"); //making sure its the correct format 
    readRGBBMP(image_name, image);
}

void saveImageRGB(){
    char image_name[100];
    cout << "Enter the name of the new image you want to save : " ;
    cin>>image_name;
    strcat (image_name, ".bmp");
    writeRGBBMP(image_name, image);
    cout << "Done! Image has been saved as : " << image_name << endl;
}

void saveImageGS(){
    //responsible for saving the image from 2D array after applying filters
    char image_name[100];
    cout << "Enter the name of the new image you want to save : " ;
    cin>>image_name;
    strcat (image_name, ".bmp");
    writeGSBMP(image_name, image_greyed); //function from the "mpblib" library to convert array to image
    cout << "Done! Image has been saved as : " << image_name << endl;
}

void toBlacknWhite(){
    for (size_t i=0; i<SIZE; i++){
        for (size_t j=0; j<SIZE; j++){
            int average_pixel{};
            for (size_t k=0; k<RGB; k++){
                average_pixel+=image[i][j][k];
            }
            average_pixel/3;
            if (average_pixel<382.5){
                image[i][j][0]=0;
                image[i][j][1]=0;
                image[i][j][2]=0;
            }
            else{
                image[i][j][0]=255;
                image[i][j][1]=255;
                image[i][j][2]=255;
            }
        }   
    }
    cout<<"Filter has been applied."<<endl;

}

void toGreyScale(){
    isGreyed = true;
    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            int average_pixel{};
            for(size_t k=0; k<RGB; k++){
                average_pixel+=image[i][j][k];
            }
            average_pixel/=3;
            image_greyed[i][j]= average_pixel;
        }
    }
    cout<<"Filter has been applied."<<endl;

}

void invertImage(){
    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            for(size_t k=0; k<RGB; k++){
                image[i][j][k]=255-image[i][j][k];
            }
        }
    }
    cout<<"Filter has been applied."<<endl;

}

void cropImage(){
    int x{}, y{}, l{}, w{};
    cout<<"Please enter x, y, l and w consececutivly: ";
    cin>>x>>y>>l>>w; 
    unsigned char image_cropped[SIZE][SIZE][RGB];
    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            image_cropped[i][j][0]=255;
            image_cropped[i][j][1]=255;
            image_cropped[i][j][2]=255;
        }
    }   
    for(size_t i=x; i<(x+l); i++){
        for(size_t j=y; j<(y+w); j++){
            image_cropped[i][j][0]=image[i][j][0];
            image_cropped[i][j][1]=image[i][j][1];
            image_cropped[i][j][2]=image[i][j][2];
        }
    }
    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            image[i][j][0]=image_cropped[i][j][0];
            image[i][j][1]=image_cropped[i][j][1];
            image[i][j][2]=image_cropped[i][j][2];
        }
    }
    cout<<"Filter has been applied."<<endl;

}

void mergeImage(){
    //declaring and intializing the name and the array of the second image
    char second_image_name[100];
    unsigned char second_image [SIZE][SIZE][RGB];

    cout << "Enter the name of the other image you need to merge : "  ;
    cin >> second_image_name ;

    strcat (second_image_name, ".bmp"); //making sure its the correct format 
    readRGBBMP(second_image_name, second_image); //loading the second image into the second 3D array

    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            for(size_t k=0; k<RGB; k++){
                image[i][j][k] = (image[i][j][k] + second_image[i][j][k])/2;
            }
        }
    }
    cout<<"Filter has been applied."<<endl;

}

void flipImage(){
    string selector;
    char image_copy[SIZE][SIZE][RGB];

    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            image_copy[i][j][0] = image[i][j][0];
            image_copy[i][j][1] = image[i][j][1];
            image_copy[i][j][2] = image[i][j][2];
        }
    } 

    cout<<"Flip (h)orizontally or (v)ertically? ";
    while (true)
    {
        cin>>selector;
        if (selector == "h"){
            for(size_t i=0; i<SIZE/2; i++){ // we only need to go to half of the array cuz if we continue it will revert the flip
                for(size_t j=0; j<SIZE; j++){
                    for(size_t k=0; k<RGB; k++){
                        int temp = image[i][j][k];                //  <=
                        image[i][j][k] = image_copy[SIZE-1-i][j][k]; //  <=  this three lines of code responsible for swapping pixels
                        image[SIZE-i-1][j][k] = temp;             //  <=
                    }
                }
            }
        cout << "Filter has been applied." << endl;
        break;// make sure to exit from the while loop if the user entered valid input
        }
        else if(selector == "v"){
            for(size_t i=0; i<SIZE; i++){
                for(size_t j=0; j<SIZE/2; j++){
                    for(size_t k=0; k<RGB; k++){
                        int temp = image[i][j][k];
                        image[i][j][k] = image_copy[i][SIZE-1-j][k];
                        image[i][SIZE-j-1][k] = temp;
                    }
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

void imageBrightness(){
    //responsible for lighten or darken by 50 %
    // taking the choice from the user either to darken or lighten
    string selector;
    cout << "Do you want to (d)arken or (l)ighten? ";
    while (true)
    {
        cin >> selector;
        if ((selector == "l" || selector == "d")){
            for (size_t i = 0; i < SIZE; i++){ // nested loop for increasing or decreasing the brightness by 50 %
                for (size_t j = 0; j < SIZE; j++){
                    for(size_t k=0; k<RGB; k++){
                        if (selector == "d"){
                            if((image[i][j][k] +(image[i][j][k] * 0.5) ) <= 0) // keep the image in our range of colors 
                                image[i][j][k] = 0;   
                            else 
                                image[i][j][k] = image[i][j][k] - (image[i][j][k] ) * 0.5 ;
                        }
                        else if (selector == "l")
                        {
                            if((image[i][j][k] +(image[i][j][k] * 0.5) ) >= 255) // keep the image in our range of colors 
                                image[i][j][k] = 255; 
                            else 
                                image[i][j][k] = image[i][j][k] + (image[i][j][k] ) * 0.5 ;
                        }
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

void rotateImage(){
    string selector;
    unsigned char image_rotated[SIZE][SIZE][RGB];

    cout<<"Rotate (90) , (180) , (270) ?"<<endl;
    while (true)
    {   
        cin>>selector;
        if (selector == "360"){
            cout << "Filter has been applied." << endl;
            return; //returns the same photo
        }
        else if (selector == "90"){
            for (size_t i=0;i<SIZE;i++){
                for (size_t j=0;j<SIZE;j++){
                    image_rotated[j][SIZE-1-i][0]=image[i][j][0];
                    image_rotated[j][SIZE-1-i][1]=image[i][j][1];
                    image_rotated[j][SIZE-1-i][2]=image[i][j][2];
                }
            }
            for (size_t i=0;i<SIZE;i++){
                for (size_t j=0;j<SIZE;j++){
                    image[i][j][0]=image_rotated[i][j][0];
                    image[i][j][1]=image_rotated[i][j][1];
                    image[i][j][2]=image_rotated[i][j][2];
                }
            }
            cout << "Filter has been applied." << endl;
            break;// make sure to exit from the while loop if the user entered valid input
        }
        else if (selector == "180"){
            for (int i=0;i<SIZE;i++){
                for (int j=0;j<SIZE;j++){
                    image_rotated[SIZE-1-i][SIZE-1-j][0]=image[i][j][0]; 
                    image_rotated[SIZE-1-i][SIZE-1-j][1]=image[i][j][1]; 
                    image_rotated[SIZE-1-i][SIZE-1-j][2]=image[i][j][2]; 
                }
            }
            for (int i=0;i<SIZE;i++){
                for (int j=0;j<SIZE;j++){
                    image[i][j][0]=image_rotated[i][j][0];
                    image[i][j][1]=image_rotated[i][j][1];
                    image[i][j][2]=image_rotated[i][j][2];
                }
            }
            cout << "Filter has been applied." << endl;
            break;// make sure to exit from the while loop if the user entered valid input
        }
        else if (selector == "270"){
            for (size_t i=0;i<SIZE;i++){
                for (size_t j=0;j<SIZE;j++){
                    image_rotated[SIZE-1-j][i][0] = image[i][j][0];
                    image_rotated[SIZE-1-j][i][1] = image[i][j][1];
                    image_rotated[SIZE-1-j][i][2] = image[i][j][2];
                }
            }
            for (size_t i = 0; i < SIZE; i++) {
                for (size_t j = 0; j < SIZE; j++) {
                    image[i][j][0] = image_rotated[i][j][0];
                    image[i][j][1] = image_rotated[i][j][1];
                    image[i][j][2] = image_rotated[i][j][2];
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

void detectImageEdges(){
    unsigned char image_bw[SIZE][SIZE];
    toBlacknWhite();
    for (size_t i = 0; i < SIZE; i++){
        for (size_t j = 0; j < SIZE; j++){
            image_bw[i][j] = image[i][j][0];
        }
        
    }
    
    for(size_t i=0; i<SIZE; i++){
        for (size_t j=1; j<SIZE-1; j++){
            if(image_bw[i][j-1] == 255){ 
                if(image_bw[i][j]==image_bw[i][j+1]==0){
                    image_bw[i][j] = 0; //leaving two consecutive black pixels in a series of consecutive ones
                    image_bw[i][j+1] = 0;
                }
                else{
                    image_bw[i][j]=255; //whitening the others and leaving only border-like shape of a black object
                }
            }
            else{
                if(image_bw[i][j]==0){
                    if(image_bw[i][j+1]==0){
                        image_bw[i][j+1]=255; //same but if the initial pixel is black not white
                    }
                }
            }
        }
    }
    for (size_t i = 0; i < SIZE; i++){
        for (size_t j = 0; j < SIZE; j++){
            image[i][j][0] = image_bw[i][j];
            image[i][j][1] = image_bw[i][j];
            image[i][j][2] = image_bw[i][j];
        }
        
    }
}

void skewImageHorizontally(){
    // filter reponsabile for skew image to the right
    double angle {} , base {} , move{} , step{};

    cout << "Please enter degree to skew right :  " ;
    cin >> angle;

    angle = angle*22 / 180 * 7 ; // changing the angle take from the user to radian instead of degree
    base = (256 / (1 + (1/tan(angle)))); // the base of the new image so we can shrink it to fit the image
    step = SIZE - base ;  // the place where we will start filling the new image after shrinking it
    move = step / SIZE ; // the rate that we will move each i to make the photo skew correct

    unsigned char temp_image [SIZE][SIZE][RGB] ;

    for (size_t i = 0; i < SIZE ; i++) { // make the temp image white
        for (size_t j = 0; j < SIZE; j++) {
            temp_image[i][j][0] = 255;
            temp_image[i][j][1] = 255;
            temp_image[i][j][2] = 255;
        }
    }

    for (size_t i = 0; i < SIZE; i++) // shrinking the image columns
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            temp_image[i][(j*(int)base) / SIZE][0] = image[i][j][0] ;       
            temp_image[i][(j*(int)base) / SIZE][1] = image[i][j][1] ;       
            temp_image[i][(j*(int)base) / SIZE][2] = image[i][j][2] ;       
        }
    }
    
    for (size_t i = 0; i < SIZE ; i++) {//updating the original image to the srhinked one
        for (size_t j = 0; j < SIZE; j++) {
            image[i][j][0] = temp_image[i][j][0];
            image[i][j][1] = temp_image[i][j][1];
            image[i][j][2] = temp_image[i][j][2];
        }
    }

    for (size_t i = 0; i < SIZE; i++){ //skewing the image after shrinking
        for (size_t j = 0; j < SIZE; j++)
        {
            temp_image[i][j + (int) step][0] = image[i][j][0]; 
            temp_image[i][j + (int) step][1] = image[i][j][1]; 
            temp_image[i][j + (int) step][2] = image[i][j][2]; 
        }
        step-= move;
        
    }
    
    // updating the original image with the final image
    for (size_t i = 0; i < SIZE ; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            image[i][j][0] = temp_image[i][j][0];
            image[i][j][1] = temp_image[i][j][1];
            image[i][j][2] = temp_image[i][j][2];
        }
    }
    cout << "Filter has been applied." << endl;
    
}

void mirrorImage(){
    string selector;
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
    unsigned char image_mirrored[SIZE][SIZE][RGB];
    unsigned char image_copy[SIZE][SIZE][RGB];
    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            image_mirrored[i][j][0] = image[i][j][0]; 
            image_mirrored[i][j][1] = image[i][j][1]; 
            image_mirrored[i][j][2] = image[i][j][2]; 
        }
    }
    while (true){ // for handling input errors
        cin>>selector;
        if (selector == "l"){
            for(size_t i=0; i<SIZE; i++){
                for(size_t j=(SIZE/2)-1; j<SIZE; j++){
                    image_mirrored[i][j][0] = image_mirrored[i][SIZE-1-j][0];
                    image_mirrored[i][j][1] = image_mirrored[i][SIZE-1-j][1];
                    image_mirrored[i][j][2] = image_mirrored[i][SIZE-1-j][2];
                }
            }
            break;
        }
        else if (selector == "r"){
            for(size_t i=0; i<SIZE; i++){
                for(size_t j = 0; j < (SIZE/2); j++){
                    image_mirrored[i][j][0] = image_mirrored[i][SIZE-1-j][0];
                    image_mirrored[i][j][1] = image_mirrored[i][SIZE-1-j][1];
                    image_mirrored[i][j][2] = image_mirrored[i][SIZE-1-j][2];
                }
            }
            break;
        }
        else if (selector == "u"){
            for(size_t i= (SIZE / 2); i < SIZE; i++){
                for(size_t j=0; j<SIZE; j++){
                    image_mirrored[i][j][0] = image_mirrored[SIZE-1-i][j][0];
                    image_mirrored[i][j][1] = image_mirrored[SIZE-1-i][j][1];
                    image_mirrored[i][j][2] = image_mirrored[SIZE-1-i][j][2];
                }
            }
            break;
        }
        else if (selector == "d"){
            for(size_t i=0; i<(SIZE/2)-1; i++){
                for(size_t j=0; j<SIZE; j++){
                    image_mirrored[i][j][0] = image_mirrored[SIZE-1-i][j][0];
                    image_mirrored[i][j][1] = image_mirrored[SIZE-1-i][j][1];
                    image_mirrored[i][j][2] = image_mirrored[SIZE-1-i][j][2];
                }
            }
            break;
        }
        else{
            cout<<"Invalid input. Type (d) to mirror downside, (u) to mirror upperside, (l) to mirror leftside or (r) to mirror rightside."<<endl;;
        }
    }
    //Uptading the original image
    for (size_t i = 0; i < SIZE ; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            image[i][j][0] = image_mirrored[i][j][0];
            image[i][j][1] = image_mirrored[i][j][1];
            image[i][j][2] = image_mirrored[i][j][2];
        }
    }
    cout << "Filter has been applied." << endl;
}

void skewImageVertically(){
    // filter reponsabile for skew image to the up
    double angle {} , base {} , move{} , step{};

    cout << "Please enter degree to skew up :  " ;
    cin >> angle;
    while (!(0 < angle < 90))
    {
        cout << "Please enter a valid degree to skew up in range 1 to 89 : " ;
        cin >> angle;
    }
    
    angle = angle*22 / 180 * 7 ; // changing the angle take from the user to radian instead of degree

    base = (256 / (1 + (1/tan(angle)))); // the base of the new image so we can shrink it to fit the image

    step = SIZE - base ;  // the place where we will start filling the new image after shrinking it
    move = step / SIZE ; // the rate that we will move each i to make the photo skew correct

    unsigned char temp_image [SIZE][SIZE][RGB] ;

    for (size_t i = 0; i < SIZE ; i++) { // make the temp image white
        for (size_t j = 0; j < SIZE; j++) {
            temp_image[i][j][0] = 255;
            temp_image[i][j][1] = 255;
            temp_image[i][j][2] = 255;
        }
    }

    for (size_t i = 0; i < SIZE; i++) // shrinking the image columns
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            temp_image[(i*(int)base) / SIZE][j][0] = image[i][j][0] ;       
            temp_image[(i*(int)base) / SIZE][j][1] = image[i][j][1] ;       
            temp_image[(i*(int)base) / SIZE][j][2] = image[i][j][2] ;       
        }
    }
    
    for (size_t i = 0; i < SIZE ; i++) {//updating the original image to the srhinked one
        for (size_t j = 0; j < SIZE; j++) {
            image[i][j][0] = temp_image[i][j][0];
            image[i][j][1] = temp_image[i][j][1];
            image[i][j][2] = temp_image[i][j][2];
        }
    }
    for (size_t i = 0; i < SIZE ; i++) { // make the temp image white
        for (size_t j = 0; j < SIZE; j++) {
            temp_image[i][j][0] = 255;
            temp_image[i][j][1] = 255;
            temp_image[i][j][2] = 255;
        }
    }
    double orginalStep = step;
    for (size_t i = 0; i < SIZE; i++){ //skewing the image after shrinking
        for (size_t j = 0; j < SIZE; j++)
        {
            if (i + (int) step > 256  || i + (int) step == 0) // to ensure not get out of array boundries
            break;
            
            temp_image[i + (int) step][j][0] = image[i][j][0]; 
            temp_image[i + (int) step][j][1] = image[i][j][1]; 
            temp_image[i + (int) step][j][2] = image[i][j][2]; 
            step-= move;
        }
        step = orginalStep;
    }
    
    //updating the original image with the final image
    for (size_t i = 0; i < SIZE ; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            image[i][j][0] = temp_image[i][j][0];
            image[i][j][1] = temp_image[i][j][1];
            image[i][j][2] = temp_image[i][j][2];
        }
    }
    cout << "Filter has been applied." << endl;
    
}

void shrinkImage(){
    unsigned char temp_image[SIZE][SIZE][RGB]; 
    int x {}; // x is the scale that will allow us to controlo the loop behavior
    for (size_t i = 0; i < SIZE; i++) // make the temp photo white
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            temp_image[i][j][0] = 255 ;
            temp_image[i][j][1] = 255 ;
            temp_image[i][j][2] = 255 ;
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
                if( x == 4){
                    temp_image[i / x][j / x][0] = (image[i][j][0] + image[i][j + 1][0] + image[i + 1][j][0] + image[i + 1][j + 1][0]) / x;
                    temp_image[i / x][j / x][1] = (image[i][j][1] + image[i][j + 1][1] + image[i + 1][j][1] + image[i + 1][j + 1][1]) / x;
                    temp_image[i / x][j / x][2] = (image[i][j][2] + image[i][j + 1][2] + image[i + 1][j][2] + image[i + 1][j + 1][2]) / x;
                }
                else if (x == 3){
                    temp_image[i / x][j / x][0] = (image[i][j][0] + image[i][j + 1][0] + image[i + 1][j][0]) / x;
                    temp_image[i / x][j / x][1] = (image[i][j][1] + image[i][j + 1][1] + image[i + 1][j][1]) / x;
                    temp_image[i / x][j / x][2] = (image[i][j][2] + image[i][j + 1][2] + image[i + 1][j][2]) / x;
                }
                else if (x == 2){
                    temp_image[i / x][j / x][0] = (image[i][j][0] + image[i][j + 1][0] ) / x;
                    temp_image[i / x][j / x][1] = (image[i][j][1] + image[i][j + 1][1] ) / x;
                    temp_image[i / x][j / x][2] = (image[i][j][2] + image[i][j + 1][2] ) / x;
                }
            }
        }
        break; // get out of the while loop if the user enters valid input
    }
    //Uptading the original image to the Shrunken Image
    for (size_t i = 0; i < SIZE ; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            image[i][j][0] = temp_image[i][j][0];
            image[i][j][1] = temp_image[i][j][1];
            image[i][j][2] = temp_image[i][j][2];
        }
    }
  cout << "Filter has been applied." << endl;
}

void menuSelect(){
    //function responsible for handling the choice of the user till he exit    
    string selector;  //The choice of the user 
    string options[18]={"1-Black & White Filter","2-Invert Filter",
                        "3-Merge Filter", "4-Flip Image", "5-Darken and Lighten Image",
                        "6-Rotate Image","7-Detect image edges Filter","8-Enlarge Image",   
                        "9-Shrink Image","a-Mirror 1/2 Image","b-Shuffle Image",            
                        "c-Blur Image","d-Crop Image","e-Skew Image Right","f-Skew Image Up",
                        "g-Greyscale", "s-Save the image to a file","0-Exit"};// <= array saveing the filters to choose from
    
    for (size_t i = 0; i < 18; i++){    // printing the menu to the user by the array we made
        cout << options[i] << endl;
    } 
    while (selector[0] != '0'){    // while loop to make sure the user's able to choose what to do till he exit by typing 0
        cout << "Please select a filter to apply , '0' to exit or 's' to save : " ; 
        cin >> selector ;
        if (selector.length() == 1){
            switch (selector[0]){ //Calling the functions by the input of the user
            case '1':
                toBlacknWhite();
                break;
            case '2':
                invertImage();
                break;
            case '3':
                mergeImage();
                break;
            case '4':
                flipImage();
                break;
            case '5':
                imageBrightness();
                break;
            case '6':
                rotateImage();
                break;
            case '7':
                detectImageEdges();
                break;
            case '8':
                enlargeImage();
                break;
            case '9':
                shrinkImage();
                break;
            case 'a':
                mirrorImage();
                break;
            case 'b':
                shuffleImage();
                break;
            case 'c':
                blurImage();
                break;
            case 'd':
                cropImage();
                break;
            case 'e':
                skewImageHorizontally();
                break;
            case 'f':
                skewImageVertically();
                break;
            case 'g':
                toGreyScale();
                break;
            case 's':
                if(isGreyed)
                    saveImageGS();
                else
                    saveImageRGB();
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

void blurImage(){
    unsigned char temp_image[SIZE][SIZE][RGB];

    for (size_t i = 0; i < SIZE; i++){
        for (size_t j = 0; j < SIZE; j++){
            for (size_t k=0; k<RGB; k++){
                // taking the average of the neighboring pixels to blur the image
                temp_image[i][j][k] = (image[i - 1][j + 1][k] + image[i - 1][j - 1][k] + image[i - 1][j][k] +
                                    image[i][j - 1][k] + image[i + 1][j - 1][k] + image[i][j + 1][k] + 
                                    image [i + 1][j][k] + image[i + 1][j + 1][k] + image[i - 2][j + 2][k] +
                                    image[i - 2][j - 2][k] + image[i - 2][j][k] + image[i][j - 2][k] + 
                                    image[i + 2][j - 2][k] + image[i][j + 2][k] + image [i + 2][j][k] + 
                                    image[i + 2][j + 2][k]) / 16 ;
            }
        }
    }
    //Uptading the original image to the Blur Image
    for (size_t i = 0; i < SIZE ; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            image[i][j][0] = temp_image[i][j][0];
            image[i][j][1] = temp_image[i][j][1];
            image[i][j][2] = temp_image[i][j][2];
        }
    }
    cout << "Filter has been applied." << endl;
}

void enlargeImage() {
    string selector;
    cout << "Which quarter do you want to enlarge? (Enter '1' for the first quarter): ";
    cin >> selector;

    if (selector == "1") {
        // Create a copy of the first quarter of the image
        unsigned char quarterCopy[SIZE / 2][SIZE / 2][RGB];
        for (size_t i = 0; i < SIZE / 2; i++) {
            for (size_t j = 0; j < SIZE / 2; j++) {
                quarterCopy[i][j][0] = image[i][j][0];
                quarterCopy[i][j][1] = image[i][j][1];
                quarterCopy[i][j][2] = image[i][j][2];
            }
        }

        // Duplicate each pixel four times in the enlarged quarter
        for (size_t i = 0; i < SIZE / 2; ++i) {
            for (size_t j = 0; j < SIZE / 2; ++j) {
                for(size_t k=0; k<RGB; k++){
                    // Top-Left
                    image[i * 2][j * 2][k] = quarterCopy[i][j][k];
                    // Top-Right
                    image[i * 2][j * 2 + 1][k] = quarterCopy[i][j][k];
                    // Bottom-Left
                    image[i * 2 + 1][j * 2][k] = quarterCopy[i][j][k];
                    // Bottom-Right
                    image[i * 2 + 1][j * 2 + 1][k] = quarterCopy[i][j][k];
                }
            }
        }

    }
    else if (selector == "2") {
        // Create a copy of the second quarter of the image
        unsigned char quarterCopy[SIZE / 2][SIZE / 2][RGB];
        for (size_t i = 0; i < SIZE / 2; ++i) {
            for (size_t j = (SIZE /2) -1 ; j < SIZE; ++j) {
                quarterCopy[i][j-127][0] = image[i][j][0];
                quarterCopy[i][j-127][1] = image[i][j][1];
                quarterCopy[i][j-127][2] = image[i][j][2];
            }
        }

        // Enlarge the copied quarter by duplicating each pixel four times
        for (size_t i = 0 ; i < SIZE / 2; ++i) {
            for (size_t j = 0; j < SIZE / 2; ++j) {
                for(size_t k=0; k<RGB; k++){
                    // Top-Left
                    image[i * 2][j * 2][k] = quarterCopy[i][j][k];
                    // Top-Right
                    image[i * 2][j * 2 + 1][k] = quarterCopy[i][j][k];
                    // Bottom-Left
                    image[i * 2 + 1][j * 2][k] = quarterCopy[i][j][k];
                    // Bottom-Right
                    image[i * 2 + 1][j * 2 + 1][k] = quarterCopy[i][j][k];
                }
            }
        }
    }
    else if (selector == "3") {
        // Create a copy of the 3rd quarter of the image
        unsigned char quarterCopy[SIZE / 2][SIZE / 2][RGB];
        for (size_t i = SIZE / 2; i < SIZE; ++i) {
            for (size_t j = 0; j < SIZE / 2; ++j) {
                quarterCopy[i - 128][j][0] = image[i][j][0];
                quarterCopy[i - 128][j][1] = image[i][j][1];
                quarterCopy[i - 128][j][2] = image[i][j][2];
            }
        }


        // Duplicate each pixel four times in the enlarged quarter
        for (size_t i = 0; i < SIZE / 2; ++i) {
            for (size_t j = 0; j < SIZE / 2; ++j) {
                for(size_t k=0; k<RGB; k++){
                    // Top-Left
                    image[i * 2][j * 2][k] = quarterCopy[i][j][k];
                    // Top-Right
                    image[i * 2][j * 2 + 1][k] = quarterCopy[i][j][k];
                    // Bottom-Left
                    image[i * 2 + 1][j * 2][k] = quarterCopy[i][j][k];
                    // Bottom-Right
                    image[i * 2 + 1][j * 2 + 1][k] = quarterCopy[i][j][k];
                }
            }
        }

    }


    else if (selector == "4") {
        // Create a copy of the 4th quarter of the image
        unsigned char quarterCopy[SIZE / 2][SIZE / 2][RGB];
        for (size_t i = (SIZE / 2) ; i < SIZE; i++) {
            for (size_t j = (SIZE / 2) ; j < SIZE; j++) {
                quarterCopy[i - 128][j - 128][0] = image[i][j][0];
                quarterCopy[i - 128][j - 128][1] = image[i][j][1];
                quarterCopy[i - 128][j - 128][2] = image[i][j][2];
            }
        }
        for (size_t i = 0; i< SIZE/2 ;i++){
            for (size_t j=0 ; j<SIZE/2; j++){
                for(size_t k=0; k<RGB; k++){
                    image[i * 2][j * 2][k]=quarterCopy[i][j][k];
                    image[i * 2+1][j * 2+1][k]=quarterCopy[i][j][k];
                    image[i * 2][j * 2+1][k]=quarterCopy[i][j][k];
                    image[i * 2+1][j * 2][k]=quarterCopy[i][j][k];

                }
            }
        }
    }
    cout<<"Filter has been applied."<<endl;

}

void shuffleImage(){
    unsigned char image_copy[SIZE][SIZE][RGB];
    unsigned char quarter1[SIZE/2][SIZE/2][RGB];
    unsigned char quarter2[SIZE/2][SIZE/2][RGB];
    unsigned char quarter3[SIZE/2][SIZE/2][RGB];
    unsigned char quarter4[SIZE/2][SIZE/2][RGB];
    
    string selector, inpt;
    for(size_t i=0; i<SIZE/2; i++){
        for(size_t j=0; j<SIZE/2; j++){
            quarter1[i][j][0] = image[i][j][0];
            quarter1[i][j][1] = image[i][j][1];
            quarter1[i][j][2] = image[i][j][2];
        }
    }
    for(size_t i=0; i<SIZE/2; i++){
        for(size_t j=(SIZE/2); j<SIZE; j++){
            quarter2[i][j-128][0] = image[i][j][0];
            quarter2[i][j-128][1] = image[i][j][1];
            quarter2[i][j-128][2] = image[i][j][2];
        }
    }
    for(size_t i=(SIZE/2); i<SIZE; i++){
        for(size_t j=0; j<SIZE/2; j++){
            quarter3[i-128][j][0] = image[i][j][0];
            quarter3[i-128][j][1] = image[i][j][1];
            quarter3[i-128][j][2] = image[i][j][2];
        }
    }
    for(size_t i=(SIZE/2); i<SIZE; i++){
        for(size_t j=(SIZE/2); j<SIZE; j++){
            quarter4[i-128][j-128][0] = image[i][j][0];
            quarter4[i-128][j-128][1] = image[i][j][1];
            quarter4[i-128][j-128][2] = image[i][j][2];
        }
    }

    cout<<"New order of quarters ? ";
    cin>>selector;
    // selector="";
    // getline(cin, inpt);
    // for (int i = 0; i<inpt.length(); i++)
    //     if (inpt[i] != ' ')
    //         selector = inpt[i];

    //filling the first quarter specified by user
    for (size_t i = 0; i < SIZE/2; i++){
        for (size_t j = 0; j < SIZE/2; j++){
            for (size_t k=0; k<RGB; k++){
                if (selector[0] == '1'){
                    image_copy[i][j][k] = quarter1[i][j][k];                
                }
                else if (selector[0]=='2'){
                    image_copy[i][j][k] = quarter2[i][j][k];
                }
                else if (selector[0]=='3'){
                    image_copy[i][j][k] = quarter3[i][j][k];
                }
                else if (selector[0]=='4'){
                    image_copy[i][j][k] = quarter4[i][j][k];
                }
            }
        }
    }
    //filling the second quarter specified by user
    for (size_t i = 0; i < SIZE/2; i++){
        for (size_t j = (SIZE/2); j <SIZE ; j++){
            for(size_t k=0; k<RGB; k++){
                if (selector[1] == '1'){
                    image_copy[i][j][k] = quarter1[i][j-128][k];                
                }
                else if (selector[1]=='2'){
                    image_copy[i][j][k] = quarter2[i][j-128][k];
                }
                else if (selector[1]=='3'){
                    image_copy[i][j][k] = quarter3[i][j-128][k];
                }
                else if (selector[1]=='4'){
                    image_copy[i][j][k] = quarter4[i][j-128][k];
                }
            }
        }
    }
    //filling the third quarter specified by user
    for (size_t i = (SIZE/2); i < SIZE; i++){
        for (size_t j = 0; j <SIZE/2 ; j++){
            for(size_t k=0; k<RGB; k++){
                if (selector[2] == '1'){
                    image_copy[i][j][k] = quarter1[i-128][j][k];                
                }
                else if (selector[2]=='2'){
                    image_copy[i][j][k] = quarter2[i-128][j][k];
                }
                else if (selector[2]=='3'){
                    image_copy[i][j][k] = quarter3[i-128][j][k];
                }
                else if (selector[2]=='4'){
                    image_copy[i][j][k] = quarter4[i-128][j][k];
                }
            }
        }
    }
    //filling the fourth quarter specified by user
    for (size_t i = (SIZE/2); i < SIZE; i++){
        for (size_t j = (SIZE/2); j <SIZE ; j++){
            for(size_t k=0; k<RGB; k++){
                if (selector[3] == '1'){
                    image_copy[i][j][k] = quarter1[i-128][j-128][k];                
                }
                else if (selector[3]=='2'){
                    image_copy[i][j][k] = quarter2[i-128][j-128][k];
                }
                else if (selector[3]=='3'){
                    image_copy[i][j][k] = quarter3[i-128][j-128][k];
                }
                else if (selector[3]=='4'){
                    image_copy[i][j][k] = quarter4[i-128][j-128][k];
                }
            }
        }
    }
    for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            image[i][j][0]=image_copy[i][j][0];
            image[i][j][1]=image_copy[i][j][1];
            image[i][j][2]=image_copy[i][j][2];
        }
    }
    cout<<"Filter has been applied."<<endl;
          
}

