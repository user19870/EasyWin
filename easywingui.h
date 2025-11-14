
 #pragma once
#define UNICODE
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windowsx.h>
#include <windows.h>
#include <commctrl.h>
 #ifndef _INC_STDIO
 #include <stdio.h>
 #endif
/* #ifndef __gl_h_
#ifndef __GL_H__
#include <GL/gl.h>
#pragma comment(lib, "opengl32.lib")
#define __gl_h_
#define __GL_H__
 */
namespace easywingui {
	struct Button {
    HWND hButton; 
    void (*onClick)();
    Button* next; // 鏈結下一個
    static void* operator new(size_t size) { void* ptr= malloc(size); return ptr;}
    static void operator delete(void* ptr) {free(ptr);}
};

struct Checkbox {
    HWND hButton;int ctrlId;
    void (*onClick)();
    Checkbox* next; // 鏈結下一個
    static void* operator new(size_t size) { void* ptr= malloc(size); return ptr;}
    static void operator delete(void* ptr) {free(ptr);}
};
	struct Inputbox {
		const char* id;
    HWND hEdit;wchar_t buf[256];
    void (*onChange)(const wchar_t*);
    Inputbox* next; // 鏈結下一個
    static void* operator new(size_t size) { void* ptr= malloc(size); return ptr;}
    static void operator delete(void* ptr) {free(ptr);}
};
    struct Label{
    const char* id;
    HWND hLabel;
    Label* next;wchar_t labelbuf[256];
    HBITMAP hBitmap;
     static void* operator new(size_t size) { void* ptr= malloc(size); return ptr;}
    static void operator delete(void* ptr) {free(ptr);}
    };
    
  
    class easyw{
    private:
    Button* buttonHead = nullptr;Button* btn;Inputbox* itb;
Button* buttonTail = nullptr;
Label* labelHead = nullptr;Label* labelTail = nullptr;
Label* imgHead = nullptr;Label* imgTail = nullptr;
    // --- 這兩個函式指標讓外部可以註冊 callback ---
void (*onButtonClick)() = nullptr;void (*oncheckClick)() = nullptr;
void (*onInputChange)(const wchar_t*) = nullptr;
void (*onChange)(const wchar_t*);
Inputbox* inputboxHead = nullptr;
HWND hScrollBar;
Inputbox* inputboxTail = nullptr;
Checkbox* checkHead = nullptr;Checkbox* checkTail = nullptr;
HANDLE stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
void (*runperframe)()=nullptr;
////////////////////////
	public:
HWND hwnd = nullptr;
volatile  bool running = false;

 
// --- 結束循環 ---
 
 
 void stoploop() {
  running = false;hwnd = nullptr;
   //  SetEvent(stopEvent);          // 通知 loop 停止
    PostMessage(hwnd, WM_NULL, 0, 0);  // 喚醒消息循環
 
}
// --- 主循環 --- 
MSG msg ;

inline void runMessage(void(*Runperframe)()){ 
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            	if (msg.message == WM_QUIT) {  running = false;break;}
            	runperframe=Runperframe;
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }  
}
inline void loopAndStopProcessing() {
    
    	running = true;
   HANDLE handles[] = { stopEvent };
      //  HANDLE timerHandle = CreateWaitableTimer(NULL, FALSE, NULL);
		  	
	  // SetTimer(  hwnd, 1, 16, NULL);
  while ( running) {
        DWORD result = MsgWaitForMultipleObjectsEx(
            1,handles, INFINITE, QS_ALLINPUT, MWMO_ALERTABLE| MWMO_INPUTAVAILABLE
        );

        if (result == WAIT_OBJECT_0) {
            // 處理定時器事件  
         break;
            // 這裡可以進行渲染或更新操作
        } else if (result == WAIT_OBJECT_0 + 1) {
            // 處理消息隊列中的消息
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            	if (msg.message == WM_QUIT) {  running = false;break;}
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
             
        }
    }
 
  // CloseHandle(timerHandle);
}
// --- 建立視窗 ---
inline void creatw(const wchar_t* title, int width, int height) {
    
    const wchar_t CLASS_NAME[] = L"MyWindowClass";
    WNDCLASS wc = {};
  //  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // <-- OwnDC 保證 OpenGL 有專屬 DC
    // wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);   // 自動補齊背景
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);
 
