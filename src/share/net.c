#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "net.h"

static int fd = -1;

static void net2sockaddr(struct sockaddr *to, const struct netaddr *np);
static void sock2netaddr(struct netaddr *np, const struct sockaddr *from);

int netinit(int ptc, unsigned port)
{
	struct sockaddr_storage ss;
	struct netaddr addr;

	assert(fd == -1);
	fd = socket((ptc == NETIP6) ? AF_INET6 : AF_INET, SOCK_DGRAM, 0);
	if (fd == -1)
		return -1;
	fcntl(fd, F_SETFL, O_NONBLOCK);
	if (port > 0) {
		addr.ptc = ptc;
		memset(&addr.addr, 0, sizeof addr.addr);
		addr.port = port;
		net2sockaddr((struct sockaddr *) &ss, &addr);
		if (bind(fd, (struct sockaddr *) &ss, sizeof ss)) {
			close(fd);
			return -1;
		}
	}
	return 0;
}

void netexit(void)
{
	assert(fd != -1);
	close(fd);
	fd = -1;
}

int netaddr(struct netaddr *np, int n, const char *s, unsigned port)
{
	char service[sizeof "65535"];
	struct addrinfo *res, *p;
	struct addrinfo hints;
	int i;

	assert(port < 65536);
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	sprintf(service, "%u", port);
	if (getaddrinfo(s, service, &hints, &res))
		return -1;
	for (i = 0, p = res; i < n && p != NULL; i++, p = p->ai_next)
		sock2netaddr(np + i, p->ai_addr);
	freeaddrinfo(res);
	return i;
}

int netaddrcmp(const struct netaddr *p, const struct netaddr *q)
{
	int r;

	if (p->ptc != q->ptc)
		return (p->ptc > q->ptc) - (p->ptc < q->ptc);
	if ((r = memcmp(p->addr, q->addr, p->ptc == NETIP4 ? 4 : 16)) != 0)
		return (r > 0) - (r < 0);
	return (p->port > q->port) - (p->port < q->port);
}

int netget(void *p, int n, struct netaddr *np)
{
	struct sockaddr_storage ss;
	socklen_t m;

	assert(fd != -1);
	m = sizeof ss;
	n = recvfrom(fd, p, n, 0, (struct sockaddr *) &ss, &m);
	if (n <= 0)
		return (errno == EAGAIN || errno == EWOULDBLOCK) ? 0 : -1;
	sock2netaddr(np, (struct sockaddr *) &ss);
	return n;
}

int netput(const void *p, int n, const struct netaddr *np)
{
	struct sockaddr_storage ss;

	assert(fd != -1);
	net2sockaddr((struct sockaddr *) &ss, np);
	return -(sendto(fd, p, n, 0, (struct sockaddr *) &ss, sizeof ss) != n);
}

void sock2netaddr(struct netaddr *np, const struct sockaddr *from)
{
	const struct sockaddr_in6 *s6;
	const struct sockaddr_in *s4;
	unsigned long x;

	assert(from->sa_family == AF_INET || from->sa_family == AF_INET6);
	if (from->sa_family == AF_INET) {
		s4 = (struct sockaddr_in *) from;
		x = ntohl(s4->sin_addr.s_addr);
		np->ptc = NETIP4;
		np->addr[0] = x >> 24;
		np->addr[1] = x >> 16;
		np->addr[2] = x >> 8;
		np->addr[3] = x;
		np->port = ntohs(s4->sin_port);
	} else {
		s6 = (struct sockaddr_in6 *) from;
		np->ptc = NETIP6;
		memcpy(np->addr, s6->sin6_addr.s6_addr, sizeof np->addr);
		np->port = ntohs(s6->sin6_port);
	}
}

void net2sockaddr(struct sockaddr *to, const struct netaddr *np)
{
	struct sockaddr_in6 *s6;
	struct sockaddr_in *s4;
	unsigned long x;

	assert(np->ptc == NETIP4 || np->ptc == NETIP6);
	if (np->ptc == NETIP4) {
		s4 = (struct sockaddr_in *) to;
		x = np->addr[0];
		x = x << 8 | np->addr[1];
		x = x << 8 | np->addr[2];
		x = x << 8 | np->addr[3];
		s4->sin_family = AF_INET;
		s4->sin_addr.s_addr = htonl(x);
		s4->sin_port = htons(np->port);
	} else {
		s6 = (struct sockaddr_in6 *) to;
		s6->sin6_family = AF_INET6;
		memcpy(s6->sin6_addr.s6_addr, np->addr, sizeof np->addr);
		s6->sin6_port = htons(np->port);
	}
}
