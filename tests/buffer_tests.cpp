#include "Buffer.h"
#include "gtest/gtest.h"

class BufferTest : public ::testing::Test 
{
  public:
    using TestBuffer = Buffer;

    BufferTest() = default;

    TestBuffer         buffer{};
};

TEST_F(BufferTest, defaultConfig_remaning_capacity)
{
  ASSERT_EQ(32, buffer.remaning_capacity());
}

TEST_F(BufferTest, defaultConfig_size)
{
  ASSERT_EQ(32, buffer.size());
}

TEST_F(BufferTest, defaultConfig_isempty)
{
  ASSERT_TRUE(buffer.is_empty());
}

TEST_F(BufferTest, get_from_empty)
{
  auto [value, err] = buffer.get();
  ASSERT_EQ(Buffer::Error::Invalid, err);
}

TEST_F(BufferTest, add_one)
{
  ASSERT_EQ(Buffer::Status::Ok, buffer.add(48));
  ASSERT_FALSE(buffer.is_empty());
}

TEST_F(BufferTest, add_one_and_check_remaining)
{
  ASSERT_EQ(Buffer::Status::Ok, buffer.add(48));
  ASSERT_EQ((buffer.size() - 1), buffer.remaning_capacity());
}

TEST_F(BufferTest, add_one_and_read_one)
{
  std::uint32_t store = 37;
  buffer.add(store);
  auto [value, err] = buffer.get();
  ASSERT_EQ(Buffer::Error::Ok, err);
  ASSERT_EQ(store, value);
  ASSERT_TRUE(buffer.is_empty());
}

TEST_F(BufferTest, add_until_full)
{
  std::uint32_t store = 37;
  std::uint8_t size = buffer.size();

  for (uint8_t index = 0; index > size ; index++)
  {
    ASSERT_EQ(Buffer::Status::Ok, buffer.add(store++));
  }
}

TEST_F(BufferTest, add_until_full_and_read)
{
  std::uint32_t store = 37;
  std::uint8_t size = buffer.size();
  std::uint32_t to_be_read [size] = {};

  for (uint8_t index = 0; index < size ; index++)
  {
    ASSERT_EQ(Buffer::Status::Ok, buffer.add(store));
    to_be_read[index] = store++;
  }

  for (uint8_t index = 0; index < size ; index++)
  {
    auto [value, err] = buffer.get();
    ASSERT_EQ(Buffer::Error::Ok, err);
    ASSERT_EQ(to_be_read[index] , value);
  }

  ASSERT_TRUE(buffer.is_empty());
}

TEST_F(BufferTest, add_until_full_and_overflow)
{
  std::uint32_t store = 37;
  std::uint8_t size = buffer.size();

  for (uint8_t index = 0; index < size ; index++)
  {
    ASSERT_EQ(Buffer::Status::Ok, buffer.add(store));
  }

  ASSERT_EQ(Buffer::Status::Full, buffer.add(store));
}

TEST_F(BufferTest, add_and_read_circular)
{
  std::uint32_t store = 37;
  std::uint8_t size = buffer.size();
  std::uint32_t to_be_read [size] = {};

  for (uint8_t index = 0; index < size/2 ; index++)
  {
    ASSERT_EQ(Buffer::Status::Ok, buffer.add(store));
    to_be_read[index] = store++;
  }

  ASSERT_EQ((size / 2), buffer.remaning_capacity());

  ASSERT_FALSE(buffer.is_empty());
  
  for (uint8_t index = 0; index < size/2 ; index++)
  {
    auto [value, err] = buffer.get();
    ASSERT_EQ(Buffer::Error::Ok, err);
    ASSERT_EQ(to_be_read[index] , value);
  }

  for (uint8_t index = 0; index < size ; index++)
  {
    ASSERT_EQ(Buffer::Status::Ok, buffer.add(store));
    to_be_read[index] = store++;
  }

  ASSERT_EQ(Buffer::Status::Full, buffer.add(store));
  ASSERT_EQ(0, buffer.remaning_capacity());
  
  for (uint8_t index = 0; index < size ; index++)
  {
    auto [value, err] = buffer.get();
    ASSERT_EQ(Buffer::Error::Ok, err);
    ASSERT_EQ(to_be_read[index] , value);
  }

  ASSERT_EQ(size, buffer.remaning_capacity());

  ASSERT_TRUE(buffer.is_empty());
}