    hwnd = CreateWindowEx(
        0, CLASS_NAME, title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, GetModuleHandle(nullptr), this);
     SetTimer(hwnd, 1, 16, NULL); // 每16毫秒觸發一次WM_TIMER
    if (!hwnd) return;

    ShowWindow(hwnd, SW_SHOW);
    
  //  running = true;
}
//刪除視窗
inline void destroyw() {
  //  if (hwnd) {
        DestroyWindow(hwnd);
        hwnd = nullptr;
  //  }
}

// --- 加按鈕 ---//(L"文字",位置x,位置y,寬,高,fun)，fun為void且不是fun()
inline void button(const wchar_t* text, int x, int y, int w, int h, void (*onClick)()) {
	Button* btn=new Button;
    btn->hButton = CreateWindow(L"BUTTON", text,
        WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x, y, w, h, hwnd, nullptr, GetModuleHandle(nullptr), btn);
        
     btn->onClick = onClick;
     onButtonClick=onClick;
    btn->next = nullptr;
 
    if (!buttonHead) { buttonHead = buttonTail = btn; }
    else { buttonTail->next = btn; buttonTail = btn; }
    
}

// --- 加輸入框 ---
inline void inputbox(const char* id,int x, int y, int w, int h, void (*onChange)(const wchar_t*)) {
	Inputbox* itb=new Inputbox;
    constexpr int INPUT_ID = 1; // 控件 ID
    itb->hEdit = CreateWindow(L"EDIT", L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        x, y, w, h, hwnd, (HMENU)INPUT_ID, GetModuleHandle(nullptr), itb);
        itb->onChange=onChange;
    onInputChange = onChange;
    itb->id=id;
    itb->next=nullptr;
    if (!inputboxHead) { inputboxHead = inputboxTail = itb; }
    else { inputboxTail->next = itb; inputboxTail = itb; }
}
char chbuf[256];
wchar_t* findinputid(const char* inid){for(Inputbox* fid=inputboxHead;fid;fid=fid->next) {  if(strcmp(fid->id, inid) == 0)return fid->buf;} return nullptr;}
inline char* getinput_s (const char* inputboxid ){ WideCharToMultiByte(CP_UTF8, 0, findinputid(inputboxid), -1, chbuf, sizeof(chbuf), nullptr, nullptr);return chbuf;}
inline wchar_t* getinput_w(const char* inputboxid){return findinputid(inputboxid);}
// --- 加標籤 ---
inline void label(const char* id,const wchar_t* text,int x,int y, int w,int h,const char* left_cneter_right){
    Label* lbl=new Label;DWORD SS_style= (strcmp(left_cneter_right,"left")==0)?SS_LEFT:((strcmp(left_cneter_right,"right")==0)?SS_RIGHT:SS_CENTER);
    wcscpy(lbl->labelbuf, text); 
    lbl->hLabel = CreateWindow(L"STATIC", lbl->labelbuf,
        WS_VISIBLE | WS_CHILD | SS_style,
        x, y, w, h, hwnd, nullptr, GetModuleHandle(nullptr), lbl);     
    lbl->next = nullptr;
    lbl->id=id;
     if (!labelHead) { labelHead = labelTail = lbl; }
    else { labelTail->next = lbl; labelTail = lbl; }
}
 // --- 加複選框 ---
inline bool checkbox(const wchar_t* text, int x, int y, int w, int h,void (*onClick)()) {
 Checkbox* ckb=new Checkbox;static int ctrlId = 1000;
    ckb->hButton = CreateWindow(L"BUTTON", text,
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        x, y, w, h, hwnd, nullptr, GetModuleHandle(nullptr), ckb);
        ckb->onClick = onClick;
        oncheckClick=onClick;
    ckb->next = nullptr; 
 
    if (!checkHead) { checkHead = checkTail = ckb; }
    else { checkTail->next = ckb; checkTail = ckb; }
    return (SendMessage(ckb->hButton, BM_GETCHECK, 0, 0) == BST_CHECKED);
}

