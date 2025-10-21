 #pragma once
#define UNICODE
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windowsx.h>
#include <windows.h>
 
namespace easywingui {
	struct Button {
    HWND hButton;
    void (*onClick)();
    Button* next; // 鏈結下一個
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
class easyw{
	public:
HWND hwnd = nullptr;
volatile  bool running = false;
// --- 這兩個函式指標讓外部可以註冊 callback ---
void (*onButtonClick)() = nullptr;
void (*onInputChange)(const wchar_t*) = nullptr;
 
// 控件句柄（只記錄一個）
HWND hButton = nullptr;
HWND hEdit = nullptr;


//狀態判斷
 
// --- 結束循環 ---
 HANDLE stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
 
 void stoploop() {
 running = false;
     SetEvent(stopEvent);          // 通知 loop 停止
    PostMessage(hwnd, WM_NULL, 0, 0);  // 喚醒消息循環
}
// --- 主循環 --- 
inline void loop() {
     	running = true;
   HANDLE handles[] = { stopEvent };
       // HANDLE timerHandle = CreateWaitableTimer(NULL, FALSE, NULL);
		  MSG msg ;	
	   //SetTimer(  hwnd, 1, 16, NULL);
  while ( running) {
        DWORD result = MsgWaitForMultipleObjectsEx(
            1,handles, INFINITE, QS_ALLINPUT, MWMO_ALERTABLE
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
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0, CLASS_NAME, title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        nullptr, nullptr, GetModuleHandle(nullptr), this);
 SetTimer(hwnd, 1, 16, nullptr);
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
Button* buttonHead = nullptr;
Button* buttonTail = nullptr;
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
void (*onChange)(const wchar_t*);
Inputbox* inputboxHead = nullptr;
Inputbox* inputboxTail = nullptr;
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

// --- 改尺寸 ---
inline void resize(int width, int height) {
    stoploop();
   
    running = true;
   
    if (hwnd) {
        SetWindowPos(hwnd, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER| SWP_FRAMECHANGED);
        RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
       // loop();//導致訊息堵塞
    } 
}
//執行續
 
 
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
            for (Inputbox* dur = inputboxHead; dur; dur = dur->next) {
    if (src == dur->hEdit && HIWORD(wParam) == EN_CHANGE) {
        GetWindowText(dur->hEdit, dur->buf, 256);
        if (onInputChange) dur->onChange(dur->buf);
        return 0;
    }
}
            return 0;
        }
        case WM_TIMER:{
          loop();
			break;
		}
        case WM_SIZE:
            InvalidateRect(hwnd, nullptr, TRUE);
            return 0;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_CLOSE:{
			  DestroyWindow(hwnd); PostQuitMessage(0);          // 點右上角 X 時
        return 0;
		}
      
        case WM_DESTROY:
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
