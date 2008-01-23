///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 26 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "cscopetabbase.h"

///////////////////////////////////////////////////////////////////////////

CscopeTabBase::CscopeTabBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	m_statusMessage = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_statusMessage->Wrap( -1 );
	mainSizer->Add( m_statusMessage, 0, wxALL|wxEXPAND, 5 );
	
	m_treeCtrlResults = new wxTreeCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_HIDE_ROOT );
	mainSizer->Add( m_treeCtrlResults, 1, wxEXPAND, 5 );
	
	m_gauge = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,15 ), wxGA_HORIZONTAL|wxGA_SMOOTH );
	m_gauge->SetValue( 0 ); 
	mainSizer->Add( m_gauge, 0, wxALL|wxEXPAND, 0 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	// Connect Events
	m_treeCtrlResults->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CscopeTabBase::OnLeftDClick ), NULL, this );
	m_treeCtrlResults->Connect( wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler( CscopeTabBase::OnItemActivated ), NULL, this );
}
