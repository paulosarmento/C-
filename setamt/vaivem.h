#include <irrlicht.h>
#include "math.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class bola
{
private:
    float tamanho;
    IMeshSceneNode * modelo;
    float peso;
    int posicao;
    char * marca;

public:
    void SetPosZ(float lugar);
    void SetTamanho(float novotam);
    bola(float tam, IMeshSceneNode * mesh, float quilo, int pos );
};
