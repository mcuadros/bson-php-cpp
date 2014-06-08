#include <phpcpp.h>
#include <bson.h>

Php::Value fillValue(bson_iter_t* iter, Php::Value* value, bool isDocument);
Php::Value bsonToValue(bson_iter_t* iter);
Php::Value bsonToArray(bson_iter_t* iter, bool isDocument);
Php::Value bsonToString(bson_iter_t* iter);
Php::Value bsonToInt32(bson_iter_t* iter);
Php::Value bsonToInt64(bson_iter_t* iter);
Php::Value bsonToBool(bson_iter_t* iter);
Php::Value bsonToNull(bson_iter_t* iter);
Php::Value bsonToDouble(bson_iter_t* iter);

//////////////////////////////////////////////////////////////////////////////
//* Objects *//
/*
static ObjectData* instanceNewObject(const StaticString* className, Array params) {
  TypedValue ret;
  Class* cls = Unit::loadClass(className->get());
  ObjectData* obj = ObjectData::newInstance(cls);
  obj->incRefCount();
  
  g_context->invokeFunc(
    &ret, 
    cls->getCtor(), 
    params,
    obj
  );

  return obj;
}

static void bsonToObject(
  bson_iter_t* iter, Array* output, 
  const StaticString* className, Array params
) {
  output->add(
    String(bson_iter_key(iter)),
    instanceNewObject(className, params)
  );
}

void bsonToMongoId(bson_iter_t* iter, Array* output) {
  const bson_oid_t* oid = bson_iter_oid(iter);
  char id[25];

  bson_oid_to_string(oid, id);
  bsonToObject(iter, output, 
    &s_MongoId, 
    make_packed_array(String(id))
  );
}

void bsonToMongoDate(bson_iter_t* iter, Array* output) {
  int64_t ts = bson_iter_date_time(iter);

  bsonToObject(iter, output,
    &s_MongoDate,
    make_packed_array(ts / 1000, (ts % 1000) * 1000)
  );
}

void bsonToMongoRegexp(bson_iter_t* iter, Array* output) {
  const char* options;
  const char* expresion = bson_iter_regex(iter, &options);

  String regex = "/" + String(expresion) +  "/" + String(options);

  bsonToObject(iter, output,
    &s_MongoRegex,
    make_packed_array(regex)
  );
}

void bsonToMongoTimestamp(bson_iter_t* iter, Array* output) {
  uint32_t timestamp;
  uint32_t increment;

  bson_iter_timestamp(iter, &timestamp, &increment);
  bsonToObject(iter, output,
    &s_MongoTimestamp,
    make_packed_array((int64_t)timestamp, (int64_t)increment)
  );
}

void bsonToMongoCode(bson_iter_t* iter, Array* output) {
  uint32_t length;
  const char* code = bson_iter_code(iter, &length);

  bsonToObject(iter, output,
    &s_MongoCode,
    make_packed_array(String(code, length, CopyString))
  );
}

void bsonToMongoCodeWithScope(bson_iter_t* iter, Array* output) {
  uint32_t length;
  uint32_t scope_len;
  const uint8_t* scope;
  const char* code = bson_iter_codewscope(iter, &length, &scope_len, &scope);

  bson_t bson;
  bson_init_static(&bson, scope, scope_len);

  Array scopeArray = Array();
  bsonToVariant(&bson, &scopeArray);

  bsonToObject(iter, output,
    &s_MongoCode,
    make_packed_array(String(code, length, CopyString), scopeArray)
  );
}

void bsonToMongoBinData(bson_iter_t* iter, Array* output) {
  bson_subtype_t subtype;
  uint32_t binary_len;
  const uint8_t* binary;

  bson_iter_binary(iter, &subtype, &binary_len, &binary);
  
  bsonToObject(iter, output,
    &s_MongoBinData,
    make_packed_array(String((const char*)binary, binary_len, CopyString), (int) subtype)
  );
}

void bsonToMongoMaxKey(bson_iter_t* iter, Array* output) {
  bsonToObject(iter, output, &s_MongoMaxKey, Array());
}

void bsonToMongoMinKey(bson_iter_t* iter, Array* output) {
  bsonToObject(iter, output, &s_MongoMinKey, Array());

}
*/
