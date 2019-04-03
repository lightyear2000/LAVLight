/*
 *      Copyright (C) 2010-2017 Hendrik Leppkes
 *      http://www.1f0.de
 *      Copyright (C) 2017 Lightyear
 *      https://github.com/lightyear2000/LAVLight
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include "BaseDSPropPage.h"
#include "LAVSplitterSettingsInternal.h"


// {F434D8EA-80D1-4AC0-BF18-2FF011C64946}
DEFINE_GUID(CLSID_LAVSplitterSettingsProp,
	0xf434d8ea, 0x80d1, 0x4ac0, 0xbf, 0x18, 0x2f, 0xf0, 0x11, 0xc6, 0x49, 0x46);

// {DA22097E-00EB-4882-9B97-51AA9952E8A5}
DEFINE_GUID(CLSID_LAVSplitterFormatsProp,
	0xda22097e, 0xeb, 0x4882, 0x9b, 0x97, 0x51, 0xaa, 0x99, 0x52, 0xe8, 0xa5);


class CLAVSplitterSettingsProp : public CBaseDSPropPage
{
public:
  CLAVSplitterSettingsProp(LPUNKNOWN pUnk, HRESULT* phr);
  virtual ~CLAVSplitterSettingsProp(void);

  HRESULT OnActivate();
  HRESULT OnConnect(IUnknown *pUnk);
  HRESULT OnDisconnect();
  HRESULT OnApplyChanges();
  INT_PTR OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  HRESULT LoadData();
  void UpdateSubtitleMode(LAVSubtitleMode mode);

  void SetDirty()
  {
    m_bDirty = TRUE;
    if (m_pPageSite)
    {
      m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);
    }
  }

private:
  ILAVFSettingsInternal *m_pLAVF = nullptr;

  // Settings
  WCHAR *m_pszPrefLang     = nullptr;
  WCHAR *m_pszPrefSubLang  = nullptr;
  WCHAR *m_pszAdvSubConfig = nullptr;

  LAVSubtitleMode m_subtitleMode;
  BOOL m_PGSForcedStream;
  BOOL m_PGSOnlyForced;
  int m_VC1Mode;
  BOOL m_substreams;
  BOOL m_MKVExternal;

  BOOL m_StreamSwitchRemoveAudio;
  BOOL m_PreferHighQualityAudio;
  BOOL m_ImpairedAudio;
  DWORD m_QueueMaxMem;
  DWORD m_QueueMaxPackets;
  DWORD m_NetworkAnalysisDuration;

  BOOL m_TrayIcon;

  LAVSubtitleMode m_selectedSubMode;
  WCHAR m_subLangBuffer[256];
  WCHAR m_advSubBuffer[256];

  WCHAR stringBuffer[256];
};

class CLAVSplitterFormatsProp : public CBaseDSPropPage
{
public:
  CLAVSplitterFormatsProp(LPUNKNOWN pUnk, HRESULT* phr);
  virtual ~CLAVSplitterFormatsProp(void);

  HRESULT OnActivate();
  HRESULT OnConnect(IUnknown *pUnk);
  HRESULT OnDisconnect();
  HRESULT OnApplyChanges();
  INT_PTR OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  void SetDirty()
  {
    m_bDirty = TRUE;
    if (m_pPageSite)
    {
      m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);
    }
  }

private:
  ILAVFSettingsInternal *m_pLAVF = nullptr;

  std::set<FormatInfo> m_Formats;
  BOOL *m_bFormats = nullptr;

  WCHAR stringBuffer[256];
};
