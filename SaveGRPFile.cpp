#include "StdAfx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

#include "SaveGRPFile.h"

struct Person persons[320];


// Big5 转 UTF-8（Windows 和 Linux 实现）
#define HEX2STR(a)	Hex2Str(a, sizeof(a))
std::string Hex2Str(const char* beg, int len)
{
	if (!beg || len <= 0)
		return "";

	std::ostringstream oss;
	unsigned char byte;

	for (int i = 0; i < len; ++i)
	{
		byte = static_cast<unsigned char>(beg[i]);  // 转为 unsigned char 防止符号扩展
		if (i > 0)
			oss << " ";  // 每个字节之间加空格
		oss << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
	}

	return oss.str();
}

// Big5 转 UTF-8（Windows 和 Linux 实现）
std::string Big5ToUTF8(const std::string& big5Str)
{
	if (big5Str.empty())
	{
		return "";
	}

#ifdef _WIN32
	// Windows: MultiByteToWideChar (Big5 = code page 950)
	int wSize = MultiByteToWideChar(950, 0, big5Str.c_str(), -1, nullptr, 0);
	if (wSize == 0)
	{
		return "";
	}
	std::wstring wstr;
	wstr.resize(wSize);
	MultiByteToWideChar(950, 0, big5Str.c_str(), -1, &wstr[0], wSize);

	int uSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (uSize == 0)
	{
		return "";
	}
	std::string utf8Str;
	utf8Str.resize(uSize - 1); // -1 for null terminator
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &utf8Str[0], uSize, nullptr, nullptr);
	return utf8Str;
#else
	// Linux/macOS: 使用 iconv
	// 注意：编译时需加 -liconv：g++ -liconv
#include <iconv.h>
	size_t inBytes = big5Str.size();
	size_t outBytes = inBytes * 3; // UTF-8 最多 3 字节/字符
	std::string utf8Str;
	utf8Str.resize(outBytes);
	char* inBuf = const_cast<char*>(big5Str.c_str());
	char* outBuf = &utf8Str[0];
	size_t inSize = inBytes;
	size_t outSize = outBytes;

	iconv_t cd = iconv_open("UTF-8", "BIG5");
	if (cd == (iconv_t)-1) return big5Str; // fallback

	size_t result = iconv(cd, &inBuf, &inSize, &outBuf, &outSize);
	iconv_close(cd);

	if (result == (size_t)-1) return big5Str;

	utf8Str.resize(outBytes - outSize);
	return utf8Str;
#endif
}

// GBK 转 UTF-8（Windows实现）
std::string GBKToUTF8(const std::string& gbk5Str)
{
	if (gbk5Str.empty())
	{
		return "";
	}

#ifdef _WIN32
	// Windows: MultiByteToWideChar (GBK = code page 936)
	int wSize = MultiByteToWideChar(936, 0, gbk5Str.c_str(), -1, nullptr, 0);
	if (wSize == 0)
	{
		return "";
	}
	std::wstring wstr;
	wstr.resize(wSize);
	MultiByteToWideChar(936, 0, gbk5Str.c_str(), -1, &wstr[0], wSize);

	int uSize = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (uSize == 0)
	{
		return "";
	}
	std::string utf8Str;
	utf8Str.resize(uSize - 1); // -1 for null terminator
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &utf8Str[0], uSize, nullptr, nullptr);
	return utf8Str;
#else

#endif
}


// UTF-8 字符串转义（防止 CSV 中逗号、引号问题）
std::string EscapeCSV(const std::string& str)
{
	std::string result;
	bool needQuote = (str.find(',') != std::string::npos ||
		str.find('"') != std::string::npos ||
		str.find('\n') != std::string::npos);

	if (needQuote)
		result += "\"";

	// 使用下标遍历（VC2010 完全支持）
	for (size_t i = 0; i < str.length(); ++i)
	{
		char c = str[i];
		if (c == '"')
			result += "\"\"";  // 转义双引号
		else
			result += c;
	}

	if (needQuote)
		result += "\"";

	return result;
}

void ReadPersonFromSaveFile(const char* pszFileName)
{
	std::ifstream file(pszFileName, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "错误：无法打开文件 " << pszFileName << std::endl;
		return;
	}

	// 计算起始偏移：0x00000344
	const std::streampos startOffset = 0x344;

	// 跳转到指定位置
	file.seekg(startOffset, std::ios::beg);
	if (!file.good())
	{
		std::cerr << "错误：无法跳转到文件偏移 0x344" << std::endl;
		file.close();
		return;
	}

	// 读取 XXX 个 Person 结构体
	file.read(reinterpret_cast<char*>(persons), sizeof(persons));

	if (file.gcount() != sizeof(persons))
	{
		std::cerr << "警告：未读取到完整的 XXX 个角色数据。" << std::endl;
		if (file.eof())
			std::cerr << "原因：文件提前结束。" << std::endl;
		else if (file.fail())
			std::cerr << "原因：读取失败（可能文件损坏）。" << std::endl;
	}
	else
	{
		std::cout << "成功从文件 '" << pszFileName
			<< "' 读取 XXX 个角色数据（偏移 0x34C）" << std::endl;
	}

	file.close();
}

