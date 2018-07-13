#pragma once


#define CLR2ARGB( c )		0xff000000 | (c & 0x000000ff) << 16 | (c & 0x0000ff00) | (c & 0x00ff0000) >> 16
#define CLRA2ARGB( c, a )	(a | (c & 0x000000ff) << 16 | (c & 0x0000ff00) | (c & 0x00ff0000) >> 16)
#define ARGB2CLR(c)			0x00ffffff & ((c & 0x000000ff) << 16 | (c & 0x0000ff00) | (c & 0x00ff0000) >> 16)
#define	CORNER_TOP_LEFT			0x01
#define	CORNER_TOP_RIGHT		0x02
#define	CORNER_BOTTOM_LEFT		0x04
#define	CORNER_BOTTOM_RIGHT		0x08

#define	CORNERS_TOPS			(CORNER_TOP_LEFT | CORNER_TOP_RIGHT)
#define	CORNERS_BOTTOMS			(CORNER_BOTTOM_LEFT | CORNER_BOTTOM_RIGHT)
#define	CORNERS_ALL				(CORNER_TOP_LEFT | CORNER_TOP_RIGHT | CORNER_BOTTOM_LEFT | CORNER_BOTTOM_RIGHT)



//==================== Definition for Main GUI ============================
//#define WINDOW_INTERNAL_BORDER_OUTLINE_WIDTH			7
#define	COLOR_APP_PAGE_BACKGROUND					RGB(255, 255, 255)	// background of all main pages
#define COLOR_WINDOW_INTERNAL_BORDER_OUTLINE 		RGB(41, 78, 133)	// internal boarder outline light/top
//#define COLOR_WINDOW_INTERNAL_BORDER_OUTLINE_DARK	RGB(2, 53, 111)		// internal boarder outline dark/botton
#define COLOR_WINDOW_INTERNAL_BORDER_OUTLINE_DARK	RGB(1, 39, 82)		// internal boarder outline dark/botton

#define PAGE_LABEL_FONT_NAME		DRAW_FONT_NAME			// font used for page label 
#define PAGE_LABEL_FONT_SIZE		14.0				// font size by page label
#define PAGE_LABEL_FONT_COLOR		RBG(0, 0, 0);	// font color by page label

#define PAGE_DESCRIPTION_FONT_NAME		DRAW_FONT_NAME			// font used for page description 
#define PAGE_DESCRIPTION_FONT_SIZE		12.0				// font size by page description
#define PAGE_DESCRIPTION_FONT_COLOR		RBG(10, 10, 10);	// font color by page description

//==================== Definition for Main Menu Button Custom Painting ============================
#define COLOR_MAINMENU_BUTTON_NORMAL_OUTLINE			RGB(23, 51, 85)		// outline of the button
#define COLOR_MAINMENU_BUTTON_NORMAL_GRADIENT_TOP		RGB(58, 145, 224)	// top gradient color
#define COLOR_MAINMENU_BUTTON_NORMAL_GRADIENT_BOTTOM	RGB(18, 74, 175)		// bottom gradient color

#define COLOR_MAINMENU_BUTTON_HOVER_OUTLINE				RGB(23, 51, 85)		// outline of the button
#define COLOR_MAINMENU_BUTTON_HOVER_GRADIENT_TOP		RGB(58, 145, 224)	// top gradient color
#define COLOR_MAINMENU_BUTTON_HOVER_GRADIENT_BOTTOM		RGB(18, 74, 175)		// bottom gradient color

#define MAINMENU_BUTTON_FONT_NAME			DRAW_FONT_NAME			// normal font definition
#define MAINMENU_BUTTON_FONT_SIZE			11.0				
#define MAINMENU_BUTTON_FONT_COLOR			RGB(0, 0, 94)		
#define MAINMENU_BUTTON_FONT_STYLE			FontStyleRegular      

#define MAINMENU_BUTTON_SELECT_FONT_NAME	DRAW_FONT_NAME			// select font definition
#define MAINMENU_BUTTON_SELECT_FONT_SIZE	11.0				
#define MAINMENU_BUTTON_SELECT_FONT_COLOR	RGB(255, 255, 255)		
#define MAINMENU_BUTTON_SELECT_FONT_STYLE	FontStyleRegular      

