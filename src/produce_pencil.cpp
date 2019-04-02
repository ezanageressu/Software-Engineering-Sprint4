#include "produce_pencil.h"
#include "ui_produce_pencil.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include <QtMath>

using namespace std;

/** This function produces pencils.                                            
*/
produce_pencil::produce_pencil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::produce_pencil)
{
    ui->setupUi(this);

    QTimer *mp = new QTimer(this);
    connect(mp, SIGNAL(timeout()), this, SLOT(material_price()));
    mp->start(5000);

    QTimer *pd = new QTimer(this);
    connect(pd, SIGNAL(timeout()), this, SLOT(public_demand()));
    pd->start(200);

    QTimer *sp = new QTimer(this);
    connect(sp, SIGNAL(timeout()), this, SLOT(sell_pencil()));
    sp->start(200);

    QTimer *m_apm = new QTimer(this);
    connect(m_apm, SIGNAL(timeout()), this, SLOT(make_apm()));
    m_apm->start(1000);
}

/** Destructor for method make pencil.                                                                                            
*/
produce_pencil::~produce_pencil()
{
    delete ui;
}

/** Getting material prices                                               
*/
void produce_pencil::material_price(){
     wood_price = rand() % ((2000 + 1) - 1000) + 1000;
     graphite_price = rand() % ((2500 + 1) - 1500) + 1500;

     ui->textWoodPrice->setText("$" + QString::number(wood_price) + " / 100m");
     ui->textGraphitePrice->setText("$" + QString::number(graphite_price) + " / 100m");
}

/** Functionality of buying a pencil                                               
*/
void produce_pencil::buy_pencil(){
    if(bank_balance >= pencil_price){
        bank_balance-=pencil_price;

        ui->textBankBalance->setText("$" + QString::number(bank_balance, 'f', 2));
    }else{
        ui->MakePencil->setEnabled(false);
    }
}

/** Functionality of selling a pencil.                                                
*/
void produce_pencil::sell_pencil(){
    if(pencil_count > 0){
        pencil_count--;
        bank_balance += pencil_price;

        ui->textPencilInventory->setText(QString::number(pencil_count));
        ui->textPencilProduced->setText(QString::number(pencil_count));
        ui->textBankBalance->setText("$" + QString::number(bank_balance, 'f', 2));
    }
}

void produce_pencil::public_demand(){
   rate = 1/pencil_price;

   ui->textPublicDemand->setText(QString::number(rate, 'f', 2));
}

/** This function makes an apm.                                                 
*/
void produce_pencil::make_apm(){
    int apm_pencil_count = (AutoPencil2000 * 2);
    for(int i = 0; i < apm_pencil_count; i++){
        if((apm_pencil_count > 0) && wood_count >= 0.42 && graphite_count >=0.40){
        pencil_count += 1;
        wood_count -= 0.21;
        graphite_count -= 0.20;

        ui->textWoodLeft->setText(QString::number(wood_count, 'f', 2) + " m");
        ui->textGraphiteLeft->setText(QString::number(graphite_count, 'f', 2) + " m");
        ui->textAPM->setText(QString::number(AutoPencil2000));
        ui->textPencilInventory->setText(QString::number(pencil_count));
        ui->textPencilProduced->setText(QString::number(pencil_count));
        }
    }
}

void produce_pencil::on_MakePencil_clicked()
{
    if (wood_count - 0.21 < 0 && graphite_count - 0.20 < 0){
        ui->MakePencil->setEnabled(false);
    }else{
        pencil_count++;
        wood_count -= 0.21;
        graphite_count -= 0.20;
        bank_balance += pencil_price;
    }
    ui->textPencilInventory->setText(QString::number(pencil_count));
    ui->textPencilProduced->setText(QString::number(pencil_count));
    ui->textWoodLeft->setText(QString::number(wood_count, 'f', 2) + " m");
    ui->textGraphiteLeft->setText(QString::number(graphite_count, 'f', 2) + " m");
    ui->textBankBalance->setText("$" + QString::number(bank_balance, 'f', 2));
}


void produce_pencil::on_BuyWood_clicked()
{
    if(bank_balance >= wood_price){
       bank_balance -= wood_price;
       wood_count += 100.00;

       ui->textWoodLeft->setText(QString::number(wood_count, 'f', 2) + " m");
       ui->textBankBalance->setText("$" + QString::number(bank_balance, 'f', 2));
    }else{
        ui->BuyWood->setEnabled(false);
    }
}

void produce_pencil::on_BuyGraphite_clicked()
{
    if(bank_balance >= graphite_price){
       bank_balance -= graphite_price;
       graphite_count += 100.00;

       ui->textGraphiteLeft->setText(QString::number(graphite_count, 'f', 2) + " m");
       ui->textBankBalance->setText("$" + QString::number(bank_balance, 'f', 2));
    }else{
        ui->BuyGraphite->setEnabled(false);
    }
}


void produce_pencil::on_BuyAPM_clicked()
{
    if(AutoPencil2000 < 10 && bank_balance >= apm_price){
      AutoPencil2000++;
      apm_price *= 1.1;

      ui->textAPM->setText(QString::number(AutoPencil2000));
      ui->textAPMPrice->setText("$" + QString::number(apm_price));
    }
}


void produce_pencil::on_DecreasePrice_clicked()
{
    if(pencil_price > 0.05){
       pencil_price -= 0.05;

       ui->textPencilPrice->setText("$" + QString::number(pencil_price, 'f', 2));
    }
}

void produce_pencil::on_IncreasePrice_clicked()
{
    if(pencil_price > 0){
        pencil_price += 0.05;

        ui->textPencilPrice->setText("$" + QString::number(pencil_price, 'f', 2));
    }
}