inline void staticImage(const wchar_t* bmpPath,int x,int y,int w,int h){
    Label* img=new Label;
     img->hBitmap = (HBITMAP)LoadImageW(NULL, bmpPath, IMAGE_BITMAP, w, h, LR_LOADFROMFILE);
       img->hLabel = CreateWindowW(L"STATIC", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP,
        x, y, w, h, hwnd, NULL, GetModuleHandle(nullptr), NULL);
    SendMessageW(img->hLabel, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img->hBitmap);
     img->next = nullptr;
     if (!imgHead) { imgHead = imgTail = img; }
    else { imgTail->next = img; imgTail = img; }

}
// --- 改尺寸 ---
inline void resize(int width, int height) {
    //stoploop();
   
   // running = true;
   
    if (hwnd) {
        SetWindowPos(hwnd, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER| SWP_FRAMECHANGED);
        RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
       // loop();//導致訊息堵塞
    } 
}
inline void changelabel(const char* id,const wchar_t* newtext){
    for(Label* cl=labelHead;cl;cl=cl->next){
        if(strcmp(cl->id,id)==0){
            wcscpy(cl->labelbuf,newtext);
            SetWindowText(cl->hLabel,cl->labelbuf);
            return;
        }
    }
}
//釋放資源
inline void release() {
    // 刪除按鈕鏈表
    Button* curbtn= buttonHead; while (curbtn) {Button* next=curbtn->next; DestroyWindow(curbtn->hButton); btn= curbtn;delete btn;curbtn = next;} buttonHead = buttonTail = nullptr; 
    // 刪除輸入框鏈表
    Inputbox* curItb = inputboxHead;while (curItb) {Inputbox* nextItb = curItb->next;DestroyWindow(curItb->hEdit);delete curItb; curItb = nextItb; }inputboxHead = inputboxTail = nullptr;
    Label* curlbl= labelHead; while (curlbl) {Label* nextlbl=curlbl->next; DestroyWindow(curlbl->hLabel); delete curlbl; curlbl=nextlbl;} labelHead=labelTail=nullptr;
    Checkbox* curckb= checkHead; while (curckb) {Checkbox* nextckb=curckb->next; DestroyWindow(curckb->hButton); delete curckb; curckb=nextckb;} checkHead=checkTail=nullptr;
    Label* curimg= imgHead; while (curimg) {Label* nextimg=curimg->next; DeleteObject(curimg->hBitmap); DestroyWindow(curimg->hLabel); delete curimg; curimg=nextimg;} imgHead=imgTail=nullptr;
} 
// 核心
     LRESULT CALLBACK procfeature(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_COMMAND: {
            HWND src = (HWND)lParam;//Button* cur = buttonHead;Inputbox* dur=inputboxHead;
            for (Button* cur = buttonHead; cur; cur = cur->next) {
            if (src == cur->hButton && HIWORD(wParam) == BN_CLICKED) {
            if (onButtonClick) cur->onClick();
          return 0; }
 }

 for (Checkbox* cur = checkHead; cur; cur = cur->next) {
    src = (HWND)lParam;
            if (src == cur->hButton && HIWORD(wParam) == BN_CLICKED) {
            if (oncheckClick) cur->onClick();
          return 0; }
 }

            for (Inputbox* dur = inputboxHead; dur; dur = dur->next) {
    if (src == dur->hEdit && HIWORD(wParam) == EN_CHANGE) {
        GetWindowText(dur->hEdit, dur->buf, 256);
        if (onInputChange) dur->onChange(dur->buf);
        return 0;
    }
}
            return 0;
        }
         case WM_ERASEBKGND:
 
    return 0;
        case WM_SIZE:
            InvalidateRect(hwnd, nullptr, TRUE);
            return 0;
        case WM_PAINT: {
        	
        	 //ValidateRect(hwnd, NULL);
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_TIMER:{
              if (runperframe) runperframe();
            //  InvalidateRect(hwnd, NULL, FALSE);
              return 0;
        }
        case WM_CLOSE:{
			  DestroyWindow(hwnd); release(); PostQuitMessage(0);          // 點右上角 X 時
        return 0;
		}
      
        case WM_DESTROY:
        DestroyWindow(hwnd); release();
            running = false;
            PostQuitMessage(0);
             hwnd = nullptr;
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
        return 0;
         }
     static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
        easyw* pThis = nullptr;

        if (uMsg == WM_NCCREATE) {
            // 把 this 指標放進窗口的 user data
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            pThis = (easyw*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        } else {
            // 從窗口取出 this 指標
            pThis = (easyw*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }

        if (pThis) {
            return pThis->procfeature(hwnd, uMsg, wParam, lParam);
        }

        return DefWindowProc(hwnd,uMsg, wParam, lParam);
    }
     
};
}