#define MAINMENU_BUTTON_HOVER_FONT_NAME		DRAW_FONT_NAME			// hover-over font definition
#define MAINMENU_BUTTON_HOVER_FONT_SIZE		11.0				
#define MAINMENU_BUTTON_HOVER_FONT_COLOR	RGB(255, 255, 255)		
#define MAINMENU_BUTTON_HOVER_FONT_STYLE	FontStyleUnderline

//==================== Definition for Main Menu Windows ===============================================
#define COLOR_MAINMENU_STATUS_PANE		RGB(213, 234, 255)		// Fill color for the status pane
#define COLOR_MAINMENU_DIVIDER			RGB(132, 172, 221)		// Pane divider line color
#define HEIGHT_MAINMENU_STATUS_PANE		80						// Height of the status Pane

//====================================================Definition for FixCleanScan Progress Dlg
#define COLOR_SCANPROCESS_BACKGROUND	RGB(41,78,133)		//the background
#define COLOR_CENTER_BOX				RGB(255,255,255)    //the center box of the dlg

//=================================================Define for Ignorelist View==========================
#define COLOR_IGNORE_BK_BOTTOM		RGB(210,210,210)

//==================== Definition for Action Menu Buttons ===============================================
#define COLOR_ACTIONMENU_BUTTON_HOVER_OUTLINE				RGB(132, 172, 221)		// outline of the button
#define COLOR_ACTIONMENU_BUTTON_HOVER_GRADIENT_TOP			RGB(252, 253, 255)		// top gradient color
#define COLOR_ACTIONMENU_BUTTON_HOVER_GRADIENT_BOTTOM		RGB(237, 245, 255)		// bottom gradient color

#define ACTIONMENU_BUTTON_LABEL_FONT_NAME			DRAW_FONT_NAME			// normal ActionMenu label font definition
#define ACTIONMENU_BUTTON_LABEL_FONT_SIZE			12.0				
#define ACTIONMENU_BUTTON_LABEL_FONT_COLOR			RGB(0, 110, 18)		
#define ACTIONMENU_BUTTON_LABEL_FONT_STYLE			FontStyleRegular      

#define ACTIONMENU_BUTTON_LABEL_HOVER_FONT_NAME		DRAW_FONT_NAME			// hover-over ActionMenu label font definition
#define ACTIONMENU_BUTTON_LABEL_HOVER_FONT_SIZE		12.0				
#define ACTIONMENU_BUTTON_LABEL_HOVER_FONT_COLOR	RGB(0, 110, 18)		
#define ACTIONMENU_BUTTON_LABEL_HOVER_FONT_STYLE	FontStyleUnderline

#define ACTIONMENU_BUTTON_DESCRIPTION_FONT_NAME		DRAW_FONT_NAME			// normal ActionMenu description font definition
#define ACTIONMENU_BUTTON_DESCRIPTION_FONT_SIZE		9.0				
#define ACTIONMENU_BUTTON_DESCRIPTION_FONT_COLOR	RGB(0, 0, 0)		
#define ACTIONMENU_BUTTON_DESCRIPTION_FONT_STYLE	FontStyleRegular      


//==========================================Definition for ClickButton=====================
#define COLOR_APP_BUTTON_BACKGROUND RGB(255,255,255)	//Grey background program by zhongqing wu
#define COLOR_BUTTON_FILLED	RGB(0,0,255)				//by using it to fill the button

#define COLOR_DLG_BUTTON_TEXT_OUTLINE			RGB(60, 60, 60) // button text outline

