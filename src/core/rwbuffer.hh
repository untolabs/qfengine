#ifndef CORE_RWBUFFER_HH
#define CORE_RWBUFFER_HH 1

/**
 * A general-purpose read-write buffer
 * mostly made for packet serialization
 */
class RWBuffer final {
public:
    std::size_t read_position;
    std::vector<std::byte> vector;

public:
    static float read_FP32(RWBuffer &buffer);
    static std::int8_t read_I8(RWBuffer &buffer);
    static std::int16_t read_I16(RWBuffer &buffer);
    static std::int32_t read_I32(RWBuffer &buffer);
    static std::int64_t read_I64(RWBuffer &buffer);
    static std::uint8_t read_UI8(RWBuffer &buffer);
    static std::uint16_t read_UI16(RWBuffer &buffer);
    static std::uint32_t read_UI32(RWBuffer &buffer);
    static std::uint64_t read_UI64(RWBuffer &buffer);
    static std::string read_string(RWBuffer &buffer);
    
public:
    static void write_FP32(RWBuffer &buffer, float value);
    static void write_I8(RWBuffer &buffer, std::int8_t value);
    static void write_I16(RWBuffer &buffer, std::int16_t value);
    static void write_I32(RWBuffer &buffer, std::int32_t value);
    static void write_I64(RWBuffer &buffer, std::int64_t value);
    static void write_UI8(RWBuffer &buffer, std::uint8_t value);
    static void write_UI16(RWBuffer &buffer, std::uint16_t value);
    static void write_UI32(RWBuffer &buffer, std::uint32_t value);
    static void write_UI64(RWBuffer &buffer, std::uint64_t value);
    static void write_string(RWBuffer &buffer, const std::string &value);

public:
    /**
     * Setup a buffer for writing
     * @param buffer The buffer
     */
    static void setup(RWBuffer &buffer);

    /**
     * Setup a buffer for reading
     * @param buffer The buffer
     * @param data The data to read from
     * @param size The data size in bytes
     */
    static void setup(RWBuffer &buffer, const void *data, std::size_t size);
};

#endif /* CORE_RWBUFFER_HH */
