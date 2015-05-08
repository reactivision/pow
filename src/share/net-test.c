#undef NDEBUG
#include <assert.h>
#include <string.h>
#include "net.h"

int main(void)
{
	unsigned char s[512];
	struct netaddr host, client;

	assert(netinit(NETIP4, 1234) == 0);
	assert(netaddr(&host, 1, "127.0.0.1", 1234) == 1);

	assert(netput("test", 4, &host) == 0);
	assert(netget(s, sizeof s, &client) == 4);
	assert(memcmp(s, "test", 4) == 0);

	assert(netput("test", 4, &client) == 0);
	assert(netget(s, sizeof s, &host) == 4);
	assert(memcmp(s, "test", 4) == 0);

	assert(netget(s, sizeof s, &host) == 0);

	memset(s, 0, sizeof s);
	assert(netput(s, sizeof s, &host) == 0);
	assert(netget(s, sizeof s, &client) == sizeof s);

	assert(netaddr(&host, 1, "127.0.0.1", 1235) == 1);
	assert(netaddrcmp(&host, &host) == 0);
	assert(netaddrcmp(&host, &client) != 0);
	assert(netaddrcmp(&host, &client) != netaddrcmp(&client, &host));

	netexit();

	assert(netinit(NETIP6, 1234) == 0);
	assert(netaddr(&host, 1, "127.0.0.1", 1234) == 1);
	netexit();

	return 0;
}
