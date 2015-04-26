//
//  main.cpp
//  LolModelView
//
//  Created by nine on 15/3/23.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <unistd.h>
#include "draw.h"
#include "SOIL.h"

using namespace Lol;
struct texinfo{
    unsigned char* data;
    int w;
    int h;
    int channel;
    GLuint texid;
};
texinfo g_tex; 

LolSknHeader* sknHeader = 0;
float yAxisRotate = 0;
void init(){
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0,0.1,0.5,1.0);
    sknHeader = loadSkn("Ashe.skn");
    if (sknHeader == NULL) std::cout<<"no file"<<std::endl;
    g_tex.data = SOIL_load_image("ashe_base_2011_TX_CM.dds", &g_tex.w, &g_tex.h, &g_tex.channel, SOIL_LOAD_AUTO);
    
    glGenTextures(1,&(g_tex.texid));
    glBindTexture(GL_TEXTURE_2D,g_tex.texid);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,g_tex.w,g_tex.h,0,GL_RGB,GL_UNSIGNED_BYTE,g_tex.data);
    
    free(g_tex.data);
}

void reshape(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.333,10,10000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(){
    glShadeModel(GL_SMOOTH);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,330,500,0,0,0,0,1,0);
    glPushMatrix();
    yAxisRotate += 0.5;
    glRotatef(yAxisRotate,0,yAxisRotate,0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR);
    glEnable(GL_DEPTH_TEST);
    glColor3f(1.0,0.5,1.0);
    //这个查看depth精度的方法已经在GL3中被无效了。
    int depth;
    glGetIntegerv(GL_DEPTH_BITS, &depth);
    std::cout<<depth<<" bits depth"<<std::endl;
    //FIXME: z-buffer为0bit！！怎么设置？由于窗口没有打开深度测试。
    drawSkn(sknHeader, g_tex.texid);
    
    glPopMatrix();
    glutSwapBuffers();
    sleep(0.33);
    glutPostRedisplay();
}

int main(int argc, char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("lol model view");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
    
    return 0;
}
