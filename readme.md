## ˵��
	�򵥵�c++���л�json,ֻ��serialize.h�ļ�

## ʹ��
	//ģ�嶨��
	//SERIALIZE_STRUCT(
	//	�ṹ��
	//  ,(public,����, ����, ����...)    //������Ҫע��:public Ϊ��λ,�����κ�����,��Ϊvsû�ҵ���������һ����������
	// ,(��������,������)
	// ,(��������,������)
	//    ...
	// )

	//���л�����
	//���� �����json
	int serialize(std::string& out)

	//�����л�����
	//���� json
	int unserialize(std::string& in)