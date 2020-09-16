#include "main.h"
#include "MyFrame.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MyFrame *frame = new MyFrame("MyWxImage", wxPoint(10, 10), wxSize(820, 690));
    frame->Show(true);
    return true;
}
