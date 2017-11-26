#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Melon/MelonUtil.h"
#include "Melon/Modes.h"
#include "Melon/Substitutions.h"
#include "Melon/Harmony.h"
#include "Melon/ConceptChord.cpp"

using namespace std;

typedef vector<ConceptChord> Progression;


RootWindow::RootWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::RootWindow)
{
    ui->setupUi(this);
    ui->dialHsuVariation->setValue(probHsuVariation = 75);
    ui->dialGenericSubstitution->setValue(probGenericSubstitutions = 50);
    ui->dialSecondaryDominant->setValue(probSecondaryDominant = 10);
    ui->dialModalMixture->setValue(probModalMixture = 5);
}

RootWindow::~RootWindow()
{
    delete ui;
}

void RootWindow::on_pushButton_clicked()
{
    Progression prog;
    Mode mode = Ionian;


    int rInt = randomInt(0, 5);
    prog = hsuList[rInt];
    variation(prog,1,hsuBasicVariationFunctions);
    variation(prog,1,hsuGenericVariationFunctions);

    /*applyModeTriads(prog, mode);
    addSecondaryDominant(prog, 2);
    modalMixture(prog,mode, 2);*/

    ui->oProgDisplay->append(QString::fromStdString(ProgToString(prog)));
}

void RootWindow::on_dialHsuVariation_valueChanged(int value)
{
    probHsuVariation = value;
}

void RootWindow::on_dialGenericSubstitution_valueChanged(int value)
{
    probGenericSubstitutions = value;
}

void RootWindow::on_dialSecondaryDominant_valueChanged(int value)
{
    probSecondaryDominant = value;
}

void RootWindow::on_dialModalMixture_valueChanged(int value)
{
    probModalMixture = value;
}
