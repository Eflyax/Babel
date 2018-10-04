//
// Created by romain on 26/09/18.
//

#ifndef SERVER_BINARYWRITER_H
#define SERVER_BINARYWRITER_H

#include "Network.h"

using buffer_t = std::vector<char>;

class BinaryWriter {
public:
    BinaryWriter();

    buffer_t &bytes();
    void seek(sizet set);
    sizet tell() const;
    void reset();

    void writeUtf(std::string const &);
    void writeFloat(float);
    void writeDouble(double);
    void writeShort(boost::int16_t);
    void writeUshort(boost::uint16_t);
    void writeInt(boost::int32_t);
    void writeUint(boost::uint32_t);
    void writeLong(boost::int64_t);
    void writeUlong(boost::uint64_t);

    template<class T>
    BinaryWriter &operator&(T primitive) {
        writeType<T>(primitive);
        return *this;
    }

private:
    template<class T>
    void writeType(T value) {
        sizet size = sizeof(T);
        _buffer.insert(_buffer.begin() + _position, (char *)&value, (char *)&value + size);
        _position += size;
    }

private:
    buffer_t _buffer;
    sizet _position;
};


#endif //SERVER_BINARYWRITER_H