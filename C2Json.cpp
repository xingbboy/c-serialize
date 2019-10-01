// test.cpp : 定义控制台应用程序的入口点。


#include "pch.h"
#include <iostream>
#include "serialize.h"
#include <algorithm>

struct name : public template_null
{
public:
	int v;
	char v1[12];
	/*std::string dce;
	std::vector<int> vv;
	std::map<std::string, std::string> vvv;*/

	class Serialize {
	public:
		static int serialize(name* data, std::string& out) {
			int ret = -1;
			cJSON* root = cJSON_CreateObject();
			if (root) {
				ret = serialize(data, root);
				char* buffer = cJSON_PrintUnformatted(root);
				if (buffer)
				{
					out.assign(buffer, strlen(buffer));
					free(buffer);
				}
				cJSON_Delete(root);
			}
			return ret;
		}

		static int unserialize(name* data, std::string& json) {
			int ret = -1;
			cJSON* root = cJSON_Parse(json.c_str());
			if (root) {
				ret = unserialize(data, root);
				cJSON_Delete(root);
			}
			return ret;
		}

		static int serialize(name* data, cJSON* root) {
			SerializeBase::serialize("v", data->v, root);
			SerializeBase::serialize("v1", data->v1, root);
			/*SerializeBase::serialize("dce", data->dce, root);
			SerializeBase::serialize("vv", data->vv, root);
			SerializeBase::serialize("vvv", data->vvv, root);*/
			return 0;
		}

		static int unserialize(name* data, cJSON* root) {
			SerializeBase::unserialize("v", data->v, root);
			SerializeBase::unserialize("v1", data->v1, root);
			/*SerializeBase::unserialize("dce", data->dce, root);
			SerializeBase::unserialize("vv", data->vv, root);
			SerializeBase::unserialize("vvv", data->vvv, root);*/
			return 0;
		}
	};

	int serialize(std::string& out) {
		return Serialize::serialize(this, out);
	}

	int unserialize(std::string& json) {
		return Serialize::unserialize(this, json);
	}
};

//模板定义
//SERIALIZE_STRUCT(
//	结构名
//  ,(public,父类, 父类, 父类...)    //这里需要注意:public 为补位,不起任何作用,因为vs没找到方法计算一个参数个数
// ,(变量类型,变量名)
// ,(变量类型,变量名)
//    ...
// )
SERIALIZE_STRUCT(
	name1
	,()
	, (int, v)
	, (char, v1, [12])
)

//这里需要注意:public 为补位,不起任何作用,因为vs没找到方法计算一个参数个数
SERIALIZE_STRUCT(
	name2
	, ()
	, (int, v2)
	, (char, v3, [12])
)

SERIALIZE_STRUCT(
	name3
	, (public, name1, name2)
	, (int, v4)
	, (char, v5, [12])
)

int main()
{
	//序列化
	std::string tmp;

	//source
	name _name;
	int i = sizeof(_name);
	std::string json = "{\"v\":11,\"v1\":\"akuuuuuuuuuuuu\",\"dce\":\"\",\"vv\":[1,3],\"vvv\":{\"v\":\"222\"}}";
	_name.unserialize(json);
	_name.serialize(tmp);
	printf(tmp.c_str());

	//template
	name1 _name1;
	i = sizeof(_name1);

	_name1.unserialize(tmp);
	tmp.clear();
	_name1.serialize(tmp);
	
	printf(tmp.c_str());

	name3 _name3;
	i = sizeof(_name3);

	_name3.unserialize(tmp);
	tmp.clear();
	_name3.serialize(tmp);

	printf(tmp.c_str());

	return 0;
}

