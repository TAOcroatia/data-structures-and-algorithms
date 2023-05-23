//Object3D - struktura - niz trokuta i njihov broj

//funkcija koja cita tekstualni stl i zapisuje u Object3D
//funkcija koja pise Object3D u tekstualnu stl
//funkcija koja cita binarnu stl i zapisuje u Object3D
//funkcija koja pise Object3D u binarnu stl
//funkcija koja brise Object3D

#include <stdio.h>

#include "stl.h"

int main(){
    //read write textual stl
    FILE *fpReadTextStl = fopen("primjertxt.stl", "r");
    Object3D *trokuti = readTextStl(fpReadTextStl);
    fclose(fpReadTextStl);
    fpReadTextStl = NULL;

    FILE *fpWriteTextStl = fopen("outtxt.stl", "w");
    writeTextStl(trokuti, fpWriteTextStl);
    fclose(fpWriteTextStl);
    fpWriteTextStl = NULL;

    deleteObject3D(trokuti);

    //read write binary stl
    FILE *fpReadBinStl = fopen("primjerbin.stl", "rb");
    Object3D *trokuti2 = readBinStl(fpReadBinStl);
    fclose(fpReadBinStl);
    fpReadBinStl = NULL;

    FILE *fpWriteBinStl = fopen("outbin.stl", "wb");
    writeBinStl(trokuti2, fpWriteBinStl);
    fclose(fpWriteBinStl);
    fpWriteBinStl = NULL;

    deleteObject3D(trokuti2);
}