#define DLG_BUTTON_NORMAL_FONT_NAME				DRAW_FONT_NAME			// normal dlg button font name
#define DLG_BUTTON_NORMAL_FONT_SIZE				10.0/*11.0*/				// normal dlg button font name
#define DLG_BUTTON_NORMAL_FONT_STYTLE			FontStyleRegular	// normal dlg button font name
#define DLG_BUTTON_NORMAL_FONT_COLOR			RGB(255,255,255)/*RGB(255,255,255)*/	// normal dlg button font color
#define COLOR_DLG_BUTTON_NORMAL_ENABLED			RGB(0,128,255)/*RGB(0, 126, 255)*/	//(0, 61, 138);	// normal dlg button color when enabled
#define COLOR_DLG_BUTTON_NORMAL_ENABLED_LIGHT	RGB(154, 206, 150)	//(0, 61, 138);	// normal dlg button color when enabled
#define COLOR_DLG_BUTTON_NORMAL_DISABLED		RGB(125,125,125)	// normal dlg button color when disabled
#define COLOR_DLG_BUTTON_NORMAL_UPLINE			RGB(0,153,255)
#define COLOR_DLG_BUTTON_NORMAL_DOWNLINE		RGB(0,102,204)

#define DLG_BUTTON_ACTION_FONT_NAME				DRAW_FONT_NAME			// action dlg button font name
#define DLG_BUTTON_ACTION_FONT_SIZE				17.0/*14.0*/				// action dlg button font name
#define DLG_BUTTON_ACTION_FONT_STYTLE			FontStyleRegular/*FontStyleBold*/		// action dlg button font name
#define DLG_BUTTON_ACTION_FONT_COLOR			RGB(255,255,255)	// action dlg button font color
#define COLOR_DLG_BUTTON_ACTION_ENABLED			RGB(0,147,0)/*RGB(27, 147, 23)*/	//(0, 61, 138);	// ACTION dlg button color when enabled
#define COLOR_DLG_BUTTON_ACTION_ENABLED_LIGHT	RGB(154, 206, 150)	//(0, 61, 138);	// ACTION dlg button color when enabled
#define COLOR_DLG_BUTTON_ACTION_DISABLED		RGB(125,125,125)					// ACTION dlg button color when disabled
#define COLOR_DLG_BUTTON_ACTION_UPLINE			RGB(0,176,0)
#define COLOR_DLG_BUTTON_ACTION_DOWNLINE		RGB(0,117,0)

#define DLG_BUTTON_NON_DISTRACTION_FONT_NAME			DRAW_FONT_NAME				// NON-DISTRACTION dlg button font name
#define DLG_BUTTON_NON_DISTRACTION_FONT_SIZE			10.0/*11.0*/					// NON-DISTRACTION dlg button font name
#define DLG_BUTTON_NON_DISTRACTION_FONT_STYTLE			FontStyleRegular		// NON-DISTRACTION dlg button font name
#define DLG_BUTTON_NON_DISTRACTION_FONT_COLOR			RGB(0,0,0)				// NON-DISTRACTION dlg button font color
#define COLOR_DLG_BUTTON_NON_DISTRACTION_ENABLED		RGB(220,220,220)/*RGB(180, 180, 180)*/ //(0, 61, 138);	// NON-DISTRACTION dlg button color when enabled
#define COLOR_DLG_BUTTON_NON_DISTRACTION_ENABLED_LIGHT	RGB(255, 255, 255) //(0, 61, 138);	// NON-DISTRACTION dlg button color when enabled
#define COLOR_DLG_BUTTON_NON_DISTRACTION_DISABLED		RGB(125,125,125)					// NON-DISTRACTION dlg button color when disabled
#define COLOR_DLG_BUTTON_NON_DISTRACTION_UPLINE			RGB(255,255,255)
#define COLOR_DLG_BUTTON_NON_DISTRACTION_DOWNLINE		RGB(176,176,176)

#define COLOR_DLG_BUTTON_OUTLINE				RGB(97,107,118)
//==============================================definition for CTULimitedList==========================
#define LIMITED_LIST_TOPTEXT_DESCRIPTION_FONT_NAME		DRAW_FONT_NAME
#define LIMITED_LIST_TOPTEXT_DESCRIPTION_FONT_SIZE		8.5
#define LIMITED_LIST_TOPTEXT_DESCRIPTION_FONT_COLOR		RGB(0,0,0)
#define LIMITED_LIST_TOPTEXT_DESCRIPTION_FONT_STYLE		FontStyleRegular

