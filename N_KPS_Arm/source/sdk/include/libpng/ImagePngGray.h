
#ifndef _IMAGE_PNG_GRAY_H_
#define _IMAGE_PNG_GRAY_H_

#include <iostream>
#include "Comm/MyDefine.h"
#include "libpng/png.h"

class ImagePngGray
{
public:
	ImagePngGray();
	~ImagePngGray();

public:
	bool imread(std::string file_path);

	//
	bool imwrite(U8     *pImgBuf,
		         S32     img_w,
		         S32     img_h,
		         std::string  file_name);

private:
	void releaseImage();

public:
	U8    *data_;
	S32    width_;
	S32    height_;

private:
	S32    color_type_;
};


#endif//_IMAGE_PNG_GRAY_H_