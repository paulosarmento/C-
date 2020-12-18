#include "fx.h"
//
///Evita redeclara as variáveis.


void reflexoSol (IrrlichtDevice * device, ILightSceneNode * sol)
{
    static ISceneManager * smgr = device->getSceneManager();
    static IGUIEnvironment * guienv = device->getGUIEnvironment();
    static IVideoDriver * driver = device->getVideoDriver();

    static f32 mult = (f32)driver->getScreenSize().Height / 600.0f;
    static rect<s32>nullRect (0,0,0,0);
    static IGUIImage * flare = guienv->addImage(nullRect,0,0,0);
    static IGUIImage * flareOp = guienv->addImage(nullRect,0,0,0);
    static IGUIImage * flareIn = guienv->addImage(nullRect,0,0,0);
    static IGUIImage * flarePq = guienv->addImage(nullRect,0,0,0);
    static IGUIImage * flarePq2 = guienv->addImage(nullRect,0,0,0);

    static bool runOnce = true;

    if(runOnce) //carregar as imagens
    {
        flare->setImage(driver->getTexture("fx/sol_flare.png"));
        flare->setUseAlphaChannel(true);
        flare->setScaleImage(true);

        flareOp->setImage(driver->getTexture("fx/grande_flare.png"));
        flareOp->setUseAlphaChannel(true);
        flareOp->setScaleImage(true);

        flareIn->setImage(driver->getTexture("fx/medio_flare.png"));
        flareIn->setUseAlphaChannel(true);
        flareIn->setScaleImage(true);

        flarePq->setImage(driver->getTexture("fx/pequeno_flare.png"));
        flarePq->setUseAlphaChannel(true);
        flarePq->setScaleImage(true);

        flarePq2->setImage(driver->getTexture("fx/pequeno_flare.png"));
        flarePq2->setUseAlphaChannel(true);
        flarePq2->setScaleImage(true);

        runOnce = false;
    };

    ICameraSceneNode * camera = device->getSceneManager()->getActiveCamera();
    vector3df solPos = sol->getPosition();

    position2d<s32> flareCentro = smgr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(solPos,camera);

    if(flareCentro.X > 800 * mult or flareCentro.Y > 600 * mult or flareCentro.X < 0 or flareCentro.Y < 0)
    {
        flare->setVisible(false);
        flareOp->setVisible(false);
        flareIn->setVisible(false);
        flarePq->setVisible(false);
        flarePq2->setVisible(false);
        return;
    }

    ISceneNode * node = 0;
    vector3df point;
    triangle3df triangle;
    node = smgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
                smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(flareCentro,camera),
                point, triangle, 0, 0, false);
    if (node)
    {
        flare->setVisible(false);
        flareOp->setVisible(false);
        flareIn->setVisible(false);
        flarePq->setVisible(false);
        flarePq2->setVisible(false);
        return;
    }

    flare->setVisible(true);
    flareOp->setVisible(true);
    flareIn->setVisible(true);
    flarePq->setVisible(true);
    flarePq2->setVisible(true);

    //posicao do sol
    rect<s32> flareRect((s32)(flareCentro.X - 128 * mult),
                        (s32)(flareCentro.Y - 132 * mult),
                        (s32)(flareCentro.X + 128 * mult),
                        (s32)(flareCentro.Y + 380 * mult));
    flare->setRelativePosition(flareRect);

    //flare oposto
    position2d<s32> opFlareCentro = position2d<s32>((s32)(800 * mult - flareCentro.X),
                                                    (s32)(600 * mult - flareCentro.Y));
    rect<s32> opFlare(  (s32)(opFlareCentro.X - 128 * mult),
                        (s32)(opFlareCentro.Y - 128 * mult),
                        (s32)(opFlareCentro.X + 128 * mult),
                        (s32)(opFlareCentro.Y + 128 * mult));

    flareOp->setRelativePosition(opFlare);


    //flare intermediario
    position2d<s32> inFlareCentro = position2d<s32>((s32)flareCentro.X - (flareCentro.X - opFlareCentro.X) / 2,
                                                    (s32)flareCentro.Y - (flareCentro.Y - opFlareCentro.Y) / 2);
    rect<s32> inFlare(  (s32)(inFlareCentro.X - 64 * mult),
                        (s32)(inFlareCentro.Y - 64 * mult),
                        (s32)(inFlareCentro.X + 64 * mult),
                        (s32)(inFlareCentro.Y + 64 * mult));

    flareIn->setRelativePosition(inFlare);


    //flare pequeno
    position2d<s32> pqFlareCentro = position2d<s32>((s32)flareCentro.X - (flareCentro.X - opFlareCentro.X) / 3,
                                                    (s32)flareCentro.Y - (flareCentro.Y - opFlareCentro.Y) / 3);
    rect<s32> pqFlare(  (s32)(pqFlareCentro.X - 16 * mult),
                        (s32)(pqFlareCentro.Y - 16 * mult),
                        (s32)(pqFlareCentro.X + 16 * mult),
                        (s32)(pqFlareCentro.Y + 16 * mult));

    flarePq->setRelativePosition(pqFlare);


    //flare pequeno 2
    position2d<s32> pqFlareCentro2 = position2d<s32>((s32)flareCentro.X - (flareCentro.X - opFlareCentro.X) / 1.5f,
                                                     (s32)flareCentro.Y - (flareCentro.Y - opFlareCentro.Y) / 1.5f);
    rect<s32> pqFlare2( (s32)(pqFlareCentro2.X - 16 * mult),
                        (s32)(pqFlareCentro2.Y - 16 * mult),
                        (s32)(pqFlareCentro2.X + 16 * mult),
                        (s32)(pqFlareCentro2.Y + 16 * mult));

    flarePq2->setRelativePosition(pqFlare2);

}
