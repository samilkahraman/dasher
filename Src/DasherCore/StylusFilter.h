#ifndef __STYLUS_FILTER_H__
#define __STYLUS_FILTER_H__

#include "DefaultFilter.h"

/// \ingroup InputFilter
/// @{
class CStylusFilter : public CDefaultFilter {
 public:
  CStylusFilter(Dasher::CEventHandler * pEventHandler, CSettingsStore *pSettingsStore, CDasherInterfaceBase *pInterface, CDasherModel *pDasherModel, ModuleID_t iID, const char *szName);

  virtual void KeyDown(int iTime, int iId, CDasherView *pView, CDasherModel *pModel, CUserLogBase *pUserLog);
  virtual void KeyUp(int iTime, int iId, CDasherView *pView, CDasherModel *pModel);
};
/// @}

#endif