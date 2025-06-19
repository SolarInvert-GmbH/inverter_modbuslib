#pragma once

// system
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>

// std
#include <optional>

namespace catta
{
namespace linux
{

/**
 * @brief Class to get an id to identify the host pc.
 * @author CattaTech - Maik Urbannek
 */
class HostId
{
  public:
    /**
     * @return Returns a id to identify the host pc. In this case the first mac address.
     */
    static std::optional<std::uint64_t> get()
    {
        struct ifreq ifr;
        struct ifconf ifc;
        char buf[1024];

        int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
        if (sock == -1) return std::optional<std::uint64_t>{};

        ifc.ifc_len = sizeof(buf);
        ifc.ifc_buf = buf;
        if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) return std::optional<std::uint64_t>{};

        struct ifreq* it = ifc.ifc_req;
        const struct ifreq* const end = it + (static_cast<std::size_t>(ifc.ifc_len) / sizeof(struct ifreq));

        for (; it != end; ++it)
        {
            strcpy(ifr.ifr_name, it->ifr_name);
            if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0)
            {
                if (!(ifr.ifr_flags & IFF_LOOPBACK))
                {
                    if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0)
                    {
                        std::uint64_t r = 0;
                        for (std::size_t i = 0; i < 6; i++) r = r << 8 | static_cast<std::uint8_t>(ifr.ifr_hwaddr.sa_data[i]);
                        return std::optional<std::uint64_t>{r};
                    }
                }
            }
            else
                return std::optional<std::uint64_t>{};
        }
        return std::optional<std::uint64_t>{};
    }
};
}  // namespace linux
}  // namespace catta
