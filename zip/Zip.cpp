#define ZIP_CHUNK 16384

#include "Zip.h"
#include "WriteFile.h"
#include "ReadFile.h"

#include <cstdio>
#include <assert.h>
#include <fcntl.h>

#include "zlib.h"
#include <iostream>

using namespace CSC1310;

Zip::Zip()
{}

Zip::~Zip()
{}

Zip* Zip::getZip()
{
	static Zip zip;
	return &zip;
}

char* Zip::buffer_zip(const char* data_file_name, const char* zip_file_name, int& zip_file_length, char* unzipped_data_buffer, int unzipped_data_buffer_length)
{
	CSC1310::WriteFile::entireFile(data_file_name, unzipped_data_buffer, unzipped_data_buffer_length);
	delete[] unzipped_data_buffer;

	CSC1310::Zip* zip = CSC1310::Zip::getZip();
	zip->zipit(data_file_name, zip_file_name);

	char* zipped_file_c_str = CSC1310::ReadFile::entireFile(zip_file_name, &zip_file_length);
	return zipped_file_c_str;
}

CSC1310::String Zip::buffer_unzip(const char* data_file_name, const char* zip_file_name, char* zipped_data_buffer, int zipped_data_buffer_length)
{
	CSC1310::WriteFile::entireFile(zip_file_name, zipped_data_buffer, zipped_data_buffer_length);
	
	CSC1310::Zip* zip = CSC1310::Zip::getZip();
	zip->unzipit(zip_file_name, data_file_name);
   
	int unzipped_file_length = 0;
	char* unzipped_file_c_str = CSC1310::ReadFile::entireFile(data_file_name, &unzipped_file_length);
	CSC1310::String unzipped_str(unzipped_file_c_str);
	delete[] unzipped_file_c_str;
	return unzipped_str;
}

int Zip::zipit(const char* input_file_name, const char* output_file_name)
{
	FILE* input_file;
   input_file = fopen(input_file_name, "r");
   
   FILE* output_file;
   output_file = fopen(output_file_name, "w");
   
    /* avoid end-of-line conversions */
	setmode(fileno(input_file), O_BINARY);
	setmode(fileno(output_file), O_BINARY);
   
	int level = Z_DEFAULT_COMPRESSION;
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[ZIP_CHUNK];
    unsigned char out[ZIP_CHUNK];

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, level);
    if (ret != Z_OK)
        return ret;

    /* compress until end of file */
    do {
        strm.avail_in = fread(in, 1, ZIP_CHUNK, input_file);
        if (ferror(input_file)) {
            (void)deflateEnd(&strm);
            return Z_ERRNO;
        }
        flush = feof(input_file) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
        do {
            strm.avail_out = ZIP_CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush);    /* no bad return value */
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            have = ZIP_CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, output_file) != have || ferror(output_file)) {
                (void)deflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */

    /* clean up and return */
    (void)deflateEnd(&strm);
	
	fclose(input_file);
	fclose(output_file);
    return Z_OK;
}

int Zip::unzipit(const char* input_file_name, const char* output_file_name)
{
	FILE* input_file;
   input_file = fopen(input_file_name, "r");
   
   FILE* output_file;
   output_file = fopen(output_file_name, "w");
   
    /* avoid end-of-line conversions */
	setmode(fileno(input_file), O_BINARY);
	setmode(fileno(output_file), O_BINARY);
	
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[ZIP_CHUNK];
    unsigned char out[ZIP_CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, ZIP_CHUNK, input_file);
        if (ferror(input_file)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = ZIP_CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = ZIP_CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, output_file) != have || ferror(output_file)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
	
	fclose(input_file);
	fclose(output_file);
	
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}
/*
int main(int argc, char** argv)
{
    int ret;
	CSC1310::Zip* zip = CSC1310::Zip::getZip();
	
	char* input_file_name = argv[1];
	char* zip_file_name = argv[2];
	char* unzip_file_name = argv[3];
	
	//ret = zip->zipit(input_file_name, zip_file_name);
	ret = zip->unzipit(zip_file_name, unzip_file_name);
 
	return ret;
}
*/
