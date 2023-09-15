#ifndef _BMD5_KYOSHO_20110903_
#define _BMD5_KYOSHO_20110903_

#include <iostream>
#include <fstream>
#include <memory>
#include <stdio.h>
#include <boost/noncopyable.hpp>

class CMD5 : boost::noncopyable
{
private:
	
  typedef unsigned char *POINTER;	// POINTER defines a generic pointer type
	typedef unsigned short UINT2;	// UINT2 defines a two byte word
	typedef unsigned long  UINT4;	// UINT4 defines a four byte word
	
  // Constants for MD5Transform routine.
	enum { S11 = 7, S12 = 12, S13 = 17, S14 = 22, S21 = 5, S22 =  9, S23 = 14, S24 = 20,
		   S31 = 4, SS32 = 11, S33 = 16, S34 = 23, S41 = 6, S42 = 10, S43 = 15, S44 = 21};
	struct CMD5_CTX
	{
		UINT4 state[4];				// state (ABCD)
		UINT4 count[2];				// number of bits, modulo 2^64 (lsb first)
		unsigned char buffer[64];	// input buffer
	} m_Context;					// md5 context
	
  unsigned char m_Digest[16];		// MD5 value
	const size_t m_nBufferSize;		// buffer size for input file
	
private:
	// Rotate x left to n bits
	UINT4 ROTATE_LEFT(UINT4 x, UINT4 n) const { return ((x << n) | (x >> (32 - n))); }
	// F, G, H and I are basic MD5 functions.
	UINT4 F(UINT4 x, UINT4 y, UINT4 z) const { return ((x & y) | (~x & z)); }
	UINT4 G(UINT4 x, UINT4 y, UINT4 z) const { return ((x & z) | (y & ~z)); }
	UINT4 H(UINT4 x, UINT4 y, UINT4 z) const { return (x ^ y ^ z); }
	UINT4 I(UINT4 x, UINT4 y, UINT4 z) const { return (y ^ (x | ~z)); }
	typedef UINT4 (CMD5::*pfBasicMd5)(UINT4, UINT4, UINT4) const;
	
