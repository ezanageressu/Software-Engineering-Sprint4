#include <iostream>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <QTimer>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStackedWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pencil.h"
#include "production.h"
#include "wallet.h"
#include "intelligence.h"
#include "intelligence.cpp"
#include "debug.h"
#include "debug.cpp"
#include "server.h"
#include "server.cpp"

using json = nlohmann::json;
/* Start: Initialization */

/// Mainwindow constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /**
    * Label is set to display as soon as the
    * MainWindow class is constructed.
    */

    ui->setupUi(this);
    getHighScore();
    ui->stackedWidget->setCurrentIndex(0);
    /**
    * Action to be taken when save is clicked
    */
    connect(ui->save, SIGNAL(clicked()), this, SLOT(save()));

    /**
    * Action to be taken when load is clicked
    */
    connect(ui->load, SIGNAL(clicked()), this, SLOT(load()));

    /**
    * Not displaying the debugging tool option
    */
    ui->debug->setVisible(true);

    /**
    * Action to be taken when debug is clicked
    */
    connect(ui->debug, SIGNAL(clicked(bool)), this, SLOT(displayDebugButton()));

    /**
    * Action to be taken when speed up is clicked
    */
    connect(ui->speedup, SIGNAL(clicked()), this, SLOT(debug()));

    std::cout<<std::getenv("JACOBS_ID")<<std::endl;
    std::cout<<std::getenv("SE_USERNAME")<<std::endl;
    std::cout<<std::getenv("GAME_USERNAME")<<std::endl;
}

