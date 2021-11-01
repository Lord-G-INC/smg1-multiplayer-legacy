#include "defines.h"
/* NOTES


$fix pipes object
041d1db0 81dd00ec
041d1db4 48000cf1
$fix vines object
043265d4 81de0104
$fix random objects by r14 containing mario (is crazy fix)
04303144 7DC37378
04302f84 7DC37378

sub optimal fixes, might be useful later



turian@axiot.us
OSGetTime is at 804ac368
in the symbol map it is at 8060aba8
8060aba8 - 804ac368 = 15E840 discrepency

discrepency for ppchalt is 15F684
PPCHalt is here 804a096c

DISCREPENCY for GxInit is 15F630

DISCREPENCT fior __GXSetViewPort is 15F5E8
__GXSetViewPort is 804be3a4

804be474 does something with a 640

8033e7e0 this draws the opening menu 3d stuff?
8033e820 leads to function that draws all 3d
8033e880 leads to graphics refreshing?
8033eef8 this leads to function that renders the land overworld whatever man

803c7360 this func must be the 3d land renderer or whatever

SDAWord -0x2450 [0x4] contains paramaters for screen size!
 80539018 has double value

SDAbyte -0x33d8 is for whether luigi or mario 806A18C8

 804be434 this func has a floats for where the viewport needs to go

 80344224 THIS FUNCTION leads to drawing mario

 PeachCastleGardenGalaxy is name of first map!

 80343c1c where the mario manager is updated (yes!!!)
    802b5734 where 9e4 of mario is set (needed for powerups)
 802afd80 this is the update mario object function probably
 80344164 leads to where mario ACTUALLY gets drawn!!!!
 mario + ab0 is position matrix i thibk

 802b0754 801654e0

 80241610 PIPE?
 803f1f58 80304204 code that calls for a mario?

 80343bf4 where warp pipe manager is updated (finnmy)

 801d21dc pip updating?
 803f1ea4 when mario hops on pipe??
 801d1b74 if mario on the pipe

 8016fae8 the pipe code for mario jump on it

 802b0cc8 where mario controls are updated, or physics?
 802ae850 where mario controleler is created
 controller id is byte 71c of controller
 802cb500 forces controller id to be zero

 803d2e34 where mario gets his controller

80343d68 function that calls maroo
8033e8c0


8009731c WHERE CAMERA SETS THE VIEW MATRIX ????
80343b34 leads to camera updating yes
800991c0 camera updating function
800991f4 vital function for camera movement on marios

8039cf3c WHERE GAME Orders the camera allocation? (probs not)
80261d30 where a game camera is created? camera is the 0x35th one to be updated or whatever
800991ec camera going to get its mario

802aee48 where the game is asking to allocate another mario?

803ef818 where camera is created?????
8034503c where camera called for creation is???

802af148 WHERE MARIOS give information to camera


803a32b0 crash handler going to update contrlls crash handler

804506d8/804e6a7c game gets contr0oller inputs here?

80027040 checks if luigi for noises

WHERE CHECKS FOR LUIGI IS CALLED
8033e510, 80378770


80343c2c, 80343c4c, 80343c7c asks for marios co ordinates
0x50

NOTICE!!!! each mario updates the star 802463f0    802befc4
STARS check mario are within 0x54 collision thingy not 0x50


EVERY VTABLE + 0X54 = ON MARIO COLLIDING!!!

801b8130 PART Of vine?
8057bdc4 black hole vtable?

800a27ec



8033e660, 8033e684 calls for weird camera
8009919c important for camera bad


804068b8 where stars check the view matrix?

$make abilities work?
042b5700 60000000
042b5710 60000000
$make abilities work
043ce2e4 38600000
043ce2e8 4e800020


$make both tornado work
042b5d0c 60000000

803fa4a4

80099240 camera were thing
80343c54 updates camera input viewey thing
802ad100
803118dc WHERE CAMERA is detectin g the a button to zoom ouyt
8009a3f4


805ea1fb

804a6e20
804a6df8
804a2370
80399b40

804a6e20

804a6e20
804a6eb4

804a71d4

804a3e94 printy winty

804a73b0
80fc2b2d

8000e5fc print j2d

8000e7c0 where j3d prints le text
80350fcc

806bdfe4

0x380 of mario is life

802b9afc MARIO KIcking func??

804b5f08 = PSMTXCopy
803a2fb0 = jutwarning_f
803a3164 = PSMTXRotRad

short** sus = SDAword(-0x2450);
    short* viewPortStuff = sus[1];
    //viewPortStuff[2] = (int)three;
    viewPortStuff[3] = 0x1c8 / 2;
    float* unk = TOCword(0x2500);
    unk[0x544 / 4] = one;
    unk[0x548 / 4] = two;
    unk[0x54c / 4] = three;
    unk[0x550 / 4] = four;
    unk[0x554 / 4] = five;
    unk[0x558 / 4] = six;
    return;
*/

