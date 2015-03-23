//
//  draw.h
//  LolModelView
//
//  Created by nine on 15/3/23.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __LolModelView__draw__
#define __LolModelView__draw__

#include <stdio.h>
namespace Lol
{
    //00 type
    typedef int int32;
    typedef unsigned int uint32;
    typedef short int16;
    typedef unsigned short uint16;
    typedef char int8;
    typedef unsigned char uint8;
    typedef float float32;
    
    
    // 00 struct
    struct LolVertex
    {
        float32 position[3];	// xyz position of vertex
        int8 boneldx[4];		// Array of 4 bone number ID's
        float32 weights[4];		// Corresponding bone weights
        float32 normals[3];		// vertex normals
        float32 texcoords[2];	// vertex UV coordinates
    };
    
    struct LolSknHeader
    {
        int32 magic;
        int16 numObjects;
        int16 matHeader;
        //---------if matHeader = 1----------------
        int32 numMaterials;	//if matHeader = 1
        //-------------------------
        
        //-----block
        // if matHeader == 1 && numMaerials
        int8 nameMat[64];		// name of material
        int32 statVertex;		// First vertex belonging to this material
        int32 numVertices;		// Number of vertices in this material
        int32 startIndex;		// First index belonging to this material
        int32 numIndices;		// Number of indicies belonging to this material
        //if matHeader == 0 the above block will be absent from the file.
        
        //----count block -------------------------
        // the values obtained here should match the sums of the numIndices and numVertices for the material blocks if present
        int32 numOfIndices;
        int32 numOfVertices;
        
        int16 *indices;		// Array of vertex indices
        LolVertex*verteces;	// Array of vertex values
    };
    
    
    // skl
    
    // Bone ID's are implicit to their order in the file starting at 0.
    // So the first bone has an ID of 0, second bone an ID of 1, etc.
    struct LolSklBone
    {
        int8 name[32];			// name of bone
        int32 parent;			// parent bone id. -1 implies no parent
        float32 scale;			// scale of bone ? of armature?
        float32 matrix[12];		// 3*4 affine bone matrix in row major format(first four values
        // belong to first row ,2nd four to 2nd row ....
    };
    
    // ---header
    // ---bone array
    struct LolSklHeader
    {
        int8 version[8];	// file format version ==== extra 1 for '\0'
        int32 numObjects;	// num of objects
        int32 skeletonHash;	// unique id
        int32 numElements; // num of bones
        LolSklBone* bonesArray;//
    };
    
    
    // not finished - version 4
    struct LolAnmHeader
    {
        int8 name[8];
        int32 version;
        int32 sizeTillEnd;
        int32 magic3;
        int32 magic4;
        int32 magic5;
        int32 numofbones;
        int32 numofframes;
        float32 playbackFPS;
        int32 offset[9];
        int32 datasize[3];
        
    };
    
    //----------------------------------------------------------------------------------------------------------
    
    // interface
    LolSknHeader* loadSkn(char* file);
    void freeSkn(LolSknHeader*);
    void drawSkn(LolSknHeader*sknHeader, unsigned int texid);
    
    LolSklHeader*loadSkl(char*file);
    void freeSkl(LolSklHeader*);
    
    
    LolAnmHeader *loadAnm(char*file);
    
    
}  // end namespace



#endif /* defined(__LolModelView__draw__) */
