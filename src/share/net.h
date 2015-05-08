enum { NETIP4, NETIP6 };

struct netaddr {
	int ptc;                 /* NETIP4 or NETIP6 */
	unsigned char addr[16];  /* 4 or 16 byte IP address */
	unsigned short port;     /* 1 to 65535 */
};

/* netinit: set up UDP socket over ptc; bind to port if port>0 */
int netinit(int ptc, unsigned port);

/* netexit: release resources acquired by netinit */
void netexit(void);

/* netaddr: copy to *np a maximum of n addresses associated with s:port */
int netaddr(struct netaddr *np, int n, const char *s, unsigned port);

/* netaddrcmp: -1 if p<q, 0 if p=q, 1 if p>q */
int netaddrcmp(const struct netaddr *p, const struct netaddr *q);

/* netget: copy up to n bytes from np to *p. return # bytes copied, 0 if no data
 *         is available, or -1 on error */
int netget(void *p, int n, struct netaddr *np);

/* netput: write n bytes from *p to np */
int netput(const void *p, int n, const struct netaddr *np);
