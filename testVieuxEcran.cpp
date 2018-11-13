#include <iostream>
#include <fstream>
#include "include/Image2DWriter.h"
#include "include/Image2DReader.h"
#include "include/Image2D.h"
#include "include/Color.h"
#include "include/Accessor.h"

using namespace std;

int main( int argc, char** argv ) {
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator ColorIterator;
    bool ok;
    if ( argc < 3 )
    {
        std::cerr << "Usage: invert_red_blue <input.pgm> <output.pgm>" << std::endl;
        return 0;
    }

    ColorImage2D img;
    ifstream input( argv[1]);
    if(! Image2DReader<Color>::read(img, input)){
        cerr << "Error reading the file" << endl; return 1;
    }

    typedef ColorImage2D::GenericIterator< ColorRedAccessor >   ColorRedConstIterator;
    typedef ColorImage2D::GenericIterator< ColorGreenAccessor > ColorGreenConstIterator;
    typedef ColorImage2D::GenericIterator< ColorBlueAccessor >  ColorBlueConstIterator;
    ColorRedConstIterator   itRed   = img.begin< ColorRedAccessor >();
    ColorGreenConstIterator itGreen = img.begin< ColorGreenAccessor >();
    ColorBlueConstIterator  itBlue  = img.begin< ColorBlueAccessor >();
// On écrit la composante verte dans l'image en niveaux de gris.
    int x = 0;
    for ( ColorIterator it = img.begin(), itE = img.end();
          it != itE; ++it )
    {
        switch ( x % 3 ) {
            case 0: *itGreen = *itBlue  = 0; break;
            case 1: *itRed   = *itBlue  = 0; break;
            case 2: *itRed   = *itGreen = 0; break;
        }
        ++itRed; ++itGreen; ++itBlue;
        x = ( x+1 ) % img.w();
    }

    ofstream output( argv[2]);
    if(!Image2DWriter<Color>::write(img, output, false)){
        cerr << "Error Writting the file" << endl;
        return 1;
    }

    return 0;
}