void MainWindow::gameStart(){
    disableComponents();

    /**
    * Not displaying the debugging tool
    */
    ui->speedup->setVisible(false);
    ui->debug->setCheckState(Qt::Unchecked);
    /**
    * Timer initialization.
    */
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(intelligenceRunner()));
    connect(timer, SIGNAL(timeout()), this, SLOT(runner()));
    connect(timer, SIGNAL(timeout()), this, SLOT(seller()));
    connect(timer, SIGNAL(timeout()), this, SLOT(apm2Seller()));
    timer->start(1000);

    /**
    * This timer is used for calculating prices of graphite and wood every 5 sec.
    */
    timer5s = new QTimer(this);
    connect(timer5s, SIGNAL(timeout()), this, SLOT(calculatePrices()));
    timer5s->start(5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/** End: Initialization */

/** Start: Functions running every second */

void MainWindow::calculatePrices(){

  Production::calculatePrices();
  QTimer *timer5s = new QTimer(this);
  timer5s->start();
}
void MainWindow::runner()
{
    checkbuttons();
    ui->inventory->setText(QString::number(Pencil::numberofPencil));
    ui->wood->setText(QString::number(Production::numberofWood));
    ui->graphite->setText(QString::number(Production::numberofGraphite));
    ui->priceofWood->setText("$ " + QString::number( Production::priceofWood));
    ui->priceofWood->setAlignment(Qt::AlignCenter);
    ui->priceofGraphite->setText("$ "+QString::number(Production::priceofGraphite));
    ui->priceofGraphite->setAlignment(Qt::AlignCenter);
    ui->priceofApmUpgrade->setText(QString::number(Pencil::apmUpgradePrice) + " IQ");
    ui->priceofApmUpgrade->setAlignment(Qt::AlignCenter);

    ui->wallet->setText("$ " + QString::number(Wallet::balance));

    ui->pencilPrice->setText("$ " + QString::number(Pencil::priceofPencil));
    ui->publicDemand->setText(QString::number(Pencil::rateofPencil));
    ui->numberofApm->setText(QString::number(Pencil::numberofApm));
    ui->priceofApm->setText("$ " + QString::number(Pencil::priceofApm));
    ui->priceofApm->setAlignment(Qt::AlignCenter);
    ui->rateofApm->setText(QString::number(Pencil::rateofApm*Pencil::numberofApm*60) + "pencils/min");
    QFont f("" , 10, QFont::Bold);
    ui->totalinventory->setText(QString::number(Pencil::totalnumberofPencil));
    ui->intelligence->setText(QString::number(Intelligence::intelligenceBalance));
    ui->marketingLevel->setText(QString::number(Pencil::marketing));
    ui->pricetoUnlockMarketing->setText(QString::number(100) + " IQ");
    ui->pricetoUnlockMarketing->setAlignment(Qt::AlignCenter);
    ui->priceofMarketingUpgrade->setText("$ "+QString::number(Pencil::marketingUpgradePrice));
    ui->priceofMarketingUpgrade->setAlignment(Qt::AlignCenter);

    QTimer *timer = new QTimer(this);
    timer->start();
    checkbuttons();
}

void MainWindow::intelligenceRunner(){
    if(!Intelligence::intelligenceIsActive){
        activateIntelligence();
	}
    if(Intelligence::intelligenceIsActive){
        Intelligence::increaseIntelligence();
    }
}


bool MainWindow::activateIntelligence(){
    if(this->totalnumberofPencil>=this->pencilsForUpgrade){
        Intelligence::intelligenceIsActive = 1;
        ui->intelligence->setVisible(true);
        ui->intelligenceLabel->setVisible(true);
        ui->upgradeApm->setVisible(true);
        ui->priceofApmUpgrade->setVisible(true);
        ui->unlockMarketing->setVisible(true);
        ui->pricetoUnlockMarketing->setVisible(true);
    }
    return Intelligence::intelligenceIsActive;
}

/** setEnabled(0) = disable button, setEnabled(1) = enable button */
void MainWindow::checkbuttons(){
    if(Intelligence::intelligenceIsActive){
        if (apmCheck()){
            ui->upgradeApm->setEnabled(1);
        }
        else{
            ui->upgradeApm->setEnabled(0);
        }

        if (!Pencil::marketingUnlocked &&
                Intelligence::intelligenceBalance>=100){
            ui->unlockMarketing->setEnabled(1);
        }
        else{
            ui->unlockMarketing->setEnabled(0);
        }

        if(Pencil::marketingUnlocked &&
                Wallet::balance>=Pencil::marketingUpgradePrice){
            ui->upgradeMarketing->setEnabled(1);
        }
        else{
            ui->upgradeMarketing->setEnabled(0);
        }
    }

  if (Wallet::balance < Production::priceofGraphite){
    ui->buyGraphite->setEnabled(0);
  }else{
    ui->buyGraphite->setEnabled(1);
  }

  if (Wallet::balance < Production::priceofWood){
    ui->buyWood->setEnabled(0);
  }else{
    ui->buyWood->setEnabled(1);
  }

  if (Wallet::balance < Pencil::priceofApm){
    ui->buyApm->setEnabled(0);
  }else{
    ui->buyApm->setEnabled(1);
  }

  /** Prevent the user from setting the price lower than 0 */
  if (Pencil::priceofPencil <= 0.1){
    ui->decreasePencil->setEnabled(0);
  }else{
    ui->decreasePencil->setEnabled(1);
  }
}

void MainWindow::seller()
{
    Pencil::sell();
    QTimer *timer = new QTimer(this);
    timer->start();
}

void MainWindow::apm2Seller()
{
    Pencil::apm2000();
    QTimer *timer = new QTimer(this);
    timer->start();
}

/** End : Functions running every second */

/** Start: Buttons and their functionalities */

void MainWindow::on_buyWood_clicked()
{
    Production::buyWood();
    checkbuttons();
}

void MainWindow::on_buyGraphite_clicked()
{
    Production::buyGraphite();
    checkbuttons();
}

void MainWindow::on_makePencil_clicked()
{
    Pencil::producePencil();
}

void MainWindow::on_increasePencil_clicked()
{
    Pencil::increasePrice();
    Pencil::newRate();
}

void MainWindow::on_decreasePencil_clicked()
{
    Pencil::decreasePrice();
    Pencil::newRate();
}

void MainWindow::on_buyApm_clicked(){
  Pencil::buyApm();
  checkbuttons();
}

void MainWindow::on_upgradeApm_clicked(){
    Pencil::upgradeApm();
    ui->upgradeApm->setVisible(false);
    ui->priceofApmUpgrade->setVisible(false);
    checkbuttons();
}


void MainWindow::on_unlockMarketing_clicked()
{
    Intelligence::intelligenceBalance -= 100;
    unlockMarketing();
    marketingUnlocked = true;
}

void MainWindow::on_upgradeMarketing_clicked()
{
    Pencil::upgradeMarketing();
}

/** End: Buttons and their functionalities */

bool MainWindow::apmCheck(){
    if(ui->upgradeApm->isVisible()){
        if(Intelligence::intelligenceBalance>=Pencil::apmUpgradePrice){
            return true;
        }
        return false;
    }

    else if(Pencil::apmUpgradeAvailable && Pencil::totalnumberofPencil>=Pencil::pencilsForUpgrade){
        ui->upgradeApm->setVisible(true);
        ui->priceofApmUpgrade->setVisible(true);
        return apmCheck();
    }
    else{
        return false;
    }
}

void MainWindow::unlockMarketing(){
    ui->unlockMarketing->setVisible(false);
    ui->pricetoUnlockMarketing->setVisible(false);
    ui->marketingLabel->setVisible(true);
    ui->marketingLevel->setVisible(true);
    ui->upgradeMarketing->setVisible(true);
    ui->priceofMarketingUpgrade->setVisible(true);
}

void MainWindow::disableComponents(){
    ui->intelligence->setVisible(false);
    ui->intelligenceLabel->setVisible(false);
    ui->upgradeApm->setVisible(false);
    ui->priceofApmUpgrade->setVisible(false);
    ui->unlockMarketing->setVisible(false);
    ui->pricetoUnlockMarketing->setVisible(false);
    ui->upgradeMarketing->setVisible(false);
    ui->priceofMarketingUpgrade->setVisible(false);
    ui->marketingLabel->setVisible(false);
    ui->marketingLevel->setVisible(false);
}

void MainWindow::save(){
    timer->stop();
    timer5s->stop();
    /** Saves game in a .sav file */
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Game"), "",
            tr("Game (*.sav);;All Files (*)"));

    if (fileName.isEmpty())
            return;
    else {
        QFile file(fileName);
        /** If openning the file fails, report to user. */
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
        /** Taking out the values to save */
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << qint32(intelligenceBalance);
        out << intelligenceIsActive;
        out << priceofPencil;
        out << rateofPencil;
        out << qint32(numberofPencil);
        out << totalnumberofPencil;
        out << qint32(pencilsForUpgrade);
        out << numberofApm;
        out << priceofApm;
        out << rateofApm;
        out << apmFractional;
        out << qint32(apmUpgradePrice);
        out << qint32(marketing);
        out << marketingUpgradePrice;
        out << marketingUnlocked;
        out << priceofWood;
        out << priceofGraphite;
        out << numberofWood;
        out << numberofGraphite;
        out << balance;
    }

    uploadScore(int(totalnumberofPencil));

    timer->start();
    timer5s->start();
}

