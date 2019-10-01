#pragma once
#include "cjson/cJSON.h"
#include "typeindex"
#include "string"
#include "map"
#include "vector"

struct template_null {};

namespace SerializeBase {
	const std::type_index type_chars = std::type_index(typeid(char*));

	static int serialize(const char* key, std::string& data, cJSON* json) {
		cJSON_AddStringToObject(json, key, data.c_str());

		return 0;
	}

	static int unserialize(std::string& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_String)
		{
			data = obj->valuestring;
		}

		return 0;
	}

	static int serialize(const char* key, char& data, cJSON* json) {
		cJSON_AddNumberToObject(json, key, data);
		return 0;
	}

	static int unserialize(char& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_Number)
		{
			data = obj->valueint;
		}
		return 0;
	}

	static int serialize(const char* key, unsigned char& data, cJSON* json) {
		cJSON_AddNumberToObject(json, key, data);
		return 0;
	}

	static int unserialize(unsigned char& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_Number)
		{
			data = obj->valueint;
		}
		return 0;
	}

	static int serialize(const char* key, short& data, cJSON* json) {
		cJSON_AddNumberToObject(json, key, data);
		return 0;
	}

	static int unserialize(short& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_Number)
		{
			data = obj->valueint;
		}
		return 0;
	}

	static int serialize(const char* key, unsigned short& data, cJSON* json) {
		cJSON_AddNumberToObject(json, key, data);
		return 0;
	}

	static int unserialize(unsigned short& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_Number)
		{
			data = obj->valueint;
		}
		return 0;
	}

	static int serialize(const char* key, int& data, cJSON* json) {
		cJSON_AddNumberToObject(json, key, data);
		return 0;
	}

	static int unserialize(int& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_Number)
		{
			data = obj->valueint;
		}
		return 0;
	}

	static int serialize(const char* key, unsigned int& data, cJSON* json) {
		cJSON_AddNumberToObject(json, key, data);
		return 0;
	}

	static int unserialize(unsigned int& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_Number)
		{
			data = obj->valueint;
		}
		return 0;
	}

	static int serialize(const char* key, long long& data, cJSON* json) {
		cJSON_AddNumberToObject(json, key, data);
		return 0;
	}

	static int unserialize(long long& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_Number)
		{
			data = obj->valueint;
		}
		return 0;
	}

	static int serialize(const char* key, unsigned long long& data, cJSON* json) {
		cJSON_AddNumberToObject(json, key, data);
		return 0;
	}

	static int unserialize(unsigned long long& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_Number)
		{
			data = obj->valueint;
		}
		return 0;
	}

	static int serialize(const char* key, float& data, cJSON* json) {
		cJSON_AddNumberToObject(json, key, data);
		return 0;
	}

	static int unserialize(float& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_Number)
		{
			data = obj->valuedouble;
		}
		return 0;
	}

	static int serialize(const char* key, double& data, cJSON* json) {
		cJSON_AddNumberToObject(json, key, data);
		return 0;
	}

	static int unserialize(const char* key, double& data, cJSON* obj) {
		if (obj&& obj->type == cJSON_Number)
		{
			data = obj->valuedouble;
		}
		return 0;
	}

	template<typename T>
	static int serialize(const char* key, std::vector<T>& data, cJSON* json) {
		cJSON* array = cJSON_CreateArray();
		for (auto& iter : data)
		{
			serialize("", iter, array);
		}
		cJSON_AddItemToObject(json, key, array);
		return 0;
	}

	template<typename T>
	static int unserialize(const char* key, std::vector<T>& data, cJSON* json) {
		data.clear();
		cJSON *jsonTmp = cJSON_GetObjectItem(json, key);
		if (jsonTmp&& jsonTmp->type == cJSON_Array)
		{
			int size = cJSON_GetArraySize(jsonTmp);
			for (int i = 0; i < size; i++)
			{
				cJSON* tmp = cJSON_GetArrayItem(jsonTmp, i);
				T t;
				unserialize(t, tmp);
				data.push_back(t);
			}
		}

		return 0;
	}

	template<typename T>
	static int serialize(const char* key, std::map<std::string, T>& data, cJSON* json) {
		cJSON* map = cJSON_CreateObject();
		for (auto& iter : data)
		{
			serialize(iter.first.c_str(), iter.second, map);
		}
		cJSON_AddItemToObject(json, key, map);
		return 0;
	}

	template<typename T>
	static int unserialize(const char* key, std::map<std::string, T>& data, cJSON* json) {
		data.clear();
		cJSON *jsonTmp = cJSON_GetObjectItem(json, key);
		if (jsonTmp&& jsonTmp->type == cJSON_Object)
		{
			int size = cJSON_GetArraySize(jsonTmp);
			for (int i = 0; i < size; i++)
			{
				cJSON* tmp = cJSON_GetArrayItem(jsonTmp, i);
				T t;
				unserialize(t, tmp);
				data.insert(std::make_pair(tmp->string, t));
			}
		}
		return 0;
	}

	template<typename T>
	static int serializeEx(const char* key, T& type, const char* data, cJSON* json) {
		std::type_index t = std::type_index(typeid(T));
		if (t == type_chars)
		{
			cJSON_AddStringToObject(json, key, data);
		}
		else
		{
			std::string tmp;
			int data_len = sizeof(type);
			tmp.assign(data, data_len);

			cJSON_AddStringToObject(json, key, tmp.c_str());
		}
		return 0;
	}

	template<typename T>
	static int unserializeEx(T& type, const char* data, cJSON* obj) {
		std::type_index t = std::type_index(typeid(T));
		if (t == type_chars)
		{
			//char* 不可以赋值
		}
		else
		{
			memset((void*)data, 0, sizeof(type));
			if (obj&& obj->type == cJSON_String)
			{
				int len = std::min(sizeof(type), strlen(obj->valuestring));
				memcpy((void*)data, obj->valuestring, len);
			}
		}
		return 0;
	}

	template<typename T>
	static int serializeEx(const char* key, T& type, T t1, cJSON* json) {
		std::type_index t = std::type_index(typeid(T));

		//未知结构
		return 0;
	}

	template<typename T>
	static int unserializeEx(T& type, T t1, cJSON* json) {
		std::type_index t = std::type_index(typeid(T));

		//未知结构
		return 0;
	}

	template<typename T>
	static int serialize(const char* key, T& data, cJSON* json) {


		return serializeEx(key, data, data, json);
	}

	template<typename T>
	static int unserialize(T& data, cJSON* json) {

		return unserializeEx(data, data, json);
	}

	template<typename T>
	static int unserialize(const char* key, T& data, cJSON* json) {
		cJSON *jsonTmp = cJSON_GetObjectItem(json, key);
		if (jsonTmp)
		{
			return unserialize(data, jsonTmp);
		}
		return 0;
	}
};