#define LIMITED_LIST_DOWNTEXT_DESCRIPTION_FONT_NAME		DRAW_FONT_NAME
#define LIMITED_LIST_DOWNTEXT_DESCRIPTION_FONT_SIZE		8.5
#define LIMITED_LIST_DOWNTEXT_DESCRIPTION_FONT_COLOR		RGB(129,129,157)
#define LIMITED_LIST_DOWNTEXT_DESCRIPTION_FONT_STYLE		FontStyleRegular

#define LIST_ODD_ROW_COLOR		RGB(255,255,255)
#define LIST_EVEN_ROW_COLOR		RGB(230,241,255)
#define LIST_TEXT_FRAGMENT_COLOR		RGB(255,0,0)
#define LIST_FRAGGRID_LINE_COLOR		RGB(218,240,252)
#define LIST_FRAGGRID_BG_COLOR			RGB(30,109,176)
#define LIST_FRAGGRID_TOP_COLOR			RGB(254,101,18)

//==============================================definition for CTUTree==========================
#define TUNE_TREE_PARENTTEXT_DESCRIPTION_FONT_NAME		DRAW_FONT_NAME
#define TUNE_TREE_PARENTTEXT_DESCRIPTION_FONT_SIZE		10.0
#define TUNE_TREE_PARENTTEXT_DESCRIPTION_FONT_COLOR		RGB(0,0,94)
#define TUNE_TREE_PARENTTEXT_DESCRIPTION_FONT_STYLE		FontStyleBold

#define TUNE_TREE_PARENTTEXT_SELNO_DESCRIPTION_FONT_NAME		DRAW_FONT_NAME
#define TUNE_TREE_PARENTTEXT_SELNO_DESCRIPTION_FONT_SIZE		9.0
#define TUNE_TREE_PARENTTEXT_SELNO_DESCRIPTION_FONT_COLOR		RGB(255,0,0)
#define TUNE_TREE_PARENTTEXT_SELNO_DESCRIPTION_FONT_STYLE		FontStyleBold

#define TUNE_TREE_TOPTEXT_DESCRIPTION_FONT_NAME		DRAW_FONT_NAME
#define TUNE_TREE_TOPTEXT_DESCRIPTION_FONT_SIZE		8.5
#define TUNE_TREE_TOPTEXT_DESCRIPTION_FONT_COLOR		RGB(0,0,0)
#define TUNE_TREE_TOPTEXT_DESCRIPTION_FONT_STYLE		FontStyleRegular

#define TUNE_TREE_DOWNTEXT_DESCRIPTION_FONT_NAME		DRAW_FONT_NAME
#define TUNE_TREE_DOWNTEXT_DESCRIPTION_FONT_SIZE		8.5
#define TUNE_TREE_DOWNTEXT_DESCRIPTION_FONT_COLOR		RGB(129,129,157)
#define TUNE_TREE_DOWNTEXT_DESCRIPTION_FONT_STYLE		FontStyleRegular

#define COLOR_TUNE_TREE_PARENT_SELECT_GRADIENT_TOP		RGB(176,216,255)
#define COLOR_TUNE_TREE_PARENT_SELECT_GRADIENT_DOWN		RGB(106,181,255)
#define COLOR_TUNE_TREE_PARENT_NORMAL_GRADIENT_TOP		RGB(255,255,255)
#define COLOR_TUNE_TREE_PARENT_NORMAL_GRADIENT_DOWN		RGB(221,238,255)
#define COLOR_TUNE_TREE_PARENT_OUTLINE					RGB(204,204,204)
#define TUNE_TREE_SELTEXT_DESCRIPTION_FONT_COLOR		RGB(255,255,255)
//==============================================definition for CMyStaticText==========================


//==============================================definition for defrag registry step text==========================
#define TEXT_STEP_FONT_SIZE                   10
#define TEXT_STEP_FONT_COLOR                  RGB(0,0,0)

#define  TEXT_STEP_ZERO_DESCRIPTION_FONT_NAME			DRAW_FONT_NAME			// defragment registry description font definition
#define  TEXT_STEP_ZERO_DESCRIPTIONFONT_SIZE			12.0				
#define  TEXT_STEP_ZERO_DESCRIPTIONFONT_COLOR			RGB(10, 10, 10)		
#define  TEXT_STEP_ZERO_DESCRIPTIONFONT_STYLE			FontStyleRegular



