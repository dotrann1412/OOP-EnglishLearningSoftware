#include "MediaPlayerWidget.h"

#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <iostream>
#include <QLayout>
#include <QAudioOutput>

QString MediaPlayerWidget::splitPath(QString path) {
    QString ret = "";
    for(int i = path.size() - 1; i >= 0; --i) {
        if(path[i] == '\\' || path[i] == '/') return ret;
        ret = path[i] + ret;
    }
    return ret;
}

void MediaPlayerWidget::stop() {
    this->player->stop();
}

MediaPlayerWidget::MediaPlayerWidget(QString mediaPath, QWidget *parent)
    : QWidget(parent)
{
    player = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);

    player->setSource(QUrl::fromLocalFile(mediaPath));
    audioOutput->setVolume(50);
    QSize icon_size(40, 40);

    QPixmap play(":/resources/icon/play.png");
    play = play.scaled(icon_size, Qt::KeepAspectRatio);

    QPixmap pause(":/resources/icon/stop.png");
    pause = pause.scaled(icon_size, Qt::KeepAspectRatio);

    QPixmap reset(":/resources/icon/return.png");
    reset = reset.scaled(icon_size, Qt::KeepAspectRatio);

    static QIcon playIcon(play);
    static QIcon pauseIcon(pause);
    static QIcon resetIcon(reset);

    playPauseButton = new QPushButton(this);
    playPauseButton->setFixedSize(icon_size);
    playPauseButton->setIcon(playIcon);

    resetState = new QPushButton(this);
    resetState->setFixedSize(icon_size);
    resetState->setIcon(resetIcon);

    stateLabel = new QLabel("0 / 0", this);

    connect(resetState, &QPushButton::clicked, [this] {
        this->player->setPosition(0);
    });

    connect(playPauseButton, &QPushButton::clicked, [this] {
        try {
            if(this->player->playbackState() == QMediaPlayer::PlayingState) {
                this->player->pause();
                this->playPauseButton->setIcon(playIcon);
            } else {
                this->player->play();
                this->playPauseButton->setIcon(pauseIcon);
            }
        } catch (const void*) {
            std::cerr << "Cannot play resource" << '\n';
        }
    });

    connect(player, &QMediaPlayer::positionChanged, [this] {
        QTime position(0, 0, 0, 0);
        QTime duration(0, 0, 0, 0);
        position = position.addSecs(this->player->position() / 1000);
        duration = duration.addSecs(this->player->duration() / 1000);
        this->stateLabel->setText(position.toString("mm ss") + " : " + duration.toString("mm ss"));
    });

    this->setLayout(new QVBoxLayout);
    this->layout()->setAlignment(Qt::AlignHCenter);

    QLabel* title = new QLabel(this->splitPath(mediaPath), this);
    title->setAlignment(Qt::AlignCenter);

    this->layout()->addWidget(title);

    QWidget* box = new QWidget(this);
    box->setLayout(new QHBoxLayout);

    box->layout()->addWidget(stateLabel);
    box->layout()->addWidget(playPauseButton);
    box->layout()->addWidget(resetState);

    this->layout()->addWidget(box);
}

MediaPlayerWidget::~MediaPlayerWidget() {
    delete player;
    delete playPauseButton;
    delete stateLabel;
}
