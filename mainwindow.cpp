#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStyle>

const QVector<QPoint> polygonOpen(
        {QPoint(4, 9), QPoint(7, 7), QPoint(20, 7), QPoint(26, 12), QPoint(44, 12),
         QPoint(47, 14), QPoint(47, 18), QPoint(50, 21), QPoint(50, 42),
         QPoint(47, 45), QPoint(11, 47), QPoint(9, 44), QPoint(7, 44), QPoint(4, 41)});
const QVector<QPoint> polygonPrev(
        {QPoint(6, 8), QPoint(8, 6), QPoint(16, 6), QPoint(18, 8), QPoint(18, 10),
         QPoint(21, 12), QPoint(21, 17), QPoint(39, 6), QPoint(43, 6), QPoint(45, 8),
         QPoint(45, 11), QPoint(48, 13), QPoint(48, 47), QPoint(46, 48), QPoint(44, 48),
         QPoint(21, 34), QPoint(21, 46), QPoint(19, 48), QPoint(13, 48), QPoint(11, 45),
         QPoint(8, 45), QPoint(6, 42)});
const QVector<QPoint> polygonPlay(
        {QPoint(5, 7), QPoint(8, 4), QPoint(9, 4), QPoint(14, 4),
         QPoint(45, 22), QPoint(45, 24), QPoint(46, 26), QPoint(48, 29),
         QPoint(47, 32), QPoint(16, 48), QPoint(15, 48), QPoint(13, 48),
         QPoint(12, 47), QPoint(9, 47), QPoint(5, 44)});
const QVector<QPoint> polygonPause(
        {QPoint(6, 7), QPoint(8, 5), QPoint(20, 5), QPoint(22, 7), QPoint(22, 10),
         QPoint(25, 12), QPoint(29, 12), QPoint(29, 7), QPoint(31, 5), QPoint(43, 5),
         QPoint(45, 7), QPoint(45, 10), QPoint(48, 13), QPoint(48, 47), QPoint(46, 49),
         QPoint(37, 49), QPoint(34, 46), QPoint(32, 46), QPoint(29, 43), QPoint(25, 43),
         QPoint(25, 47), QPoint(23, 49), QPoint(13, 49), QPoint(11, 46), QPoint(9, 46),
         QPoint(6, 43)});
const QVector<QPoint> polygonStop(
        {QPoint(6, 9), QPoint(10, 6), QPoint(41, 6), QPoint(45, 10), QPoint(45, 13),
         QPoint(47, 15), QPoint(47, 44), QPoint(44, 47), QPoint(15, 47), QPoint(13, 45),
         QPoint(10, 45), QPoint(6, 41)});
const QVector<QPoint> polygonNext(
        {QPoint(6, 8), QPoint(9, 6), QPoint(12, 6), QPoint(33, 19), QPoint(33, 8),
         QPoint(36, 6), QPoint(43, 6), QPoint(45, 9), QPoint(45, 11), QPoint(48, 13),
         QPoint(48, 46), QPoint(46, 48), QPoint(40, 48), QPoint(38, 45), QPoint(36, 45),
         QPoint(33, 42), QPoint(33, 36), QPoint(15, 48), QPoint(13, 48), QPoint(11, 45),
         QPoint(8, 45), QPoint(6, 42)});
const QString PUSHBUTTON_OPEN_STYLE_0 =
        "QPushButton {border-image:url(../MediaPlayer/ico/open.png)}"
        "QPushButton:pressed {border-image:url(../MediaPlayer/ico/open_pressed.png)}"
        "QPushButton:hover:!pressed {border-image:url(../MediaPlayer/ico/open_hover.png)}";
const QString PUSHBUTTON_PREV_STYLE_0 =
        "QPushButton {border-image:url(../MediaPlayer/ico/prev.png)}"
        "QPushButton:pressed {border-image:url(../MediaPlayer/ico/prev_pressed.png)}"
        "QPushButton:hover:!pressed {border-image:url(../MediaPlayer/ico/prev_hover.png)}";
const QString PUSHBUTTON_PLAY_STYLE_0 =
        "QPushButton {border-image:url(../MediaPlayer/ico/play.png)}"
        "QPushButton:pressed {border-image:url(../MediaPlayer/ico/play_pressed.png)}"
        "QPushButton:hover:!pressed {border-image:url(../MediaPlayer/ico/play_hover.png)}";
const QString PUSHBUTTON_PAUSE_STYLE_0 =
        "QPushButton {border-image:url(../MediaPlayer/ico/pause.png)}"
        "QPushButton:pressed {border-image:url(../MediaPlayer/ico/pause_pressed.png)}"
        "QPushButton:hover:!pressed {border-image:url(../MediaPlayer/ico/pause_hover.png)}";
const QString PUSHBUTTON_STOP_STYLE_0 =
        "QPushButton {border-image:url(../MediaPlayer/ico/stop.png)}"
        "QPushButton:pressed {border-image:url(../MediaPlayer/ico/stop_pressed.png)}"
        "QPushButton:hover:!pressed {border-image:url(../MediaPlayer/ico/stop_hover.png)}";
const QString PUSHBUTTON_NEXT_STYLE_0 =
        "QPushButton {border-image:url(../MediaPlayer/ico/next.png)}"
        "QPushButton:pressed {border-image:url(../MediaPlayer/ico/next_pressed.png)}"
        "QPushButton:hover:!pressed {border-image:url(../MediaPlayer/ico/next_hover.png)}";
const QString HORIZONTALSLIDER_PROGRESS_STYLE_0 =
        "QSlider::groove:horizontal {"
        "border: 1px solid #969696;"
        "background: #eaeaea;"
        "height: 10px;"
        "border-radius: 4px;}"

        "QSlider::handle:horizontal {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #f2adad, stop:1 #ff1414);"
        "border: 2px solid #1b4d66;"
        "border-color: #000;"
        "width: 14px;"
        "height: 14px;"
        "margin-top: -4px;"
        "margin-bottom: -4px;"
        "border-radius: 8px;}"

        "QSlider::handle:horizontal:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #ff1414, stop:1 #ac1313);"
        "border: 2px solid #113c51;"
        "border-color: #000;"
        "border-radius: 8px;}"

        "QSlider::sub-page:horizontal {"
        "background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 1, stop: 0 #f2adad, stop: 1 #ff1414);"
        "border: 1px solid #777;"
        "height: 10px;"
        "border-radius: 4px;}"

        "QSlider::add-page:horizontal {"
        "background: #eeeeee;"
        "border: 1px solid #777;"
        "height: 10px;"
        "border-radius: 4px;}"

        "QSlider::sub-page:horizontal:disabled {"
        "background: #bbb;"
        "border-color: #999;}"

        "QSlider::add-page:horizontal:disabled {"
        "background: #eee;"
        "border-color: #999;}"

        "QSlider::handle:horizontal:disabled {"
        "background: #eee;"
        "border: 2px solid #aaa;"
        "border-radius: 4px;}";


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
        QAudioDecoder *ad = new QAudioDecoder(this);
        ad->setSourceFilename(file);
        connect(ad, &QAudioDecoder::durationChanged, this, &MainWindow::onDurationChanged);
        ad->start();
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
void MainWindow::onDurationChanged(qint64 d)
{
    t = QTime(0, 0, 0, 0);
    t = t.addMSecs(d);
    ui->labelDuration->setText(t.toString("hh:mm:ss"));
}
/////////////////
