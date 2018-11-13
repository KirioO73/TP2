#ifndef TP2_IMAGE2DREADER_H
#define TP2_IMAGE2DREADER_H

#include <iostream>
#include <string>
#include <fstream> // flux sur les fichiers
#include <sstream> // flux sur les chaînes de caractères
#include "Color.h"
#include "Image2D.h"

template <typename TValue>
class Image2DReader {
public:
    typedef TValue Value;
    typedef Image2D<Value> Image;
    static bool read( Image & img, std::istream & input, bool ascii )
    {
        std::cerr << "[Image2DReader<TValue>::read] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};
/// Specialization for gray-level images.
template <>
class Image2DReader<unsigned char> {
public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;
    static bool read( Image & img, std::istream & input)
    {
        std::string str;
        if ( !input.good() ) {
            std::cerr << "Probleme !";
            return false;
        }
        std::getline( input, str);
        //std::cout << str << std::endl;
        if( (!str.empty()) && str != "P2"){
            std::getline( input, str );
            //if (( !str.empty() ) && (str[0]=='#')) std::cout << "C'est un commentaire ! J'ignore superbement" << std::endl;

            std::getline(input, str);
            std::istringstream istr(str);
            int x,y;
            istr >> x >> y;

            img = Image(x,y);
            int i;
            for ( Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it ){
                input >> i;
                //cout << i << endl;
                *it = i;
            }
            return true;
        }
        if((!str.empty()) && str != "P5"){
            std::getline( input, str );
            //if (( !str.empty() ) && (str[0]=='#')) std::cout << "C'est un commentaire ! J'ignore superbement" << std::endl;

            std::getline(input, str);
            std::istringstream istr(str);
            int x,y;
            istr >> x >> y;

            input >> std::noskipws;
            img = Image(x,y);
            Value i;
            for ( Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it ){
                input >> i;
                //cout << i << endl;
                *it = i;
            }
            return true;
        }
        return false;
    }
};
/// Specialization for color images.
template <>
class Image2DReader<Color> {
public:
    typedef Color Value;
    typedef Image2D<Value> Image;
    typedef Image::ConstIterator ConstIterator;
    static bool read( Image & img, std::istream & input)
    {
        std::string str;
        if ( !input.good() ) {
            std::cerr << "Probleme !";
            return false;
        }
        std::getline( input, str);
        if( (!str.empty()) && str == "P3"){
            std::getline( input, str );
            //if (( !str.empty() ) && (str[0]=='#')) std::cout << "C'est un commentaire ! J'ignore superbement" << std::endl;

            std::getline(input, str);
            std::istringstream istr(str);
            int x,y;
            istr >> x >> y;

            std::getline(input, str);

            img = Image(x,y, Color(0,0,0));
            int r,g,b;
            for ( Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it ){
                input >> r;
                input >> g;
                input >> b;
                *it = Color(r,g,b);
            }
            return true;
        }
        else if( (!str.empty()) && str == "P6") {
            std::getline( input, str );
            //if (( !str.empty() ) && (str[0]=='#')) std::cout << "C'est un commentaire ! J'ignore superbement" << std::endl;

            std::getline(input, str);
            std::istringstream istr(str);
            int x,y;
            istr >> x >> y;

            std::getline(input, str);

            input >> std::noskipws;
            img = Image(x,y, Color(0,0,0));
            int r,g,b;
            for ( Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it ){
                r=input.get();
                g=input.get();
                b=input.get();

                *it = Color(r,g,b);
            }
            return true;
        }else{
        return false;
        }
    };
};

#endif //TP2_IMAGE2DREADER_H
