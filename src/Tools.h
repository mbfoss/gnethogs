#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <pwd.h>

static inline std::string gtUserName(uint32_t uid)
{
	struct passwd const *pwd = getpwuid(uid);
	if(pwd) return pwd->pw_name;
	return std::to_string(uid);
}

static inline std::string getFileName(const std::string& s) 
{
	const char sep = '/';
	const size_t i = s.rfind(sep, s.length());
	if (i != std::string::npos) {
		return(s.substr(i+1, s.length() - i));
	}
	return(s);
}

static inline std::string formatByteCount(double v, const char** orders, int nb_orders)
{
	int order = 0;
	while (v >= 1024 && order + 1 < nb_orders) {
		order++;
		v  = v/1024;
	}
	char buffer1[20];
	int pos = snprintf(buffer1, sizeof(buffer1), "%.2lf", v);
	for(--pos; pos > 0; --pos )
	{
		if(buffer1[pos] == '0' || buffer1[pos] == '.' )
			buffer1[pos] = 0;
		else
			break;
	}
	char buffer2[30];
	snprintf(buffer2, sizeof(buffer2), "%s %s", buffer1, orders[order]);
	return buffer2;
}

static inline std::string formatByteCount(double v)
{
	static const char* orders[] = { "B", "KB", "MB", "GB" };
	return formatByteCount(v, orders, sizeof(orders)/sizeof(orders[0]));
}

static inline std::string formatBandwidth(double v)
{
	static const char* orders[] = { "KB/sec", "MB/sec", "GB/sec" };
	return formatByteCount(v, orders, sizeof(orders)/sizeof(orders[0]));
}

#endif // TOOLS_H
