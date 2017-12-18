#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H

#include <QMainWindow>
#include "Melon/MelonLogger.h"

namespace Ui {
class RootWindow;
}

class RootWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RootWindow(QWidget *parent = 0);
    MelonLogger* logger;
    ~RootWindow();

private slots:
    void on_pushButton_clicked();
private:
    Ui::RootWindow *ui;
};

#endif // ROOTWINDOW_H