// global options
void storeFloatFuncNew(float one, float two, float three, float four, float five, float six);
static u32** cameraMario = -1;
static int isSplitScreen = 1;
static int is30fps = 1;
static int isHorizontal = 1;
static int focusOnP1 = 1;
static int saveMemory = -1;
static int testBlueBuffer = 0;
//static int draw3DType = 0;
static int firstPerson = -1;

static int mehrioreset = 1;
static int lifeP1 = 3;
static int lifeP2 = 3;
void flushCode(u32* addr, u32* val) {
    addr[0] = val;
    flushCache(addr, 4);
}

// 8039f294 gets every font somehow
// le function to get font is 8000ed8c?
// u32* font = 0x8069e4d8;?
static long long printColor = 0x00ff00ff00ff00ff;
static float testMatrix[] = { 0, 1, 0, 0,
0, 0, 1, 0,
0, 0, 0, 1,
0, -304, 228, 304,
-228, 0.75, 1, 1 };
// I belive print is centered in Y axis for some reason r/woosh
static float printAtTest[] = { 0.75, 0, 0, -1, // this is X
0, 1, 0, -5, // this is Y
0, 0, 1, 0 };
void printString(float x, float y, char* str) {
    printAtTest[3] = x;
    printAtTest[7] = (y - 224) * -1;

    u32 test[0x100 / 4];
    memclear(test, 0x100);
    short oddStr[0x100];
    int i = 0;
    while (1) {
        if (str[i] == 0) break;
        oddStr[i] = str[i];
        i++;
    }
    u32 insidePrint[0x5c / 4];
    // make my own vtable cuz this is stupid
    memclear(insidePrint, 0x5c);
    insidePrint[0] = 0x80550370;
    insidePrint[2] = &insidePrint[2];
    insidePrint[3] = &insidePrint[2];
    insidePrint[4] = 0x0;
    insidePrint[5] = 0x00;
    (*(long long*)(insidePrint + 6)) = printColor; // set the weird color
    insidePrint[8] = 0x00ff00ff;
    insidePrint[9] = 0x000000ff;
    insidePrint[10] = 0xffffffff;
    insidePrint[11] = 0xffffffff;
    insidePrint[12] = 0xffffffff;
    insidePrint[13] = 0xffffffff;
    // this + 0x84 is also a position matrix!
    // fc should be 4?
    // b5 shud be ff?
    // b6 shud be 4?
    // 4c shud be 30 flaot? (might be font size)
    // 50 float shud be 33?
    // d8-db is color i think
    // dc-df is color related i think
    test[0] = 0x80550198;
    test[0x28 / 4] = insidePrint;
    (*(float*)(test + 0x44 / 4)) = 1;
    (*(float*)(test + 0x48 / 4)) = 1;
    (*(float*)(test + 0x4c / 4)) = 1000; // sets maximum string length, might as well be infinite
    (*(float*)(test + 0x50 / 4)) = 33;
    memcpy(test + 0x84 / 4, printAtTest, 12 * 4);
    test[0xb4 / 4] = 0xffff0401;
    test[0xd4 / 4] = oddStr;
    // everything has these set to this idk
    test[0xd8 / 4] = 0xffffffff;
    test[0xdc / 4] = 0xffffffff;

    (*(float*)(test + 0xe4 / 4)) = 32; // font length
    (*(float*)(test + 0xe8 / 4)) = 48; // font height
    u32**** fontSomething = SDAword(-0x3A78);
    test[0xe0 / 4] = fontSomething[0x18 / 4][0xc / 4];
    test[0xf8 / 4] = i;
    testPrintGoodLoc(test, testMatrix);
}
// color must be long to allow for bit shifting
void setColor(u32 color) {
    long long c = color;
    printColor = ((c & 0xff) + ((c & 0xff00) << 8)
        + ((c & 0xff0000) << 16) + ((c & 0xff000000) << 24));
}
static u32 highlightColor = 0xe9f542ff;
static u32 white = 0xffffffff;
static int* currentDataAddress = -1;
static int currentMax = -1;
static int currentMin = -1;
static int currentOption = -1;
static int highLightedOption = -1;
static int yOffset = 0;
static int yMultiplication = 60;
static int displayOptions = 1;
static int bruh = -1;
void processInput() {
    if (currentOption <= 0) return;
    u32******** contMgr = SDAword(-0x3A78);
    contMgr = contMgr[0x20 / 4][0x24 / 4];
    u32 input = contMgr[0][2][2]; // for single input lol
    // 0x1000 is minus even tho 0x10 is +? weird
    if (input == 0x1000) displayOptions ^= 1;
    if (displayOptions == 0) return;
    if (input == 0x2) {
        if (currentDataAddress[0] >= currentMax) {
            currentDataAddress[0] = currentMin;
        }
        else {
            currentDataAddress[0]++;
        }
    }
    // down d pad
    if (input == 0x4) {
        if (highLightedOption == currentOption - 1) {
            highLightedOption = 0;
        }
        else {
            highLightedOption++;
        }
    }
    // up d pad
    if (input == 0x8) {
        if (highLightedOption == 0) {
            highLightedOption = currentOption - 1;
        }
        else {
            highLightedOption--;
        }
    }
}
void checkOptionDefault(int* dataAddress, int min, unsigned int max) {
    if (currentOption == highLightedOption) {
        currentMax = max;
        currentMin = min;
        currentDataAddress = dataAddress;
        setColor(highlightColor);
    }
    else {
        setColor(white);
    }
    currentOption++;
}
void printYesNoOption(char* string, int* dataAddress) {
    checkOptionDefault(dataAddress, 0, 1);
    char* yesNo;
    switch (dataAddress[0]) {
    case 0: yesNo = "No"; break;
    case 1: yesNo = "Yes"; break;
    default: yesNo = "This text is wrong!"; break;
    }
    char toPrint[0x100];
    for (int i = 0; i < 0x100; i++) {
        if (string[i] == 0) {
            memcpy(toPrint, string, i);
            memcpy(toPrint + i, yesNo, 4);
            break;
        }
    }
    printString(40, currentOption * yMultiplication + yOffset, toPrint);
}
// notice string count will become - 1 for max!
void printStringOption(char* baseString, char** strings, int* dataAddress, int stringCount) {
    checkOptionDefault(dataAddress, 0, stringCount - 1);
    char toPrint[0x100];
    //    sprintf(toPrint, "%s%s", baseString, strings[dataAddress[0]]);
    printString(40, currentOption * yMultiplication + yOffset, toPrint);
}
void printNumberOption(char* string, int* dataAddress, int minNumber, int maxNumber) {
    checkOptionDefault(dataAddress, minNumber, maxNumber);
    char toPrint[0x100];
    //    sprintf(toPrint, "%s%d", string, dataAddress[0]);
    printString(40, currentOption * yMultiplication + yOffset, toPrint);
}
void drawLife(float x, float y, char* str, int life) {
    u32 c;
    switch (life) {
    case 1: c = 0xff0000ff; break;
    case 2: c = 0xffff00ff; break;
    case 3: c = 0x00ffffff; break;
    default: c = 0x00ff00ff; break;
    }
    setColor(c);
    for (int i = 0; i < 0x100; i++) {
        if (str[i] == 0) {
            str[i - 1] = (life | 0x30);
            break;
        }
    }
    printString(x, y, str);
}
void drawCustom2D() {
    char* mainMar;
    if (mehrioreset == 1)
    {
        mainMar = "P1";
    }
    else {
        mainMar = "P2";
    }
    printString(0, 0, mainMar);
    //drawLife(680, 0, "LifeP1:  ", lifeP1);
    drawLife(680, 0, "LifeP2:  ", lifeP2);
    // this is for better initilization of values
    if (firstPerson == -1) {
        firstPerson = 0;
        saveMemory = 0;
    }
    if (displayOptions == 1) {
        if (highLightedOption < 0) highLightedOption = 0;
        printString(40, 0, "Press minus to toggle options screen");
        currentOption = 0;
        printYesNoOption("SplitScreen: ", &isSplitScreen);
        printYesNoOption("30FPS mode: ", &is30fps);
        printYesNoOption("horizontal: ", &isHorizontal);
        printYesNoOption("focus on P1: ", &focusOnP1);
        printYesNoOption("save memory: ", &saveMemory);
        printYesNoOption("first person: ", &firstPerson);
       // printYesNoOption("blue buffer: ", &testBlueBuffer);
     //   printYesNoOption("Test Draw3D: ", &draw3DType);
        if (is30fps == 1) {
            flushCode(0x803a0058, 0x60000000);
            u32** fpsZone = SDAword(-0x27a0);
            fpsZone[0x2c / 4] = 2;
        }
        else {
            flushCode(0x803a0058, 0x480001dd);
            u32** fpsZone = SDAword(-0x27a0);
            fpsZone[0x2c / 4] = 1;
        }
        if (testBlueBuffer == 1) {
            flushCode(0x803a0058, 0x480001dd);
        }
    }
    if(SDAword(-0x400c) != 0) focusOnP1 = (SDAword(-0x400c) - 1) ^ 1;
    processInput();
}