#define SERIALIZE_CONCAT(x, y) 		SERIALIZE_CONCAT_I(x, y)
#define SERIALIZE_CONCAT_I(x, y) 		x ## y

#define SERIALIZE_ARGS(...) __VA_ARGS__

# define SERIALIZE_ARGS_NUM_CONV( \
    _0,  _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8, \
   N, ...) N

#define SERIALIZE_ARGS_NUM(...) \
    SERIALIZE_ARGS(SERIALIZE_ARGS_NUM_CONV(__VA_ARGS__, \
	 9,  8,  7,  6,  5,  4,  3,  2,  1,  0))

#define SERIALIZE_FN1() 
#define SERIALIZE_FN2(sType, sName, sArray, ...) SerializeBase::serialize(#sName, data->sName, json);
#define SERIALIZE_FN3 SERIALIZE_FN2
#define SERIALIZE_UNFN1() 
#define SERIALIZE_UNFN2(sType, sName, sArray, ...) SerializeBase::unserialize(#sName, data->sName, json);
#define SERIALIZE_UNFN3 SERIALIZE_UNFN2

#define SERIALIZE_CLASS_PARENT_SERIALIZE_FN1(...) 
#define SERIALIZE_CLASS_PARENT_SERIALIZE_FN2(N,P1) \
	P1::Serialize::serialize(dynamic_cast<P1*>(data),json);
#define SERIALIZE_CLASS_PARENT_SERIALIZE_FN3(N,P1,P2) \
	P1::Serialize::serialize(dynamic_cast<P1*>(data),json); \
	P2::Serialize::serialize(dynamic_cast<P2*>(data), json);

#define SERIALIZE_CLASS_PARENT_UNSERIALIZE_FN1(...) 
#define SERIALIZE_CLASS_PARENT_UNSERIALIZE_FN2(N,P1) \
	P1::Serialize::unserialize(dynamic_cast<P1*>(data),json);
#define SERIALIZE_CLASS_PARENT_UNSERIALIZE_FN3(N,P1,P2) \
	P1::Serialize::unserialize(dynamic_cast<P1*>(data),json); \
	P2::Serialize::unserialize(dynamic_cast<P2*>(data), json);

#define SERIALIZE_DEFINE_PARENT_FN_IMPL_(FN,N, ...) \
		SERIALIZE_ARGS(SERIALIZE_CONCAT(FN, N)__VA_ARGS__)

#define SERIALIZE_DEFINE_PARENT_FN_IMPL(FN,...) \
	SERIALIZE_DEFINE_PARENT_FN_IMPL_(FN,SERIALIZE_ARGS_NUM __VA_ARGS__,__VA_ARGS__)