#define  TEXT_DEFG_REG_SCAN_FONT_SIZE			15.0				
#define  TEXT_DEFG_REG_SCAN_FONT_COLOR			RGB(0, 0, 0)	


//==============================================definition for  Smart window==========================
//#define  TOP_BANNER_HEIGHT                      81
#define  SMART_TOP_DDESCRIPTION_FONT_SIZE       18
#define  SMART_TOP_DDESCRIPTION_FONT_COLOR      Color(255,255,255)
#define  TOP_LABLE_SIZE			(18.0)
#define  TOP_LABLE_COLOR		RGB(255,255,255)
#define  TOP_LABLE_STYLE		FontStyleRegular
#define  TOP_DESCRIPTION_SIZE	(11.0)
#define  TOP_DESCRIPTION_COLOR	RGB(255,255,255)
#define  TOP_DESCRIPTION_STYLE	FontStyleRegular
//==================== Definition for Smart Buttons ===============================================
#define COLOR_SMART_BUTTON_HOVER_OUTLINE				RGB(132, 172, 221)		// outline of the button
#define COLOR_SMART_BUTTON_HOVER_GRADIENT_TOP			RGB(255, 255, 255)		// top gradient color
#define COLOR_SMART_BUTTON_HOVER_GRADIENT_BOTTOM		RGB(225, 240, 255)		// bottom gradient color

#define SMART_BUTTON_LABEL_FONT_NAME_PROCESS			DRAW_FONT_NAME			// normal ActionMenu label font definition
#define SMART_BUTTON_LABEL_FONT_SIZE_PROCESS			10.0				
#define SMART_BUTTON_LABEL_FONT_COLOR_PROCESS			RGB(21,28,85)		
#define SMART_BUTTON_LABEL_FONT_STYLE_PROCESS			FontStyleBold      

#define SMART_BUTTON_DESCRIPTION_FONT_NAME_PROCESS		                DRAW_FONT_NAME			// normal ActionMenu description font definition
#define SMART_BUTTON_DESCRIPTION_FONT_SIZE_PROCESS		                9.0				
#define SMART_BUTTON_DESCRIPTION_FONT_COLOR_PROCESS_NO_ERROR		    RGB(0, 85, 0)	
#define SMART_BUTTON_DESCRIPTION_FONT_COLOR_PROCESS_WITH_ERROR	        RGB(255, 0, 0)
#define SMART_BUTTON_DESCRIPTION_FONT_COLOR_PROCESS_SCANNING	        RGB(0, 0, 0)	
#define SMART_BUTTON_DESCRIPTION_FONT_COLOR_PROCESS_WAIT	            RGB(0, 0, 0)	
#define SMART_BUTTON_DESCRIPTION_FONT_STYLE_PROCESS	                    FontStyleRegular      

#define SMART_BUTTON_LABEL_FONT_NAME_REPORT			    DRAW_FONT_NAME			// normal ActionMenu label font definition
#define SMART_BUTTON_LABEL_FONT_SIZE_REPORT			    10.0				
#define SMART_BUTTON_LABEL_FONT_COLOR_REPORT			RGB(21,28,85)		
#define SMART_BUTTON_LABEL_FONT_STYLE_REPORT			FontStyleRegular      

#define SMART_BUTTON_DESCRIPTION_FONT_NAME_REPORT		            DRAW_FONT_NAME			// normal ActionMenu description font definition
#define SMART_BUTTON_DESCRIPTION_FONT_SIZE_REPORT		            9.0	
#define SMART_BUTTON_DESCRIPTION_FONT_COLOR_REPORT_NO_ERROR	        RGB(0, 85, 0)
#define SMART_BUTTON_DESCRIPTION_FONT_COLOR_REPORT_WITH_ERROR	    RGB(255, 0, 0)
#define SMART_BUTTON_DESCRIPTION_FONT_STYLE_REPORT_WITH_ERROR       FontStyleUnderline  
#define SMART_BUTTON_DESCRIPTION_FONT_STYLE_REPORT_NO_ERROR         FontStyleRegular