u32** getViewMatrix() {
    u32***** unk = SDAword(-0x3A78);
    return unk[0x24 / 4][0xac / 4][0x10 / 4][0x5c / 4];
}

u32** getControllerMgr() {
    u32***** unk = SDAword(-0x3A78);
    unk = unk[0x20 / 4];
    if (unk == 0) return 0;
    return unk[0x24 / 4][0x8 / 4]; // small differences
}
u32** getController(int controllerId) {
    u32***** unk = SDAword(-0x3A78);
    unk = unk[0x20 / 4];
    if (unk == 0) return 0;
    unk = unk[0x24 / 4][0x8 / 4]; // small differences
    return unk[controllerId * 2];
}

static u32***** cameras[4] = { -1, -1, -1, -1 };
static u32* marioControlStorage[4] = { -1, -1, -1, -1 };
u32** getCameraMgr() {
    u32***** unk = SDAword(-0x3A78);
    unk = unk[0x24 / 4];
    if (unk == 0) return 0;
    unk = unk[0xac / 4];
    if (unk == 0) return 0;
    unk = unk[0x8 / 4][0x8 / 4][0]; // small differences
    if (unk == 0) return 0;
    return unk + (2 * 20 / 4);
}
u32** getWeirdMarioMgr() {
    u32***** unk = SDAword(-0x3A78);
    return unk[0x24 / 4][0xac / 4][0x10 / 4][0x50 / 4];
}
u32** getWeirdCameraPointer() {
    u32***** unk = SDAword(-0x3A78);
    return unk[0x24 / 4][0xac / 4][0x10 / 4];
    // c4 is cam
}

