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

    ON_CALL(mdb, login("Terminator", "asdf")).WillByDefault(Return(1));

    // Act
    int retValue = db.Init("Terminator", "asdf");

    // Assert
    EXPECT_EQ(retValue, 1);
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}