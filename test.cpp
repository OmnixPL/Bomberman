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
#include <thread>

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

TEST( ClientTest_1, test)
{

    Client client(6, "127.0.0.1", TEST_PORT, "resources/moves.txt");
    client.test4();

}

TEST( ClientSenderTest_1, test)
{
    char addr[] = "127.0.0.1";
    sockaddr_in6 servaddr;
    servaddr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, addr, &servaddr.sin6_addr);
    servaddr.sin6_port = htons(TEST_PORT);
    int cliSockfd;
    if ((cliSockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }

    std::mutex m;
    ClientSender sender(cliSockfd, addr, TEST_PORT, m);
    sender();
}

TEST( ClientSenderTests, pushThenPop )
{
    char addr[] = "127.0.0.1";
    sockaddr_in6 servaddr;
    servaddr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, addr, &servaddr.sin6_addr);
    servaddr.sin6_port = htons(TEST_PORT);
    int cliSockfd;
    if ((cliSockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }
    std::mutex m;
    ClientSender sender(cliSockfd, addr, TEST_PORT, m);
    sender.addToQueue(new PacketAck(4, "testUser"));
    Packet * p = sender.popFromQueue();
    ASSERT_EQ(p->getUser(), "testUser");
    ASSERT_EQ(dynamic_cast<PacketAck*>(p)->getNoAck(), 4);
}

TEST( ClientSenderTests, runInThread )
{
    char addr[] = "127.0.0.1";
    sockaddr_in6 servaddr;
    servaddr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, addr, &servaddr.sin6_addr);
    servaddr.sin6_port = htons(TEST_PORT);
    int cliSockfd;
    if ((cliSockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }
    std::mutex m;
    ClientSender sender(cliSockfd, addr, TEST_PORT, m);
    sender.addToQueue(new PacketAck(4, "testUser"));
    
    std::thread thread(sender);
    thread.join();
}

TEST( ClientControllerTests, putSomePackets )
{
    char addr[] = "127.0.0.1";
    sockaddr_in6 servaddr;
    servaddr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, addr, &servaddr.sin6_addr);
    servaddr.sin6_port = htons(TEST_PORT);
    int cliSockfd;
    if ((cliSockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return;
    }
    std::mutex m;
    ClientSender sender(cliSockfd, addr, TEST_PORT, m);
    Model model("testUser");
    Controller controller("resources/moves.txt", &sender, &model);
    controller();
    
    Packet * p = sender.popFromQueue();
    ASSERT_EQ(p->getUser(), "testUser");

}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}