u32** getMarioMgr() {
    u32***** unk = SDAword(-0x3A78);
    unk = unk[0x24 / 4];
    if (unk == 0) return 0;
    unk = unk[0xac / 4];
    if (unk == 0) return 0;
    unk = unk[0x8 / 4][0x8 / 4][0];
    if (unk == 0) return 0;
    return unk + (37 * 20 / 4);
}

static u32** currCamera = -1;
static u32* currMario = -1;
static int doDraw = 1;
static u32* cullingBytes = -1;
static char currCullByte = -1;
static u32 red = 0xff0000ff;
void beforeDrawAll3D(u32* unk) {
    if (is30fps == 1 && doDraw == 0) {
        doDraw = 1;
        return;
    }
    doDraw = 0;
    u32***** m = getMarioMgr();
    if (isSplitScreen == 0 || m[2] < 3) {
        if (focusOnP1 == 69) {
            bruh = -1;
            int chicken = 0;
            u32*** c = getCameraMgr()[0][0];
            u32*** c2 = getCameraMgr()[0][1]; // good c
            c[0x34 / 4][1] = c2[0x34 / 4][1];
            u32** wc = getWeirdCameraPointer();
            for (int i = 0; i < (int)m[2]; i++) {
                if (m[0][i][0] == 0x805a399c) {
                    if (chicken == 0) { 
                        currCullByte = 0;
                        c2[0x34 / 4][1][0x10 / 4] = m[0][i];
                        getWeirdMarioMgr()[0xc / 4] = m[0][i];
                        wc[0xc4 / 4] = c;
                        updateCamera(c); 
                        set3DViewBetter(SDAword(-0x3A78));
                        break;
                    }
                    chicken++;
                }
            }
        }
        updateManager(4);
        drawAll3D(unk);
        bruh = -1;
        return;
    }
    bruh = 2;
    u32*** c = getCameraMgr()[0][0];
    u32*** c2 = getCameraMgr()[0][1]; // good c
    c[0x34 / 4][1] = c2[0x34 / 4][1];
    u32** wc = getWeirdCameraPointer();
    for (int i = 0; i < (int)m[2]; i++) {
        if (m[0][i][0] == 0x805a399c) {
            currCullByte = 0;
            c2[0x34 / 4][1][0x10 / 4] = m[0][i];
            getWeirdMarioMgr()[0xc / 4] = m[0][i];
            if (bruh == 2) {
                wc[0xc4 / 4] = c;
                updateCamera(c);
            }
            if (bruh == 1) { wc[0xc4 / 4] = c2; updateCamera(c2); }
            set3DViewBetter(SDAword(-0x3A78));
            updateManager(4);
            //blueBuffer(SDAword(-0x27a0), &red); // fix rendering on wii?
            currMario = m[0][i];
            drawAll3D(unk);
            bruh--;
        }
    }
    // fix things???
    c2[0x34 / 4][1][0x10 / 4] = m[0][(int)m[2] - 1];
    getWeirdMarioMgr()[0xc / 4] = m[0][(int)m[2] - mehrioreset];
}
/*
void beforeDrawShadowMario() {
    if(currMario != -1) drawShadowMario(currMario);
} */

