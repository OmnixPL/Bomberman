#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <server.h>

using namespace std;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

class DataBaseConnect {
    public:
    virtual bool login(string username, string password) {return true;}
    virtual bool logout(string username) {return true;}
    virtual int fetchRecord() { return -1;}
};

class MockDB : public DataBaseConnect {
    public:
    MOCK_METHOD0(fetchRecord, int());
    MOCK_METHOD1(logout, bool (string username));
    MOCK_METHOD2(login, bool(string username, string password));
};

class MyDatabase {
    DataBaseConnect & dbC;
    public:
    MyDatabase(DataBaseConnect & _dbC) : dbC(_dbC){}
    int Init(string username, string password)
    {
        if (dbC.login(username, password) != true) {
            std::cout<<"DB FAILURE"<<endl; return -1;
        }
        else
        {
            std::cout<<"DB SUCCESS"<<endl; return 1;
        }
    }
};
 
TEST(HelloWorldTest, BasicMock) { 
    // Arrange
    MockDB mdb;
    MyDatabase db(mdb);

    EXPECT_CALL(mdb, login("Terminator", "asdf"));
    ON_CALL(mdb, login("Terminator", "asdf")).WillByDefault(Return(1));

    // Act
    int retValue = db.Init("Terminator", "asdf");

    // Assert
    EXPECT_EQ(retValue, 1);
}


TEST( PacketTest, CreatePacket )
{
    Packet::userDefault = "default";
    
    Packet p1(packet_t::ACK, "user");
    Packet p2(packet_t::GAME, "");

    EXPECT_EQ(p1.getType(), packet_t::ACK);
    EXPECT_EQ(p1.getUser(), "user");

    EXPECT_EQ(p2.getType(), packet_t::GAME);
    EXPECT_EQ(p2.getUser(), "default");
}

TEST( PacketTest, SerializeAndDeserialize )
{
    size_t len = 512;
    char bufferUsed[512];
    
    Packet p2(packet_t::GAME);
    p2.serialize(bufferUsed, len);
    Packet p3(bufferUsed, len);
    
    EXPECT_EQ(p2.getType(), packet_t::GAME);
    EXPECT_EQ(p2.getType(), p3.getType());
}

TEST( PacketTest, CreateAckPacket )
{
    Packet::userDefault = "default";
    int numberUsed = 10;
    PacketAck p1(numberUsed, "");

    EXPECT_EQ(p1.getType(), packet_t::ACK);
    EXPECT_EQ(p1.getUser(), "default");

}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}