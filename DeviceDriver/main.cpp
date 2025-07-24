#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverFixture : public Test {
public:
	FlashMock flashMock;
	DeviceDriver driver{ &flashMock };
};

TEST_F(DeviceDriverFixture, FiveRead) {
	// TODO : replace hardware with a Test Double

	EXPECT_CALL(flashMock, read((long)0xFF))
		.Times(5);
	
	driver.read((long)0xFF);
}

TEST_F(DeviceDriverFixture, FiveReadWithSameValue) {
	// TODO : replace hardware with a Test Double

	unsigned char expected = 0x1;
	EXPECT_CALL(flashMock, read((long)0xFF))
		.Times(5)
		.WillRepeatedly(Return(expected));

	unsigned char actual = driver.read((long)0xFF);
	EXPECT_EQ(expected, actual);
}

TEST_F(DeviceDriverFixture, FiveReadWithDifferentValue) {
	// TODO : replace hardware with a Test Double

	unsigned char expected1 = 0x1;
	unsigned char expected2 = 0x2;
	unsigned char expected3 = 0x3;
	unsigned char expected4 = 0x4;
	unsigned char expected5 = 0x5;
	EXPECT_CALL(flashMock, read((long)0xFF))
		.Times(AtMost(5))
		.WillOnce(Return(expected1))
		.WillOnce(Return(expected2))
		.WillOnce(Return(expected3))
		.WillOnce(Return(expected4))
		.WillOnce(Return(expected5));

	EXPECT_THROW(driver.read((long)0xFF), ReadFailException);
}

TEST_F(DeviceDriverFixture, ReadBeforeWrite) {
	long address = 0x1;
	unsigned char data = 0x2;
	EXPECT_CALL(flashMock, read(address))
		.Times(1)
		.WillRepeatedly(Return((unsigned char)0xFF));
	driver.write(address, (int)data);
}

TEST_F(DeviceDriverFixture, WriteSuccess) {
	long address = 0x1;
	unsigned char data = 0x2;
	EXPECT_CALL(flashMock, read(address))
		.Times(1)
		.WillRepeatedly(Return((unsigned char)0xFF));
	EXPECT_CALL(flashMock, write(address, data))
		.Times(1);
	driver.write(address, (int)data);
}

TEST_F(DeviceDriverFixture, WriteFail) {
	long address = 0x1;
	unsigned char data = 0x2;
	EXPECT_CALL(flashMock, read(address))
		.Times(1)
		.WillRepeatedly(Return((unsigned char)0x1));
	EXPECT_CALL(flashMock, write(address, data))
		.Times(0);
	EXPECT_THROW(driver.write(address, (int)data), std::exception);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}