#ifndef _WXPRPCANVAS_H
#define _WXPRPCANVAS_H

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <map>
#include <wx/glcanvas.h>
#include <PRP/Object/plSceneObject.h>
#include <PRP/Geometry/plDrawableSpans.h>

struct LayerInfo {
    LayerInfo();
    LayerInfo(size_t nameId, GLuint target);

    size_t fTexNameId;
    GLuint fTexTarget;
};

const wxChar wxPrpCanvasClassName[] = wxT("PrpCanvas");

class wxPrpCanvas : public wxGLCanvas {
public:
    // Scene Mode
    enum { MODE_MODEL, MODE_SCENE, MODE_MODEL_IN_SCENE };

    // Draw Mode
    enum {
        DRAW_POINTS, DRAW_WIRE, DRAW_FLAT, DRAW_TEXTURED,
        DRAW_MODEMASK = 0x00000003,
        DRAW_FORCE2SIDED = 0x4
    };

private:
    bool fInited;
    hsTArray<plKey> fObjects;
    std::map<plKey, LayerInfo> fLayers;
    GLuint fRenderListBase;
    GLuint* fTexList;
    
    int fMode, fDrawMode;
    float fRotZ, fRotX, fModelDist;
    hsVector3 fViewPos;
    hsVector3 fModelMins, fModelMaxs;
    plKey fCenterObj;

public:
    wxPrpCanvas(wxWindow* parent, wxWindowID id = wxID_ANY,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0, const wxString& name = wxPrpCanvasClassName);
    ~wxPrpCanvas();

    void InitGL();
    void Render();

    void AddObject(plKey obj);
    void SetView(hsVector3 view, float angle=0.0f);
    void Center(plKey obj, bool world);
    void Build(int mode);
    void ReBuild();
    void ReBuildObject(plKey obj);

protected:
    DECLARE_EVENT_TABLE()

    void OnPaint(wxPaintEvent& evt);
    void OnSize(wxSizeEvent& evt);
    void OnEraseBackground(wxEraseEvent& evt);
    void OnMouse(wxMouseEvent& evt);

    void CompileObject(plKey obj);
    void CompileTexture(plKey layer, size_t id);

private:
    wxPoint fMouseFrom;
    int fMouseBtn;
};

#endif