#include <gtest/gtest.h>
#include <server.h>
 
TEST(SquareRootTest, PositiveNos) { 
    Server server = Server(4200);
    server.test();
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}