//==================== Definition for Smart Bottom Rect ===============================================
#define COLOR_SMART_BOTTOM_RECT_GRADIENT_TOP			RGB(225, 240, 255)		// top gradient color
#define COLOR_SMART_BOTTOM_RECT_GRADIENT_BOTTOM		    RGB(255, 255, 255)		// bottom gradient color

//==================== Definition for Smart Title Buttons ===============================================
#define COLOR_SMART_TITLE_BTN_OUTLINE_WITH_ERROR	                RGB(255, 140, 160)		// outline of the button
#define COLOR_SMART_TITLE_BTN_OUTLINE_NO_ERROR	                    RGB(0, 147, 0)	

#define COLOR_SMART_TITLE_BTN_GRADIENT_TOP		            RGB(255, 255, 255)		// top gradient color
#define COLOR_SMART_TITLE_BTN_WITH_ERROR_GRADIENT_BOTTOM	RGB(255, 192, 203)		// bottom gradient color
#define COLOR_SMART_TITLE_BTN_NO_ERROR_GRADIENT_BOTTOM  	RGB(204, 255, 204)

#define PURCHASE_RESULT_TITLE_BTN_LABEL_FONT_NAME			DRAW_FONT_NAME
#define PURCHASE_RESULT_TITLE_BTN_LABEL_FONT_SIZE			14.0
#define PURCHASE_RESULT_TITLE_BTN_LABEL_FONT_COLOR			RGB(0,0,94)
#define PURCHASE_RESULT_TITLE_BTN_LABEL_FONT_STYLE			FontStyleBold
#define COLOR_PURCHASE_RESULT_TITLE_GRADIENT_TOP			RGB(255,255,255)
#define COLOR_PURCHASE_RESULT_TITLE_GRADIENT_BOTTOM			RGB(153,204,255)
#define COLOR_PURCHASE_RESULT_TITLE_OUTLINE					RGB(153,204,255)

#define SMART_TITLE_BTN_LABEL_FONT_NAME			            DRAW_FONT_NAME			// label font definition
#define SMART_TITLE_BTN_LABEL_FONT_SIZE		                14.0				
#define SMART_TITLE_BTN_LABEL_FONT_COLOR_WITH_ERROR			RGB(139,0,0)
#define SMART_TITLE_BTN_LABEL_FONT_STYLE_WITH_ERROR			FontStyleBold      

#define SMART_TITLE_BTN_LABEL_FONT_NAME_NO_ERROR			DRAW_FONT_NAME			
#define SMART_TITLE_BTN_LABEL_FONT_SIZE_NO_ERROR			14.0				
#define SMART_TITLE_BTN_LABEL_FONT_COLOR_NO_ERROR			RGB(0,0,94)		
#define SMART_TITLE_BTN_LABEL_FONT_STYLE_NO_ERROR			FontStyleBold     

#define SMART_TITLE_BTN_DESCRIPTION_FONT_NAME		                        DRAW_FONT_NAME			
#define SMART_TITLE_BTN_DESCRIPTION_FONT_SIZE_NO_ERROR		                9.0				
#define SMART_TITLE_BTN_DESCRIPTION_FONT_COLOR_NO_ERROR		                RGB(0, 85, 0)		
#define SMART_TITLE_BTN_DESCRIPTION_FONT_STYLE_NO_ERROR	                    FontStyleRegular 


#define SMART_TITLE_BTN_DESCRIPTION_FONT_SIZE_WITH_ERROR		            9.0				
#define SMART_TITLE_BTN_DESCRIPTION_FONT_COLOR_WITH_ERROR		            RGB(0, 0, 0)		
#define SMART_TITLE_BTN_DESCRIPTION_FONT_STYLE_WITH_ERROR	                FontStyleRegular 

