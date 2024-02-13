#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //              MainWindow style
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->hide();
    //      labels
    ui->labelFile->setStyleSheet("QLabel {color: #f2f3ff;}");
    ui->labelDuration->setStyleSheet("QLabel {color: #f2f3ff;}");
    ui->labelProgress->setStyleSheet("QLabel {color: #f2f3ff;}");
    ui->labelVolume->setStyleSheet("QLabel {color: #f2f3ff;}");
    //      background
    QPixmap bkgnd("../MediaPlayer/bkgnd.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);      //scale img to window size
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    //              Player init
    m_player = new QMediaPlayer(this);
    m_player->setVolume(20);
    ui->labelVolume->setText(QString("Volume: ").append(QString::number(m_player->volume())));
    ui->horizontalSliderVolume->setValue(m_player->volume());

    //              Buttons init
    //      Open
    ui->pushButtonOpen->setMask(QPolygon(polygonOpen));
    ui->pushButtonOpen->setStyleSheet(PUSHBUTTON_OPEN_STYLE_0);
    //      Prev
    ui->pushButtonPrev->setMask(QPolygon(polygonPrev));
    ui->pushButtonPrev->setStyleSheet(PUSHBUTTON_PREV_STYLE_0);
    //      Play
    ui->pushButtonPlay->setMask(QPolygon(polygonPlay));
    ui->pushButtonPlay->setStyleSheet(PUSHBUTTON_PLAY_STYLE_0);
    //      Stop
    ui->pushButtonStop->setMask(QPolygon(polygonStop));
    ui->pushButtonStop->setStyleSheet(PUSHBUTTON_STOP_STYLE_0);
    //      Next
    ui->pushButtonNext->setMask(QPolygon(polygonNext));
    ui->pushButtonNext->setStyleSheet(PUSHBUTTON_NEXT_STYLE_0);

    //              Sliders init
    //      Progress
    ui->horizontalSliderProgress->setStyleSheet(HORIZONTALSLIDER_PROGRESS_STYLE_0);

    //              Connect
    connect(m_player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
}

MainWindow::~MainWindow()
{
    delete m_player;
    delete ui;
}

void MainWindow::on_pushButtonOpen_clicked()
{
    QString file = QFileDialog::getOpenFileName
            (
                this,
                "Open file",
                NULL,
                "Audio files(*.mp3 *.flac);; MP-3 (*.mp3);; Flac (*.flac)"
                );
    if(file != NULL)
    {
        ui->pushButtonPlay->setMask(QPolygon(polygonPlay));
        ui->pushButtonPlay->setStyleSheet(PUSHBUTTON_PLAY_STYLE_0);
        this->ui->labelFile->setText(file);
        this->setWindowTitle("MediaPlayerPD_321: " + file.split('/').last());
        this->m_player->setMedia(QUrl::fromLocalFile(file));

        /////////////////
        //QAudioDecoder *ad = new QAudioDecoder(this);
        //ad->setSourceFilename(file);
        //connect(ad, &QAudioDecoder::durationChanged, this, &MainWindow::onDurationChanged);
        //ad->start();
        /////////////////
    }
}


void MainWindow::on_horizontalSliderVolume_valueChanged(int value)
{
    m_player->setVolume(value);
    ui->labelVolume->setText(QString("Volume:").append(QString::number(m_player->volume())));
}


void MainWindow::on_pushButtonPlay_clicked()
{
    switch(m_player->state())
    {
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
    {
        if(m_player->mediaStatus() != QMediaPlayer::NoMedia)
        {
            m_player->play();
            ui->pushButtonPlay->setMask(QPolygon(polygonPause));
            ui->pushButtonPlay->setStyleSheet(PUSHBUTTON_PAUSE_STYLE_0);
        }
    } break;
    case QMediaPlayer::PlayingState:
    {
        ui->pushButtonPlay->setMask(QPolygon(polygonPlay));
        ui->pushButtonPlay->setStyleSheet(PUSHBUTTON_PLAY_STYLE_0);
        m_player->pause();
    } break;
    default: break;
    }
}

/////////////////
void MainWindow::on_durationChanged(qint64 d)
{
    this->ui->horizontalSliderProgress->setMaximum(d);
    QTime t = QTime(0, 0, 0, 0).addMSecs(d);
    ui->labelDuration->setText(t.toString("hh:mm:ss"));
    //ui->labelDuration->setText(QString("Duration: ").append(QString::number(d)));
}

void MainWindow::on_positionChanged(qint64 pos)
{
    QTime t = QTime(0, 0, 0, 0).addMSecs(pos);
    this->ui->labelProgress->setText(QString(t.toString("hh:mm:ss")));
    this->ui->horizontalSliderProgress->setSliderPosition(pos);
}
/////////////////


void MainWindow::on_horizontalSliderProgress_sliderMoved(int position)
{
    this->m_player->setPosition(position);
}