  // transformations for rounds 1, 2, 3, and 4.
	// Rotation is separate from addition to prevent recomputation.
	void Func(pfBasicMd5 f, UINT4 &a, UINT4 b, UINT4 c, UINT4 d, UINT4 x, UINT4 s, UINT4 ac) const
	{
		a += (this->*f)(b, c, d) + x + ac; 
		a = ROTATE_LEFT(a, s) + b;
	}
private:
	// MD5 basic transformation. Transforms state based on block.
	void MD5Transform(UINT4 state[4], const unsigned char block[64]) const
	{
		UINT4 a = state[0];
		UINT4 b = state[1];
		UINT4 c = state[2];
		UINT4 d = state[3];
		UINT4 x[16] = {0};
		Decode(x, block, 64);
		/* Round 1 */
		Func(&CMD5::F, a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
		Func(&CMD5::F, d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
		Func(&CMD5::F, c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
		Func(&CMD5::F, b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
		Func(&CMD5::F, a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
		Func(&CMD5::F, d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
		Func(&CMD5::F, c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
		Func(&CMD5::F, b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
		Func(&CMD5::F, a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
		Func(&CMD5::F, d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
		Func(&CMD5::F, c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
		Func(&CMD5::F, b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
		Func(&CMD5::F, a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
		Func(&CMD5::F, d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
		Func(&CMD5::F, c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
		Func(&CMD5::F, b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
		/* Round 2 */
		Func(&CMD5::G, a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
		Func(&CMD5::G, d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
		Func(&CMD5::G, c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
		Func(&CMD5::G, b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
		Func(&CMD5::G, a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
		Func(&CMD5::G, d, a, b, c, x[10], S22,  0x2441453); /* 22 */
		Func(&CMD5::G, c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
		Func(&CMD5::G, b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
		Func(&CMD5::G, a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
		Func(&CMD5::G, d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
		Func(&CMD5::G, c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
		Func(&CMD5::G, b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
		Func(&CMD5::G, a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
		Func(&CMD5::G, d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
		Func(&CMD5::G, c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
		Func(&CMD5::G, b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
		/* Round 3 */
		Func(&CMD5::H, a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
		Func(&CMD5::H, d, a, b, c, x[ 8], SS32, 0x8771f681); /* 34 */
		Func(&CMD5::H, c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
		Func(&CMD5::H, b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
		Func(&CMD5::H, a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
		Func(&CMD5::H, d, a, b, c, x[ 4], SS32, 0x4bdecfa9); /* 38 */
		Func(&CMD5::H, c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
		Func(&CMD5::H, b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
		Func(&CMD5::H, a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
		Func(&CMD5::H, d, a, b, c, x[ 0], SS32, 0xeaa127fa); /* 42 */
		Func(&CMD5::H, c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
		Func(&CMD5::H, b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
		Func(&CMD5::H, a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
		Func(&CMD5::H, d, a, b, c, x[12], SS32, 0xe6db99e5); /* 46 */
		Func(&CMD5::H, c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
		Func(&CMD5::H, b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */
		/* Round 4 */
		Func(&CMD5::I, a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
		Func(&CMD5::I, d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
		Func(&CMD5::I, c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
		Func(&CMD5::I, b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
		Func(&CMD5::I, a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
		Func(&CMD5::I, d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
		Func(&CMD5::I, c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
		Func(&CMD5::I, b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
		Func(&CMD5::I, a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
		Func(&CMD5::I, d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
		Func(&CMD5::I, c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
		Func(&CMD5::I, b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
		Func(&CMD5::I, a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
		Func(&CMD5::I, d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
		Func(&CMD5::I, c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
		Func(&CMD5::I, b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */
		state[0] += a;
		state[1] += b;
		state[2] += c;
		state[3] += d;
		// Zeroize sensitive information
		memset((POINTER)x, 0, sizeof(x));
	}
	// Encodes input (UINT4) into output (unsigned char). Assumes len is a multiple of 4
	void Encode(unsigned char *output, const UINT4 *input, size_t len) const
	{
		for (size_t i = 0, j = 0; j < len; i++, j += 4)
		{
			output[j + 0] = (unsigned char)((input[i] >>  0) & 0xff);
			output[j + 1] = (unsigned char)((input[i] >>  8) & 0xff);
			output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
			output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
		}
	}
	// Decodes input (unsigned char) into output (UINT4). Assumes len is a multiple of 4
	void Decode(UINT4 *output, const unsigned char * input, size_t len) const
	{
		for (size_t i = 0, j = 0; j < len; i++, j += 4)
		{
			output[i] = (((UINT4)input[j+0]) <<  0)
					  | (((UINT4)input[j+1]) <<  8)
					  | (((UINT4)input[j+2]) << 16)
					  | (((UINT4)input[j+3]) << 24);
		}
	}
private:
	// MD5 initialization. Begins an MD5 operation, writing a new m_Context.
	void MD5Init()
	{
		memset(&m_Digest,  0, sizeof(m_Digest));
		memset(&m_Context, 0, sizeof(m_Context));
		m_Context.count[0] = 0;
		m_Context.count[1] = 0;
		m_Context.state[0] = 0x67452301;
		m_Context.state[1] = 0xefcdab89;
		m_Context.state[2] = 0x98badcfe;
		m_Context.state[3] = 0x10325476;
	}
	// MD5 block update operation. Continues an MD5 message-digest operation, 
	// processing another message block, and updating the m_Context.
	void MD5Update (const unsigned char *input, unsigned int inputLen)
	{
		// Compute number of bytes mod 64
		unsigned int index = (unsigned int)((m_Context.count[0] >> 3) & 0x3F);
		const unsigned int partLen = 64 - index;
		// Update number of bits
		if ((m_Context.count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
		{
			m_Context.count[1]++;
		}
		m_Context.count[1] += ((UINT4)inputLen >> 29);
		// Transform as many times as possible.
		unsigned int i = 0;
		if (inputLen >= partLen)
		{
			memcpy(&m_Context.buffer[index], input, partLen);
			MD5Transform(m_Context.state, m_Context.buffer);
			for (i = partLen; i + 63 < inputLen; i += 64)
			{
				MD5Transform(m_Context.state, &input[i]);
			}
			index = 0;
		}
		// Buffer remaining input
		memcpy((POINTER)&m_Context.buffer[index], (POINTER)&input[i], inputLen-i);
	}
	// MD5 finalization. Ends an MD5 message-digest operation, writing the
	// the message digest and zeroizing the m_Context.
	void MD5Final()
	{
		unsigned char bits[8] = {0};
		// Save number of bits
		Encode(bits, m_Context.count, 8);
		// Pad out to 56 mod 64. */
		const unsigned int index  = (unsigned int)((m_Context.count[0] >> 3) & 0x3f);
		const unsigned int padLen = (index < 56) ? (56 - index) : (120 - index);
		const unsigned char padding[64] = {0x80, 0};
		MD5Update(padding, padLen);
		MD5Update(bits, 8);							// Append length (before padding)
		Encode(m_Digest, m_Context.state, 16);		// Store state in digest
		memset(&m_Context, 0, sizeof(m_Context));	// Zeroize sensitive information.
	}
public:
	CMD5(size_t nBufferSize = BUFSIZ) : m_nBufferSize(std::max<size_t>(BUFSIZ, nBufferSize))
	{
		MD5Init();
	}
	// Digests a file and return the result.
	std::string MD5File(const char *filename)
	{
		unsigned char buffer[BUFSIZ] = {0};
		MD5Init();
		for (std::ifstream ifs(filename, std::ios_base::binary); ifs; NULL)
		{
			ifs.read((char*)buffer, BUFSIZ);
			MD5Update(buffer, ifs.gcount());
		}
		MD5Final();
		return MD5Hex();
	}
	// Digests a string and return the result.
	std::string MD5String(const char *string)
	{
		MD5Init();
		MD5Update((const unsigned char *)string, strlen(string));
		MD5Final();
		return MD5Hex();
	}
	// Digests a buffer and return the result.
	std::string MD5Binary(const void *buffer, size_t byteLen)
	{
		MD5Init();
		MD5Update((const unsigned char *)buffer, byteLen);
		MD5Final();
		return MD5Hex();
	}
	// Format a message digest in hexadecimal.
	std::string MD5Hex() const
	{
		char buffer[16 * 2 + 1] = {0};
		for (unsigned int i = 0; i < 16; i++)
		{
			#ifdef _WINDOWS
			sprintf_s(buffer + i * 2, 3, "%02x", m_Digest[i]);
			#else
			snprintf( buffer + i * 2, 3, "%02x", m_Digest[i]);
			#endif
		}
		return buffer;
	}
};
#endif//_BMD5_KYOSHO_20110903_
