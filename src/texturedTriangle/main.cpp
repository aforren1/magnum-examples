/*
    Copyright © 2010, 2011 Vladimír Vondruš <mosra@centrum.cz>

    This file is part of Magnum.

    Magnum is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License version 3
    only, as published by the Free Software Foundation.

    Magnum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License version 3 for more details.
*/

#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Utility/Resource.h"
#include "Scene.h"
#include "TexturedTriangle.h"

Magnum::Scene* s;

/* Wrapper functions so GLUT can handle that */
void setViewport(int w, int h) {
    s->setViewport(w, h);
}
void draw() {
    s->draw();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    /* Init GLUT */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Shaded TexturedTriangle example");
    glutReshapeFunc(setViewport);
    glutDisplayFunc(draw);

    /* Init GLEW */
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::cerr << "GLEW error:" << glewGetErrorString(err) << std::endl;
        return 1;
    }

    /* Initialize scene */
    Magnum::Scene scene;
    s = &scene;

    /* Every scene needs a camera */
    scene.setCamera(new Magnum::Camera(&scene));

    /* Add triangle to the scene */
    Corrade::Utility::Resource rs("data");
    std::istringstream in(rs.get("stone.tga"));
    new Magnum::Examples::TexturedTriangle(in, &scene);

    /* Main loop calls draw() periodically and setViewport() on window size change */
    glutMainLoop();
    return 0;
}
