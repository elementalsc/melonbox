#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Melon/MelonUtil.h"
#include "Melon/Modes.h"
#include "Melon/Harmony.h"

using namespace std;

typedef vector<ConceptChord> ProgressionType;

int variationCount;


RootWindow::RootWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::RootWindow)
{
    ui->setupUi(this);
    ui->variationNumber->setValue(variationCount = 1);
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

    ui->oProgDisplay->append(QString::fromStdString(ProgToString(prog)));
}

