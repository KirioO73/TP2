#include <iostream>
#include <fstream>
#include "include/Image2DWriter.h"
#include "include/Image2DReader.h"
#include "include/Image2D.h"
#include "include/Color.h"
#include "include/Histogramme.h"
#include "include/Accessor.h"


using namespace std;

int main( int argc, char** argv ) {
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;

    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef GrayLevelImage2D::Iterator GrayIterator;

    if ( argc < 3 )
    {
        std::cerr << "Usage: testBuildHistogramme <input.pgm> <output.pgm>" << std::endl;
        return 0;
    }

    ColorImage2D img;
    ifstream input( argv[1]);
    if(! Image2DReader<Color>::read(img, input)){
        cerr << "Error reading the file" << endl; return 1;
    }

    Histogramme H;
    H.init(img.begin<ColorValueAccessor>(), img.end<ColorValueAccessor>());

    GrayLevelImage2D imgRes(256*2, 100, 255);
    double* hI = H.gethI();
    double* HI = H.getHI();
    for(int i = 0; i < 256; i++){
        cout << "hI " << i << " " <<hI[i] << endl;
        cout << "HI " << i << " " <<HI[i] << endl;
    }
    /*
    for(int i = 0; i < 256; i++){
        for( int j = 0; j < hI[i] * 100; j++){
            imgRes.at(i,j) = 0;
        }
    }
    for(int i = 0; i < 256; i++){
        for( int j = 0; j < HI[i] * 100; j++){
            imgRes.at(i+256,j) = 0;
        }
    }*/
    ofstream output( argv[2]);
    if(!Image2DWriter<unsigned char>::write(imgRes, output, false)){
        cerr << "Error Writting the file" << endl;
        return 1;
    }

    return 0;
}