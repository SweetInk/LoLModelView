//
//  draw.cpp
//  LolModelView
//
//  Created by nine on 15/3/23.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "draw.h"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <fstream>
#include <assert.h>
using namespace std;
namespace Lol
{
    LolSknHeader* loadSkn(char* file)
    {
        ifstream in(file,ios::binary);
        if(!in.is_open()) return NULL;
        
        LolSknHeader *header = (LolSknHeader*) malloc(sizeof(LolSknHeader));
        memset(header,0,sizeof(LolSknHeader));
        in.read((char*)&header->magic,4);
        in.read((char*)&header->numObjects,2);
        in.read((char*)&header->matHeader,2);
        assert(header->matHeader == 1 && "matHeader == else not implimented!");
        in.read((char*)&header->numMaterials,4);
        in.read(header->nameMat,64);
        in.read((char*)&header->statVertex,4);
        in.read((char*)&header->numVertices,4);
        in.read((char*)&header->startIndex,4);
        in.read((char*)&header->numIndices,4);
        in.read((char*)&header->numOfIndices,4);
        in.read((char*)&header->numOfVertices,4);
        header->indices = (int16*)malloc(sizeof(int16) * header->numOfIndices);
        in.read((char*)header->indices,sizeof(int16)* header->numOfIndices);
        header->verteces = (LolVertex*)malloc(sizeof(LolVertex)* header->numOfVertices);
        in.read((char*)header->verteces,sizeof(LolVertex)*header->numOfVertices);
        return header;
    }
    
    
    void freeSkn(LolSknHeader* headerPtr)
    {
        if(headerPtr == 0) return ;
        if(headerPtr->indices) free(headerPtr->indices);
        if(headerPtr->verteces) free(headerPtr->verteces);
        free(headerPtr);
    }
    
    void drawSkn(LolSknHeader*sknHeader, unsigned int texid)
    {
        if(texid != 0)
        {
            glBindTexture(GL_TEXTURE_2D,texid);
        }
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);		// 1.
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
        glNormalPointer(GL_FLOAT,sizeof(LolVertex),&(sknHeader->verteces[0].normals[0]));
        glVertexPointer(3,GL_FLOAT,sizeof(LolVertex),sknHeader->verteces);	// 2.
        glTexCoordPointer(2,GL_FLOAT,sizeof(LolVertex),&sknHeader->verteces[0].texcoords[0]);
        glDrawElements(GL_TRIANGLES,sknHeader->numOfIndices,GL_UNSIGNED_SHORT,sknHeader->indices);
        
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        if(texid != 0)
        {
            glBindTexture(GL_TEXTURE_2D,0);
        }
    }
    
    
    LolSklHeader*loadSkl(char*file)
    {
        ifstream in(file,ios::binary);
        if(!in.is_open()) return NULL;
        LolSklHeader*sklPtr = (LolSklHeader*)malloc(sizeof(LolSklHeader));
        memset(sklPtr,0,sizeof(LolSklHeader));
        in.read(sklPtr->version,8);
        in.read((char*)&sklPtr->numObjects,4);
        in.read((char*)&sklPtr->skeletonHash,4);
        in.read((char*)&sklPtr->numElements,4);
        sklPtr->bonesArray = (LolSklBone*)malloc(sizeof(LolSklBone)*sklPtr->numElements);
        in.read((char*)sklPtr->bonesArray,sizeof(LolSklBone)*sklPtr->numElements);
        return sklPtr;
    }
    
    void freeSkl(LolSklHeader*sklHeadePtr)
    {
        if(!sklHeadePtr)return ;
        if(sklHeadePtr->bonesArray)
            free(sklHeadePtr->bonesArray);
        free(sklHeadePtr);
    }
    
    
    LolAnmHeader *loadAnm(char*file)
    {
        ifstream in(file,ios::binary);
        if(!in.is_open()) return NULL;
        LolAnmHeader*anmPtr = (LolAnmHeader*)malloc(sizeof(LolAnmHeader));
        memset(anmPtr,0,sizeof(LolAnmHeader));
        in.read((char*)anmPtr,sizeof(LolAnmHeader) - sizeof(anmPtr->datasize));
        
        /*
         data.data_size4=data.start_offset5-data.start_offset4-- 12720 bytes
         data.data_size5=data.start_offset6-data.start_offset5-- 29296 bytes
         data.data_size6=file_size-data.start_offset6-- 36900 bytes
         */
        
        anmPtr->datasize[0] = anmPtr->offset[4]- anmPtr->offset[3];
        anmPtr->datasize[1] = anmPtr->offset[5]- anmPtr->offset[4];
        anmPtr->datasize[2] = anmPtr->sizeTillEnd - anmPtr->offset[5];
        
        
        int size = sizeof (LolAnmHeader);
        return anmPtr;
    }
}