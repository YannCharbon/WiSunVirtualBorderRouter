/**
 * @author Yann Charbon <yann.charbon@heig-vd.ch>
 * @copyright 2024
 */

#ifndef WISUN_VIRTUAL_BORDER_ROUTER_H
#define WISUN_VIRTUAL_BORDER_ROUTER_H

#include "WiSunBorderRouterManager.h"
#include "WiSunBackboneLinkService.h"
#include "WiSunBackboneLinkMDNSDiscovery.h"

class WiSunVirtualBorderRouter : WiSunBorderRouterManager {
public:
    WiSunVirtualBorderRouter(const char *wisun_network_name) :  WiSunBorderRouterManager(wisun_network_name),
                                                                _thread(osPriorityNormal, OS_STACK_SIZE, nullptr, "WSBBLinkThread"),
                                                                _mDNSDiscovery(wisun_network_name),
                                                                _wsBBLinkService(&_mDNSDiscovery) {}

    int start() override {
        int ret;
        ret = WiSunBorderRouterManager::start();
        if (ret) {
            return ret;
        }

        _wsBBLinkService.start(ws_network_name, WiSunBackboneLinkService::Role::MASTER_BR);

        return 0;
    }

private:
    Thread _thread;
    WiSunBackboneLinkMDNSDiscovery _mDNSDiscovery;
    WiSunBackboneLinkService _wsBBLinkService;
};

#endif