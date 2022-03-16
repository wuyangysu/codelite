#ifndef CLTHEMEDTEXTCTRL_HPP
#define CLTHEMEDTEXTCTRL_HPP

#include "cl_command_event.h"
#include "codelite_exports.h"

#include <wx/stc/stc.h>

class WXDLLIMPEXP_SDK clThemedTextCtrl : public wxStyledTextCtrl
{
protected:
    void OnKeyDown(wxKeyEvent& event);
    void OnAddChar(wxStyledTextEvent& event);
    void OnChange(wxStyledTextEvent& event);
    void OnPaste(wxStyledTextEvent& event);

private:
    void ApplySettings();
    void TrimText();

public:
    virtual ~clThemedTextCtrl();

    clThemedTextCtrl() {}
    clThemedTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString,
                     const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0);
    void OnSysColours(clCommandEvent& event);
};

#endif // CLTHEMEDTEXTCTRL_HPP
