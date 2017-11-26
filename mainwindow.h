#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H

#include <QMainWindow>

namespace Ui {
class RootWindow;
}

class RootWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RootWindow(QWidget *parent = 0);
    ~RootWindow();

private slots:
    void on_pushButton_clicked();

    void on_dialHsuVariation_valueChanged(int value);

    void on_dialGenericSubstitution_valueChanged(int value);

    void on_dialSecondaryDominant_valueChanged(int value);

    void on_dialModalMixture_valueChanged(int value);

private:
    Ui::RootWindow *ui;
};

#endif // ROOTWINDOW_H
