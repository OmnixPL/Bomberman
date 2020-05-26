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
        map[i] = 'a';
    }
    int bombPos[NO_PLAYERS * NO_BOMBS][2] = 
    {
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1}
    };


    float playerPos[NO_PLAYERS][2] = 
    {
        {1.0f, 1.0f},
        {1.0f, 2.0f},
        {1.0f, 3.0f},
        {1.0f, 4.0f},
    };
    bool playerAlive[] = {true, true, true, true};
    std::string user = "testUser";
    
    PacketGame p(user, map, bombPos, playerPos, playerAlive);
    int bombPosGot[NO_PLAYERS * NO_BOMBS][2] =
    {
        {p.getBombPositionX(0,0), p.getBombPositionY(0,0)},
        {p.getBombPositionX(0,1), p.getBombPositionY(0,1)},
        {p.getBombPositionX(1,0), p.getBombPositionY(1,0)},
        {p.getBombPositionX(1,1), p.getBombPositionY(1,1)},
        {p.getBombPositionX(2,0), p.getBombPositionY(2,0)},
        {p.getBombPositionX(2,1), p.getBombPositionY(2,1)},
        {p.getBombPositionX(3,0), p.getBombPositionY(3,0)},
        {p.getBombPositionX(3,1), p.getBombPositionY(3,1)}
    };
    float playerPosGot[NO_PLAYERS][2] = {
        {p.getPlayerPosition(0,0),p.getPlayerPosition(0,1)},
        {p.getPlayerPosition(1,0),p.getPlayerPosition(1,1)},
        {p.getPlayerPosition(2,0),p.getPlayerPosition(2,1)},
        {p.getPlayerPosition(3,0),p.getPlayerPosition(3,1)}
        };
    bool playerAliveGot[] = {
        p.getPlayerAlive(0),
        p.getPlayerAlive(1),
        p.getPlayerAlive(2),
        p.getPlayerAlive(3)
    };
    char * mapInfoGot = p.getMapInfo();
    ASSERT_EQ(p.getUser(), user);
    ASSERT_THAT(playerAliveGot, testing::ElementsAreArray(playerAlive));

    for(int i = 0; i < NO_PLAYERS * NO_BOMBS; i++)
    {
        ASSERT_EQ(bombPos[i][0], p.getBombPositionX(i/2, i%2));
        ASSERT_EQ(bombPos[i][1], p.getBombPositionY(i/2, i%2));
    }

    for(int i = 0; i < NO_MAP_FIELDS; i++)
    {
        ASSERT_EQ(map[i], mapInfoGot[i]);
    }
}

TEST( PacketGameTests, SerializePacket)
{
    char map[NO_MAP_FIELDS];
    for(int i = 0; i < NO_MAP_FIELDS; i++)
    {
        map[i] = '\1';
    }
    int bombPos[NO_PLAYERS * NO_BOMBS][2] = 
    {
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1}
    };
    float playerPos[NO_PLAYERS][2] = 
    {
        {1.0f, 1.0f},
        {1.0f, 2.0f},
        {1.0f, 3.0f},
        {1.0f, 4.0f},
    };
    bool playerAlive[] = {true, true, true, true};
    std::string user = "testUser";
    
    PacketGame p(user, map, bombPos, playerPos, playerAlive);
    char buffer[BUFFERSZ];
    int offset = p.serialize(buffer, BUFFERSZ);

    for(int i = 17; i < 17+NO_MAP_BYTES-1; i++)
    {
        ASSERT_EQ(buffer[i], (char)85);
    }
    ASSERT_EQ(buffer[16+NO_MAP_BYTES], (char)64);

}

TEST( PacketGameTests, SerializeAndDeserialize )
{
    char map[NO_MAP_FIELDS];
    for(int i = 0; i < NO_MAP_FIELDS; i++)
    {
        map[i] = '\1';
    }
    int bombPos[NO_PLAYERS * NO_BOMBS][2] = 
    {
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1},
        {1,1}
    };
    float playerPos[NO_PLAYERS][2] = 
    {
        {1.0f, 1.0f},
        {1.0f, 2.0f},
        {1.0f, 3.0f},
        {1.0f, 4.0f},
    };
    bool playerAlive[] = {true, true, true, true};
    std::string user = "testUser";
    
    PacketGame p(user, map, bombPos, playerPos, playerAlive);
    char buffer[BUFFERSZ];
    int offset = p.serialize(buffer, BUFFERSZ);    

    PacketGame p2(buffer, BUFFERSZ);
    char buffer2[BUFFERSZ];
    p2.serialize(buffer2, BUFFERSZ);

    for(int i = 0; i < offset; i++)
    {
        ASSERT_EQ(buffer[i], buffer2[i]);
    }
}

TEST( IntegrationTests, TestServerLoop )
{
    Server server(TEST_PORT);
    server.testLoop();
}

TEST( IntegrationTests, TestClientLoop )
{
    Client client(6, "127.0.0.1", TEST_PORT, "testUser", "resources/moves.txt",2);
    client.testLoop();
}

TEST( IntegrationTests, RunServer )
{
    Server server(TEST_PORT, "Haselko");
    server.testLoop();
}

TEST( IntegrationTests, RunClientSequentially )
{
    Client client(6, "127.0.0.1", TEST_PORT, "testUser", "resources/moves.txt",2);
    client.runSequential();
}

TEST( IntegrationTests, TestCase1 )
{
    Client client(6, "127.0.0.1", TEST_PORT, "testUser1", "resources/test1.txt",2);
    client.runSequential();
}

TEST( IntegrationTests, TestCase2 )
{
    Client client(6, "127.0.0.1", TEST_PORT, "testUser2", "resources/test2.txt",2);
    client.runSequential();
}

TEST( IntegrationTests, TestCase3 )
{
    Client client(6, "127.0.0.1", TEST_PORT, "testUser3", "resources/test3.txt",2);
    client.runSequential();
}
TEST( IntegrationTests, TestCase4 )
{
    Client client(6, "127.0.0.1", TEST_PORT, "testUser4", "resources/test4.txt",2);
    client.runSequential();
}

TEST( IntegrationTests, TestCase5 )
{
    Client client(6, "127.0.0.1", TEST_PORT, "testUser4", "resources/test5.txt",2);
    client.runSequential();
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}