int beforeAstroDomeVolumeCheck(u32* dome, u32* marXYZ) {
    u32***** m = getMarioMgr();
    for (int i = 0; i < (int)m[2]; i++) {
        if (m[0][i][0] == 0x805a399c) {
            if(astroDomeVolumeCheck(dome, m[0][i] + 3) == 1) return 1;
        }
    }
    return 0;
}

// make rendering look nicer
int makeCullingWork(u32** unk) {
    currCullByte++;
    if (isSplitScreen == 1 && bruh == 1) {
        return cullingBytes[currCullByte] & cullingFunc(unk);
    }
    else {
        cullingBytes[currCullByte] = cullingFunc(unk);
        return cullingBytes[currCullByte];
    }
}


void editMtxOrtho(float one, float two, float three, float four, float five, float six) {
    if (one == 0 || two == 456 || three == 0 || four == 832) {
        if (isHorizontal == 1) {
            if (bruh == 2) one = two / 2;
            else if (bruh != -1) two = two / 2;
        }
        else {
            if (bruh == 2) three = four / 2;
            else if (bruh != -1) four /= 2;
        }
    }
    __asm("fsubs 11, 4, 3");
    C_MTXOrtho(one, two, three, four, five, six);
}

void storeFloatFuncNew(float one, float two, float three, float four, float five, float six) {
    if (bruh == -1) return;
    if (one != 0 || two != 0 || three != 640 || four != 456 || five != 0 || six != 1) return;
    float* unk = TOCword(0x2500);
    if (isHorizontal == 1) {
        if (bruh == 2) two = 456 / 2;
        four = 456 / 2;
    }
    else {
        if (bruh == 2) one = 640 / 2;
        three /= 2;
    }
    unk[0x544 / 4] = one;
    unk[0x548 / 4] = two;
    unk[0x54c / 4] = three;
    unk[0x550 / 4] = four;
    unk[0x554 / 4] = five;
    unk[0x558 / 4] = six;
    setScissor((int)one, (int)two, (int)three, (int)four);
}

void beforeSetScissor(int one, int two, int three, int four) {
    if (bruh != -1) {
        if (isHorizontal == 1) {
            if (bruh == 2) two = 456 / 2;
            four = 456 / 2;
        }
        else {
            if (bruh == 2) one = 640 / 2;
            three /= 2;
        }
    }
    setScissor(one, two, three, four);
}

u32* allocateCameras(u32* allocSpace, u32* unk) { 
    mehrioreset = 1; // this should make it so each level only starts with player one now!
    cullingBytes = alloc(0x1000);
    memclear(allocSpace, 500);
    for (int i = 1; i < 2; i++) {
        u32* c = alloc(500);
        memclear(c, 500);
        cameras[i] = setupCamera(c, unk);
    }
    cameras[0] = setupCamera(allocSpace, unk);
    cameras[0][0x34 / 4][1] = cameras[1][0x34 / 4][1];
    return cameras[0];
}
void updateCameraManager() {
    u32******* c = getCameraMgr();
    u32 remember = 0;
    u32** wc = getWeirdCameraPointer();
    if (cameraMario != -1) {
        currCullByte = 0;
        remember = getWeirdMarioMgr()[0xc / 4];
        getWeirdMarioMgr()[0xc / 4] = cameraMario;
        wc[0xc4 / 4] = c[0][(int)c[2] - 1];
        c[0][(int)c[2] - 1][0x34 / 4][1][0x10 / 4] = cameraMario;
    }
    if (bruh == -1 && c != 0 && c[2] != 0) {
        updateCamera(c[0][(int)c[2] - 1]);
        updateManager(4); // remember to cull!!!!
    }
    if (remember != 0) getWeirdMarioMgr()[0xc / 4] = remember;
}

u32** getMainCamerasThingy() {
    u32****** c = getCameraMgr();
    return c[0][(int)c[2] - 1][0x34 / 4][1];
}

// idk what fixCamera does tbh
// order of instructions matters severely!!!
//    u32** t = alloc(156);
//    setUpCameraRelatedThing(t);
//    setUpCameraRelatedThingToo(t);
void fixBothCameras() {
    cameraMario = -1;
    u32** wc = getWeirdCameraPointer();
    fixCamera(cameras[0]); // loads camera objects for re orientation or whatever man
    for (int i = 1; i < 2; i++) {
        wc[0xc4 / 4] = cameras[i];
        fixCameraToo(cameras[i]);
    }
    wc[0xc4 / 4] = cameras[0];
    fixCameraToo(cameras[0]);
}
// to make game use player 1 for entering galaxzies
void makeBothMarios(u32* unk) {
    for (int i = 0; i < 2; i++) {
        spawnMario(unk);
    }
}

