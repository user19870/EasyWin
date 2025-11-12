#include <easywingui.h>
using namespace easywingui;easyw c;
bool checked=0;
void check(){
   c.changelabel("1", (!checked)? L"1":L"0"); checked=!checked;
}
int main(){
    c.creatw(L"checkbox",400,300);c.label("1",L"0",200,100,100,30,"center");
    checked=c.checkbox(L"checkbox",200,200,100,30,check);
c.loopAndStopProcessing();
     
}
