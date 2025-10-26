#include <iostream>
#include <string>
#include <regex>

int main() {
	// 示例1: 普通字符串 vs 原始字符串 - Windows 路径
	std::string str1;
	str1 = "C:\\workspace\\sonoquest_yiru\\sonoquest_oem\\sq_common\\dcmtk3.6.9\\etc\\dcmqrprf.cfg";
	std::cout << "示例1 - 普通字符串:\n" << str1 << std::endl << std::endl;

	std::string str2;
	str2 = R"(C:\workspace\sonoquest_yiru\sonoquest_oem\sq_common\dcmtk3.6.9\etc\dcmqrprf.cfg)";
	std::cout << "示例1 - 原始字符串:\n" << str2 << std::endl << std::endl;

	// 示例2: 多行字符串 - JSON 格式
	std::string json = R"({
    "name": "张三",
    "age": 25,
    "path": "C:\Users\Documents\file.txt",
    "description": "这是一段\"包含引号\"的文本"
})";
	std::cout << "示例2 - JSON 字符串:\n" << json << std::endl << std::endl;

	// 示例3: SQL 查询语句
	std::string sql = R"(
SELECT * FROM users 
WHERE name = 'Tom' 
  AND age > 18 
  AND path LIKE 'C:\data\%'
ORDER BY id DESC;
)";
	std::cout << "示例3 - SQL 查询:\n" << sql << std::endl << std::endl;

	// 示例4: 正则表达式（避免双重转义）
	std::string phonePattern = R"(\d{3}-\d{4}-\d{4})";  // 匹配电话号码
	std::string emailPattern = R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})";
	std::cout << "示例4 - 正则表达式模式:\n电话: " << phonePattern
		<< "\n邮箱: " << emailPattern << std::endl << std::endl;

	// 示例5: HTML 代码
	std::string html = R"(
<!DOCTYPE html>
<html>
<head>
    <title>测试页面</title>
</head>
<body>
    <h1>欢迎使用原始字符串</h1>
    <p>路径: C:\Program Files\App\config.xml</p>
</body>
</html>
)";
	std::cout << "示例5 - HTML 代码:\n" << html << std::endl << std::endl;

	// 示例6: 包含特殊字符的字符串
	std::string special = R"(特殊字符测试:
制表符:	这里有tab
引号: "双引号" 和 '单引号'
反斜杠: \ \\ \\\
换行和回车都保留
)";
	std::cout << "示例6 - 特殊字符:\n" << special << std::endl << std::endl;

	// 示例7: 自定义分隔符 - 当字符串中包含 )" 时使用
	std::string withDelimiter = R"delim(
这个字符串中可以包含 )" 这样的组合
而不会提前结束字符串，因为使用了自定义分隔符 "delim"
)delim";
	std::cout << "示例7 - 自定义分隔符:\n" << withDelimiter << std::endl << std::endl;

	// 示例8: XML 配置文件
	std::string xml = R"(<?xml version="1.0" encoding="UTF-8"?>
<config>
    <database>
        <host>localhost</host>
        <path>C:\Database\data.db</path>
    </database>
    <settings name="app" value="test"/>
</config>)";
	std::cout << "示例8 - XML 配置:\n" << xml << std::endl << std::endl;

	// 示例9: C++ 代码片段（作为字符串）
	std::string cppCode = R"(
void processFile(const std::string& path) {
    std::cout << "处理文件: " << path << std::endl;
    // 更多代码...
}
)";
	std::cout << "示例9 - C++ 代码字符串:\n" << cppCode << std::endl << std::endl;

	// 示例10: 网络路径和 URL
	std::string networkPath = R"(\\server\share\folder\file.txt)";
	std::string url = R"(https://example.com/api/v1/users?filter={"age":">18"}&sort=name)";
	std::cout << "示例10 - 网络路径和 URL:\n"
		<< "网络路径: " << networkPath << "\n"
		<< "URL: " << url << std::endl << std::endl;

	return 0;
}