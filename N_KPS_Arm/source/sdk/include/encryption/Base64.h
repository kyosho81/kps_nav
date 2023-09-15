#ifndef _BASE64_KYOSHO_20230303_H
#define _BASE64_KYOSHO_20230303_H

#include <string>
#include <vector>
#include <stdexcept>


class Base64Encrypt
{
public:
	Base64Encrypt() : _groupLength(0) {}
	Base64Encrypt(const void *input, size_t length) : _groupLength(0)
	{
		Update(input, length);
	}

	void Update(const void *input, size_t length)
	{
		static const size_t LEN = 3;
		_buf.reserve(_buf.size() + (length - (LEN - _groupLength) + LEN - 1) / LEN * 4 + 1);
		const unsigned char *buff = reinterpret_cast<const unsigned char *>(input);
		unsigned int i;

		for (i = 0; i < length; ++i)
		{
			_group[_groupLength++] = buff[i];
			if (_groupLength == LEN)
			{
				Encode();
			}
		}
	}
	const unsigned char *CipherText()
	{
		Final();
		return _buf.data();
	}
	std::string GetString()
	{
		const char *pstr = (const char *)CipherText();
		size_t length = GetSize();
		return std::string(pstr, length);
	}
	void Reset()
	{
		_buf.clear();
		_groupLength = 0;
		for (unsigned int i = 0; i < sizeof(_group) / sizeof(_group[0]); ++i)
		{
			_group[i] = 0;
		}
	}
	size_t GetSize()
	{
		CipherText();
		return _buf.size();
	}

private:
	Base64Encrypt(const Base64Encrypt &);
	Base64Encrypt & operator = (const Base64Encrypt &);

	void Encode()
	{
		unsigned char index;

		// 0 index byte
		index = _group[0] >> 2;
		_buf.push_back(Base64EncodeMap[index]);
		// 1 index byte
		index = ((_group[0] & 0x03) << 4) | (_group[1] >> 4);
		_buf.push_back(Base64EncodeMap[index]);
		// 2 index byte
		index = ((_group[1] & 0x0F) << 2) | (_group[2] >> 6);
		_buf.push_back(Base64EncodeMap[index]);
		// 3 index byte
		index = _group[2] & 0x3F;
		_buf.push_back(Base64EncodeMap[index]);

		_groupLength = 0;
	}
	void Final()
	{
		unsigned char index;

		if (_groupLength == 1)
		{
			_group[1] = 0;
			// 0 index byte
			index = _group[0] >> 2;
			_buf.push_back(Base64EncodeMap[index]);
			// 1 index byte
			index = ((_group[0] & 0x03) << 4) | (_group[1] >> 4);
			_buf.push_back(Base64EncodeMap[index]);
			// 2 index byte
			_buf.push_back('=');
			// 3 index byte
			_buf.push_back('=');
		}
		else if (_groupLength == 2)
		{
			_group[2] = 0;
			// 0 index byte
			index = _group[0] >> 2;
			_buf.push_back(Base64EncodeMap[index]);
			// 1 index byte
			index = ((_group[0] & 0x03) << 4) | (_group[1] >> 4);
			_buf.push_back(Base64EncodeMap[index]);
			// 2 index byte
			index = ((_group[1] & 0x0F) << 2) | (_group[2] >> 6);
			_buf.push_back(Base64EncodeMap[index]);
			// 3 index byte
			_buf.push_back('=');
		}

		_groupLength = 0;
	}

private:
	std::vector<unsigned char> _buf;
	unsigned char _group[3];
	int _groupLength;

	static const unsigned char Base64EncodeMap[64];
};


class Base64Decrypt
{
public:
	Base64Decrypt() : _groupLength(0) {}
	Base64Decrypt(const void *input, size_t length) : _groupLength(0)
	{
		Update(input, length);
	}

	void Update(const void *input, size_t length)
	{
		static const size_t LEN = 4;
		_buf.reserve(_buf.size() + (length + (LEN - _groupLength) + LEN - 1) / LEN * 3 + 1);
		const unsigned char *buff = reinterpret_cast<const unsigned char *>(input);
		unsigned int i;

		for (i = 0; i < length; ++i)
		{
			if (Base64DecodeMap[buff[i]] == 0xFF)
			{
				throw std::invalid_argument("ciphertext is illegal");
			}

			_group[_groupLength++] = buff[i];
			if (_groupLength == LEN)
			{
				Decode();
			}
		}
	}

	const unsigned char *PlainText()
	{
		if (_groupLength)
		{
			throw std::invalid_argument("ciphertext's length must be a multiple of 4");
		}
		return _buf.data();
	}

	std::string GetString()
	{
		const char *pstr = (const char *)PlainText();
		size_t length = GetSize();
		return std::string(pstr, length);
	}
	void Reset()
	{
		_buf.clear();
		_groupLength = 0;
		for (unsigned int i = 0; i < sizeof(_group) / sizeof(_group[0]); ++i)
		{
			_group[i] = 0;
		}
	}
	size_t GetSize()
	{
		PlainText();
		return _buf.size();
	}

private:
	Base64Decrypt(const Base64Decrypt &);
	Base64Decrypt & operator = (const Base64Decrypt &);

	void Decode()
	{
		unsigned char buff[3];
		unsigned int top = 1;
		if (_group[0] == '=' || _group[1] == '=')
		{
			throw std::invalid_argument("ciphertext is illegal");
		}

		buff[0] = (Base64DecodeMap[_group[0]] << 2) | (Base64DecodeMap[_group[1]] >> 4);
		if (_group[2] != '=')
		{
			buff[1] = ((Base64DecodeMap[_group[1]] & 0x0F) << 4) | (Base64DecodeMap[_group[2]] >> 2);
			top = 2;
		}
		if (_group[3] != '=')
		{
			buff[2] = (Base64DecodeMap[_group[2]] << 6) | Base64DecodeMap[_group[3]];
			top = 3;
		}

		for (unsigned int i = 0; i < top; ++i)
		{
			_buf.push_back(buff[i]);
		}

		_groupLength = 0;
	}

private:
	std::vector<unsigned char> _buf;
	unsigned char _group[4];
	int _groupLength;

	static unsigned char Base64DecodeMap[256];
};
#endif //_BASE64_KYOSHO_20230303_H

