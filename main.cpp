#include <iostream>
#include "pixel.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void average_colors(vector<Pixel> &pixel_list);
void flip_vertically(vector<Pixel> &pixel_list);

int main(int argc, char *argv[]){
    //handle command line arguments
    if(argc < 2){
	cout << argv[0] << "<input file>" << endl;
	return 1;
    }

    string filename = argv[1];

    //open and read pixel.dat file
    ifstream Plist(filename);
    if(!Plist.is_open()){
	cout << "File can't be opened!" << endl;
	Plist.close();
	return 1;
    }
    
    //create vector
    vector<Pixel> pixel_list;

    //write file to vector
    string line;
    while(getline(Plist, line)){
	Pixel pixel;
	
	//assign x
	int commaPos = line.find(',');
	string value = line.substr(0, commaPos);
	pixel.x = stoi(value);

	line = line.substr(commaPos + 1);

	commaPos = line.find(',');
	
	//assign y
	value = line.substr(0, commaPos);
	pixel.y = stoi(value);

        line = line.substr(commaPos + 1);

        commaPos = line.find(',');
	
	//assign r
	value = line.substr(0, commaPos);
	pixel.r = stod(value);

        line = line.substr(commaPos + 1);

        commaPos = line.find(',');
	
	//assign g
        value = line.substr(0, commaPos);
        pixel.g = stod(value);

        line = line.substr(commaPos + 1);

        commaPos = line.find(',');

        //assign b
        value = line.substr(0, commaPos);
        pixel.b = stod(value);

	//add this pixel to vector
	pixel_list.push_back(pixel);
    }

    Plist.close();

    average_colors(pixel_list);
    flip_vertically(pixel_list);
    
    //write to flipped.dat
    ofstream flipped_p("flipped.dat");
    
    if(!flipped_p.is_open()){
	cout << "Error opening flipped.dat!" << endl;
	return 1;
    }

    for(int i = 0; i <  pixel_list.size(); i++){
	flipped_p << pixel_list[i].x << ","
	    << pixel_list[i].y << ","
	    << pixel_list[i].r << ","
	    << pixel_list[i].g << ","
	    << pixel_list[i].b << endl;
    }

    flipped_p.close();

    cout << "Pixel's written to flipped.dat!" << endl;

    return 0;
}

//find average of r,g,b colors individually
void average_colors(vector<Pixel> &pixel_list){
    double totalR = 0.0, totalG = 0.0, totalB = 0.0;

    for(int i = 0; i < pixel_list.size(); i++){
	totalR += pixel_list[i].r;
	totalG += pixel_list[i].g;
	totalB += pixel_list[i].b;
    }

    double averageR = totalR / pixel_list.size();
    double averageG = totalG / pixel_list.size();
    double averageB = totalB / pixel_list.size();

    cout << "Average R: " << averageR << endl;
    cout << "Average G: " << averageG << endl;
    cout << "Average B: " << averageB << endl;
}

//function to flip pixel rbg postions where the rbg value at y = 0 becomes the values at y =255 and vice versa
void flip_vertically(vector<Pixel> &pixel_list){

    vector<Pixel> original = pixel_list;

    for(int i = 0; i < pixel_list.size(); i++){
	int x = pixel_list[i].x;
	int y = pixel_list[i].y;

	int flippedY = 255 - y;
	int index = x * 256 + flippedY;
	
	pixel_list[i].r = original[index].r;
	pixel_list[i].g = original[index].g;
	pixel_list[i].b = original[index].b;
    }
}