void MainWindow::load(){

    /** Loads game from a .sav file */
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Game"), "",
            tr("Game (*.sav);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        /** If openning the file fails, report to user. */
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        /** Taking in the values to load */
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        in >> intelligenceBalance;
        in >> intelligenceIsActive;
        in >> priceofPencil;
        in >> rateofPencil;
        in >> numberofPencil;
        in >> totalnumberofPencil;
        in >> pencilsForUpgrade;
        in >> numberofApm;
        in >> priceofApm;
        in >> rateofApm;
        in >> apmFractional;
        in >> apmUpgradePrice;
        in >> marketing;
        in >> marketingUpgradePrice;
        in >> marketingUnlocked;
        in >> priceofWood;
        in >> priceofGraphite;
        in >> numberofWood;
        in >> numberofGraphite;
        in >> balance;

        gameStart();
        activateIntelligence();
        if(marketingUnlocked){
            unlockMarketing();
        }
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::displayDebugButton(){
    if(ui->speedup->isVisible()){
        ui->speedup->setVisible(false);
    }
    else{
        ui->speedup->setVisible(true);
    }
}

void MainWindow::debug(){
    Debug::speedUp();
}

void MainWindow::on_startGame_clicked()
{
    gameStart();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_loadGame_clicked()
{
    load();
}

void MainWindow::on_quit_clicked()
{
    getHighScore();
    ui->stackedWidget->setCurrentIndex(0);
    initializePencil();
    initializeWallet();
    initializeProduction();
    initializeIntelligence();
    delete timer5s;
    delete timer;
}

void MainWindow::getHighScore(){
    ui->tableWidget->setRowCount(0);

    /*std::map<std::string, int>::iterator it = highScores.begin();
    while (it != highScores.end())
        {
            std::string scoreString = it->first;
            scoreString += ":\t";
            scoreString += std::to_string(it->second);

            std::cout << scoreString << std::endl;
            ui->listWidget->addItem(scoreString.c_str());

            it++;
        }*/

    getScores();

    int row=0;
    ui->tableWidget->setRowCount(int(Server::playerNames.size()));
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Player"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Score"));
    for (int i = 0 ; i < int(Server::playerNames.size());i++) {
        int score = playerScores[i];
        QTableWidgetItem *itemName = new QTableWidgetItem();
        QTableWidgetItem *itemNo = new QTableWidgetItem();

        itemNo->setText(QString::number(score));
        itemName->setText(QString::fromUtf8(playerNames[i].c_str()));

        ui->tableWidget->setItem(row, 1, itemNo);
        ui->tableWidget->setItem(row, 0, itemName);
        row++;
    }
   //ui->tableWidget->horizontalHeader()->Resize;
}
