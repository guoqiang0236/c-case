#include <iostream>
#include <string>
#include <regex>

int main() {
	// ʾ��1: ��ͨ�ַ��� vs ԭʼ�ַ��� - Windows ·��
	std::string str1;
	str1 = "C:\\workspace\\sonoquest_yiru\\sonoquest_oem\\sq_common\\dcmtk3.6.9\\etc\\dcmqrprf.cfg";
	std::cout << "ʾ��1 - ��ͨ�ַ���:\n" << str1 << std::endl << std::endl;

	std::string str2;
	str2 = R"(C:\workspace\sonoquest_yiru\sonoquest_oem\sq_common\dcmtk3.6.9\etc\dcmqrprf.cfg)";
	std::cout << "ʾ��1 - ԭʼ�ַ���:\n" << str2 << std::endl << std::endl;

	// ʾ��2: �����ַ��� - JSON ��ʽ
	std::string json = R"({
    "name": "����",
    "age": 25,
    "path": "C:\Users\Documents\file.txt",
    "description": "����һ��\"��������\"���ı�"
})";
	std::cout << "ʾ��2 - JSON �ַ���:\n" << json << std::endl << std::endl;

	// ʾ��3: SQL ��ѯ���
	std::string sql = R"(
SELECT * FROM users 
WHERE name = 'Tom' 
  AND age > 18 
  AND path LIKE 'C:\data\%'
ORDER BY id DESC;
)";
	std::cout << "ʾ��3 - SQL ��ѯ:\n" << sql << std::endl << std::endl;

	// ʾ��4: ������ʽ������˫��ת�壩
	std::string phonePattern = R"(\d{3}-\d{4}-\d{4})";  // ƥ��绰����
	std::string emailPattern = R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})";
	std::cout << "ʾ��4 - ������ʽģʽ:\n�绰: " << phonePattern
		<< "\n����: " << emailPattern << std::endl << std::endl;

	// ʾ��5: HTML ����
	std::string html = R"(
<!DOCTYPE html>
<html>
<head>
    <title>����ҳ��</title>
</head>
<body>
    <h1>��ӭʹ��ԭʼ�ַ���</h1>
    <p>·��: C:\Program Files\App\config.xml</p>
</body>
</html>
)";
	std::cout << "ʾ��5 - HTML ����:\n" << html << std::endl << std::endl;

	// ʾ��6: ���������ַ����ַ���
	std::string special = R"(�����ַ�����:
�Ʊ��:	������tab
����: "˫����" �� '������'
��б��: \ \\ \\\
���кͻس�������
)";
	std::cout << "ʾ��6 - �����ַ�:\n" << special << std::endl << std::endl;

	// ʾ��7: �Զ���ָ��� - ���ַ����а��� )" ʱʹ��
	std::string withDelimiter = R"delim(
����ַ����п��԰��� )" ���������
��������ǰ�����ַ�������Ϊʹ�����Զ���ָ��� "delim"
)delim";
	std::cout << "ʾ��7 - �Զ���ָ���:\n" << withDelimiter << std::endl << std::endl;

	// ʾ��8: XML �����ļ�
	std::string xml = R"(<?xml version="1.0" encoding="UTF-8"?>
<config>
    <database>
        <host>localhost</host>
        <path>C:\Database\data.db</path>
    </database>
    <settings name="app" value="test"/>
</config>)";
	std::cout << "ʾ��8 - XML ����:\n" << xml << std::endl << std::endl;

	// ʾ��9: C++ ����Ƭ�Σ���Ϊ�ַ�����
	std::string cppCode = R"(
void processFile(const std::string& path) {
    std::cout << "�����ļ�: " << path << std::endl;
    // �������...
}
)";
	std::cout << "ʾ��9 - C++ �����ַ���:\n" << cppCode << std::endl << std::endl;

	// ʾ��10: ����·���� URL
	std::string networkPath = R"(\\server\share\folder\file.txt)";
	std::string url = R"(https://example.com/api/v1/users?filter={"age":">18"}&sort=name)";
	std::cout << "ʾ��10 - ����·���� URL:\n"
		<< "����·��: " << networkPath << "\n"
		<< "URL: " << url << std::endl << std::endl;

	return 0;
}