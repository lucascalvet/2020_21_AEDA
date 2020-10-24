#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "carpark.h"
#include <string>

using testing::Eq;

TEST(test_1, a_CarPark){
    CarPark p1(4, 6);
    // park capacity
    EXPECT_EQ(4, p1.getNumPlaces());
    // number max of clients
    EXPECT_EQ(6, p1.getNumMaxClients());
}


TEST(test_1, b_AddClient){
    CarPark p1(3, 5);
    // adding a new client
    EXPECT_EQ(true, p1.addClient("Joao"));
    p1.addClient("Antonio");
    p1.addClient("Rui");
    p1.addClient("Maria");
    p1.addClient("Clara");
    // park has the maximum number of clients
    EXPECT_EQ(false, p1.addClient("Paula"));
    // client position
    EXPECT_EQ(1, p1.clientPosition("Antonio"));
    // client does not exist
    EXPECT_EQ(-1, p1.clientPosition("Joana"));
}

TEST(test_1, c_EnterPark){
    CarPark p1(3, 5);
    p1.addClient("Joao");
    p1.addClient("Maria");
    p1.addClient("Antonio");
    p1.addClient("Rui");
    // client entering the park
    EXPECT_EQ(true, p1.enter("Maria"));
    // client does not exist
    EXPECT_EQ(false, p1.enter("Paula"));
    // client already in the park
    EXPECT_EQ(false, p1.enter("Maria"));
    p1.enter("Joao");
    p1.enter("Antonio");
    // park is full
    EXPECT_EQ(false, p1.enter("Rui"));
}

TEST(test_1, d_RemoveClient){
    CarPark p1(3, 5);
    p1.addClient("Joao");
    p1.addClient("Maria");
    p1.addClient("Antonio");
    p1.enter("Maria");
    // client is in the park, cannot be removed
    EXPECT_EQ(false, p1.removeClient("Maria"));
    // client is out of the park, can be removed
    EXPECT_EQ(true, p1.removeClient("Antonio"));
    // client does not exist, cannot be removed
    EXPECT_EQ(false, p1.removeClient("Ana"));
}

TEST(test_1, e_LeavePark){
    CarPark p1(3, 5);
    p1.addClient("Joao");
    p1.addClient("Maria");
    p1.addClient("Rui");
    p1.enter("Maria");
    p1.enter("Joao");
    p1.enter("Rui");
    // client leaves the park.
    EXPECT_EQ(true, p1.leave("Maria"));
    // client is not in the park
    EXPECT_EQ(false, p1.leave("Maria"));
    // client does not exist
    EXPECT_EQ(false, p1.leave("Antonio"));
}

TEST(test_1, f_ParkPlaces){
    CarPark p1(3, 5);
    p1.addClient("Joao");
    p1.addClient("Maria");
    p1.addClient("Antonio");
    p1.enter("Maria");
    p1.enter("Antonio");
    // park capacity
    EXPECT_EQ(3, p1.getNumPlaces());
    // number of occupied places
    EXPECT_EQ(2, p1.getNumOccupiedPlaces());
    // number of registered clients
    EXPECT_EQ(3, p1.getNumClients());
}
