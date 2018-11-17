// save-channels.cpp
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include "include/Image2D.h"
#include "include/Image2DReader.h"
#include "include/Image2DWriter.h"
#include "include/Accessor.h"

int main( int argc, char** argv )
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef ColorImage2D::Iterator ColorIterator;
    if ( argc < 2 )
    {
        std::cerr << "Usage: save-green-channel <input.ppm>" << std::endl;
        return 0;
    }
    ColorImage2D imgL;
    char * imgName = argv[1];
    std::ifstream input( imgName ); // récupère le 1er argument.
    bool ok = ColorImage2DReader::read( imgL, input );
    if ( !ok )
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();

    ColorImage2D const img = imgL;

    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;
    GrayLevelImage2D img2( img.w(), img.h() );
    //-----------------------------------------------------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal vert est ici vvvvvvvvvvvv
    //
    // Servira à parcourir la composante verte de l'image couleur.
    typedef ColorImage2D::GenericConstIterator< ColorGreenAccessor > ColorGreenConstIterator;
    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorGreenConstIterator itGreen = img.begin< ColorGreenAccessor >();
    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = img2.begin(), itE = img2.end();
          it != itE; ++it )
    {
        *it = *itGreen;
        ++itGreen;
        // NB: si on veut faire *itGreen++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }
    //-----------------------------------------------------------------------------
    char filename2[100];
    std::strncpy(filename2, imgName, strlen(imgName)-5);
    std::strcat(filename2, "_green.ppm");
    std::ofstream output( filename2 );
    bool ok2 = GrayLevelImage2DWriter::write( img2, output, false );
    if ( !ok2 )
    {
        std::cerr << "Error writing output file. 2" << std::endl;
        return 1;
    }
    output.close();

    GrayLevelImage2D img3( img.w(), img.h() );
    //-----------------------------------------------------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal Bleu est ici vvvvvvvvvvvv
    //
    // Servira à parcourir la composante Bleu de l'image couleur.
    typedef ColorImage2D::GenericConstIterator< ColorBlueAccessor > ColorBlueConstIterator;
    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorBlueConstIterator itBlue = img.begin< ColorBlueAccessor >();
    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = img3.begin(), itE = img3.end();
          it != itE; ++it )
    {
        *it = *itBlue;
        ++itBlue;
        // NB: si on veut faire *itGreen++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }
    //-----------------------------------------------------------------------------
    char filename3[100];
    std::strncpy(filename3, imgName, strlen(imgName)-5);
    std::strcat(filename3, "_blue.ppm");
    output.open( filename3);
    bool ok3 = GrayLevelImage2DWriter::write( img3, output, false );
    if ( !ok3 )
    {
        std::cerr << "Error writing output file. 3 " << std::endl;
        return 1;
    }
    output.close();

    GrayLevelImage2D img4( img.w(), img.h() );
    //-----------------------------------------------------------------------------
    // vvvvvvvvv Toute la transformation couleur -> canal Bleu est ici vvvvvvvvvvvv
    //
    // Servira à parcourir la composante Bleu de l'image couleur.
    typedef ColorImage2D::GenericConstIterator< ColorRedAccessor > ColorRedConstIterator;
    // Notez comment on appelle la méthode \b générique `begin` de `Image2D`.
    ColorRedConstIterator itRed = img.begin< ColorRedAccessor >();
    // On écrit la composante verte dans l'image en niveaux de gris.
    for ( GrayLevelIterator it = img4.begin(), itE = img4.end();
          it != itE; ++it )
    {
        *it = *itRed;
        ++itRed;
        // NB: si on veut faire *itGreen++, il faut redéfinir GenericConstIterator<T>::operator++(int).
    }
    //-----------------------------------------------------------------------------
    char filename4[100];
    std::strncpy(filename4, imgName, strlen(imgName)-5);
    std::strcat(filename4, "_red.ppm");
    output.open( filename4 );
    bool ok4 = GrayLevelImage2DWriter::write( img4, output, false );
    if ( !ok4 )
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    return 0;
}