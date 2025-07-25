#include <qpdf/RC4.hh>

#include <qpdf/QPDFCryptoProvider.hh>

RC4::RC4(unsigned char const* key_data, int key_len) :
    crypto(QPDFCryptoProvider::getImpl())
{
    crypto->RC4_init(key_data, key_len);
}

void
RC4::process(unsigned char const* in_data, size_t len, unsigned char* out_data)
{
    crypto->RC4_process(in_data, len, out_data);
}

void
RC4::process(std::string_view key, std::string& data)
{
    RC4 rc4(reinterpret_cast<unsigned char const*>(key.data()), static_cast<int>(key.size()));
    rc4.process(
        reinterpret_cast<unsigned char const*>(data.data()),
        data.size(),
        reinterpret_cast<unsigned char*>(data.data()));
}
