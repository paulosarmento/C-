#include"vaivem.h"

bola :: bola(float tam, IMeshSceneNode * mesh, float quilo, int pos)
{
    tamanho = tam;
    modelo = mesh;
    peso = quilo;
    posicao = pos;
    if (peso == 0.8f)
        marca = "topper";
    else if (peso == 0.7f)
        marca = "adidas";
    else if (peso == 0.9)
        marca = "nike";
}
void bola :: SetTamanho(float novotam)
{
    tamanho = novotam;
    modelo->setScale(vector3df(novotam/0.3));
};
void bola :: SetPosZ(float lugar)
{
    posicao = lugar;
    modelo->setPosition(vector3df(0.0f,0.0f,lugar));
}
