## 说明
	简单的c++序列化json,只有serialize.h文件

## 使用
	//模板定义
	//SERIALIZE_STRUCT(
	//	结构名
	//  ,(public,父类, 父类, 父类...)    //这里需要注意:public 为补位,不起任何作用,因为vs没找到方法计算一个参数个数
	// ,(变量类型,变量名)
	// ,(变量类型,变量名)
	//    ...
	// )

	//序列化函数
	//参数 输出的json
	int serialize(std::string& out)

	//反序列化函数
	//参数 json
	int unserialize(std::string& in)