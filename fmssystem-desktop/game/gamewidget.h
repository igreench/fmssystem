// gamewidget.h

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QGLWidget>

class Cube {
public:
    Cube(QVector3D *vector, GLfloat side);

    QVector3D *getVector();
    GLfloat getSide();

private:
    QVector3D *vector;
    GLfloat side;
};

class GameWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

    void ButtonExitClick();

private:
    void draw();
    void drawUI();

    int xRot;
    int yRot;
    int zRot;

    QPoint lastPos;

    void drawCube(Cube cube);
    std::vector < Cube > cubes;

    bool isButtonExitHovered;
};

#endif // GAMEWIDGET_H
