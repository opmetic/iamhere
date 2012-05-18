#include "BaseWindowWnd.h"

CBaseWindowWnd::CBaseWindowWnd(void)
{
	SetLocalStyleValue(WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
}


CBaseWindowWnd::~CBaseWindowWnd(void)
{
}

void CBaseWindowWnd::SetSkinName(CStdString skinName)
{
	if (!skinName.IsEmpty())
	{
		m_skinName = _T(skinName);
	}
}


LPCTSTR CBaseWindowWnd::GetWindowClassName() const 
{ 
	return _T(m_className); 
}

UINT CBaseWindowWnd::GetClassStyle() const 
{ 
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; 
}

LONG CBaseWindowWnd::GetLocalStyleVaule()
{
	return m_localStyleValue;
}

LRESULT CBaseWindowWnd::SetLocalStyleValue(LONG styleValue) //
{
	m_localStyleValue = styleValue;
	return 0;
}


//ÏûÏ¢ÏìÓ¦
LRESULT CBaseWindowWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | m_localStyleValue);

	m_paintManager.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T(this->m_skinName.GetData()), (UINT)0, NULL, &m_paintManager);

	ASSERT(pRoot && "Failed to parse XML");

	m_paintManager.AttachDialog(pRoot);

	m_paintManager.AddNotifier(this);
	return 0;
}