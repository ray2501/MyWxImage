#include "MyFrame.h"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_OPEN, MyFrame::OnOpen)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_PAINT(MyFrame::OnPaint)
wxEND_EVENT_TABLE()

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, "&Open...\tCtrl-O",
                     "Open file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Ready");
}

void MyFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("It is written by wxWidgets.",
                 "About MyWxImage", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnOpen(wxCommandEvent &event)
{
    wxFileDialog
        openFileDialog(this, _("Open Image file"), "", "",
                       "Image files (*.png;*.jpg;*.bmp)|*.png;*.jpg;*.bmp", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    filename = openFileDialog.GetPath();

    Refresh();
    SetStatusText(filename);
}

void MyFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    if (filename.Len() > 0) {        
        bool isNeedScale = false;

        wxFileName file(filename);
        wxString ext = file.GetExt();

        wxImage image;
        if(ext.IsSameAs("png")) {
            image = wxImage( filename, wxBITMAP_TYPE_PNG, -1 );
        } else if(ext.IsSameAs("jpg")) {
            image = wxImage( filename, wxBITMAP_TYPE_JPEG, -1 );
        } else if(ext.IsSameAs("bmp")) {
            image = wxImage( filename, wxBITMAP_TYPE_BMP, -1 );
        }

        int width = image.GetWidth();
        int height = image.GetHeight();
        if(width > 800) {
            width = 800;
            isNeedScale = true;
        }

        if(height > 600) {
            height = 600;
            isNeedScale = true;
        }

        if(isNeedScale) {
            image = image.Rescale(width, height);
        }

        wxBitmap bitmap = wxBitmap(image);
        dc.DrawBitmap(bitmap, 1, 1, TRUE);
    }
}
