// логистика
#ifndef LOGISTICSCOMPANY_H
#define LOGISTICSCOMPANY_H

#include "Corporation.h"

class LogisticsCompany : public Corporation {
public:
    LogisticsCompany(int level = 1);
    
    std::string getName() const override;
    void applyEffect(Empire* empire, Galaxy* galaxy) override;
    
    bool buildRoute(int fromId, int toId, Galaxy* galaxy, Empire* empire);
    bool upgradeRoute(int routeId, Galaxy* galaxy, Empire* empire);
};

#endif 