#define COLOR_MAINMENU_BACKGROUND_LEFT			RGB(204,230,255)
#define COLOR_MAINMENU_BACKGROUND_RIGHT			RGB(255,255,255)
#define COLOR_LIST_TITLE_FOR_ALL				RGB(0,0,94)
#define COLOR_LIST_SELECTED_BACKGROUND			RGB(106,181,255)
//#define SMART_BUTTON_LABEL_FONT_NAME_REPORT 		    DRAW_FONT_NAME			
//#define SMART_BUTTON_LABEL_FONT_SIZE_REPORT			    10.0				
//#define SMART_BUTTON_LABEL_FONT_COLOR_REPORT			RGB(21,28,85)		
//#define SMART_BUTTON_LABEL_FONT_STYLE_REPORT			FontStyleRegular      
//
//#define SMART_BUTTON_DESCRIPTION_FONT_NAME_REPORT		            DRAW_FONT_NAME			
//#define SMART_BUTTON_DESCRIPTION_FONT_SIZE_REPORT		            9.0	
//#define SMART_BUTTON_DESCRIPTION_FONT_COLOR_REPORT_NO_ERROR	        RGB(0, 85, 0)
//#define SMART_BUTTON_DESCRIPTION_FONT_COLOR_REPORT_WITH_ERROR	    RGB(255, 0, 0)
//#define SMART_BUTTON_DESCRIPTION_FONT_STYLE_REPORT_WITH_ERROR       FontStyleUnderline  
//#define SMART_BUTTON_DESCRIPTION_FONT_STYLE_REPORT_NO_ERROR         FontStyleRegular




class CFontInfo
{
public:
	CString			strFontName;
	REAL			fFontSize;
	INT				nFontStyle;
	COLORREF		nFontCor;
	StringAlignment saH;
	StringAlignment	saV;
	BOOL bDontChangeAlias;
	CFontInfo()
	{
		strFontName = _T("Arial");
		fFontSize = 9.0;
		nFontStyle = FontStyleRegular;
		nFontCor = RGB(0, 0, 0);
		saH = StringAlignmentNear;
		saV = StringAlignmentCenter;
		bDontChangeAlias = FALSE;
	};
};

DLLEXPORT Image* LoadImageInAppPath(CString lpszImageFile);
DLLEXPORT Image* LoadImageInResource(UINT unResID);
DLLEXPORT Font* CreateDefaultFont(int iFontSize = -1, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bUnderline = FALSE);
DLLEXPORT void DrawText(Graphics* g, ::CRect rect, LPCTSTR lpszText, LPCTSTR lpszFontName, REAL fFontSize, int iFontStyle, COLORREF cr, StringAlignment saH, StringAlignment saV, BOOL bDontChangeAlias = FALSE, BOOL bIsDrawOutline = FALSE, StringTrimming stringTrim = StringTrimmingEllipsisCharacter);
DLLEXPORT void DrawText(Graphics* g, ::CRect rect, LPCTSTR lpszText, CFontInfo fontInfo, StringTrimming stringTrim = StringTrimmingEllipsisCharacter);
DLLEXPORT void DrawText(Graphics* g, ::CRect rect, UINT uTextId, LPCTSTR lpszFontName, REAL fFontSize, int iFontStyle, COLORREF cr, StringAlignment saH, StringAlignment saV, BOOL bDontChangeAlias = FALSE, BOOL bIsDrawOutline = FALSE, StringTrimming stringTrim = StringTrimmingEllipsisCharacter);
DLLEXPORT void DrawText(Graphics* g, ::CRect rect, UINT uTextId, CFontInfo fontInfo, StringTrimming stringTrim = StringTrimmingEllipsisCharacter);
DLLEXPORT void DrawImageAlpha(Graphics* g, Image* pImg, ::CRect rect, float fAlpha);
DLLEXPORT void FillSolidRect(Graphics* g, ::CRect rect, REAL radius, COLORREF cr, DWORD fCorners);
DLLEXPORT void FillSolidRect(Graphics* g, ::CRect rect, REAL radius, Color cr, DWORD fCorners);
DLLEXPORT void FillSolidRect(Graphics* g, RectF* rectF, REAL radius, const Brush* pBrush, DWORD fCorners);
DLLEXPORT void FillSolidRect(Graphics* g, ::CRect	rect, REAL radius, const Brush* pBrush, DWORD fCorners);
DLLEXPORT void _CreateRectPath(GraphicsPath *gp, ::CRect rect, REAL radius, DWORD dwCorners);
