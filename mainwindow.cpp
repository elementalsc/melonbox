#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Melon/Harmony.h"

using namespace std;

RootWindow::RootWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::RootWindow)
{
    ui->setupUi(this);
    ui->variationNumber->setValue(1);
    logger = MelonLogger::getInstance();
}

RootWindow::~RootWindow()
{
    delete ui;
}

void RootWindow::on_pushButton_clicked()
{
    ProgressionType prog;
    Mode mode = Ionian;

    int rInt = randomInt(0, 5);
    prog = hsuList[rInt];
    applyVariation(prog,ui->variationNumber->value(),allVariationFunctions);

    // [ ] faire un tableau donnant l'historique de la création de la progression
    // [ ] donne la progression en degrés, puis en accords
    // [/] faire un logger qui est un singleton
    ui->oProgDisplay->append(QString::fromStdString(ProgToString(prog)));
}