/*
static int whatCameraReal = 1;
static int whatCamera = 0;
u32 getCameraNew() {
    return cameras[whatCamera];
}


int beforeMarioCreation() {
    whatCameraReal = 0;
    whatCamera = whatCameraReal;
    return 0; // luigi mode or mario mode
}
void afterMarioCreation() {
    whatCamera = 0;
}
*/
// worst fuinction ever but I don't care about anuthing anyormoe
u32* getOtherMario(int whichMario) {
    u32*** m = getMarioMgr();
    int j = 0;
    for (int i = (int)m[2] - 1; i >= 0; i--) {
        if (m[0][i][0] == 0x805a399c) {
            if (j == whichMario) {
                return m[0][i];
            }
            j++;
        }
    }
    OSReport("This should never happen!");
    return 0; // this should never happen but I am too lazy to panic_f
}
// apparently there's a third mario????
static int burger = 1;
u32* onStartMarioUpdate(u32*** mario) {
    /* this is over engineered but might be useful later */
    u32*** m = getMarioMgr();
    u32*** c = getCameraMgr()[0][0];
    u32*** c2 = getCameraMgr()[0][1]; // good c
    c[0x34 / 4][1] = c2[0x34 / 4][1];
    if (m[2] > 2) {
        u32******** contMgr = SDAword(-0x3A78);
        contMgr = contMgr[0x20 / 4][0x24 / 4];
        u32** wc = getWeirdCameraPointer();
        for (int i = 0; i < m[2]; i++) {
            if (m[0][i][0] == 0x805a399c && m[0][i] == mario) {
                //burger = 0;
                getWeirdMarioMgr()[0xc / 4] = mario;
                contMgr[0] = marioControlStorage[burger];
                c2[0x34 / 4][1][0x10 / 4] = mario;
                //  wc[0xc4 / 4] = cameras[(i - 1) ^ 1];
                if (isSplitScreen == 1 || SDAword(-0x400c) != 0) updateCamera(cameras[burger]);
                if (burger == 0 && focusOnP1 == 1) {
                    cameraMario = mario;
                }
                if (burger == 1 && focusOnP1 == 0) {
                    cameraMario = mario;
                }
                if (burger == 0) {
                    lifeP1 = mario[0x380 / 4];
                }
                else {
                    lifeP2 = mario[0x380 / 4];
                }
                burger ^= 1; // remember that onStartMario is ran only once per mario

                u32 input = contMgr[0][2][1];
                if ((input & 0x200) == 0x200) {
                    memcpy(m[0][i] + 0xc / 4, getOtherMario(burger) + 0xc / 4, 0xc);
                }
                if ((input & 0x100) == 0x100) {
                    mehrioreset = (int)m[2] - i;
                    OSReport("mehrio change to: %d", mehrioreset);
                    getWeirdMarioMgr()[0xc / 4] = m[0][(int)m[2] - mehrioreset];
                }
                // for respawning crystals
                if (mario[0x4a4 / 4] != 0) {
                    respawnCrystalItem(mario[0x4a4 / 4][0x24 / 4]);
                    mario[0x4a4 / 4] = 0;
                }
            }
        }
    }
    return mario + 2784 / 4;
}

void updateMarioManager() {
    burger = 1; // sometimes the game can mess up and not make burger ^
    u32** contMgr = SDAword(-0x3A78);
    contMgr = contMgr[0x20 / 4][0x24 / 4];
    marioControlStorage[0] = contMgr[0];
    marioControlStorage[1] = contMgr[1];
    updateManager(37);
    contMgr[0] = marioControlStorage[0];
    u32*** m = getMarioMgr();
    if ((int)m[2] > 2) {
        getWeirdMarioMgr()[0xc / 4] = m[0][(int)m[2] - mehrioreset];
    }
}

u32* __attribute__((noinline)) onStartMarioAlternativeUpdate(u32* mario) {
    __asm("stw 28, -0x10(11)");
    __asm("stw 29, -0x0c(11)");
    __asm("stw 30, -0x08(11)");
    __asm("stw 31, -0x04(11)");
    __asm("b m");
}
u32* m(u32* mario) {
    //getWeirdMarioMgr()[0xc / 4] = mario;
    return mario;
}

void updateStuffManager() {
    updateManager(34);
}
/*
int onMarioTouchPipe(u32** mario) {
    u32*** m = getMarioMgr();
    for (int i = 0; i < m[2]; i++) {
        if (m[0][i] == mario) {
            mehrioreset = i;
            getWeirdMarioMgr()[0xc / 4] = m[0][(int)m[2] - mehrioreset];
        }
    }
    return 1;
}*/

static int weegeeMode = -1;
int isLuigiNew() {
    if (weegeeMode == -1) weegeeMode = 0;
    return weegeeMode;
}
int toggleWeegeeMode() {
    if(saveMemory == 0) weegeeMode ^= 1;
    return weegeeMode ^ 1;
}


