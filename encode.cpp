#include <phpcpp.h>
#include <bson.h>
#include "encode.h"

void fillBSONWithArray(const std::map<std::string,Php::Value>& value, bson_t* bson) {
  for (auto &iter : value) {
      const char* key = iter.first.c_str();
      variantToBSON(iter.second, key, bson);
  }
}

void variantToBSON(const Php::Value& value, const char* key, bson_t* bson) {
  switch(value.type()) {
    case Php::Type::Null:
      nullToBSON(key, bson);
      break;
    case Php::Type::Bool:
      boolToBSON(value.boolValue(), key, bson);
      break;
    case Php::Type::Numeric:
      int64ToBSON(value.numericValue(), key, bson);
      break;
    case Php::Type::Float:
      doubleToBSON(value.floatValue(), key, bson);
      break;
    case Php::Type::String:
      stringToBSON(value.stringValue().c_str(), key, bson);
      break;
    case Php::Type::Array:
      arrayToBSON(value.mapValue(), key, bson);
      break;
    default:
      printf("missed type: %d\n", value.type());
      break;
  }
}


void nullToBSON(const char* key, bson_t* bson) {
  bson_append_null(bson, key, -1);
}

void boolToBSON(const bool value, const char* key, bson_t* bson) {
  bson_append_bool(bson, key, -1, value);
}

void int64ToBSON(const int64_t value, const char* key, bson_t* bson) {
  bson_append_int64(bson, key, -1, value);
}

void doubleToBSON(const double value,const char* key, bson_t* bson) {
  bson_append_double(bson, key, -1, value);
}

void stringToBSON(const char* value, const char* key, bson_t* bson) {
  bson_append_utf8(bson, key, strlen(key), value, -1);
}

void arrayToBSON(const std::map<std::string,Php::Value>& value, const char* key, bson_t* bson) {
  bson_t child;
  bool isDocument = arrayIsDocument(value);
  if (isDocument) {
    bson_append_document_begin(bson, key, -1, &child);
  } else {
    bson_append_array_begin(bson, key, -1, &child);
  }

  fillBSONWithArray(value, &child);

  if (isDocument) {
    bson_append_document_end(bson, &child);
  } else {
    bson_append_array_end(bson, &child);
  }
}


//////////////////////////////////////////////////////////////////////////////
//* Objects *//
bool arrayIsDocument(const std::map<std::string,Php::Value>& value) {
   for (auto &iter : value) {
      const char* key = iter.first.c_str();
      if (strlen(key) != 0) {
        return true;
      }
  }

  return false;
}
