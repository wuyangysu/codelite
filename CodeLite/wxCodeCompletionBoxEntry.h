#ifndef WXCODECOMPLETIONBOXENTRY_H
#define WXCODECOMPLETIONBOXENTRY_H

#include <wx/clntdata.h>
#include <wx/sharedptr.h>
#include <vector>
#include "codelite_exports.h"
#include <wx/gdicmn.h>
#include <wx/string.h>

class wxStyledTextCtrl;
class WXDLLIMPEXP_CL wxCodeCompletionBoxEntry
{
    wxString m_text;
    wxString m_comment;
    int m_imgIndex;
    wxClientData* m_clientData;
    wxRect m_itemRect;
    friend class wxCodeCompletionBox;

public:
    typedef wxSharedPtr<wxCodeCompletionBoxEntry> Ptr_t;
    typedef std::vector<wxCodeCompletionBoxEntry::Ptr_t> Vec_t;

public:
    wxCodeCompletionBoxEntry(const wxString& text, int imgId = wxNOT_FOUND, wxClientData* userData = NULL)
        : m_text(text)
        , m_imgIndex(imgId)
        , m_clientData(userData)
    {
    }

    virtual ~wxCodeCompletionBoxEntry()
    {
        wxDELETE(m_clientData);
        m_imgIndex = wxNOT_FOUND;
        m_text.Clear();
    }

    /**
     * @brief helper method for allocating wxCodeCompletionBoxEntry::Ptr
     * @return
     */
    static wxCodeCompletionBoxEntry::Ptr_t
    New(const wxString& text, int imgId = wxNOT_FOUND, wxClientData* userData = NULL)
    {
        wxCodeCompletionBoxEntry::Ptr_t pEntry(new wxCodeCompletionBoxEntry(text, imgId, userData));
        return pEntry;
    }

    void SetImgIndex(int imgIndex) { this->m_imgIndex = imgIndex; }
    void SetText(const wxString& text) { this->m_text = text; }
    int GetImgIndex() const { return m_imgIndex; }
    const wxString& GetText() const { return m_text; }
    /**
     * @brief set client data, deleting the old client data
     * @param clientData
     */
    void SetClientData(wxClientData* clientData)
    {
        wxDELETE(this->m_clientData);
        this->m_clientData = clientData;
    }
    wxClientData* GetClientData() { return m_clientData; }
    void SetComment(const wxString& comment) { this->m_comment = comment; }
    const wxString& GetComment() const { return m_comment; }
};
#endif // WXCODECOMPLETIONBOXENTRY_H