u32** onMarioTouchesObject(u32** mario, u32** unk) {
    u32*** m = getMarioMgr();
    if ((int)m[2] < 3) return unkFunc(mario, unk);
    for (int i = 0; i < (int)m[2]; i++) {
        if (m[0][i] == mario) {
            OSReport("mehrio change to: %d\n", mehrioreset);
            mehrioreset = (int)m[2] - i;
            getWeirdMarioMgr()[0xc / 4] = m[0][(int)m[2] - mehrioreset];
        }
    }
    return unkFunc(mario, unk);
}

// requires ar code works for both stars now
u32** onMarioTouchesStar(u32* unk, u32* unk2, u32* unk3) {
    u32** mario = unk[0x8c / 4];
    if (mario == 0) return 0;
    u32*** m = getMarioMgr();
    for (int i = 0; i < (int)m[2]; i++) {
        if (m[0][i] == mario) {
            OSReport("mehrio change to: %d\n", mehrioreset);
            mehrioreset = (int)m[2] - i;
            getWeirdMarioMgr()[0xc / 4] = m[0][(int)m[2] - mehrioreset];
        }
    }
    return mario;
}

// SO FAR THIS ONLY SLIGHTLY FIXES the problem!!!
void onMarioTouchesSwing(u32* unk, u32* unk2, u32* unk3) {
    u32** mario = unk[0xec / 4]; // sligjh didferetn
    if (mario == 0) return;
    u32*** m = getMarioMgr();
    for (int i = 0; i < (int)m[2]; i++) {
        if (m[0][i] == mario) {
            OSReport("mehrio change to: %d\n", mehrioreset);
            mehrioreset = (int)m[2] - i;
            getWeirdMarioMgr()[0xc / 4] = m[0][(int)m[2] - mehrioreset];
        }
    }
    funcInSwingyWhoCares(unk2, unk3);
}
float calcDistance(u32* xyz1, u32* xyz2);
float calcMarioDistanceNew(u32* xyz, u32* mario) {
    u32***** m = getMarioMgr();
    u32** marios[2];
    int j = 0;
    for (int i = 0; i < (int)m[2]; i++) {
        if (m[0][i][0] == 0x805a399c) {
            marios[j] = m[0][i];
            j++;
        }
    }
    float one = calcDistance(marios[0] + 3, xyz);
    float two = calcDistance(marios[1] + 3, xyz);
    if (two <= one) return two;
    return one;
}

u32* getClosestMario(u32* xyz) {
    u32***** m = getMarioMgr();
    u32** marios[2];
    int j = 0;
    for (int i = 0; i < (int)m[2]; i++) {
        if (m[0][i][0] == 0x805a399c) {
            marios[j] = m[0][i];
            j++;
        }
    }
    float one = calcDistance(marios[0] + 3, xyz);
    float two = calcDistance(marios[1] + 3, xyz);
    if (two <= one) return marios[1];
    return marios[0];
}

inline u32* getClosestMarioPos(u32* xyz) {
    return getClosestMario(xyz) + 3;
}
//make sure r3 is an object and + 0xc has xyz
u32* replaceGetMarioPos(u32* obj) {
    return getClosestMarioPos(obj + 3);
}

void deathBarrierCheckNew(u32*** deathArea) {
    u32***** m = getMarioMgr();
    for (int i = 0; i < (int)m[2]; i++) {
        if (m[0][i][0] == 0x805a399c) {
            int (*func)(u32* deathArea, u32* xyz) = deathArea[0][0x24 / 4];
            if ((*func)(deathArea, m[0][i] + 3)) {
                if (deathAreaGetDeathType(deathArea) == 0) forceKillPlayerByAbyss();
            }
        }
    }
}


// Using code injection I have placed a new function right before calling the original mario kick function
void beforeMarioKick(u32* mario, u32*** unk) {
    //unk is something I don't know what to call but has the object being kicked within 0x24 of itself.
    //0x805a999c is the first value within the mario actor always as it is the vtable and therefore is a constant. So basically we are just testing if the object is mario
    if (unk[0x24 / 4][0] == 0x805a399c) return;
    //only allow mario to do the kicking action if the object he is kicking is not mario.
    marioKick(mario, unk);
}

void giveMarioPos(float* paste, u32* cam, int isP2Star) {
    u32***** m = getMarioMgr();
    for (int i = 0; i < (int)m[2]; i++) {
        if (m[0][i][0] == 0x805a399c) {
            isP2Star--;
            if (isP2Star == 0) continue;
            memcpy(paste, m[0][3] + 720 / 4, 0xc);
            float*** m2 = getMarioMgr();
            paste[0] = (paste[0] * 120) + m2[0][3][3];
            paste[1] = (paste[1] * 120) + m2[0][3][4];
            paste[2] = (paste[2] * 120) + m2[0][3][5];
            break;
        }
    }
}

