#include"particle2.h"

Particle2::Particle2(int t,int type){
    switch (type){
        case 1:
            position2 = {-2.0f,-1.9f};
            break;

        case 2:
            position2 = {-2.0f,-1.7f};
            break;

        case 3:
            position2 = {-2.0f,-1.5f};
            break;

        case 4:
            position2 = {-2.0f,-1.3f};
            break;

        case 5:
            position2 = {-2.0f,-1.1f};
            break;

        case 6:
            position2 = {-2.0f,-0.9f};
            break;

        case 7:
            position2 = {-2.0f,-0.7f};
            break;

        case 8:
            position2 = {-2.0f,-0.5f};
            break;

        case 9:
            position2 = {-2.0f,-0.3f};
            break;

        case 10:
            position2 = {-2.0f,-0.1f};
            break;

        case 11:
            position2 = {-2.0f,0.0f};
            break;
        
        case 12:
            position2 = {-2.0f,0.1f};
            break;

        case 13:
            position2 = {-2.0f,0.3f};
            break;

        case 14:
            position2 = {-2.0f,0.5f};
            break;

        case 115:
            position2 = {-2.0f,0.7f};
            break;

        case 16:
            position2 = {-2.0f,0.9f};
            break;

        case 17:
            position2 = {-2.0f,1.1f};
            break;

        case 18:
            position2 = {-2.0f,1.3f};
            break;

        case 19:
            position2 = {-2.0f,1.5f};
            break;

        case 20:
            position2 = {-2.0f,1.7f};
            break;

        case 21:
            position2 = {-2.0f,1.9f};
            break;
    }
    timeOrigin2 = t;
}