#define SERIALIZE_CLASS_BEGIN(name,parent,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,...) \
class Serialize { \
public: \
static int serialize(name* data, cJSON* json) { \
		SERIALIZE_DEFINE_PARENT_FN_IMPL(SERIALIZE_CLASS_PARENT_SERIALIZE_FN,parent) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_FN,P1) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_FN,P2) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_FN,P3) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_FN,P4) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_FN,P5) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_FN,P6) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_FN,P7) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_FN,P8) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_FN,P9) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_FN,P10) \
		return 0; \
	} \
	static int unserialize(name* data, cJSON* json) { \
		SERIALIZE_DEFINE_PARENT_FN_IMPL(SERIALIZE_CLASS_PARENT_UNSERIALIZE_FN,parent) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_UNFN,P1) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_UNFN,P2) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_UNFN,P3) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_UNFN,P4) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_UNFN,P5) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_UNFN,P6) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_UNFN,P7) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_UNFN,P8) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_UNFN,P9) \
		SERIALIZE_DEFINE_GENERIC_STRUCT(SERIALIZE_UNFN,P10) \
		return 0; \
	} \
	static int serialize(name* data, std::string& out) { \
		int ret = -1; \
		cJSON* json = cJSON_CreateObject(); \
		if (json) { \
			ret = serialize(data, json); \
			char* buffer = cJSON_PrintUnformatted(json); \
			if (buffer) \
			{ \
				out.assign(buffer, strlen(buffer)); \
				free(buffer); \
			} \
			cJSON_Delete(json); \
		} \
		return ret; \
	} \
	static int unserialize(name* data, std::string& in) { \
		int ret = -1; \
		cJSON* json = cJSON_Parse(in.c_str()); \
		if (json) { \
			ret = unserialize(data, json); \
			cJSON_Delete(json); \
		} \
		return ret; \
	} \
};

#define SERIALIZE_DEFINE_STRUCT_IMPL(FN,N, ...) \
		SERIALIZE_ARGS(SERIALIZE_CONCAT(FN, N)__VA_ARGS__)

#define SERIALIZE_DEFINE_GENERIC_STRUCT(FN,...) \
	SERIALIZE_DEFINE_STRUCT_IMPL(FN,SERIALIZE_ARGS_NUM __VA_ARGS__,__VA_ARGS__)

#define SERIALIZE_DEFINE_FIELD(sType, sName, sArray, ...) sType sName sArray;

#define SERIALIZE_DEFINE_PARENT_IMPL_(FN,N, ...) \
		SERIALIZE_ARGS(SERIALIZE_CONCAT(FN, N)(__VA_ARGS__))

#define SERIALIZE_DEFINE_PARENT_IMPL(FN,...) \
	SERIALIZE_DEFINE_PARENT_IMPL_(FN,SERIALIZE_ARGS_NUM __VA_ARGS__,__VA_ARGS__)

#define SERIALIZE_DEFINE_PARENT_0(N,...) ,__VA_ARGS__
#define SERIALIZE_DEFINE_PARENT_1(...) 
#define SERIALIZE_DEFINE_PARENT_2(...) SERIALIZE_DEFINE_PARENT_0 __VA_ARGS__
#define SERIALIZE_DEFINE_PARENT_3(...) SERIALIZE_DEFINE_PARENT_0 __VA_ARGS__

#define SERIALIZE_DEFINE_PARENT(...) \

# define SERIALIZE_STRUCT_TEMPLATE( name,parent,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,... ) \
struct name : public template_null SERIALIZE_DEFINE_PARENT_IMPL(SERIALIZE_DEFINE_PARENT_,parent)\
{ \
public: \
	SERIALIZE_DEFINE_FIELD P1 \
	SERIALIZE_DEFINE_FIELD P2 \
	SERIALIZE_DEFINE_FIELD P3 \
	SERIALIZE_DEFINE_FIELD P4 \
	SERIALIZE_DEFINE_FIELD P5 \
	SERIALIZE_DEFINE_FIELD P6 \
	SERIALIZE_DEFINE_FIELD P7 \
	SERIALIZE_DEFINE_FIELD P8 \
	SERIALIZE_DEFINE_FIELD P9 \
	SERIALIZE_DEFINE_FIELD P10 \
public: \
	SERIALIZE_CLASS_BEGIN(name,parent,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,__VA_ARGS__) \
	int serialize(std::string& out) {return Serialize::serialize(this, out);} \
	int unserialize(std::string& json) {return Serialize::unserialize(this, json);} \
};

#define SERIALIZE_STRUCT(...) \
	SERIALIZE_ARGS(SERIALIZE_STRUCT_TEMPLATE(__VA_ARGS__,(),(),(),(),(),(),(),(),(),())) \