//getWeirdMarioMgr()[0xc / 4] = mario;

/* objects
obj[0][0] == 0x8057efcc && obj[0][0] == 0x8057efcc &&

0x8057efcc = pipe
805A399C = pull star probs not
8058C5AC = big stars?
8058FF8C = mini stars????



// mario coolider is within 0 of obj
void checkCollidedObjectNew(u32** obj) {
    // only find mario if these objects are associated
    u32** mario = findClosePlumber(obj[0] + 0xc / 4);
    int doThing = 0;
    switch (obj[0][0]) {
    case 0x8057efcc: doThing = 1; break;
    }
      if (doThing == 1 && mario != 0) {
        u32*** m = getMarioMgr();
        for (int i = 1; i < m[2]; i++) {
            if (m[0][i] == mario) {
                OSReport("object vtable: %X\n", obj[0][0]);
                OSReport("mehrio change to: %d", mehrioreset);
                mehrioreset = 3 - i;
                getWeirdMarioMgr()[0xc / 4] = m[0][(int)m[2] - mehrioreset];
            }
        }
      }
      checkCollidedObject(obj);
}
*/


// FIRST PERSON SECTION
static float* test = -1;
static float testxyz[] = { -1, -1, -1 };
//static int doFirstPerson = 1;
static int dontFirstPersonCuzMario = 0;
void beforeFirstPerson(u32**** camera) {
    test = camera[0x34 / 4][1];

    u32******** contMgr = SDAword(-0x3A78);
    contMgr = contMgr[0x20 / 4][0x24 / 4][0][0x20 / 4];
    /*u32 input = contMgr[0][2][2]; // for single input lol
    if (input == 0x10) doFirstPerson ^= 1;*/
    if (firstPerson == 1) {
        firstPersonMain(camera);
    }
}
void testCameraFunc(u32* unk, float* unk2, int one, float unk3, float unk4);
/* for mario's head first person */
static float sus = -1;
static float sus2 = -1;
void firstPersonControlsOverhaul(u32******** camera) {
    u32**** m = getMarioMgr();
    float* camInner = camera[0x48 / 4];
    float******** contMgr = SDAword(-0x3A78);
    int AMONGUS = camera[0xc / 4][0x34 / 4][1][0x10 / 4] == m[0][1];
    //somewhat okay fix for focus on p2 and first person
    AMONGUS |= (focusOnP1 ^ 1) & isSplitScreen;
    float* bob = contMgr[0x20 / 4][0x24 / 4][0][0x20 / 4];
    int input = contMgr[0x20 / 4][0x24 / 4][AMONGUS][0x20 / 4][0][2][1];
    float temp = bob[2];
    float temp2 = bob[1];
    //testCameraFunc(m[0][1][0x230 / 4], testxyz, 1, bob[1], bob[2]);
    float one = 1;
    if (bob[2] < 0) one = bob[2];
    u32* reddit = camera[0xc / 4][0x34 / 4][1][0x10 / 4][0x230 / 4];
    if (reddit == 0) reddit = m[0][1][0x230 / 4];
    testCameraFunc(reddit, testxyz, 1, 0, one);
    /*if (input == 0x10) {
        camInner[0x50 / 4] = 0;
        camInner[0x54 / 4] = 0;
        camInner[0x58 / 4] = 0;
        camInner[0x5c / 4] = 0;
    }*/
    sus = bob[1];
    sus2 = bob[2];
    bob[2] = (((input >> 2) & 1) * -1) + (((input >> 0x3) & 1) * 1);
    // bob[1] = 0;
     // remember camera buffer because sus
    firstPersonSetupFunc(camera);
    firstPersonControlsUpdate(camera);
    /*    u32 mtx[0x30 / 4];
        PSMTXRotRad(mtx, 0x59, -((camInner[0x58 / 4] * 3.14159) / 180));
        MTXMultiply(camInner + 92 / 4, mtx); */
    bob[2] = temp;
    bob[1] = 0;
}
static int doRotate = 1;
void beforeMovement(u32* unk) {
    if (firstPerson == 0) {
        movement(unk);
        return;
    }
    // prevent mario from rotating
    u32* mRot = unk[0x230 / 4] + 520;
    u32 temp[3];
    memcpy(temp, mRot, 0xc);
    mRotateNew(unk[0x230 / 4], testxyz);
    doRotate = 0;
    movement(unk);
    doRotate = 1;
    mRotateNew(unk[0x230 / 4], temp);
}
void mRotateNew(u32* unk, u32* unk2) {
    if (doRotate == 1) {
        asmMRotate(unk, unk2);
    }
}
void asmMRotate(u32* unk, u32* unk2) {
    __asm("stwu 1, -0x60(1)");
    __asm("b mRotate");
}
