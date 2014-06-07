#include <phpcpp.h>
#include <bson.h>

void fillBSONWithArray(const std::map<std::string,Php::Value>& value, bson_t* bson);
void variantToBSON(const Php::Value& value, const char* key, bson_t* bson);
void nullToBSON(const char* key, bson_t* bson);
void boolToBSON(const bool value, const char* key, bson_t* bson);
void int64ToBSON(const int64_t value, const char* key, bson_t* bson);
void doubleToBSON(const double value,const char* key, bson_t* bson);
void stringToBSON(const char* value, const char* key, bson_t* bson);
void arrayToBSON(const std::map<std::string,Php::Value>& value, const char* key, bson_t* bson);
bool arrayIsDocument(const std::map<std::string,Php::Value>& value);
