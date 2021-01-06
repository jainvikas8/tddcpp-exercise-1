#ifndef BUFFER_H

    #define BUFFER_H

    #include <array>
    #include <optional>

    class Buffer 
    {
        public:
            enum class Status
            { 
                Ok,
                Full,
            };
            enum class Error
            { 
                Ok,
                Invalid,
            };

            Buffer()  = default;
            ~Buffer() = default;

            Status  add(uint32_t value);
            std::pair<std::uint32_t, Error> get();
            bool    is_empty();
            std::uint8_t    size();
            std::uint8_t    remaning_capacity();

        private:
            static constexpr std::uint8_t sz = 32;
            std::uint32_t   read{};
            std::uint32_t   write{};
            std::uint8_t    num_items{};

            std::array<std::uint32_t, sz> buffer{};
    };

#endif // BUFFER_H