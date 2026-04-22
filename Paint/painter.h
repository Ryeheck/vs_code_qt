#ifndef PAINTER_H
#define PAINTER_H


#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class DVDScreenSaver : public QWidget {
    Q_OBJECT

public:
    DVDScreenSaver(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    int _x = 0, _y = 0;
    int _stepX = 1, _stepY = 1;
    int _idleTime = 0;
    bool _isVisible = false;
    
    QPixmap _image;
};

#endif // PAINTER_H