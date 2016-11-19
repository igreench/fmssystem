#include "cube.h"

Cube::Cube(QVector3D *vector, GLfloat side) {
    this->vector = vector;
    this->side = side;
}

QVector3D *Cube::getVector(){
    return this->vector;
}

GLfloat Cube::getSide(){
    return this->side;
}
