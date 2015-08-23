///-----------------------------------------------------------------
///
/// @file      CMYuvPropertyDlg.h
/// @author    zstein
/// Created:   2012-11-11 ¿ÀÈÄ 6:35:34
/// @section   DESCRIPTION
///            CMYuvPropertyDlg class declaration
///
///------------------------------------------------------------------

#ifndef __CMYUVPROPERTYDLG_H__
#define __CMYUVPROPERTYDLG_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
////Header Include End
#include "../CMImage.h"

////Dialog Style Start
#undef CMYuvPropertyDlg_STYLE
#define CMYuvPropertyDlg_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End


class CMYuvPropertyDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		CMYuvPropertyDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("zyuv"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = CMYuvPropertyDlg_STYLE);
		virtual ~CMYuvPropertyDlg();
	
	private:
		// No description
		int m_presetIndex;
		int m_width;
		int m_height;
        CMImageFormat m_imageFormat;
        CMYUVFormat   m_yuvFormat;
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		
    // Event handler
	public:
        bool TransferDataFromWindow();
        void OnOK(wxCommandEvent& event);
        void OnCancel(wxCommandEvent& event);
		// No description
		void OnPresetSelected(wxCommandEvent& event);

    // Access
    public:
        int GetWidth() { 
            return m_width; 
        }
        int GetHeight() { 
            return m_height; 
        }
        CMImageFormat GetImageFormat() {
            return m_imageFormat;
        }
        CMYUVFormat GetYUVFormat() {
            return m_yuvFormat;
        }
};

#endif