void ExportToCSV(const char* filename)
{
	std::ofstream file(filename, std::ios::out | std::ios::trunc);
	if (!file.is_open())
	{
		std::cerr << "无法创建文件: " << filename << std::endl;
		return;
	}

	// 写入 CSV 头（列名）
	// 注意：中文在 CSV 中建议用 UTF-8 with BOM，否则 Excel 可能乱码
	file << "\xEF\xBB\xBF"; // UTF-8 BOM，让 Excel 正确识别中文

	// === 表头（简体中文，假设源码为 UTF-8）===
	// 如果你源码保存为 UTF-8，则直接写入
	file << GBKToUTF8("序号") << ","
		<< GBKToUTF8("编号") << ","
		<< GBKToUTF8("模型") << ","
		<< GBKToUTF8("未知0") << ","
		<< GBKToUTF8("身份") << ","
		<< GBKToUTF8("姓名") << ","
		<< GBKToUTF8("江湖称号") << ","
		<< GBKToUTF8("性别") << ","
		<< GBKToUTF8("等级") << ","
		<< GBKToUTF8("经验") << ","
		<< GBKToUTF8("生命值") << ","
		<< GBKToUTF8("生命最大值") << ","
		<< GBKToUTF8("受伤程度") << ","
		<< GBKToUTF8("中毒程度") << ","
		<< GBKToUTF8("体力") << ","
		<< GBKToUTF8("未知1") << ","
		<< GBKToUTF8("装备武器") << ","
		<< GBKToUTF8("装备防具") << ","
		<< GBKToUTF8("未知2") << ","
		<< GBKToUTF8("内力属性") << ","
		<< GBKToUTF8("内力值") << ","
		<< GBKToUTF8("内力最大值") << ","
		<< GBKToUTF8("攻击力") << ","
		<< GBKToUTF8("轻功") << ","
		<< GBKToUTF8("防御力") << ","
		<< GBKToUTF8("医疗能力") << ","
		<< GBKToUTF8("用毒能力") << ","
		<< GBKToUTF8("解毒能力") << ","
		<< GBKToUTF8("抗毒能力") << ","
		<< GBKToUTF8("拳掌功夫") << ","
		<< GBKToUTF8("御剑能力") << ","
		<< GBKToUTF8("耍刀技巧") << ","
		<< GBKToUTF8("特殊兵器") << ","
		<< GBKToUTF8("暗器技巧") << ","
		<< GBKToUTF8("武学常识") << ","
		<< GBKToUTF8("道德值") << ","
		<< GBKToUTF8("武功带毒") << ","
		<< GBKToUTF8("双手互搏") << ","
		<< GBKToUTF8("声望值") << ","
		<< GBKToUTF8("资质") << ","
		<< GBKToUTF8("修炼物品") << ","
		<< GBKToUTF8("修炼经验");

	// 武功 1-10
	for (long long i = 1; i <= 10; ++i)
		file << "," << GBKToUTF8("武功" + std::to_string(i));
	for (long long i = 1; i <= 10; ++i)
		file << "," << GBKToUTF8("武功" + std::to_string(i) + "经验");

	// 物品 1-4
	for (long long i = 1; i <= 4; ++i)
		file << "," << GBKToUTF8("物品" + std::to_string(i));
	for (long long i = 1; i <= 4; ++i)
		file << "," << GBKToUTF8("物品" + std::to_string(i) + "数量");

	file << GBKToUTF8(",备注\n"); // 结束表头

	// 写入数据
	for (int idx = 0; idx < sizeof(persons)/sizeof(Person); ++idx)
	{
		const Person& p = persons[idx];

		// 跳过空数据（可选）
		if (p.szName[0] == '\0') continue;

		// 提取姓名和称号（Big5 编码）
		std::string nameBig5(p.szName);
		std::string nickBig5(p.szNick);

		// 转换为 UTF-8
		std::string nameUtf8 = Big5ToUTF8(nameBig5);
		std::string nickUtf8 = Big5ToUTF8(nickBig5);

		file << idx << ","
			<< p.usNo << ","
			<< p.usModel << ","
			<< HEX2STR(p.szRev4) << ","
			<< p.usType << ","
			<< EscapeCSV(nameUtf8) << ","
			<< EscapeCSV(nickUtf8) << ","
			<< p.usSex << ","
			<< p.usLevel << ","
			<< p.usExp << ","
			<< p.usLife << ","
			<< p.usMaxLife << ","
			<< p.usInjury << ","
			<< p.usPoison << ","
			<< p.usStamina << ","
			<< HEX2STR(p.szRev1) << ","//
			<< p.usWeapon << ","
			<< p.usArmor << ","
			<< HEX2STR(p.szRev2) << ","//
			<< p.usForceType << ","
			<< p.usForce << ","
			<< p.usMaxForce << ","
			<< p.usAttack << ","
			<< p.usLightness << ","
			<< p.usDefense << ","
			<< p.usMedicine << ","
			<< p.usToxic << ","
			<< p.usDetox << ","
			<< p.usResistance << ","
			<< p.usFist << ","
			<< p.usSword << ","
			<< p.usBlade << ","
			<< p.usExotic << ","
			<< p.usDagger << ","
			<< p.usKnowledge << ","
			<< p.usMorality << ","
			<< p.usPoisonSkill << ","
			<< p.usAmbidextrous << ","
			<< p.usReputation << ","
			<< p.usTalent << ","
			<< p.usTrainItem << ","
			<< p.usTrainExp << ",";

		// 写入武功
		for (int i = 0; i < 10; ++i)
			file << p.usSkills[i] << ",";
		for (int i = 0; i < 10; ++i)
			file << p.usSkillExps[i] << ",";

		// 写入物品
		for (int i = 0; i < 4; ++i)
			file << p.usItem[i] << ",";
		for (int i = 0; i < 4; ++i)
			file << p.usItemCount[i] << ",";

		file << "\n"; // 一行结束
	}

	file.close();
	std::cout << "CSV 文件已生成: " << filename << std::endl;
}