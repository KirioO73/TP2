#ifndef TP1_HISTOGRAMME_H
#define TP1_HISTOGRAMME_H

#include "../../TP1/src/GrayLevelImage2D.h"

class Histogramme {
public:
    int egalisation(int j){
        return (int) (255 * HI[j]);
    }

    template <typename InputIterator> void init(InputIterator it, InputIterator itE){
        int nb = 0;
        for (; it != itE; ++it){
            //std::cout << "in hI " << *it << std::endl;
            hI[(*it * 255)]++;
            nb++;
            //for(int i = *it; i < 256; i++) HI[i]++;
        }

        //Divise par le nombre total de pixel pour obtenir la proportion
        //for (double &y : hI) y = y / (nb);

        //Construction de HI a partir de hI
        HI[0] = hI[0];
        for(int i = 1; i<256;++i) HI[i] = HI[i-1] + hI[i];
    }
    double* gethI(){return hI;}
    double* getHI(){return HI;}

private:
    double hI[256] = {0.0};
    double HI[256] = {0.0};
};


#endif //TP1_HISTOGRAMME_H
