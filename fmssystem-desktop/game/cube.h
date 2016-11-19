#ifndef CUBE_H
#define CUBE_H

#include <QVector3D>
#include <QGL>

class Cube {
public:
    Cube(QVector3D *vector, GLfloat side);

    QVector3D *getVector();
    GLfloat getSide();

private:
    QVector3D *vector;
    GLfloat side;
};

#endif // CUBE_H
