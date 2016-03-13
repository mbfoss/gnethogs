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
	char buffer1[30];
	snprintf(buffer1, sizeof(buffer1), "%.2lf %s", v, orders[order]);
	return buffer1;
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
