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

#include "LAVVideoSettings.h"
#include "BaseDSPropPage.h"
#include "Media.h"

// {7680A5ED-DB9E-4514-A268-C1FBD5BEBFE3}
DEFINE_GUID(CLSID_LAVVideoSettingsProp,
	0x7680a5ed, 0xdb9e, 0x4514, 0xa2, 0x68, 0xc1, 0xfb, 0xd5, 0xbe, 0xbf, 0xe3);

// {11955265-3841-43F2-9C74-F0860DAEF1C5}
DEFINE_GUID(CLSID_LAVVideoFormatsProp,
	0x11955265, 0x3841, 0x43f2, 0x9c, 0x74, 0xf0, 0x86, 0xd, 0xae, 0xf1, 0xc5);

class CLAVVideoSettingsProp : public CBaseDSPropPage
{
public:
  CLAVVideoSettingsProp(LPUNKNOWN pUnk, HRESULT* phr);
  ~CLAVVideoSettingsProp();

  HRESULT OnActivate();
  HRESULT OnConnect(IUnknown *pUnk);
  HRESULT OnDisconnect();
  HRESULT OnApplyChanges();
  INT_PTR OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  HRESULT LoadData();
  HRESULT UpdateHWOptions();
  HRESULT UpdateYADIFOptions();

  void SetDirty()
  {
    m_bDirty = TRUE;
    if (m_pPageSite)
    {
      m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);
    }
  }

private:
  ILAVVideoSettings *m_pVideoSettings = nullptr;
  ILAVVideoStatus   *m_pVideoStatus   = nullptr;

  DWORD m_dwNumThreads;
  DWORD m_StreamAR;
  DWORD m_DeintFieldOrder;
  LAVDeintMode m_DeintMode;
  DWORD m_dwRGBOutput;

  BOOL  m_bPixFmts[LAVOutPixFmt_NB];
  DWORD m_HWAccel;
  BOOL  m_HWAccelCodecs[HWCodec_NB];
  BOOL  m_HWAccelCUVIDDXVA;

  DWORD m_HWRes;
  DWORD m_HWDeviceIndex;

  DWORD m_HWDeintAlgo;
  DWORD m_HWDeintOutMode;
  LAVSWDeintModes m_SWDeint;
  DWORD m_SWDeintOutMode;

  DWORD m_DitherMode;
  BOOL m_TrayIcon;
};

class CLAVVideoFormatsProp : public CBaseDSPropPage
{
public:
  CLAVVideoFormatsProp(LPUNKNOWN pUnk, HRESULT* phr);
  ~CLAVVideoFormatsProp();

  HRESULT OnActivate();
  HRESULT OnConnect(IUnknown *pUnk);
  HRESULT OnDisconnect();
  HRESULT OnApplyChanges();
  INT_PTR OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  HRESULT LoadData();

  void SetDirty()
  {
    m_bDirty = TRUE;
    if (m_pPageSite)
    {
      m_pPageSite->OnStatusChange(PROPPAGESTATUS_DIRTY);
    }
  }

private:
  ILAVVideoSettings *m_pVideoSettings = nullptr;

  BOOL m_bFormats[Codec_VideoNB];
  BOOL m_bWMVDMO;
  BOOL m_bDVD;
};
