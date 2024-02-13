#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioDecoder>
#include <QFileDialog>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonOpen_clicked();

    void on_horizontalSliderVolume_valueChanged(int value);

    void on_pushButtonPlay_clicked();

    void on_durationChanged(qint64 d);

    void on_positionChanged(qint64 pos);

    void on_horizontalSliderProgress_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *m_player;
};
#endif // MAINWINDOW_H
