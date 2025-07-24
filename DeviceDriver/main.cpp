#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
    MOCK_METHOD(unsigned char, read, (long address), (override));
    MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriverRead, FiveRead) {
    FlashMock mock;

    EXPECT_CALL(mock, read((long)0xB))
        .Times(5);

    DeviceDriver driver{ &mock };
    int data = driver.read((long)0xB);
}

TEST(DeviceDriverRead, ReadAndException) {
    FlashMock mock;

    EXPECT_CALL(mock, read((long)0xB))
        .WillOnce(Return((unsigned char)0xA))
        .WillOnce(Return((unsigned char)0xA))
        .WillOnce(Return((unsigned char)0xA))
        .WillOnce(Return((unsigned char)0xA))
        .WillOnce(Return((unsigned char)0xB));

    DeviceDriver driver{ &mock };
    EXPECT_THROW(driver.read((long)0xB), std::exception);
}

TEST(DeviceDriverWrite, ReadBeforeWrite) {
    NiceMock<FlashMock> mock;

    EXPECT_CALL(mock, read((long)0xB))
        .Times(1)
        .WillRepeatedly(Return((unsigned char)0xFF));

    DeviceDriver driver{ &mock };
    driver.write((long)0xB, 7);
}
TEST(DeviceDriverWrite, WriteException) {
    NiceMock<FlashMock> mock;

    EXPECT_CALL(mock, read((long)0xB))
        .WillRepeatedly(Return((unsigned char)0xFE));

    DeviceDriver driver{ &mock };
    EXPECT_THROW(driver.write((long)0xB, 7), std::exception);
}


TEST(Application, ReadAndPrint) {
    NiceMock<FlashMock> mock;
    DeviceDriver dd{ &mock };
    Application app{ &dd };

    EXPECT_CALL(mock, read)
        .Times(25);

    //콘솔출력 될것
    app.readAndprint(0x00, 0x04);

    //1. 안한다. 
    //    내부적으로 랩퍼 클래스 반환값 Proxy 출력
    //2. 콘솔 버퍼 옮겼다가 다시 원복 
         //Trivia KATA
    //3. 행동검증
}

TEST(Application, WriteAll) {
    NiceMock<FlashMock> mock;
    DeviceDriver dd{ &mock };
    Application app{ &dd };

    EXPECT_CALL(mock, read)
        .Times(5)
        .WillRepeatedly(Return((unsigned char)0xFF));

    app.writeAll(0x77);
}

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}