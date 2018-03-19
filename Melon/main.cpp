



int main()
{
  Note iNote = static_cast<Note>(ui->uScaleList->currentRow());
  Mode iMode = static_cast<Mode>(ui->uModeList->currentRow()+1);
  ModeType iModeType = static_cast<ModeType>(ui->uModeTypeList->currentRow()+1);
  int iVariation = ui->uVariationNumber->value();

  ModalMixtureParameters iModalMixtureParameters =
  {
    ui->uCheckSecondaryDominant->isChecked(),
    ui->uCheckNeopolitan->isChecked(),
    ui->uCheckMajorMinor->isChecked(),
    ui->uCheckModalMixture->isChecked()
  };

  ProgressionBuilder progBuilder(iVariation, iNote, iMode, iModeType,iModalMixtureParameters);

  Progression prog = progBuilder.generate();
  ui->oProgDisplay->append(QString::fromStdString(prog.toString()));
  ui->oProgDisplay->append(QString::fromStdString(prog.printChords()));
}
