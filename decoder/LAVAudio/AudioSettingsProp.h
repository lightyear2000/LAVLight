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

#include "LAVAudioSettings.h"
#include "BaseDSPropPage.h"
#include "Media.h"

// alt 2D8F1801-A70D-48F4-B76B-7F5AE022AB54
// {C5FA0AAD-2C55-4DB0-9125-D085D14236E7}
DEFINE_GUID(CLSID_LAVAudioSettingsProp, 
0xC5FA0AAD, 0x2C55, 0x4DB0, 0x91, 0x25, 0xD0, 0x85, 0xD1, 0x42, 0x36, 0xE7);

// alt C89FC33C-E60A-4C97-BEF4-ACC5762B6404
// {07E1E12F-4465-421B-B971-5494B36ED352}
DEFINE_GUID(CLSID_LAVAudioMixingProp,
0x07E1E12F, 0x4465, 0x421B, 0xB9, 0x71, 0x54, 0x94, 0xB3, 0x6E, 0xD3, 0x52);

// alt 20ED4A03-6AFD-4FD9-980B-2F6143AA0892
// {6DB2D8CB-3064-4B4A-86C1-062E07896AC4}
DEFINE_GUID(CLSID_LAVAudioStatusProp, 
0x6DB2D8CB, 0x3064, 0x4B4A, 0x86, 0xC1, 0x06, 0x2E, 0x07, 0x89, 0x6A, 0xC4);

// alt BD72668E-6BFF-4CD1-8480-D465708B336B
// {1396B683-75EA-47E8-84E7-7D76DD1E3767}
DEFINE_GUID(CLSID_LAVAudioFormatsProp,
0x1396B683, 0x75EA, 0x47E8, 0x84, 0xE7, 0x7D, 0x76, 0xDD, 0x1E, 0x37, 0x67);

class CLAVAudioSettingsProp : public CBaseDSPropPage
{
public:
  CLAVAudioSettingsProp(LPUNKNOWN pUnk, HRESULT* phr);
  ~CLAVAudioSettingsProp();

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
  ILAVAudioSettings *m_pAudioSettings = nullptr;

  BOOL m_bDRCEnabled;
  int m_iDRCLevel;

  bool m_bBitstreaming[Bitstream_NB];
  BOOL m_bDTSHDFraming;
  BOOL m_bAutoAVSync;
  BOOL m_bOutputStdLayout;
  BOOL m_bOutput51Legacy;
  BOOL m_bExpandMono;
  BOOL m_bExpand61;
  bool m_bSampleFormats[SampleFormat_NB];
  BOOL m_bDither;
  BOOL m_bAudioDelay;
  int  m_iAudioDelay;
  BOOL m_TrayIcon;
};

class CLAVAudioMixingProp : public CBaseDSPropPage
{
public:
  CLAVAudioMixingProp(LPUNKNOWN pUnk, HRESULT* phr);
  ~CLAVAudioMixingProp();

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
  ILAVAudioSettings *m_pAudioSettings = nullptr;

  BOOL  m_bMixing;
  DWORD m_dwSpeakerLayout;
  DWORD m_dwFlags;
  DWORD m_dwMixingMode;
  DWORD m_dwMixCenter;
  DWORD m_dwMixSurround;
  DWORD m_dwMixLFE;
};

class CLAVAudioFormatsProp : public CBaseDSPropPage
{
public:
  CLAVAudioFormatsProp(LPUNKNOWN pUnk, HRESULT* phr);
  ~CLAVAudioFormatsProp();

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
  ILAVAudioSettings *m_pAudioSettings = nullptr;

  bool m_bFormats[Codec_AudioNB];
};


class CLAVAudioStatusProp : public CBaseDSPropPage
{
public:
  CLAVAudioStatusProp(LPUNKNOWN pUnk, HRESULT* phr);
  ~CLAVAudioStatusProp();

  HRESULT OnActivate();
  HRESULT OnDeactivate();
  HRESULT OnConnect(IUnknown *pUnk);
  HRESULT OnDisconnect();
  INT_PTR OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  void UpdateVolumeDisplay();

private:
  ILAVAudioStatus *m_pAudioStatus = nullptr;
  int m_nChannels = 0;
};
