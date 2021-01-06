#include "Buffer.h"

bool Buffer::is_empty()
{
  return (num_items == 0);
}

std::uint8_t  Buffer::size()
{
  return sz;
}

std::uint8_t Buffer::remaning_capacity()
{
  return (sz - num_items);
}

std::pair<std::uint32_t, Buffer::Error> Buffer::get()
{
    if (num_items)
    {
        std::uint32_t value = buffer[read];

        --num_items;
        ++read;

        if (read == sz) 
        {
            read = 0;
        }

        return {value, Error::Ok};
    }
    else
    {
        return {0, Error::Invalid};
    }
}

Buffer::Status Buffer::add(std::uint32_t value)
{
    if (num_items == sz) 
    {
        return Status::Full;
    }
    {
        buffer[write] = value;

        ++num_items;
        ++write;

        if (write == sz) 
        {
            write = 0;
        }

        return Status::Ok;
    }
}
