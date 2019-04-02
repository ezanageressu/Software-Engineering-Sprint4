#ifndef PRODUCE_PENCIL_H
#define PRODUCE_PENCIL_H

#include <QMainWindow>

namespace Ui {
class produce_pencil;
}

class produce_pencil : public QMainWindow
{
    Q_OBJECT

public:
    explicit produce_pencil(QWidget *parent = nullptr);
    ~produce_pencil();

    /*!
     * \brief Private variables that are used throughout the project
     */
private:
    Ui::produce_pencil *ui;
    int pencil_count = 0;
    double graphite_count = 1000.00;
    double graphite_price;
    double wood_count = 1000.000;
    double wood_price;
    /*!
     * For the purpose of testing the buttons, we've made the bank balance $145,000.00 instead
     * of $145.00 (as written on the spring write up because the prices for wood/graphite/apm
     * are greater than 1,000, which we will never have unless we make a lot of money from making pencil
     */
    double bank_balance = 145000.00;
    double pencil_price = 1.00;
    double rate = 0.00;
    int AutoPencil2000 = 0;
    double apm_price = 150.00;

private slots:
    /*! \brief Using rand() function to generate random prices for both price of graphite and wood
     *
     * \return Wood and graphite price
     */
    void material_price();

    /*! \brief Decreasing bank balance as you buy a pencil by first checking if there is enough money
     *
     * \return New bank balance after buying pencil
     */
    void buy_pencil();

    /*! \brief Checking if there are available pencil in inventory, then you can see the pencil
     *
     * \return Decrease pencil inventory and return new number
     */
    void sell_pencil();

    /*! \brief Calculate the public demand rate by the given rate equation from the sprint
     *
     * \return The rate of public demand
     */
    void public_demand();

    /*! \brief Creating pencils using the APM machine, which prduces 2 pencils per seconds by checking
     *         if there are enough material first
     *
     * \return New pencil count, new material inventory
     */
    void make_apm();

    /*! \brief QPushButton action that makes pencil
     *
     * \return void
     */
    void on_MakePencil_clicked();

    /*! \brief QPushButton action that buys wood
     *
     * \return void
     */
    void on_BuyWood_clicked();

    /*! \brief QPushButton action that buys graphite
     *
     * \return void
     */
    void on_BuyGraphite_clicked();

    /*! \brief QPushButton action that buys an APM machine, with the restriction of 10 machines
     *
     * \return void
     */
    void on_BuyAPM_clicked();

    /*! \brief QPushButton action that decreases the pencil price
     *
     * \return void
     */
    void on_DecreasePrice_clicked();

    /*! \brief QPushButton action that increases the pencil price
     *
     * \return void
     */
    void on_IncreasePrice_clicked();
};

#endif // PRODUCE_PENCIL_H
