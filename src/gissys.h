#ifndef GISSYS_H
#define GISSYS_H

#include "sysdefs.h"
#include "glutsys.h"
#include "textures.h"
#include "fbo.h"
#include "globj.h"
#include "batchcfg.h"

class GradientPicker;
class GeoAerial;
class GeoLayer;

class GisSys : protected GlutSys
{
    /*
public:
    struct Config
    {
        std::string mode; // windowless, desktop

        // output
        bool mapToDisk;
        int mapw;
        int maph;
        std::string mapfile;

        std::string outtype;
        std::string datafile;


        Config()
        {
            mode = "desktop";
            mapToDisk = true;
            mapw = 1024;
            maph = 1024;
            mapfile = "map.png";
            outtype = "";
            datafile = "data.txt";
        }

        bool windowless()
        {
            if (mode == "windowless") return true;
            return false;
        }
    };
    typedef shared_ptr<Config> PConfig;
*/
public:
	GisSys();

    virtual bool init(QCoreApplication *app, int argc, const char** argv, int winWidth, int winHeight, PFilePaths pPaths);
    virtual void run(QCoreApplication *app);

    bool setConfig(PConfig cfg);
    Config* getConfig();

    void setBatchCfg(PBatchCfg cfg) { _batchCfg = cfg; }

    void saveFrameToDisk(const std::string &path);

    void zoomExtents();

    void insertBack(PGlObj obj);
    void insertFront(PGlObj obj);
    void insert(GlObjList *list);
    void clearObjs();
    void initObjs();

    box3d computeBox();

    virtual DrawData* dd() { return m_dd.get(); }

    static PGlObj loadTiff(const char *file, GradientPicker *picker);
    static PGlObj loadGeoJson(const char *file, const char *lyrname, const char *objname="");
    static PGlObj loadGeoJson(const char *file, int lyrnum, const char *objname="");

    PGlObj loadDem(const char *file);
    PGlObj loadChan(const char *file);
    PGlObj loadAerial(const Extents &ext);
    bool loadAerial(GeoAerial *pa, const Extents &ext);

protected:
    virtual void onPreDisplay();
    virtual void displayData();
    virtual void setCamera();

    virtual void destroy();
    virtual void onKeyboard(unsigned char key, int x, int y);

    bool initFbo();

    void displayStandard();
    void displayLyrOutMode();
    void displayLyrOut(GeoLayer *lyr, int lyrnum);


protected:
    PBatchCfg _batchCfg;
    PGlObj _rootNode;
    PFbo _fbo;
    bool _fboToDisk;

    //PConfig _cfg;
};

#endif
