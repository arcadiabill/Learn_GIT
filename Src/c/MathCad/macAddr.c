/* Returns the MAC Address
   Params: int iNetType - 0: ethernet, 1: Wifi
           char chMAC[6] - MAC Address in binary format
   Returns: 0: success
           -1: Failure
    */
int getMACAddress(int iNetType, char chMAC[6]) {
  struct ifreq ifr;
  int sock;
  char *ifname=NULL;
 
  if (!iNetType) {
    ifname="eth0"; /* Ethernet */
  } else {
    ifname="wlan0"; /* Wifi */
  }
  sock=socket(AF_INET,SOCK_DGRAM,0);
  strcpy( ifr.ifr_name, ifname );
  ifr.ifr_addr.sa_family = AF_INET;
  if (ioctl( sock, SIOCGIFHWADDR, &amp;ifr ) &lt; 0) {
    return -1;
  }
  memcpy(chMAC, ifr.ifr_hwaddr.sa_data, 6)
  close(sock);
  return 0;
}
