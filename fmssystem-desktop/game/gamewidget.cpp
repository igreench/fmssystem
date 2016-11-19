#include <QtWidgets>
#include <QtOpenGL>

#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 45 * 16;
    yRot = 45 * 16;
    zRot = 0;

    cubes.push_back(Cube(new QVector3D(1.0f, 0.0f, 1.0f), 0.4f));
    cubes.push_back(Cube(new QVector3D(1.0f, 0.0f, 0.0f), 0.4f));
    cubes.push_back(Cube(new QVector3D(-1.0f, 0.0f, 0.0f), 0.4f));

    isButtonExitHovered = false;

    setMouseTracking(true);
}

GameWidget::~GameWidget()
{

}

QSize GameWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GameWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void GameWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GameWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GameWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GameWidget::initializeGL()
{
    qglClearColor(Qt::white);

    glEnable(GL_DEPTH_TEST);
}

void GameWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    draw();
    drawUI();
}

void GameWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void GameWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();

    if (QRect(590, 490, 152, 52).contains(lastPos)) {
        emit ButtonExitClick();
    }
}

void GameWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();

    if (QRect(590, 490, 152, 52).contains(lastPos)) {
        if (!this->isButtonExitHovered) {
            this->isButtonExitHovered = true;
            updateGL();
        }
    } else {
        if (this->isButtonExitHovered) {
            this->isButtonExitHovered = false;
            updateGL();
        }
    }
}

void GameWidget::draw()
{
    qglColor(Qt::green);
    for (size_t i = 0; i < cubes.size(); i++) {
        drawCube(cubes[i]);
    }
}

void GameWidget::drawUI()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Label
    painter.setFont(QFont("Microsoft Sans Serif", 52));
    painter.setPen(Qt::black);
    painter.drawText(24, 144, 728, 59, Qt::AlignVCenter | Qt::AlignHCenter, "Игра");

    // Button "Exit"
    if (this->isButtonExitHovered) {
        painter.fillRect(590, 490, 152, 52, QColor("#5cb85c"));
    } else {
        painter.fillRect(590, 490, 152, 52, QColor("#5cd25c"));
    }
    painter.setFont(QFont("Microsoft Sans Serif", 18));
    painter.setPen(Qt::white);
    painter.drawText(590, 490, 152, 52, Qt::AlignVCenter | Qt::AlignHCenter, "Выход");

    painter.end();
}

void GameWidget::drawCube(Cube cube) {
    glBegin(GL_QUADS);
        // front quad
        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        // left quad
        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        // right quad
        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        // back quad
        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        // bottom quad
        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() - cube.getSide() / 2);

        // top quad
        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() - cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() + cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);

        glVertex3f(cube.getVector()->x() + cube.getSide() / 2,
                   cube.getVector()->y() - cube.getSide() / 2,
                   cube.getVector()->z() + cube.getSide() / 2);
    glEnd();
}

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
