#include "painter.h"

#include <QPainter>
#include <QTimer>
#include <QMouseEvent>

#define MAX_SEC  1000
#define SIZE_X   100
#define SIZE_Y   100

void DVDScreenSaver::paintEvent(QPaintEvent *event) 
{
    if (_isVisible) {
        QPainter painter(this);
        
        painter.fillRect(rect(), Qt::black);

        if (!_image.isNull())  painter.drawPixmap(_x, _y, _image);
    }
}
void DVDScreenSaver::mouseMoveEvent(QMouseEvent *event) 
{
    _idleTime = 0;
    _isVisible = false;
    update();
}
void DVDScreenSaver::keyPressEvent(QKeyEvent *event) 
{
    _idleTime = 0;
    _isVisible = false;
    update();
}

DVDScreenSaver::DVDScreenSaver(QWidget *parent) : QWidget(parent) 
{
    // setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setFocusPolicy(Qt::StrongFocus);

    _image.load("Paint/images/pingvin.png");
    _image = _image.scaled(SIZE_X, SIZE_Y, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this] () { 
        _idleTime += 20;

        if (_idleTime > MAX_SEC) {
            _isVisible = true;

            _x += _stepX;
            _y += _stepY;

            if (_x + SIZE_X > width() || _x < 0)    _stepX *= -1;
            if (_y + SIZE_Y > height() || _y < 0)    _stepY *= -1;
        }

        update();
    });

    timer->start(20);
}