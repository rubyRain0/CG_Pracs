#pragma once
#include "iostream"
#include "CG_Prac1/GradientTriangle.h"
#include "CG_Prac2/TwoTriangles.h"
#include "CG_Prac3/MovingTriangle.h"
#include "CG_Prac4/TextureSquare.h"
#include "CG_Prac5/Cube.h"
#include "CG_Prac6/2TextureSquare.h"
#include "CG_Prac7/CubeAndLight.h"
#include "CG_Prac8/CubeTexture.h"

int main(int argc, char* argv[]) {

 
    int choice = 7;

    switch (choice) {
    case 1:
        return gradientTriangleMain(argc, argv);
    case 2:
        return mainTwoTriangles(argc, argv);
    case 3:
        return movingTriangleMain(argc, argv);
    case 4:
        return mainTextureSquare(argc, argv);
    case 5:
        return gradientCubeMain(argc, argv);
    case 6:
        return twoTextureSquare(argc, argv);
    case 7:
        return cubeAndLightMain(argc, argv); 
    case 8:
        return cubeTextureMain(argc, argv);
    default:
        std::cerr << "Invalid choice!" << std::endl;
        return 1;
    }
}