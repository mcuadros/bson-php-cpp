#include <phpcpp.h>
#include <bson.h>
#include "encode.h"
#include "decode.h"

Php::Value bson_encode(Php::Parameters &params)
{
    Php::Value value = params[0];

    bson_t bson;
    bson_init(&bson);

    fillBSONWithArray(value.mapValue(), &bson);

    std::string output((const char*) bson_get_data(&bson), bson.len);

    return output;
}

Php::Value bson_decode(Php::Parameters &params) {
    Php::Value data = params[0];

    bson_reader_t* reader;
    const bson_t* bson;
    bool reached_eof;
    bson_iter_t iter;

    reader = bson_reader_new_from_data((uint8_t *)data.stringValue().c_str(), data.size());
    bson = bson_reader_read(reader, &reached_eof);

    bson_iter_init(&iter, bson);
    Php::Value output;
    fillValue(&iter, &output, true);
    bson_reader_destroy(reader);

    return output;
}

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("mongo", "1.0");

        extension.add("bson_encode", bson_encode);
        extension.add("bson_decode", bson_decode);

        // return the extension
        return extension;
    }
}
