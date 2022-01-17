#ifndef MEDIAPLAYERWIDGET_H
#define MEDIAPLAYERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMediaPlayer>

class MediaPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MediaPlayerWidget(QString mediaPath, QWidget *parent = nullptr);
    ~MediaPlayerWidget();

private:
    QString splitPath(QString path);

public:
    void stop();

private:
    QMediaPlayer* player;
    QPushButton* playPauseButton;
    QPushButton* resetState;
    QLabel* stateLabel;
};

#endif // MEDIAPLAYERWIDGET_H
