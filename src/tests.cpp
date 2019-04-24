#include <QApplication>
#include <iostream>
#include "src/mainwindow.h"
#include "src/pencil.h"
#include "src/pencil.cpp"
#include "src/production.h"
#include "src/production.cpp"
#include "src/wallet.h"
#include "src/wallet.cpp"
#include "src/intelligence.h"
#include "src/debug.h"
#include <gtest/gtest.h>

// Tests for Pencil class
TEST(PencilProduce, pencilMake){
    Pencil P;

    ASSERT_EQ(0, P.numberofPencil);
    P.producePencil();
    ASSERT_EQ(1, P.numberofPencil);

    ASSERT_EQ(1, P.numberofApm);
    ASSERT_EQ(1, P.rateofPencil);
    ASSERT_EQ(1, P.rateofPencil);

    P.increasePrice();
    ASSERT_EQ(1.05, P.priceofPencil);

    P.newRate();

    ASSERT_EQ(.95, P.rateofPencil);

    P.decreasePrice();
    ASSERT_EQ(1.00, P.priceofPencil);

    ASSERT_EQ(1, P.getInventory());

    EXPECT_ANY_THROW(P.buyApm(););


}

// Tests APM Upgrade
TEST(PencilProduce, ApmUpgrade){
    Pencil P;
    P.intelligenceBalance = 100;
    P.upgradeApm();
    ASSERT_EQ(2.20, P.rateofApm);
    ASSERT_EQ(200, P.apmUpgradePrice);
    ASSERT_EQ(5000, P.pencilsForUpgrade);
    ASSERT_EQ(50, P.intelligenceBalance);
}

// Tests Marketing Upgrade
TEST(PencilProduce, MarketingUpgrade){
    Pencil P;
    P.intelligenceBalance = 50;
    P.balance = 1000;
    P.upgradeMarketing();
    ASSERT_EQ(1, P.marketing);
    ASSERT_EQ(550, P.marketingUpgradePrice);
    ASSERT_EQ(500, P.balance);
    ASSERT_EQ(1.1, P.rateofPencil);
}

// Tests for Wallet class
TEST(WalletTest, WalletMake){
  Wallet W;

  ASSERT_EQ(145.00, W.balance);

  W.setBalance(150.00);

  ASSERT_EQ(150.00, W.balance);
}

// Tests for Production class
TEST(ProductionTest, ProductionMake){
  Production P;

  ASSERT_EQ(P.numberofWood, 1000);
  ASSERT_EQ(P.numberofGraphite, 1000);
  P.decreaseWood();

  ASSERT_EQ(P.numberofWood, 999.8);
  P.decreaseGraphite();
  ASSERT_EQ(P.numberofGraphite, 999.79);

  ///Check whether it is possible to buy Wood and Graphite or not with current
  ///balance.
  EXPECT_ANY_THROW(P.buyWood(););
  EXPECT_ANY_THROW(P.buyGraphite(););

  bool testwoodButton;
  testwoodButton =  P.disable_buyWood();
  ASSERT_EQ(testwoodButton, true);

  bool testgraphiteButton;
  testgraphiteButton = P.disable_buyGraphite();
  ASSERT_EQ(testgraphiteButton, true);
}

//Tests for Intelligence class
TEST(IntelligenceTest, IntelligenceIncrease){
  Intelligence I;
  ASSERT_EQ(false, I.intelligenceIsActive);
  ASSERT_EQ(0, I.intelligenceBalance);
  I.increaseIntelligence();
  ASSERT_EQ(1, I.intelligenceBalance);
}

//Tests for Debug Class
TEST(DebugTest, SpeedUp){
    Debug D;
    ASSERT_EQ(145,D.balance);
    ASSERT_EQ(0,D.numberofPencil);
    ASSERT_EQ(0,D.totalnumberofPencil);
    ASSERT_EQ(1000,D.numberofWood);
    ASSERT_EQ(1000,D.numberofGraphite);

    D.speedUp();
    ASSERT_EQ(1145,D.balance);
    ASSERT_EQ(1000,D.numberofPencil);
    ASSERT_EQ(1000,D.totalnumberofPencil);
    ASSERT_EQ(1010,D.numberofWood);
    ASSERT_EQ(1010,D.numberofGraphite);
}

//Tests for Server Class
TEST(ServerTest, getScores){
    Server S;
    S.getScores();
    EXPECT_EQ(10, int(S.playerNames.size()));
    ASSERT_LT(0, int(S.playerNames.size()));
    EXPECT_EQ(10, int(S.playerScores.size()));
    ASSERT_LT(0, int(S.playerScores.size()));
}

int main(int argc, char *argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
