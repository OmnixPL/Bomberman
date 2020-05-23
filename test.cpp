#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <server.h>
#include <client.h>
#include <clientReceiver.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TEST_PORT 57312

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

TEST( PacketTest, SerializeAndDeserializePacket )
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

    EXPECT_EQ(p1.getNoAck(), 10);
    EXPECT_EQ(p1.getType(), packet_t::ACK);
    EXPECT_EQ(p1.getUser(), "default");
}

TEST( PacketTest, CreateAuthPacket )
{
    std::string passwordUsed = "password";
    const std::string user = "user";
    PacketAuth p1(passwordUsed, user);
    
    ASSERT_EQ(p1.getPassword(), passwordUsed);
    ASSERT_EQ(p1.getUser(), user);
    ASSERT_EQ(p1.getType(), packet_t::AUTH);
}

TEST( PacketTest, CreatePacketRdy )
{
    bool isReadyUsed = true;
    const std::string user = "user";
    PacketRdy p1(isReadyUsed, user);
    
    ASSERT_EQ(p1.getRdy(), isReadyUsed);
    ASSERT_EQ(p1.getUser(), user);
    ASSERT_EQ(p1.getType(), packet_t::RDY);
}

TEST( PacketTest, CreatePacketRenew )
{
    const std::string user = "user";
    PacketRenew p1(user);
    
    ASSERT_EQ(p1.getUser(), user);
    ASSERT_EQ(p1.getType(), packet_t::RENEW);
}

TEST( PacketTest, CreatePacketDisconnect )
{
    const std::string user = "user";
    PacketDisconnect p1(user);
    
    ASSERT_EQ(p1.getUser(), user);
    ASSERT_EQ(p1.getType(), packet_t::DISCONNECT);
}

TEST( PacketTest, CreatePacketAns )
{
    const std::string user = "user";
    ans_t answerUsed = ans_t::BAD_PASSWORD;
    PacketAns p1(answerUsed, user);
    
    ASSERT_EQ(p1.getUser(), user);
    ASSERT_EQ(p1.getAns(), answerUsed);
    ASSERT_EQ(p1.getType(), packet_t::ANS);
}

TEST( PacketTest, CreatePacketLobby )
{
    std::vector<std::string> playersUsed = {"first", "second"};
    std::vector<bool> readyVectorUsed = {true, true};
    const std::string user = "user";
    PacketLobby p1(playersUsed, readyVectorUsed, user);
    
    ASSERT_EQ(p1.getUser(), user);
    ASSERT_EQ(p1.players, playersUsed);
    ASSERT_EQ(p1.rdy, readyVectorUsed);
    ASSERT_EQ(p1.getType(), packet_t::LOBBY);
}

TEST( PacketActionTests, CreatePacketAction)
{
    char buffer[BUFFERSZ];
    PacketAction p(buffer, BUFFERSZ);
}

TEST( PacketActionTests, SerializePacketAction )
{
    PacketAction p("testUser", action_t::DOWN, true);
    char buffer[BUFFERSZ];
    p.serialize(buffer, BUFFERSZ);
    ASSERT_EQ(strcmp("\5\0\0\0\0\0\0\0testUser\0\2\1", buffer), 0);
}

TEST( PacketActionTests, SerializeAndDeserialize )
{
    char * buffer = "\5\0\0\0\0\0\0\0testUser\0\2\1";

    PacketAction p(buffer, sizeof(char)*19);
    char buffer2[BUFFERSZ];
    p.serialize(buffer2, BUFFERSZ);
    ASSERT_EQ(strcmp(buffer, buffer2), 0);
}

TEST( PacketGameTests, CreatePacket )
{
    char map[NO_MAP_FIELDS];
    for(int i = 0; i < NO_MAP_FIELDS; i++)
    {
        map[i] = (char)i + 'a';
    }
    int bombPos[NO_PLAYERS][NO_BOMBS] = 
    {
        {0xFF,0xFF},
        {0xFF,0xFF},
        {0xFF,0xFF},
        {0xFF,0xFF}
    };
    float playerPos[] = {0.0f, 1.0f, 2.0f, 3.0f};
    bool playerAlive[] = {true, true, true, true};
    std::string user = "testUser";
    
    PacketGame p(user, map, bombPos, playerPos, playerAlive);
    int bombPosGot[NO_PLAYERS][NO_BOMBS] =
    {
        {p.getBombPosition(0,0), p.getBombPosition(0,1)},
        {p.getBombPosition(1,0), p.getBombPosition(1,1)},
        {p.getBombPosition(2,0), p.getBombPosition(2,1)},
        {p.getBombPosition(3,0), p.getBombPosition(3,1)}
    };
    float playerPosGot[] = {
        p.getPlayerPosition(0),
        p.getPlayerPosition(1),
        p.getPlayerPosition(2),
        p.getPlayerPosition(3)
        };
    bool playerAliveGot[] = {
        p.getPlayerAlive(0),
        p.getPlayerAlive(1),
        p.getPlayerAlive(2),
        p.getPlayerAlive(3)
    };
    char * mapInfoGot = p.getMapInfo();
    ASSERT_EQ(p.getUser(), user);
    for(int i = 0; i < NO_PLAYERS; i++)
    {
        for(int j = 0; j < NO_BOMBS; j++)
        {
            ASSERT_EQ(bombPosGot[i][j], bombPos[i][j]);
        }
    }
    ASSERT_THAT(playerPosGot, testing::ElementsAreArray(playerPos));
    ASSERT_THAT(playerAliveGot, testing::ElementsAreArray(playerAlive));
    // ASSERT_THAT(mapInfoGot, testing::ElementsAreArray(map));
}

TEST( IntegrationTests, TestServerLoop )
{
    Server server(TEST_PORT);
    server.testLoop();
}

TEST( IntegrationTests, TestClientLoop )
{
    Client client(6, "127.0.0.1", TEST_PORT);
    client.testLoop();
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}