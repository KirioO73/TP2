
#include <iostream>
#include <fstream>
#include "include/Image2DWriter.h"
#include "include/Image2DReader.h"
#include "include/Image2D.h"
#include "include/Color.h"

using namespace std;

int main( int argc, char** argv ) {
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;
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

    Color c;
    for(Iterator it=img.begin(), ite=img.end(); it!=ite; it++){
        c = *it;
        *it = Color(c.blue,c.green,c.red);
    }

    ofstream output( argv[2]);
    if(!Image2DWriter<Color>::write(img, output, false)){
        cerr << "Error Writting the file" << endl;
        return 1;
    }

    return 0;
}